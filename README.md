# String-Algorithms

suffixTree.c was the naive implementation of suffix tree construction. The running time is O(n^2). The application takes two arguments: the first is the filename of the string to search in, the second is the pattern to search for. E.g. if the file mississippi.txt contains the string "mississippi\n", then the application should be called as:

./search mississippi.txt ss

The output you'll get as a result would be:

3 6

The second code tandemRepeats.c was the implementation of Stoye-Gusfield algorithm for finding all occurences of tandem repeats in a string S of length n. The running time for this implementation is O(nlogn + occ) where occ is the number of accurences the code finds. 
The application takes one argument: the filename of the string to search for tandem repeats. E.g. if the file abaabaabbba.txt contains the string "abaabaabbba\n", then the application should be called as:

./tandem abaabaabbba.txt

and should output:

4 3

Folder StringAlgorithms contains java code for exact pattern matching. This java code contains three algorithms for exact pattern matching i.e. naive quadratic time algorithm, the BA-algorithm based on the border array of the pattern and the text, and the KMP-algorithm. The naive algorithm has worst case running time O(nm) and the BA- and KMP-algorithms have worst case running time O(n + m).
