# Performance Report
## Lemmatization using AVL and BS trees

### Introduction
This report's aim is to compare the results obtained in terms of performance
using two versions of the same program to lemmatize an input text: one
version using AVL tree and the other using binary search tree. The node structure used
in both versions contains two character vectors, one being the
word represented by the node, and the other the lemma associated with this word, 
in addition to the pointers that indicate the node's sub-trees and the node's 
balancing factor (only in the version that uses AVL).

The application was tested using different amounts of nodes
(word and lemma pairs) and the tests results are presented at the end of this document.
The results englobe time of execution and number of comparisons made in the search 
operations in each chosen structure. This results were analyzed in order to find a 
pattern behavior in each version of the program and compare the performances of each
one.

### Analyzing tested cases
| # nodes | Structure | Average execution time (ms) counting from dictionary assembling | Average execution time (ms) counting from write to output file | Comparisons |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| 41760 | AVL | 173.4 | 18 | 453622 |
| 41760 | BST | 171 | 21 | 558954 |
| 33580 | AVL | 152.6 | 17.2 | 445586 |
| 33580 | BST | 164.3 | 20 | 550304 |
| 19888 | AVL | 86.3 | 16 | 428018 |
| 19888 | BST | 90 | 18.3 | 521594 |
| 4737 | AVL | 45 | 15.3 | 366148 |
| 4737 | BST | 74 | 17.1 | 428432 |

Using the test files provided, four different cases were tested, as shown in the table above.
The number of nodes represents the number of pairs word-lemma read from the dictionary
file and the execution times presented were calculated using the arithmetic median of 
three consecutive executions' times.

Reading 41760 pairs, the two programs are similar in terms of
execution time counting from the assembly of the structure that stores the
dictionary, but if counting starts from the lemma tree search, the program using AVL
performed slightly better. In terms of number of comparisons, the program using AVL
performed less comparisons when searching for lemmas.

Reading 33580 pairs, the program using AVL stood out in
performance in both cases of counting initiation, as well as in the number of
comparisons. In the case where 19888 pairs were read, the execution times of the two
programs counting from the assembly of the structure were similar, differing in
about 3 milliseconds. The runtime of the program that used AVL counting from the
writing of lemmas in the output file was less than the execution time of the
program that used BST. Again, the number of comparisons made by the program
that used AVL was less than the number of comparisons made by the program that used
BST.

In the case where 4737 pairs were read, the execution time of the program that used
AVL was less than the time of the program that used BST in the two cases of counting initiation
(counting from the assembly of the structure and counting from the writing in the output file), 
as well as the number of comparisons made.

### Conclusions
What can be seen is that as the number of nodes increases, the construction of the AVL
structure takes more time, due to the need to balance the tree in most insertion 
operations. This is because, as every new node is inserted as a leaf, balancing the
descendants of this new node will require a maximum of log2(n) operations, one for
each level of the tree. If a subtree has become unbalanced, two rotations are necessary
to correct the balance. As each rotation has an execution time of O(1), the execution
time of the insertion operation tends to O log2 (n)). The similarity of execution time
in the case with more nodes is explained because setting up the AVL takes more time
than the BST, but the difference is leveled during search, which was faster in AVL.

The assembly of the dictionary with BST is faster compared to the assembly with AVL, 
as there is no need to evaluate the height of the nodes at the time of insertion. 
However, the search in BST may end up making much more comparisons in some cases. 
For example, if the nodes are inserted already ordered in a BST 
(in the case of lemmatizating in alphabetical order), the height is equal to the total
number of nodes (n) and the performance is O(n), which is slower than O(log n). 
In this case, the tree is degenerated like a linked list and is called a zig-zag tree. 
In the tested cases there is no insertion of nodes already sorted alphabetically, 
just randmly, so there is not a very large time discrepancy between the two programs.

What is most noticeable is that the difference in performance increases when working
with fewer nodes, the advantage of using the AVL structure to store and work with
word-lemma pairs in these quantities being evident; but the difference in performance
decreases as the number of nodes increases. Another fact to be noted is that as the
objects are strings, the operations have a slightly longer execution time than that
provided by the Big O formulas given above, both in the program that uses AVL
and the one that uses BST, because there is a comparison of each string at the time
of insertion to know the lexicographic relationship between the two. In this case,
the construction of an BST with strings is done with execution time O(n * h), where n
is the length of the string and h is the height of the tree. In the case of AVL, the
construction execution time is O(n * log n) in the worst case. The search for a string
of length m in an BST has execution time of O(m + l) where l is the length of each path
in the tree, and in an AVL the search time is O(m + log n) in the worst case.

According to the results, the search also becomes faster in AVL, and this speed is 
reflected in the number of total comparisons made and in the execution time
counting from the moment of searching and writing the lemmas in the output file. 
This is due to the characteristic of AVL, the balancing. In the AVL, the search 
operation, in the worst case, has time O(log n) where n is the number of nodes, 
a result considered excellent when compared to the other execution times in Big O. 
In an BST, the search in the worst case, the execution time is O(n), where n is the
number of nodes, or O(h) in more general cases, being the height of the tree. 
Both O(n) and O(h) are slower than O(log n), so AVL search becomes faster.

The following graphs show the comparison of performance between the two
versions of the program with the tested cases, and the growth curve of some
Big O notations for comparison purposes.

![table1](https://user-images.githubusercontent.com/44986993/111890148-8c47a400-89c5-11eb-8fff-67a150a9aace.png)

In the graph 1 above, out of scale for visualization purposes, the x-axis shows the
number of nodes, and the y-axis the time in milliseconds that each program took to 
execute, starting the count from the tree construction. The green points refer to the
values collected during the execution of the program that used AVL as a structure, 
and the green curve is the parabola of adjustment of least squares between these points.
Similarly, the curve and red dots refer to the runtime values of the program that used
BST. Note that the distance between the two curves is greater for small x values, with 
the BST curve above the AVL curve, but the two curves are getting closer as the x value
increases, corroborating the conclusion made from the analysis of table 1.

![table2](https://user-images.githubusercontent.com/44986993/111890160-a2556480-89c5-11eb-9427-84814e7c48dd.png)

In graph 2, also out of scale, the x-axis shows the number of nodes, and
the y-axis the time in milliseconds that each program took to execute starting the
counting from the lemma search in the chosen data structure. The green dots
refer to the values collected during the execution of the program that used AVL as
structure, and the green curve is the parabola for adjusting least squares between these
points. Similarly, the curve and the red dots refer to the run time values
execution of the program that used BST. Note that the distance between the two curves
does not decreases as the nodes increase, as it happened in the previous graph, but the 
curves move away as the nodes increase, indicating that the difference grows with the
number of nodes. The execution time curve of the program that used BST is always greater
than the curve of the program that used AVL, corroborating the result found in the analysis of
table 1.
