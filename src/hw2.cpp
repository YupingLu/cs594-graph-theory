//hw2, Allan
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges
int *vertices;

char** adj_matrix;

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
	vertices = new int[n];
	for(i=0; i<n; i++)
		vertices[i] = 0;

	//allocate the memory for adj_matrix
	if ((adj_matrix=(char**) malloc(n*sizeof(char*)))==NULL) {
		printf ("Error allocating memory for adj_matrix\n");
		exit(1);
	}
	
	for (i=0; i<n; i++) {
		if ((adj_matrix[i]=(char*) calloc(n,sizeof(char)))==NULL) {
			printf ("Error allocating memory for adj_matrix[%d]\n",i);
			exit(1);
		}
	}

	for(i=0; i<e; i++) { 
		fscanf(fp, "%d\t%d", &row, &col);
		adj_matrix[row][col]=1;
		adj_matrix[col][row]=1;
	}

	fclose(fp);
	
}

void findNeighbor(int vertex) {
	int *neighbor = new int[n];
	int i;
	int j = 0;
	for(i=0; i<n; i++) {
		//if there is edge between the two vertices and the vertex has not been visited
		if((adj_matrix[vertex][i] == 1) && (vertices[i] == 0))
			neighbor[j++] = i;  //store the neighbor index
	}

	for(i=0; i<j; i++) {
		if(vertices[neighbor[i]] == 0) {
			cout << neighbor[i] << " ";
			vertices[neighbor[i]] = 1;
			findNeighbor(neighbor[i]);
		}
	}

	delete[] neighbor;
}

void dfs() {
	int i;
	for(i=0; i<n; i++) {
		if(vertices[i] == 0) {
			cout << i << " ";
			vertices[i] = 1;
			findNeighbor(i);
			cout << endl;
		}
	}
}

int main(int argc, char* argv[]) {

	readGraph(argv[1]);

	dfs();
	
	return 0;
}


