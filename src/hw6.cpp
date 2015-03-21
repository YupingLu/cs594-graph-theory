//hw6, Allan
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges

list<int> *adj_list;  //adjacency list

int** matching;  //2d array stores the maximal matching
int size;  //store the size of the maximal matching
map<int,int> highmap;
typedef pair<int, int> PAIR;  
int cmp(const PAIR& x, const PAIR& y)  
{
    return x.second != y.second ? x.second < y.second : x.first < y.first;
}
int cmp1(const PAIR& x, const PAIR& y)  
{
    return x.second != y.second ? x.second > y.second : x.first > y.first;
}
vector<PAIR> degree;  //store the degree of each vertex




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
	size = int(n/2+1);
	
	matching = new int*[size];
	for(i=0; i<size; i++) {
		matching[i] = new int[2]; 
	}

	for(i=0; i<e; i++) { 
		fscanf(fp, "%d\t%d", &row, &col);

		adj_list[row].push_back(col); 
    	adj_list[col].push_back(row); 

	}

	//reset the size to 0
	size = 0;

	fclose(fp);
	
}

//calcute vertex degrees
void computeDeg() {
	
	for (int i=0; i<n; i++) {
		degree.push_back(make_pair(i, adj_list[i].size()));  
	}
}

//choose index for method 4
int searchIndex(bool* visited) {
	int i;
	for(i=0; i<n; i++) {
		if(visited[i] == false) {
			return i;
		}
	}
	return -1;
}



//compute the maximal matching
void maximalMatching() {
	list<int>::iterator it;
	int index;
	int temp = n;
	int marker = -1;
	vector<int> v;

	//shuffle vertices for random access
	for(int i=0; i<n; i++) {
		v.push_back(i);
	}
	random_shuffle(v.begin(), v.end());

	// all vertices are not visited by default
	bool visited[n];
	for (int i=0; i<n; i++)
    	visited[i] = false;

    //Method 1: highest degree
    sort(degree.begin(), degree.end(), cmp1);
	for(int i=0; i<n; i++) {
		highmap[degree[i].first] = i;
	}

	for(int i=0; i<n; i++) {
		index = degree[i].first;
		if((visited[index] == false) && !adj_list[index].empty()) {
    		for(it = adj_list[index].begin(); it != adj_list[index].end(); it++) {
    			int j = *it;
    			if(visited[j] == false) {
    				if(highmap[j] < temp) {
    					temp = highmap[j];
    					marker = j;
    				}
    			}
    		}
		}
		if(marker != -1) {
			visited[index] = true;
    		visited[marker] = true;
    		if(index>marker) {
				matching[size][0] = marker;
				matching[size++][1] = index;
			}else {
				matching[size][0] = index;
				matching[size++][1] = marker;
			}
			temp = n;
			marker = -1;
		}

	}

	cout<< "Highest Degree: " << size << " edges" <<endl;
	for(int i=0; i<size-1; i++) {
		cout << matching[i][0] << "-" << matching[i][1] << ", ";
	}
	cout << matching[size-1][0] << "-" << matching[size-1][1] << endl;

	//reset variables
	temp = n;
	marker = -1;
	size = 0;
	for (int i=0; i<n; i++)
    	visited[i] = false;

	//Method 2: lowest degree
	sort(degree.begin(), degree.end(), cmp);
	for(int i=0; i<n; i++) {
		highmap[degree[i].first] = i;
	}
	for(int i=0; i<n; i++) {
		index = degree[i].first;
		if((visited[index] == false) && !adj_list[index].empty()) {
    		for(it = adj_list[index].begin(); it != adj_list[index].end(); it++) {
    			int j = *it;
    			if(visited[j] == false) {
    				if(highmap[j] < temp) {
    					temp = highmap[j];
    					marker = j;
    				}
    			}
    		}
		}
		if(marker != -1) {
			visited[index] = true;
    		visited[marker] = true;
    		if(index>marker) {
				matching[size][0] = marker;
				matching[size++][1] = index;
			}else {
				matching[size][0] = index;
				matching[size++][1] = marker;
			}
			temp = n;
			marker = -1;	
		}
	}

	cout<< "Lowest Degree: " << size << " edges" <<endl;
	for(int i=0; i<size-1; i++) {
		cout << matching[i][0] << "-" << matching[i][1] << ", ";
	}
	cout << matching[size-1][0] << "-" << matching[size-1][1] << endl;

	//reset variables
	temp = n;
	marker = -1;
	size = 0;
	for (int i=0; i<n; i++)
    	visited[i] = false;

	//Method 3: random edges
	/*cout << "random access order" <<endl;
	for(int i=0; i<n; i++) {
		cout<< v[i] << " ";
	}
	cout << endl;*/
	for(int i=0; i<n; i++) {
		highmap[v[i]] = i;
	}
	for(int i=0; i<n; i++) {
		index = v[i];
		if((visited[index] == false) && !adj_list[index].empty()) {
    		for(it = adj_list[index].begin(); it != adj_list[index].end(); it++) {
    			int j = *it;
    			if(visited[j] == false) {
    				if(highmap[j] < temp) {
    					temp = highmap[j];
    					marker = j;
    				}
    			}
    		}
		}
		if(marker != -1) {
			visited[index] = true;
    		visited[marker] = true;
    		if(index>marker) {
				matching[size][0] = marker;
				matching[size++][1] = index;
			}else {
				matching[size][0] = index;
				matching[size++][1] = marker;
			}
			temp = n;
			marker = -1;	
		}
	}

	cout<< "Random Edges: " << size << " edges" <<endl;
	for(int i=0; i<size-1; i++) {
		cout << matching[i][0] << "-" << matching[i][1] << ", ";
	}
	cout << matching[size-1][0] << "-" << matching[size-1][1] << endl;

	//reset variables
	temp = n;
	marker = -1;
	size = 0;
	for (int i=0; i<n; i++)
    	visited[i] = false;

	//Method 4: my method
	index = 0;
	for(int i=0; i<n; i++) {
		temp = index;
		if((visited[index] == false) && !adj_list[index].empty()) {
    		for(it = adj_list[index].begin(); it != adj_list[index].end(); it++) {
    			int j = *it;
    			if(visited[j] == false) {
    				visited[index] = true;
    				visited[j] = true;

    				if(index>j) {
						matching[size][0] = j;
						matching[size++][1] = index;
					}else {
						matching[size][0] = index;
						matching[size++][1] = j;
					}

    				it++;
    				
    				if(it != adj_list[index].end() && (visited[*it] == false)) {
    					//cout<< "j is:" << j << "it is :" << *it <<endl;
    					index = *it;
    				}
    				break;
    			}
    		}
		}
		//cout<< "temp is:" << temp << "index is :" << index <<endl;

		visited[temp] = true;
		
		if(temp == index) {
			index = searchIndex(visited); 
		}
		//cout<< "2nd index is :" << index <<endl;

		if(index == -1)
			index = 0;


	}

	cout<< "My Method: " << size << " edges" <<endl;
	for(int i=0; i<size-1; i++) {
		cout << matching[i][0] << "-" << matching[i][1] << ", ";
	}
	cout << matching[size-1][0] << "-" << matching[size-1][1] << endl;
   
}


int main(int argc, char* argv[]) {

	readGraph(argv[1]);

	computeDeg();

	maximalMatching();
	
	return 0;
}