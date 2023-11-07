HOMEWORK 3: MATRIX CLASS


NAME:  < Josh Suber >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< class notes, submitty, cplusplus.com, geeksforgeeks.org, cppreference.com, stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 hours >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

num_rows O(1)

get_column O(m)

operator<< O(mn)

quarter O(mn)

operator== O(mn)

operator!= O(mn)

swap_rows O(n)

rref (provided in matrix_main.cpp) O(n*m^2)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

To debug I started by using std::cout and print statements which allowed me to make
sure each of the functions was working correctly with simple cases. Then I used Valgrind 
for memory debugging and Clion's built-in debugging option. To test corner cases I tested
a lot of weird cases and made sure I was accounting for all tests. The tests I added the most 
were testing all the functions with empty matrices since they are the most different cases that not
a lot of people think of and take into account. The hardest ones were the quarter function because 
I had to take into account if there was one column or an odd number 
of columns and rows. I also added tests to functions that did not have any tests such as
swap_row() and transpose().


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

