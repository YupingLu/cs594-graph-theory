//hw3, Dijkstra’s algorithm implementation
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges
int *vertices;	//unvisited vertices
int *neighbor;   //neighbors of a vertex
int j;			//the number of neighbors of a vertex
int *dist;		//the distance value for each vetex
int *prev;		//Previous node in optimal path from source
int *queue;		//output path queue;
int w;		//the number of path queue;

int** adj_matrix;


typedef pair<int, int> PAIR;  
int cmp(const PAIR& x, const PAIR& y)  
{  
    return x.second < y.second;  
}
vector<PAIR> vec; 


//read input graph into adjacency matrix, the graph is tab seperated.
void readGraph(char* graph) {
	int i, row, col, weight;
	FILE *fp;

	if ((fp=fopen(graph,"r"))==NULL) {
		printf ("Error opening input file %s\n",graph);
		exit(1);
	}


	//read the number of vertices and edges
	rewind(fp);
	fscanf(fp,"%d\t%d",&n,&e);

	//store all the vertices, 0 is unvisited, 1 is visited. Default is 0
	vertices = new int[n];
	for(i=0; i<n; i++)
		vertices[i] = 0;

	neighbor = new int[n];
	dist = new int[n];
	prev = new int[n];
	queue = new int[n];

	//initialize dist and prev. -1 means unknown or infinity
	for (i=0; i<n; i++) {
		dist[i] = -1;
		prev[i] = -1;
	}
	

	//allocate the memory for adj_matrix
	if ((adj_matrix=(int**) malloc(n*sizeof(int*)))==NULL) {
		printf ("Error allocating memory for adj_matrix\n");
		exit(1);
	}
	
	for (i=0; i<n; i++) {
		if ((adj_matrix[i]=(int*) calloc(n,sizeof(int)))==NULL) {
			printf ("Error allocating memory for adj_matrix[%d]\n",i);
			exit(1);
		}
	}

	for(i=0; i<e; i++) { 
		fscanf(fp, "%d\t%d\t%d", &row, &col, &weight);
		adj_matrix[row][col]=weight;
		adj_matrix[col][row]=weight;
	}

	fclose(fp);
	
}

void findNeighbor(int vertex) {
	int i;
	j = 0;
	for(i=0; i<n; i++) {
		//if there is edge between the two vertices and the vertex has not been visited
		if((adj_matrix[vertex][i] > 0) && (vertices[i] == 0))
			neighbor[j++] = i;  //store the neighbor index
	}
}

//find the vertex in vertices with min dist[u]
int minDist() {
	int i;
	int temp = -1;
	int distance = -1;
	for(i=0; i<n; i++) {
		if((vertices[i] == 0) && (dist[i] > -1)) {
			distance = dist[i];
			temp = i;
			break;
		}
	}

	//cout<< "diantance is "<< distance <<endl;

	for(i=0; i<n; i++) {
		if((vertices[i] == 0) && (dist[i] > -1)) {
			if(distance > dist[i]) {
				distance = dist[i];
				temp = i;
			}
		}
	}

	return temp;
}

//Print the optimal path
void printQueue(int vertex) {
	int pre;
	w = 0;
	queue[w++] = vertex;
	while(prev[vertex] != -1){
		queue[w++] = prev[vertex];
		vertex = prev[vertex];
	}
	cout<< queue[w-1];
	for(int i=w-2; i>-1; i--)
		cout<<"-"<<queue[i];
}

// Implementation is based on the pseudocode from wikipedia
void dijkstra(int source) {
	int i, u, v, alt, k;
	dist[source] = 0; 		// Distance from source to source

	for (i=0; i<n; i++) {
		u = minDist();
		//cout << "u is " << u <<endl;
		if(u != -1) {
			//remove u from vertices
			vertices[u] = 1;
			findNeighbor(u);

			for (k=0; k<j; k++) {
				v = neighbor[k];
				alt = dist[u] + adj_matrix[u][v];

				if(dist[v] == -1) {
					dist[v] = alt;
					prev[v] = u;
				}else if(alt < dist[v]) {
					dist[v] = alt;
					prev[v] = u;
				}

				//cout<< "v is " << v << "distance is " << dist[v] <<endl;
			}
		}
		
	}


	//sort dist
	for (i=0; i<n; i++) {
		vec.push_back(make_pair(i, dist[i]));  
	}

	sort(vec.begin(), vec.end(), cmp);

	//print the results
	cout << "Sink Cost Path" <<endl;

	for(vector<PAIR>::iterator curr = vec.begin(); curr != vec.end(); ++curr) {
		if((*curr).second == -1) {
			cout << (*curr).first << " is unreachable." <<endl; 
		} else {
			cout << (*curr).first << " " << (*curr).second << " ";
			printQueue((*curr).first);
			cout<<endl;
		}
	} 

}

int main(int argc, char* argv[]) {

	readGraph(argv[1]);

	dijkstra(0);
	
	return 0;
}


