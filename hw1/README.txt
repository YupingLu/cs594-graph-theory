CS 690 Homework 1  Allan

1. Assume we have a function to find whether a loop exists in a graph. My idea is based on this function. If the loop is detected, we check if it is K3. 

We use dfs to traverse the graph. If a loop is detected(that is a node is visited before), we check if this circle is K3. If K3 is not found, we continue until all nodes have been marked as visited.

The worst case is that we have to visit all the nodes in the graph, then the complexity is O(n).

2.
gcc hw1.c -o degree

./degree graph1.txt                                                                                                                                                     
Minimum degree: 2
Maximum degree: 5
Density: 0.53333333