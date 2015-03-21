//hw5, Allan
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges
int *vertices;
vector<int> eulerian;
vector<int> temp_eulerian;
int depth;
bool even_degree;
bool connected;
int source;  //the start vertex

char** adj_matrix;

//read input graph into adjacency matrix, the graph is tab seperated.
void readGraph(char* graph) {
	int i, row, col, count;
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

	//check if all vertices have even degree
	even_degree = true;

	for(row=0; row<n; row++) {
		count = 0;
		for(col=0; col<n; col++) {
			if (adj_matrix[row][col]==1) {
				count++;
			}
		}
		if(count%2) {
			cout << "The graph contains no Eulerian cycle" << endl;
			even_degree = false;
			break;
		}
	}

	connected = true;

	fclose(fp);
	
}

//find the circuit 
int findNeighbor(int vertex) {
	int *neighbor = new int[n];
	int i;
	int j = 0;
	
	for(i=0; i<n; i++) {
		//if there is edge between the two vertices and the edge has not been visited
		if(adj_matrix[vertex][i] == 1) {
			neighbor[j++] = i;  //store the neighbor index

		}
	}

	if((j>0) && (neighbor[0]!=source)) {
		//mark visited vertices
	
		vertices[neighbor[0]] = 1;
		depth++;
		temp_eulerian.push_back(neighbor[0]);
		adj_matrix[vertex][neighbor[0]] = 0;
		adj_matrix[neighbor[0]][vertex] = 0;
		findNeighbor(neighbor[0]);
		
	}else if((j>0) && (neighbor[0]==source)) {
		adj_matrix[vertex][neighbor[0]] = 0;
		adj_matrix[neighbor[0]][vertex] = 0;
	}

	delete[] neighbor;
}

//find lowest numbered vertex with unused edges.
int findVertex() {

	int row, col;
	bool exist = false;
	int vertex = n;

	for(row=0; row<n; row++) {
		for(col=0; col<n; col++) {
			if (adj_matrix[row][col]==1) {
				if(vertices[row]) {
					//cout << "row: "<< row << endl;
					vertex = (vertex > row) ? row : vertex;
					exist = true;
				}else if(vertices[col]) {
					//cout << "col: "<< col << endl;
					vertex = (vertex > col) ? col : vertex;
					exist = true;
				}
			}
		}
	}

	if(exist)
		return vertex;
	else
		return -1;

}

int hierholzer() {
	int i;
	vector<int>::iterator curr;
	vector<int>::iterator marker;

	source = 0;
	eulerian.push_back(source);
	while(source != (-1)) {
		vertices[source] = 1;

		temp_eulerian.resize(0);
		depth = 0;
		findNeighbor(source);
		if(depth>1) {
			temp_eulerian.push_back(source);

			for(curr = eulerian.begin(); curr < eulerian.end(); ++curr) {
				if((*curr) == source) {
					marker = curr;
					curr = eulerian.end()-1;
				}
			}
			eulerian.insert(marker+1, temp_eulerian.begin(), temp_eulerian.end());
		}

		source = findVertex();
		//cout<< "source: " << source <<endl;
	}


	for(i=0; i<n; i++) {
		if(vertices[i] == 0) {
			connected = false;
		}
	}
}

int main(int argc, char* argv[]) {
	vector<int>::iterator curr;
	readGraph(argv[1]);

	if(even_degree) {
		hierholzer();
		//If the graph is a connected graph
		if(connected) {
			for(curr = eulerian.begin(); curr != eulerian.end()-1; ++curr) {
				cout << *curr << "-";
			}
			cout << *curr << endl;
		}else
			cout << "The graph contains no Eulerian cycle" << endl;
	}
	
	return 0;
}


