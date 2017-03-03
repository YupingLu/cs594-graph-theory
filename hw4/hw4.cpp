//hw4, a greedy coloring algorithm implementation with three schemes
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

//read input graph into adjacency matrix, the graph is tab seperated.
vector<vector<int> > readGraph(char* file) {
    int n;                                  // NO. of vertices
    int e;                                  // NO. of edges
    vector<vector <int> > graph;     // graph matrix
    int i, row, col;
    FILE *fp;

    if ((fp=fopen(file,"r"))==NULL) {
        printf ("Error opening input file %s\n",file);
        exit(1);
    }
    //read the number of vertices and edges
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

// get graph degree
vector<int> graphDeg(vector<vector<int> > &graph) {
    int n = graph.size();
    vector<int> deg(n, 0);
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(graph[i][j]) {
                deg[i]++;
                deg[j]++;
            }
        }
    }
    return deg;
}

// ascending order
bool inc(const pair<int,int> &a, const pair<int,int> &b)
{
    return a.second < b.second;
}
// descending order
bool desc(const pair<int,int> &a, const pair<int,int> &b)
{
    return a.second > b.second;
}

// color graph
int color(vector<vector<int> > &graph, vector<int> order) {
    int cnt = 0;     // color counter
    int n = order.size();
    vector<int> colors(n, -1);
    for(int i = 0; i < n; i++) {
        int idx = order[i];
        set<int> tmpcolors;
        //check the neighbors
        for(int j = 0; j < n; j++) {
            if(idx != j && graph[idx][j] && colors[j] != -1) {
                tmpcolors.insert(colors[j]);
            }
        }
        if(tmpcolors.size() == cnt) {
            colors[idx] = cnt++;
        }else {
            for(int j = 0; j < cnt; j++) {
                if(tmpcolors.count(j) == 0) {
                    colors[idx] = j;
                    break;
                }
            }
        }
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "error arguments" << endl;
        return 0;
    }
    int numofcolors;
    vector<vector<int> > graph = readGraph(argv[1]);
    int n = graph.size();
    vector<int> order(n, 0);              // vertex processing order
    vector<int> deg = graphDeg(graph);
    vector<pair<int, int> > degorder;
    for(int i = 0; i < n; i++) {
        degorder.push_back(make_pair(i, deg[i]));
    }
    clock_t t;
    double diff;
    // High to low degree
    sort(degorder.begin(), degorder.end(), desc);
    for(int i = 0; i < n; i++)
        order[i] = degorder[i].first;
    t = clock();
    numofcolors = color(graph, order);
    t = clock() - t;
    diff = ((double)t)/CLOCKS_PER_SEC; // in seconds
    cout << "High to low: " << numofcolors << " colors, " << diff << " sec" << endl;
    
    // Low to high degree
    sort(degorder.begin(), degorder.end(), inc);
    for(int i = 0; i < n; i++)
        order[i] = degorder[i].first;
    t = clock();
    numofcolors = color(graph, order);
    t = clock() - t;
    diff = ((double)t)/CLOCKS_PER_SEC; // in seconds
    cout << "Low to high: " << numofcolors << " colors, " << diff << " sec" << endl;

    // Shuffle vector to get random order
    // using built-in random generator:
    random_shuffle (order.begin(), order.end());
    t = clock();
    numofcolors = color(graph, order);
    t = clock() - t;
    diff = ((double)t)/CLOCKS_PER_SEC; // in seconds
    cout << "Random: " << numofcolors << " colors, " << diff << " sec" << endl;

    return 0;
}

