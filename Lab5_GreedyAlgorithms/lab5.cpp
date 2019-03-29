/*
============= APPLICATION GOAL ==============
Running a motel with N rooms
- receive requests for bookings in an array
- algorithm should return 
  - 1 if can accomodate the set of bookings 
  - 0 if N rooms are insufficient to accommodate bookins.

============= STRATEGY: GREEDY ALGORITHM ==============
- sort by smallest range in days
- start couting with smallest booking for each day by storing the booking
- if one day exceeds 3 the set of bookings cannot be done
- if n never passes 3 to all the day its possible
- by checking the shortest ranges first we cover a bigger number of booking in smallest time
- if we are not greedy and get random booking the longest booking might take the time of 2 or more smaller bookings
- in some cases the negative solutin might be found later
Problem similar to:
- processes scheduling time
- line-up at groccery store
*/

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

// Driver function to sort the vector elements 
// by second element of pairs 
bool sortByShortestPeriod(const pair<int,int> &a, const pair<int,int> &b);
void printVectorOfPairs(vector< pair <int, int> > vect, int n);
int canBook(vector< pair <int, int> > vect, int n, int numRooms);

int main()
{  
    // declaring vector of pairs 
    vector< pair <int, int> > vect; 
    // Initialising bookings
    int arrive_dates[] = {1,3,5,6,6};
    int leave_dates[] =  {2,6,8,7,8};
    int maxNumRooms = 3;
    int n = sizeof(arrive_dates)/sizeof(arrive_dates[0]); 
    // Entering dates as pairs into vector
    for (int i=0; i<n; i++) 
        vect.push_back( make_pair(arrive_dates[i],leave_dates[i]) ); 
    
    cout << canBook(vect,n, maxNumRooms) << "\n";

    return 0;
}

int canBook(vector< pair <int, int> > vect, int n, int numRooms) {
     //sort booking by smallest period
     //printVectorOfPairs(vect, n);
     sort(vect.begin(), vect.end(), sortByShortestPeriod); 
     //printVectorOfPairs(vect, n);
     //keep track of booked rooms (array)
     //go through the sorted list of items
     //increment number booked rooms
    return 0;
}

bool sortByShortestPeriod(const pair<int,int> &a, const pair<int,int> &b) 
{ 
    return ((a.second-a.first)+1 < (b.second-b.first)+1); 
}

void printVectorOfPairs(vector< pair <int, int> > vect, int n) {
    cout << "The vector before sort operation is:\n" ; 
    for (int i=0; i<n; i++) 
    { 
        cout << vect[i].first << " " << vect[i].second << endl; 
    }
}