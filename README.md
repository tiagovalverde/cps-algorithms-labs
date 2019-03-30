# CPS 616 - Algorithms

### Lab 1 - Sorting and Problem Size

Sort arrays of different size using:
- Selection Sort
- Merge Sort
- A combination of Merge Sort and Selection Sort
  (Call Selection within Merge sort when size of the array is small enough)

Additionally, measure the running time of each of the sorting algorithms

### Lab 2 - Divide and Conquer

Implement your own **pow** function in:
- linear time
- lg n time

### Lab 3 - Divide and Conquer

Implement number multiplication digit by digit using the following divide and conquer algorithms:
- multiply 4
- multiply 3 (Karatsuba Algorithm)

### Lab 4 - Graphs

Given a graph as input, write an algorithm to determine a minimum spanning tree.
- Minimum Spanning Tree determined using Prim's Algorithm.
- Alternatively, Dijkstra's Algorithm could have been used.

### Lab 5 - Greedy Algorithm

Run a motel with N rooms. Determine if a set of bookings can be accomodated using a greedy algorithm.
- Input: batches of bookings represented in arrays
- Output: return 1 if able to accomodate set of bookings, 0 otherwise.

Problem similar to the interval scheduling for processes in a operating system. In processes interval scheduling, we look for a algorithm that assigns a much number of processes as possible in the shortest period of time. To complete that, a greddy algorithm is implemented to obtain the shortest processes first.

The same approach is used with the room accomodation, which sorts the bookings by shortest period and in a greedy way books the smallest bookings first. This allows to encounter a day that the number of rooms may be greater than the maximum number of rooms available sooner.   