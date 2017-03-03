// hw6. this program is compute the Jaccard similarity between two vertices.
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

using namespace std;

// read input graph into adjacency matrix, the graph is tab seperated.
vector<vector<int> > readGraph(char* file) {
    int n;                                  // NO. of vertices
    int e;                                  // NO. of edges
    vector<vector <int> > graph;            // graph matrix
    int i, row, col;
    FILE *fp;

    if ((fp=fopen(file,"r"))==NULL) {
        printf ("Error opening input file %s\n",file);
        exit(1);
    }
    // read the number of vertices and edges
    rewind(fp);
    fscanf(fp,"%d\t%d",&n,&e);

    graph.resize(n);
    for(i = 0; i < n; i++) {
        graph[i].resize(n, 0);
    }
    for(i = 0; i < e; i++) { 
        fscanf(fp, "%d\t%d", &row, &col);
        graph[row][col] = 1;
        graph[col][row] = 1;
    }

    fclose(fp);
    return graph;
}

double getJaccard(vector<vector<int> > &graph, int u, int v) {
    int n = graph.size();
    //check if u and v are correct input
    if(u < 0 || u >= n) return -1;
    if(v < 0 || v >= n) return -1;
    double neighbors_u = 0, neighbors_v = 0, common = 0;
    for(int i = 0; i < n; i++) {
        bool a = false, b = false;
        if(i != u && graph[i][u]) {
            neighbors_u++;
            a = true;
        }
        if(i != v && graph[i][v]) {
            neighbors_v++;
            b = true;
        }
        if(a && b) common++;
    }

    // If union is 0, then it's NaN
    if(neighbors_u + neighbors_v - common == 0) return -2;
    return common / (neighbors_u + neighbors_v - common);
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout << "error arguments" << endl;
        return 0;
    }

    vector<vector<int> > graph = readGraph(argv[1]);
    
    double jaccard = getJaccard(graph, atoi(argv[2]), atoi(argv[3]));
    if(jaccard == -1) cout << "Wrong vertex index" << endl;
    else if(jaccard == -2) cout << "NaN" << endl;
    else cout << setprecision(10) << jaccard << endl;

    return 0;
}

