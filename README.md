# Algos

Collection of different algorithms, used for programming competitions like ACM ICPC.

Algorithms are divided by topic. Most algorithms are runnable from the file as is.
Every algorithm has a reference problem on which it was tested, and some notes about its time and space complexity.

Feel free to use for any purposes (you may contact authors before, if you feel like it).

For any suggestions, corrections or questions contact [adilet.zxy@gmail.com](mailto:adilet.zxy@gmail.com) or open issue and/or pull request here.

## List of algorithms

### Dynamic Programming

* [Convex Hull trick](https://github.com/ADJA/algos/blob/master/DP/ConvexHullTrick.cpp) – Convex Hull trick is a geometry based dynamic programming modification. [More about it](http://wcipeg.com/wiki/Convex_hull_trick).
* [Longest Increasing Sequence](https://github.com/ADJA/algos/blob/master/DP/LIS.cpp) – Fast way to find longest increasing subsequence (subsequence in which each next element is greater than previous).

### Data Structures

* [Cartesian Tree](https://github.com/ADJA/algos/blob/master/DataStructures/CartesianTree.cpp) – Cartesian tree is a randomized balanced binary search tree.
* [Cartesian Tree with implicit keys](https://github.com/ADJA/algos/blob/master/DataStructures/CartesianTreeImplicitKeys.cpp) – Cartesian tree with implicit keys is a powerful modification of cartesian tree, which can be used to solve many interesting problems. This implementation solves the problem of finding range minimum and also can perform reverse of an array segment.
* [Fenwick tree](https://github.com/ADJA/algos/blob/master/DataStructures/FenwickTree.cpp) – Fenwick tree is a simple and easy-to-write data structure which can be used to find the value of some reversible function on the interval and also change the value of some element. This implementation can find the sum on the interval and update any arbitrary element.
* [Fenwick tree 2D](https://github.com/ADJA/algos/blob/master/DataStructures/FenwickTree2D.cpp) – Extension of Fenwick tree on 2D case. This code can find the sum on the rectangle and update any arbitrary element.
* [Implicit segment tree](https://github.com/ADJA/algos/blob/master/DataStructures/ImplicitSegmentTree.cpp) – Implicit segment tree is a modification of segment tree which creates nodes only when they are needed. It can be used on big intervals like [1..10<sup>9</sup>].  This code performs addition on the interval and getting the value of some element.
* [Queue with minimum](https://github.com/ADJA/algos/blob/master/DataStructures/QueueWithMinimum.cpp) – Modification of queue, which allows finding the minimum element in it.
* [Segment Tree (Add-Min-Max)](https://github.com/ADJA/algos/blob/master/DataStructures/SegmentTree(Add-Min-Max).cpp) – Segment tree is a powerful data structure which can perform many operations on the intervals in O(logN) time. This implementation performs addition and min/max interval. 
* [Segment Tree (Assign-Sum)](https://github.com/ADJA/algos/blob/master/DataStructures/SegmentTree(Assign-Sum).cpp) – Segment tree implementation that performs assignment and gets the sum on the interval.
* [Segment Tree (minimum on a segment and update)](https://github.com/ADJA/algos/blob/master/DataStructures/SegmentTree.cpp) – Segment tree. Solves RMQ problem (maximum on a segment and value update).
* [Sparse table](https://github.com/ADJA/algos/blob/master/DataStructures/SparseTable.cpp) – Solves static RMQ problem (range minimum/maximum query without element changes).

### Geometry

* [Closest pair of points](https://github.com/ADJA/algos/blob/master/Geometry/ClosestPairOfPoints.cpp) ([Code 2](https://github.com/ADJA/algos/blob/master/Geometry/ClosestPairOfPointsNurlan.cpp)) – Divide-and-conquer approach to find the closest pair of points.
* [Convex Hull](https://github.com/ADJA/algos/blob/master/Geometry/ConvexHull.cpp) ([Code 2](https://github.com/ADJA/algos/blob/master/Geometry/convex_hull_graham_scan.cpp)) – Graham-Andrew and Graham scan methods to find convex hull (the least convex polygon containing all given points).

### Graphs

* [Bellman-Ford algorithm](https://github.com/ADJA/algos/blob/master/Graphs/BellmanFord.cpp) – Bellman-Ford algorithm finding shortest distances from a single vertex in graph.
* [Bipartite matching](https://github.com/ADJA/algos/blob/master/Graphs/BipartiteMatchingKuhn.cpp) – Kuhn algorithm for maximum matching in bipartite graph.
* [Bridges search](https://github.com/ADJA/algos/blob/master/Graphs/BridgesSearch.cpp) – Algorithm for finding all bridges in the graph (edges, after removal of which graph divides into several components).
* [Centroid decomposition](https://github.com/ADJA/algos/blob/master/Graphs/CentroidDecomposition.cpp) – Centroid decomposition of a tree.
* [Cutpoints search](https://github.com/ADJA/algos/blob/master/Graphs/CutpointsSearch.cpp) – Algorithm for finding all cutpoints in the graph (vertices, after removal of which graph divides into several components).
* [Dijkstra algorithm](https://github.com/ADJA/algos/blob/master/Graphs/DijkstraHeap.cpp) ([set version](https://github.com/ADJA/algos/blob/master/Graphs/DijkstraSet.cpp)) – Finding minimum distances from the single source with Dijkstra algorithm. No negative edges are allowed. Best for sparse graphs. Two versions using set and heap.
* [Dinic maxflow](https://github.com/ADJA/algos/blob/master/Graphs/Dinic.cpp) – Dinic algorithm with scaling for finding the maximum flow.
* [Eulerian path/cycle](https://github.com/ADJA/algos/blob/master/Graphs/EulerianCycle.cpp) – Algorithm for finding the Eulerian path/cycle, i.e. path/cycle that visits every edge of the graph exactly once.
* [Floyd-Warshall algorithm](https://github.com/ADJA/algos/blob/master/Graphs/FloydWarshall.cpp) – Floyd-Warshall algorithm finding shortest distance between all pairs of vertices in graph.
* [Ford-Fulkerson maxflow](https://github.com/ADJA/algos/blob/master/Graphs/FordFulkerson.cpp) – Ford-Fulkerson algorithm for finding the maximum flow.
* [Heavy-light decomposition](https://github.com/ADJA/algos/blob/master/Graphs/HLD.cpp) – Heavy-light decomposition with segment trees in paths. Used for finding maximum on the path between two vertices.
* [Hungarian matching](https://github.com/ADJA/algos/blob/master/Graphs/HungarianMatching.cpp) – Hungarian algorithm for solving the assignment problem.
* [LCA. Binary ascent.](https://github.com/ADJA/algos/blob/master/Graphs/LCABinary.cpp) – Finding LCA (Least common ancestor) of two vertices in the tree. Uses dp calculated on powers of 2.  
* [LCA. Heavy-light decomposition.](https://github.com/ADJA/algos/blob/master/Graphs/LCAHLD.cpp) – Finding LCA (Least common ancestor) of two vertices in the tree. Uses heavy-light decomposition.
* [MinCost MaxFlow Dijkstra](https://github.com/ADJA/algos/blob/master/Graphs/MinCostDijkstra.cpp) ([Heap Dijkstra](https://github.com/ADJA/algos/blob/master/Graphs/MinCostDijkstraHeap.cpp)) – Solution to MinCost MaxFlow (or simply MinCost Flow) using Dijkstra algorithm with potentials as shortest path search method.
* [MinCost MaxFlow Ford-Bellman](https://github.com/ADJA/algos/blob/master/Graphs/MinCostFB.cpp) – Solution to MinCost MaxFlow (or simply MinCost Flow) using Ford-Bellman algorithm as shortest path search method.
* [Minimum spanning tree. Kruskal algorithm](https://github.com/ADJA/algos/blob/master/Graphs/MSTKruskal.cpp) – Kruskal algorithm for finding the minimum spanning tree (tree connecting the given graph with minumim sum of edges).
* [Minimum spanning tree. Prim algorithm](https://github.com/ADJA/algos/blob/master/Graphs/MSTPrim.cpp) – Prim algorithm for finding the minimum spanning tree (tree connecting the given graph with minumim sum of edges).

### Number Theory

* [BigInt](https://github.com/ADJA/algos/blob/master/NumberTheory/BigInt.cpp) – Structure implementing long arithmetic in C++. Analogous to BigInteger in Java.
* [Catalan numbers](https://github.com/ADJA/algos/blob/master/NumberTheory/CatalanNumbers.cpp) – Finding Nth Catalan number modulo some mod (mod is not necessary prime). Uses Eratosthenes sieve for fast factorization.
* [Diophantine equation](https://github.com/ADJA/algos/blob/master/NumberTheory/DiophantineEquation.cpp) – Solving Diophantine equations in form of a * x + b * y = c. Uses extended Euclid algorithm (which finds such x, y that a * x + b * y = gcd(a, b)).
* [Fast Fourier transformation](https://github.com/ADJA/algos/blob/master/NumberTheory/FFT.cpp) – Fast Fourier transformation used to multiply long numbers. Fast non-recursive version.
* [Gauss](https://github.com/ADJA/algos/blob/master/NumberTheory/Gauss.cpp) – Gauss method of solving systems of linear algebraic equation.
* [Matrix](https://github.com/ADJA/algos/blob/master/NumberTheory/Matrix.cpp) – Matrix multiplication and fast binary power.
* [Number by permutation](https://github.com/ADJA/algos/blob/master/NumberTheory/NumberByPermutation.cpp) – Finding number of permutation in lexicographical order.
* [Permutation by number](https://github.com/ADJA/algos/blob/master/NumberTheory/PermutationByNumber.cpp) – Finding permutation by its length and number in lexicographical order.

### Other

* [Expression result calculation](https://github.com/ADJA/algos/blob/master/Other/ExpressionCalc.cpp) – Calculation of the value of the algebraic expression (like 2 * (5 + 7) - 25 / 5). Uses recursive descend. See code for the list of supported operations.
* [Merge sort](https://github.com/ADJA/algos/blob/master/Other/MergeSort.cpp) – Merge sort for sorting the array of integers.
* [Quick sort](https://github.com/ADJA/algos/blob/master/Other/QuickSort.cpp) – Quick sort with random pivoting for sorting the array of integers.
* [Radix sort](https://github.com/ADJA/algos/blob/master/Other/RadixSort.cpp) – Radix sort for sorting the array of integers.

### Strings

* [Aho-Corasick](https://github.com/ADJA/algos/blob/master/Strings/Aho-Corasick.cpp) – Aho-Corasick algorithm. This code finds all words in the text that contain any of the initially given words.
* [Hashing](https://github.com/ADJA/algos/blob/master/Strings/Hashing.cpp) – Hashing in strings based problems. This code compares substrings using two hashes (one uses 2^64 as a modulo, another 10^9 + 7).
* [Manacher's algorithm](https://github.com/ADJA/algos/blob/master/Strings/ManacherPalindromes.cpp) – Manacher's algorithm for finding all subpalindromes in the string.
* [Palindrome tree](https://github.com/ADJA/algos/blob/master/Strings/PalindromeTree.cpp) – Useful structure to deal with palindromes in strings. This code counts number of palindrome substrings of the string.
* [Prefix function](https://github.com/ADJA/algos/blob/master/Strings/PrefixFunction.cpp) – Calculating the prefix function of the given string.
* [Suffix Array](https://github.com/ADJA/algos/blob/master/Strings/SuffixArray.cpp) – Building suffix array in O(NlogN). Also LCP array is calculated. This code counts number of different substrings in the string.
* [Trie](https://github.com/ADJA/algos/blob/master/Strings/Trie.cpp) – Builds trie (tree with characters on the edges) from the set of strings. This code counts number of different substrings in the string.
* [Suffix Tree. Ukkonen's algorithm](https://github.com/ADJA/algos/blob/master/Strings/UkkonenSuffixTree.cpp) – Ukkonen's algorithm for building the suffix tree. Uses sibling lists in the nodes. This code counts number of different substrings in the string.
* [Z function](https://github.com/ADJA/algos/blob/master/Strings/ZFunction.cpp) – Calculating the Z-function of the given string.
