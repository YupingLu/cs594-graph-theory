// hw5, a algorithm to find cut vertices and bridges 
// Acknowledge : implementation is based on algorithms from this website: 
// http://www.slideshare.net/TraianRebedea/algorithm-design-and-complexity-course-8
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>

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

// helper function for dfs
void dfs_visit(int u, vector<vector <int> > &graph, set<int> &cutvertices, set<pair<int, int> > &bridges, 
               vector<bool> &visited, vector<int> &low, vector<int> &d, vector<int> &p, int &time) {
    int n = graph.size();
    int children = 0;
    visited[u] = true;
    d[u] = low[u] = ++time;
    // check all neighbours of vertex u
    for(int v = 0; v < n; v++) {
        if(v != u && graph[v][u]) {
            if(!visited[v]) {
                children++;
                p[v] = u;
                dfs_visit(v, graph, cutvertices, bridges, visited, low, d, p, time);
                low[u] = min(low[u], low[v]);
                // (1) u is root of DFS tree and has two or more chilren.
                if (p[u] == -1 && children > 1)
                   cutvertices.insert(u);
                // (2) If u is not root and low value of one of its child is more
                // than discovery value of u.
                if (p[u] != -1 && low[v] >= d[u])
                   cutvertices.insert(u);
                // check if the edge is bridge
                if (low[v] > d[u])
                    bridges.insert(make_pair(u, v));
            } else if(v != p[u]) {
                low[u] = min(low[u], d[v]);
            }
        }
    }
}

void dfs(vector<vector <int> > &graph, set<int> &cutvertices, set<pair<int, int> > &bridges) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> low(n);     // low value
    vector<int> d(n);       // discover time
    vector<int> p(n, -1);       // parent

    // call the recursive function dfs_visit
    for(int i = 0; i < n; i++) {
        int time = 0;
        if(!visited[i]) {
            dfs_visit(i, graph, cutvertices, bridges, visited, low, d, p, time);
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "error arguments" << endl;
        return 0;
    }
    set<int> cutvertices;
    set<pair<int, int> > bridges;
    vector<vector<int> > graph = readGraph(argv[1]);
    // call Tarjan's algorithm
    dfs(graph, cutvertices, bridges);
    // print cut vertices
    cout << "Cut vertices: ";
    for(set<int>::iterator it = cutvertices.begin(); it != cutvertices.end(); it++) {
        cout << *it << " "; 
    }
    cout << endl;
    // print bridges
    cout << "Bridges: ";
    for(set<pair<int, int> >::iterator it = bridges.begin(); it != bridges.end(); it++) {
        cout << "(" << it->first << "," << it->second << ") "; 
    }
    cout << endl;

    return 0;
}

