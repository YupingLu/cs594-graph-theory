//hw4, a brute force minimum vertex cover algorithm implementation
//first part is to find a approximate one, then run brute force on it.
//However, the first part is not guaranteed to find a maximum matching. 
//As the time is limited, I just run brute force on the whole graph.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <list>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges

int *mvc;  //store the vertices in minimum vertex cover
int *mvc1;
int size;	//store the size of the mvc
list<int> *adj_list;  //adjacency list
list<int> *adj_list_bak;

//read input graph into adjacency list, the graph is tab seperated.
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

	adj_list = new list<int>[n];
	adj_list_bak = new list<int>[n];
	mvc = new int[n];
	mvc1 = new int[n];
	size = 0;

	for(i=0; i<e; i++) { 
		fscanf(fp, "%d\t%d", &row, &col);

		adj_list[row].push_back(col); 
    	adj_list[col].push_back(row); 

	}

	fclose(fp);
	
}

/* pseudo code from wikipedia
APPROX VERTEX COVER(G)
C=∅
E'= G.E
while E'≠ ∅

	let (u,v) be an arbitrary edge of E'
	C = C ∪ {u,v}
	remove from E' every edge incident on either u or v
return C
*/

void vertexCover() {
	list<int>::iterator it;
	// all vertices are not visited by default
	bool visited[n];
	for (int i=0; i<n; i++)
    	visited[i] = false;


    /*for(int i=0; i<n; i++)
    	cout<< adj_list[i].size() << endl;*/

    for(int i=0; i<n; i++) {
    	if((visited[i] == false) && !adj_list[i].empty()) {
    		for(it = adj_list[i].begin(); it != adj_list[i].end(); it++) {
    			int j = *it;
    			if(visited[j] == false) {
    				visited[i] = true;
    				visited[j] = true;
    				break;
    			}
    		}
    	}
    }

    //store vertex cover into mvc
    for (int i=0; i<n; i++)
		if (visited[i]) {
			mvc1[size] = i;
			mvc[size++] = i;
		}
}

//run brute force on mvc
void minVertex(int* vertices, int length) {
	list<int>::iterator it;

	for(int i=0; i<length; i++) {
		int count = 0;
		int* newvertices = new int[length-1];
		int temp = 0;

		//copy adjacency list
		for (int x=0; x<n; x++) {
			adj_list_bak[x] = adj_list[x];
		}

		for (int j=0; j<length; ++j) {
			if(j!=i) {
				newvertices[temp++] = vertices[j];

				for(it = adj_list_bak[vertices[j]].begin(); it != adj_list_bak[vertices[j]].end(); it++) {
	    			int s = *it;
	    			adj_list_bak[s].remove(vertices[j]);
	    			count++;
	    		}
				
			}
		}

		if(count < e)
			continue;
		else {
			if(size > (length-1)) {
				for(int k=0; k<length-1; k++) {
					mvc[k] = newvertices[k];
				}
				size = length-1;
			}
			minVertex(newvertices, length-1);
		}
		delete[] newvertices;
	}
}


int main(int argc, char* argv[]) {

	readGraph(argv[1]);

	//vertexCover();

	for (int i=0; i<n; i++) {
		mvc1[size] = i;
		mvc[size++] = i;
	}

	minVertex(mvc1, size);

	cout<<"Minimum Vertex Cover Size: "<<size<<endl;
	for (int i=0; i<size; i++)
		cout<<mvc[i]<<" ";
	cout<<endl;
	
	return 0;
}


