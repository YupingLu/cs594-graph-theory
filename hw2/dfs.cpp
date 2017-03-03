//hw2, Allan
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges

vector<vector <int> > adj_matrix;
vector<bool> visited;

//read input graph into adjacency matrix, the graph is tab seperated.
void readGraph(char* graph) {
    int i, row, col;
    FILE *fp;

    if ((fp=fopen(graph,"r"))==NULL) {
        printf ("Error opening input file %s\n",graph);
        exit(1);
    }
    //read the number of vertices and edges
    rewind(fp);
    fscanf(fp,"%d\t%d",&n,&e);
    //store all the vertices, 0 is unvisited, 1 is visited. Default is 0
    adj_matrix.resize(n);
    for(i=0; i<n; i++) {
        visited.push_back(0);
        adj_matrix[i].resize(n, 0);
    }
    for(i=0; i<e; i++) { 
        fscanf(fp, "%d\t%d", &row, &col);
        adj_matrix[row][col]=1;
        adj_matrix[col][row]=1;
    }

    fclose(fp);
}

void dfs(int vertex) {
    // mark the current vertex as visited
    cout << vertex << " ";
    visited[vertex] = 1;
    // find the neighbors
    vector<int> neighbor(n);
    int i;
    int j = 0;
    for(i=0; i<n; i++) {
        //if there is edge between the two vertices and the vertex has not been visited
        if((adj_matrix[vertex][i] == 1) && (visited[i] == 0))
            neighbor[j++] = i;  //store the neighbor index
    }
    for(i=0; i<j; i++) {
        if(visited[neighbor[i]] == 0) {
            dfs(neighbor[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "error arguments" << endl;
        return 0;
    }
    readGraph(argv[1]);

    if(atoi(argv[2]) < 0 || atoi(argv[2]) >= n) {
        cout << "error arguments" << endl;
        return 0;
    }

    dfs(atoi(argv[2]));
    cout << endl;
    return 0;
}