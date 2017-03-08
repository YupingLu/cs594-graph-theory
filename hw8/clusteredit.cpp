// hw8. find a cluster editing solution of size k or less
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>

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

// calculate the global clustering coefficient
vector<int> findP3(vector<vector<int> > &graph) {
    int n = graph.size();
    vector<int> res;
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n-1; j++) 
            for(int k = j+1; k < n; k++) {
                if(i != k && i != j) {
                    // open p3
                    if(graph[i][j] && graph[i][k] && !graph[j][k]) {
                        res.push_back(j);
                        res.push_back(i);
                        res.push_back(k);
                        return res;
                    }
                }
            }
    return res;
}

int clusterEdit(vector<vector<int> > &graph, int k, vector<string> &res) {
    if(k >= 0) {
        // find open p3 in graph
        vector<int> p3 = findP3(graph);
        if(p3.empty()) return 1;
        else {
            int u = p3[0], v = p3[1], w = p3[2];
            // G’ = G\(u,v) , add (u, v) to list;   ClusterEdit(G’, k-1)
            graph[u][v] = 0;
            graph[v][u] = 0;
            res.push_back("delete (" + to_string(u) + "," + to_string(v) + ")");
            if(clusterEdit(graph, k-1, res) == 1) return 1;
            // restore the graph
            graph[u][v] = 1;
            graph[v][u] = 1;
            res.pop_back();

            // G’ = G\(v, w), add (v, w) to list;  ClusterEdit(G’, k-1)
            graph[v][w] = 0;
            graph[w][v] = 0;
            res.push_back("delete (" + to_string(v) + "," + to_string(w) + ")");
            if(clusterEdit(graph, k-1, res) == 1) return 1;
            // restore the graph
            graph[v][w] = 1;
            graph[w][v] = 1;
            res.pop_back();

            // G’ = G+(u, w), add (u, w) to list;  ClusterEdit(G’, k-1)
            graph[u][w] = 1;
            graph[w][u] = 1;
            res.push_back("insert (" + to_string(u) + "," + to_string(w) + ")");
            if(clusterEdit(graph, k-1, res) == 1) return 1;
            // restore the graph
            graph[u][w] = 0;
            graph[w][u] = 0;
            res.pop_back();
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "error arguments" << endl;
        return 0;
    }
    vector<vector<int> > graph = readGraph(argv[1]);
    vector<string> res;

    clusterEdit(graph, atoi(argv[2]), res);
    if(res.empty()) {
        cout << "no solution" << endl;
        return 0;
    }
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }

    return 0;
}