HOMEWORK 4: TOOL RENTAL LISTS


NAME:  < Josh Suber >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< cplusplus.com, cpp.com, stackoverflow, submitty notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file:

Rental event:
O(ep) because it is a loop that goes through every customer which rents an item
and then loop through those items to make sure it can be rented.

Return event - no pending customer(s):
O(c) because it has to loop through all of the customers.

Return event - with pending customer(s):
O(p+c) because it has to loop through all the customers and pending customers.

Entire program:
O(icpqrpe) because there is a lot of loops and if statements that take into account
all of these variables.


MISC. COMMENTS TO GRADER:
(I need help with order notation please don't make fun of my answers lmao)

