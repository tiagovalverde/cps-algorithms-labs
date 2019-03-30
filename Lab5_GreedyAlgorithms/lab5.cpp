#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

/*
============= APPLICATION GOAL ==============
Running a motel with N rooms
- receive requests for bookings in an array
- algorithm should return 
  - 1 if can accomodate the set of bookings 
  - 0 if N rooms are insufficient to accommodate bookings.
*/

using namespace std;

bool sortByShortestPeriod(const pair<int,int> &a, const pair<int,int> &b);
void printVectorOfPairs(vector< pair <int, int> > vect, int n);
int canBook(vector< pair <int, int> > vect, int n, int numRooms);
int getMaxDate(vector< pair <int, int> > vect, int n);
int getMinDate(vector< pair <int, int> > vect, int n);

int main()
{  
    // declaring vector of pairs 
    vector< pair <int, int> > bookingDates; 
    // Initialising bookings
    int arrive_dates[] = {1,3,5,6,6};
    int leave_dates[] =  {2,6,8,7,8};
    int maxNumRooms = 3;
    int n = sizeof(arrive_dates)/sizeof(arrive_dates[0]); 
    
    // Entering dates as pairs into vector
    for (int i=0; i<n; i++) {
        bookingDates.push_back( make_pair(arrive_dates[i],leave_dates[i]) ); 
    }
    
    cout << "===============================================\n";
    cout << canBook(bookingDates,n, maxNumRooms) << endl;
    cout << "===============================================\n";
    
    maxNumRooms = 4; // same set of bookings, 1 extra room
    cout << canBook(bookingDates,n, maxNumRooms) << endl;
    

    vector< pair <int, int> > bookingDates2;
    int arrive_dates2[] = {1,5,8,1,3,5,7,10,1,6};
    int leave_dates2[] =  {4,7,10,2,4,6,9,10,5,10};
    maxNumRooms = 3;
    n = sizeof(arrive_dates2)/sizeof(arrive_dates2[0]); 
    
    for (int i=0; i<n; i++) {
        bookingDates2.push_back( make_pair(arrive_dates2[i],leave_dates2[i]) ); 
    }

    cout << "===============================================\n";
    cout << canBook(bookingDates2,n, maxNumRooms) << endl;
    cout << "===============================================\n";

    return 0;
}

int canBook(vector< pair <int, int> > vect, int n, int numRooms) {
     
    //sort booking by smallest period
    sort(vect.begin(), vect.end(), sortByShortestPeriod); 

    // vector to track total number of rooms booked in each day
    int min =  getMinDate(vect, n);
    int max =  getMaxDate(vect, n);
    vector< pair <int, int> > bookedDays;

    for (int i=min; i <= max; i++) {
        bookedDays.push_back( make_pair(i,0));
    }
    
    // iterate from smallest booking to largest
    // and add days booked at each booking
    for(int i = 0; i < n; i++)  {
        
        int j = vect[i].first;
        
        while(j <= vect[i].second) {
            
            bookedDays[j-1].second = (bookedDays[j-1].second) + 1;

            if(bookedDays[j-1].second > numRooms) {
                cout << "Set of bookings provided cannot be accomodated\n" 
                     << "(day: " << bookedDays[j-1].first << " exceeds number of rooms)"  
                     << endl;
                return 0;
            }
            j++;
        }
    }
    
    cout << "Set of bookings provided can be accomodated" << endl;
    return 1;
}

int getMinDate(vector< pair <int, int> > bookingDates, int n) {
    
    int min = bookingDates[0].first;
    
    for (int i = 1; i < n; i++){
        if (bookingDates[i].first <  min) {
                min = bookingDates[i].first;
        } 
    }

    return min;
}

int getMaxDate(vector< pair <int, int> > bookingDates, int n) {
    int max = bookingDates[0].second;
    
    for (int i = 1; i < n; i++){
        if (bookingDates[i].second >  max) {
                max = bookingDates[i].second;
        } 
    }

    return max;
}

bool sortByShortestPeriod(const pair<int,int> &a, const pair<int,int> &b) 
{ 
    return ((a.second-a.first)+1 < (b.second-b.first)+1); 
}

void printVectorOfPairs(vector< pair <int, int> > bookingDates, int n) {
    
    for (int i=0; i<n; i++) 
    { 
        cout << bookingDates[i].first << " " << bookingDates[i].second << endl; 
    }
}