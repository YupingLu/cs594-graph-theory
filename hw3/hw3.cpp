//hw3, Dijkstra’s algorithm implementation
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cfloat>
#include <stack>

using namespace std;

int n;                                  //NO. of vertices
int e;                                  //NO. of edges
vector<vector <float> > adj_matrix;    // graph matrix

//read input graph into adjacency matrix, the graph is tab seperated.
void readGraph(char* graph) {
    int i, row, col;
    float weight;
    FILE *fp;

    if ((fp=fopen(graph,"r"))==NULL) {
        printf ("Error opening input file %s\n",graph);
        exit(1);
    }
    //read the number of vertices and edges
    rewind(fp);
    fscanf(fp,"%d\t%d",&n,&e);

    adj_matrix.resize(n);
    for(i = 0; i < n; i++) {
        adj_matrix[i].resize(n, 0);
    }
    for(i = 0; i < e; i++) { 
        fscanf(fp, "%d\t%d\t%f", &row, &col, &weight);
        adj_matrix[row][col] = weight;
        adj_matrix[col][row] = weight;
    }

    fclose(fp);
}

int minDist(vector<float> &dist, vector<bool> &visited) {
    // Initialize min value
    float min = FLT_MAX;
    int min_index = 0;
  
    for(int i = 0; i < n; i++)
        if(visited[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
  
    return min_index;
}

// Implementation is based on the pseudocode from wikipedia
void dijkstra(int source, int target) {           
    vector<int> pre(n, -1);                    //preious node in optimal path from source
    vector<float> dist(n, FLT_MAX);            //the distance value for each vetex
    vector<bool> visited(n, false);            // 0 is unvisited, 1 is visited. Default is 0
	dist[source] = 0; 		                   // set source to 0

	for(int i = 0; i < n; i++) {
        int u = minDist(dist, visited);
        if(u == target) break;
        visited[u] = true;
        for(int v = 0; v < n; v++) {
            if (!visited[v] && adj_matrix[u][v] != 0 
                && dist[u] != FLT_MAX && dist[u] + adj_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adj_matrix[u][v];
                pre[v] = u;
            }
        }
    }
    // Print the shortest path and path weight
    if(dist[target] == FLT_MAX) {
        cout << "There's no path between source and target" << endl;
    }else {
        stack<int> s;
        int t = target;
        while(pre[t] != -1) {
            s.push(t);
            t = pre[t];
        }
        s.push(t);
        while(!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
        cout << dist[target] << endl;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout << "error arguments" << endl;
        return 0;
    }
    readGraph(argv[1]);
    // check if source index is correct
    if(atoi(argv[2]) < 0 || atoi(argv[2]) >= n) {
        cout << "wrong source index" << endl;
        return 0;
    }
    // check if target index is correct
    if(atoi(argv[3]) < 0 || atoi(argv[3]) >= n) {
        cout << "wrong target index" << endl;
        return 0;
    }
	dijkstra(atoi(argv[2]), atoi(argv[3]));
	return 0;
}


