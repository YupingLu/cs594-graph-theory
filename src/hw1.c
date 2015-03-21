//hw1, Allan
#include <stdio.h>
#include <stdlib.h>

int n; //NO. of vertices
int e;  //NO. of edges
int min_degree;
int max_degree;
double density;
char** adj_matrix;

//read input graph, the graph is tab seperated.
void readGraph(char* graph)
{
	int i, row, col;
	int count;
	FILE *fp;

	if ((fp=fopen(graph,"r"))==NULL) {
		printf ("Error opening input file %s\n",graph);
		exit(1);
	}


	//read the number of vertices and edges
	rewind(fp);
	fscanf(fp,"%d\t%d",&n,&e);

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

	//compute max degree and min degree
	count = 0;
	for(col=0; col<n; col++) {
		if (adj_matrix[0][col]==1) {
			count++;
		}
	}
	//store the first result
	max_degree = min_degree = count;
	for(row=1; row<n; row++) { 
		count = 0;
		for(col=0; col<n; col++) {
			if (adj_matrix[row][col]==1) {
				count++;
			}
		}
		if(max_degree < count)
			max_degree = count;
		if(min_degree > count)
			min_degree = count;
	}

	fclose(fp);
	
}


int main(int argc, char* argv[])
{
	readGraph(argv[1]);

	density = e/(n*(n-1)/2.0);

	printf("Minimum degree: %d\n", min_degree);
	printf("Maximum degree: %d\n", max_degree);
	printf("Density: %.8f\n", density);

	return 0;
}


