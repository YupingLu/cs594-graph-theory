1  
a. As κ(G) <= λ(G) <= 𝛿(G), BruteForceEdgeConnectivity will not reach its final return statement.
b. Complete graph
c. O(T(n)λ(G))

2
Compile code: g++ dfs.cpp -o DFS
Run: ./DFS graph2.txt 3

3
Compile code: g++ bfs.cpp -o BFS
Run: ./BFS graph2.txt 3

4
Compile code: g++ ConnectedComponents.cpp -o ConnectedComponents
Run: ./ConnectedComponents graph2.txt

5
Graphs                               dfs time           bfs time
arenas-jazz.txt                      0.006s             0.006s
Random-1000.01.txt                   0.020s             0.018s
Random-1000.8.txt                    0.132s             0.116s
Random-500.5.txt                     0.026s             0.023s
socfb-Caltech36.txt                  0.017s             0.016s
foodweb-baydry.txt                   0.003s             0.003s
Random-1000.1.txt                    0.034s             0.030s
Random-500.01.txt                    0.007s             0.007s
Random-500.8.txt                     0.035s             0.031s
socfb-Reed98.txt                     0.023s             0.020s
inf-USAir97.txt                      0.005s             0.005s
Random-1000.5.txt                    0.094s             0.084s
Random-500.1.txt                     0.013s             0.010s         
scc_fb-forum.txt                     0.027s             0.025s
sociopatterns-infectious.txt         0.007s             0.006s

No graph DFS runs faster than BFS.
The depth of a graph may be longer than the breadth. BFS is generally faster to traverse graph.
