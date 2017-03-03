//hw2, Allan
#include <iostream>
#include <vector>
#include <queue>
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
    //int *neighbor = new int[n];
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
    //delete[] neighbor;
}

void bfs(int vertex) {
    queue<int> Q;
    Q.push(vertex);
    visited[vertex] = 1;  // mark the current vertex as visited;
    
    while(!Q.empty()) {
        int t = Q.front();
        Q.pop();
        cout << t << " ";

        // find the neighbors
        int *neighbor = new int[n];
        int i;
        int j = 0;
        for(i=0; i<n; i++) {
            //if there is edge between the two vertices and the vertex has not been visited
            if((adj_matrix[t][i] == 1) && (visited[i] == 0))
                neighbor[j++] = i;  //store the neighbor index
        }

        for(i=0; i<j; i++) {
            if(visited[neighbor[i]] == 0) {
                visited[neighbor[i]] = 1;
                Q.push(neighbor[i]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "error arguments" << endl;
        return 0;
    }
    readGraph(argv[1]);

    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            //bfs(i);
            dfs(i);
            cout << endl;
        }
    }
    return 0;
}

/*
time ./cdfs arenas-jazz.txt 0.005s
time ./cbfs arenas-jazz.txt 0.004s
time ./cdfs Random-1000.01.txt 0.022s
time ./cbfs Random-1000.01.txt  0.017s
time ./cdfs Random-1000.8.txt  0.146s
time ./cbfs Random-1000.8.txt  0.116s
time ./cdfs Random-500.5.txt   0.030s
time ./cbfs Random-500.5.txt  0.023s
time ./cdfs socfb-Caltech36.txt 0.019s
time ./cbfs socfb-Caltech36.txt 0.016s
time ./cdfs foodweb-baydry.txt  0.005s
time ./cbfs foodweb-baydry.txt  0.003s
time ./cdfs Random-1000.1.txt  0.034s
time ./cbfs Random-1000.1.txt  0.030s
time ./cdfs Random-500.01.txt  0.009s
time ./cbfs Random-500.01.txt  0.006s
time ./cdfs Random-500.8.txt  0.042s
time ./cbfs Random-500.8.txt 0.031s
time ./cdfs socfb-Reed98.txt 0.023s
time ./cbfs socfb-Reed98.txt 0.023s
time ./cdfs inf-USAir97.txt 0.006s
time ./cbfs inf-USAir97.txt   0.005s
time ./cdfs Random-1000.5.txt 0.096s
time ./cbfs Random-1000.5.txt 0.094s
time ./cdfs Random-500.1.txt 0.012s
time ./cbfs Random-500.1.txt 0.012s
time ./cdfs scc_fb-forum.txt  0.032s
time ./cbfs scc_fb-forum.txt  0.024s
time ./cdfs sociopatterns-infectious.txt 0.007s
time ./cbfs sociopatterns-infectious.txt 0.006s*/