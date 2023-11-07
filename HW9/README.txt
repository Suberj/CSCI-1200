HOMEWORK 9: MINIBLAST


NAME:  < Josh Suber >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 hours >


HASH FUNCTION DESCRIPTION
I used the hash function that was given to us in lab 11.






HASH TABLE IMPLEMENTATION
My hash table uses a vector of pairs that consists of a string and a list.

The string is the "key" and the list holds positions of that key in the data.






ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
O((L-k)p)


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?
genome - O(L)
kmer - O(L-k)
occupancy - O(1)
table_size - O(1)
query - O(q*p)

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


