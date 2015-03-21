//hw3, a greedy coloring algorithm implementation
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges

int *neighbor;   //neighbors of a vertex
int j;			//the number of neighbors of a vertex
int *colors;	//the color for each vertex

int *tempcolors;
int t;		//the number of temp colors

int** adj_matrix;

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

	neighbor = new int[n];

	//initialize colors
	colors = new int[n];
	for(i=0; i<n; i++)
		colors[i] = n;

	tempcolors = new int[n];
	for(i=0; i<n; i++)
		tempcolors[i] = n;

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
		fscanf(fp, "%d\t%d", &row, &col);
		adj_matrix[row][col]=1;
		adj_matrix[col][row]=1;
	}

	fclose(fp);
	
}

void findNeighbor(int vertex) {
	int i;
	j = 0;
	for(i=0; i<n; i++) {
		//if there is edge between the two vertices and the vertex has not been visited
		if(adj_matrix[vertex][i] == 1)
			neighbor[j++] = i;  //store the neighbor index
	}
}

void checkColor(int color) {
	int l = 0;
	for(int i=0; i<n; i++)
		if(tempcolors[i] == color)
			l = 1;
	if(l != 1)
		tempcolors[t++] = color;
}

void coloring() {
	int i, k, s;
	int temp = -1;
	cout<<"Vertex Color"<<endl;
	for(i=0; i<n; i++) {
		cout<< i << " ";
		findNeighbor(i);
		t = 0;
		//cout << "j is " << j <<endl;

		for(k=0; k<j; k++) {
			checkColor(colors[neighbor[k]]);
		}

		//cout << "t is " << t <<endl;

		//sort tempcolors
		sort(tempcolors, tempcolors + t);
		for(s=0; s<t; s++) {
			if((s != tempcolors[s]) && (tempcolors[s] != n)) {
				temp = s;
				break;
			}

		}
		if(temp != -1)
			colors[i] = temp;
		else
			colors[i] = t;
	
		cout << colors[i] << endl;

		//reset tempcolors
		for(k=0; k<n; k++)
			tempcolors[k] = n;
	}

	//find the number of colors
	for(i=0; i<n; i++) {
		if(temp < colors[i])
			temp = colors[i];
	}
	cout << "Colors Used " << temp+1 << endl;
}

int main(int argc, char* argv[]) {

	readGraph(argv[1]);

	coloring();
	
	return 0;
}


