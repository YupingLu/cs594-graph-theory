// hw6. this program is to compute the global clustering coefficient and local clustering coefficient
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

// calculate the local clustering coefficient
double getLocal(vector<vector<int> > &graph, int v) {
    int n = graph.size();
    if(v < 0 || v >= n) return -1;
    double degree = 0, edges = 0;
    vector<int> res;
    // compute the degree of vertex v
    for(int i = 0; i < n; i++) {
        if(i != v && graph[i][v]) {
            degree++;
            res.push_back(i);
        }
    }
    // If vertex degree is 0 or 1, then it's NaN
    if(degree < 2) return -2;
    // compute the number of edges between neighbors of v
    for(int i = 0; i < res.size() - 1; i++) 
        for(int j = i+1; j < res.size(); j++) {
            if(graph[res[i]][res[j]]) edges++;
        }

    return (2 * edges) / ((degree - 1) * degree);
}

// calculate the global clustering coefficient
double getGlobal(vector<vector<int> > &graph) {
    double open = 0, closed = 0; 
    int n = graph.size();
    
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n-1; j++) 
            for(int k = j+1; k < n; k++) {
                if(i != k && i != j) {
                    if(graph[i][j] && graph[i][k]) {
                        open += 1;                     // open p3
                        if(graph[j][k]) closed += 1;   // closed p3
                    }
                }
            }
    if(open == 0) return -2;
    else return closed / open;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "error arguments" << endl;
        return 0;
    }

    vector<vector<int> > graph = readGraph(argv[1]);
    
    double lc = getLocal(graph, atoi(argv[2]));
    if(lc == -1) cout << "Local: Wrong vertex index" << endl;
    else if(lc == -2) cout << "Local: NaN" << endl;
    else cout << "Local: " << setprecision(10) << lc << endl;

    double cc = getGlobal(graph);
    if(cc == -2) cout << "Global: NaN" << endl;
    else cout << "Global: " << setprecision(10) << cc << endl;

    return 0;
}

