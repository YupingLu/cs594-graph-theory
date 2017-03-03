// hw7. this program is to compute the prufer sequence of a tree
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

// read input graph into adjacency matrix, the graph is tab seperated.
vector<vector<bool> > readGraph(char* file) {
    int n;                                  // NO. of vertices
    int e;                                  // NO. of edges
    vector<vector <bool> > graph;            // graph matrix
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
        graph[i].resize(n, false);
    }
    for(i = 0; i < e; i++) { 
        fscanf(fp, "%d\t%d", &row, &col);
        graph[row-1][col-1] = true;
        graph[col-1][row-1] = true;
    }

    fclose(fp);
    return graph;
}

// This dfs function to is check if the graph has cycles.
bool isCycle(vector<vector<bool> > &graph, int vertex, int parent, vector<bool> &visited) {
    int n = graph.size();
    vector<int> neighbor;
    // mark the current vertex as visited
    visited[vertex] = true;
    // find the neighbors
    for(int i=0; i<n; i++) {
        //if there is edge between the two vertices
        if(graph[vertex][i] && i != parent) {
            if(visited[i])
                return true;
            else
                neighbor.push_back(i);  //store the neighbor index
        }
    }
    // recursive call dfs on its neighbors
    for(int i = 0; i < neighbor.size(); i++) {
        if(isCycle(graph, neighbor[i], vertex, visited))
            return true;
    }
    return false;
}

// check if a graph is tree
bool isTree(vector<vector<bool> > &graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    // check if the graph has cycle
    if(isCycle(graph, 0, -1, visited))
        return false;
    // check if the graph is connected
    for(int i = 0; i < n; i++) {
        if(!visited[i])
            return false;
    }
    return true;
}

// find the leaf with the smallest index. The leaves are vertices with degree 1
int getSmallestLeaf(vector<vector<bool> > &graph) {
    int n = graph.size();
    int leaf = n;
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if(graph[i][j]) cnt++;
        }
        if(cnt == 1 && i < leaf)
            leaf = i;
    }
    return leaf;
}

// convert tree into prufer code
vector<int> treeToPrufer(vector<vector<bool> > &graph) {
    int n = graph.size();
    vector<int> prufercode;
    for(int i = 0; i < n-2; i++) {
        // find the leaf with the smallest index
        int leaf = getSmallestLeaf(graph);
        // put the leaf's neighbor into prufercode and delete the edge
        for(int i = 0; i < n; i++) {
            if(graph[leaf][i]) {
                prufercode.push_back(i+1);
                graph[leaf][i] = false;
                graph[i][leaf] = false;
                break;
            }
        }
    }
    return prufercode;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "error arguments" << endl;
        return 0;
    }
    // read the graph
    vector<vector<bool> > graph = readGraph(argv[1]);
    // check if the graph is a tree
    if(!isTree(graph)) {
        cout << "not a tree" << endl;
        return 0;
    }
    // convert tree into prufer code
    vector<int> prufercode = treeToPrufer(graph);
    for(int i = 0; i < prufercode.size(); i++) {
        cout << prufercode[i] << " ";
    }
    cout << endl;
    return 0;
}

