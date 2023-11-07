HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Josh Suber >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< submitty notes, labs, cplusplus.com, geeksforgeeks, stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 hours >



NAIVE ALGORITHM:

Order Notation: O(w^2 * h^2)

Timing Experiment Data:

tiny_5x5.ppm -
real: 0.012s
user: 0.003s
sys: 0.0s

small_10x10.ppm -
real: 0.010s 
user: 0.003s
sys: 0.0s

squiggle_30x30.ppm - 
real: 0.014s
user: 0.007s
sys: 0.0s

lines_100x100.ppm -
real: 0.556s
user: 0.544s
sys: 0.0s

data_structures_300x300.ppm -
real: 45.770s
user: 45.751s
sys: 0.0s

Discussion:
As we can see from the timing experiment data, the algorithm 
takes a significant amount of time for larger input images, 
with the data_structures_300x300.ppm taking about 45.770 
seconds to complete. his makes sense because as the width and 
height go upthe time it takes the program to complete goes
 up exponentially.

IMPROVED ALGORITHM:

Order Notation: O(w^2 * h^2)

Timing Experiment Data:

tiny_5x5.ppm -
real: 0.016s
user: 0.002s
sys: 0.0s

small_10x10.ppm -
real: 0.017s
user: 0.002s
sys: 0.0s

squiggle_30x30.ppm - 
real: 0.013s
user: 0.003s
sys: 0.0s

lines_100x100.ppm -
real: 0.037s
user: 0.020s
sys: 0.0s

data_structures_300x300.ppm -
real: 4.109s
user: 4.067s
sys: 0.010s

Discussion:
This algorithm is an optimized version of the naive method.
Even though the time complexity is not different (due to the nested for loops)
the time it takes to complete is signifigantly quicker then the naive method with
the largest image, data_structures_300x300.ppm, only taking 4.109s.


FAST MARCHING METHOD (with a map):

Order Notation: O(w*h*log(w*h))

Timing Experiment Data:

tiny_5x5.ppm -
real: 0.042s
user: 0.00s
sys: 0.001s

small_10x10.ppm -
real: 0.081s
user: 0.001s
sys: 0.008s

squiggle_30x30.ppm - 
real: 0.071s
user: 0.001s
sys: 0.015s

lines_100x100.ppm -
real: 0.140s
user: 0.062s
sys: 0.00s

data_structures_300x300.ppm -
real: 0.745s
user: 0.588s
sys: 0.020s

Discussion:
Tis algorithm is the most efficient out of the three algorithms. 
The timing experiment data shows that the algorithm takes a reasonable 
amount of time to complete for all input images, with the largest input 
image data_structures_300x300.ppm taking only about 0.745 seconds to complete.

==============================================================
DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






