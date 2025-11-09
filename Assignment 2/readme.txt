Assignment 2: K-d Trees

/* *****************************************************************************
 *  Describe the Node data type you used to implement the
 *  2d-tree data structure.
 **************************************************************************** */
Each node has its own point, a value which can be of any data type since its a template, 
Its rectangle; the region this node covers, and then pointers to left and right since its a tree.


/* *****************************************************************************
 *  Describe your method for range search in a k-d tree.
 **************************************************************************** */
Its a recursive function which if a node is null or it doesn't intersect with the query rectangle then that point will not be added in the result,
otherwise if that query rectangle does contain that point 'p', then it will be added in the result.
After that its just a recursive call to left and right pointers.


/* *****************************************************************************
 *  Describe your method for nearest neighbor search in a k-d tree.
 **************************************************************************** */
To find the nearest neighbor, I first calculated the distance to that point from the query point.
Since each level has alternating vertical or horizontal points, I check that which alignment is it.
If it's vertical then compare the 'x' coordinate first otherwise 'y'.
Same for horizontal too but their I check the 'y' first and then 'x'.
I also assign first and second nodes, which corresponds which is closest.
If first node is already found then make a recursive call to that side and repeat,
else check that if the second node is not null.
If it is not then calculate the distance and if it's lesser than the best distance then make a recursive call.

/* *****************************************************************************
 *  How many nearest-neighbor calculations can your PointST implementation
 *  perform per second for input1M.txt (1 million points), where the query
 *  points are random points in the unit square?
 *
 *  Fill in the table below, rounding each value to use one digit after
 *  the decimal point. Use at least 1 second of CPU time. Do not use -Xint.
 *  (Do not count the time to read the points or to build the 2d-tree.)
 *  (See the checklist for information on how to do this)
 *
 *  Repeat the same question but with your KdTreeST implementation.
 *
 **************************************************************************** */


                 # calls to         /   CPU time     =   # calls to nearest()
                 client nearest()       (seconds)        per second
                ------------------------------------------------------
PointST:         10,000             /   51.3         =   195.1
                 20,000             /   72.6         =   275.3
                 40,000             /   263.7        =   151.7

    This shows that it can handle around 20,000 calls to the nearest(). Then it decreases.

KdTreeST:        10,000             /   0.06         =   172,710
                 40,000             /   0.16         =   245,166
                 80,000             /   0.32         =   253,102
                 160,000            /   0.7          =   238,879
                 320,000            /   0.99         =   160,529
                 1000,000           /   3.5          =   282,239
                 2000,000           /   9.8          =   204,105

    This shows that it can handle around 2000,000 calls to the nearest(). Then it decreases.

Overall the KdTreeST showed performance as it reached 2 million calls whereas PointST reached only twenty thousand.
This was done without any optimization flag, and more importantly their wasn't file named 'input1M.txt' so I used 'input100K.txt'.

Note: more calls per second indicates better performance.

/* *****************************************************************************
 *  Suppose you wanted to add a method numberInRange(RectHV rect) to your
 *  KdTreeST, which should return the number of points that are inside rect
 *  (or on the boundary), i.e. the number of points in the iterable returned by
 *  calling range(rect).
 *
 *  Describe a pruning rule that would make this more efficient than the
 *  range() method. Also, briefly describe how you would implement it.
 *
 *  Hint: consider a range search. What can you do when the query rectangle
 *  completely contains the rectangle corresponding to a node?
 **************************************************************************** */
 This is basically intersecting, if the nodes rectangle does not intersects the query rectangle then we we can simply not do anything ahead since this tells that there is not point inside.

/* *****************************************************************************
 *  Describe your unit test results
 **************************************************************************** */
Overall Test Status:<in one sentence>.
The PointSt class, having a brute force approach using map cannot handle large data points, and higher number of calls. 
On 100,000 points it went on to more than 20,000 calls. While the KdTreeST class can handle sufficiently more points than that.

Specific Test Cases:
1. **BasicKdTreeTest:** Passed.
2. **ModerateKdTreeTest:** Passed.
3. **HarderKdTreeTest:** Passed.
4. **EdgeCaseKDTreeTest:** Passed.
5. **NearestNeighborTest:** Passed.

Detailed Test Output:<a table of inputs and outputs for each of the tests>
I have done the input output table above with the 'input100K.txt' file for both classes.

/* *****************************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on  how helpful the class meeting was and on how much you learned 
 * from doing the assignment, and whether you enjoyed doing it.
 **************************************************************************** */
