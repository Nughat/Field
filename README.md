# Field
Implements a field class

# Parameterized constructor, Parameterized "move" constructor

# Weight
This method returns the sum of all elements in the rectangle defined by the points (x1,y1) and (x2,y2).
Pay attention, the relative position of (x1,y1) and (x2,y2) can be any. If coordinates go beyond the array boundaries, 
throw the out_of_range exception. The Weight function should be O(1) run time. To achieve this, you will need to do 
the precomputing in the constructors. Precomputing should be done in O(N) time and O(N) space. Here, N is the total 
number of the elements in the 2-D array.

# Path
This method computes the cost of the cheapest path from top-left corner of the field to the bottom-right corner. 
The only possible moves are right and down. The function PathCost should be O(N) time.
