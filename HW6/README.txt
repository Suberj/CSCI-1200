HOMEWORK 6: INVERSE WORD SEARCH


NAME:  < Josh Suber >


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< submitty notes, cplusplus.com, geekforgeeks.com, stackoverflow, youtube >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25-30 hours >


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
O(n^4), because there is 4 nested loops in the main recursive function.
However, the program does not feel like it runs that slow so perhaps I am missing something
or the input files are not big enough to see a huge difference.



TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

My program ran every test pretty quick not taking more than a few second 
on any of the test cases.

I created several different tests including using bad words that use the letter 'z'
because my board will default to z if no letter will fit there. I also added bigger sized boards
and boards that would have no solution. The z did not seem to be a major problem like a thought 
I only saw one or two cases that conflicted, but I could not figure out how to fix this. The bigger boards
too a fair bit of time compared to the small ones but that was expected. Finally, the no solutions worked as
expected with the fail safes I put in the file for this exact purpose.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


