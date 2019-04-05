#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

/* ============= Problem  ==============
- Carrying a backpack that holds a limit amount of weight.
- Select the items that have the greatest values s.t. the 
  items you choose dont exceed a specific limited weight limit.
*/

using namespace std;

int max(int a, int b) { return (a > b)? a : b; } 
int knapsack(int weight[], int value[], int n, int W);
void printComputedValues(int a[][27],int n, int W);

int main()
{  
    int n = 10;
    int value[] = {210,220,180,120,160,170,90,40,60,10};
    int weight[] = {15,12,10,9,8,7,5,4,3,1};
    int W = 26;


    cout << "=========================================\n" 
         << "Maximum item value that can be carried " 
         << knapsack(weight, value, n, W)
         << "\n=========================================";

    return 0;
}

/* Returns the max value that can be put in knapsack
   given a set of items
   - n = number of items in the set
   - W = maximum weight that can be carried
   - value = how much each item is worth
   - weight = weights of each item
*/
int knapsack(int weight[], int value[], int n, int W) {

    int K[n+1][W+1]; // 2D array storing computed values

    for(int i = 0; i <= n; i++) { // num items
        for(int w = 0; w <= W; w++) { // weights
            if(i == 0 || w == 0) {
                K[i][w] = 0;
            } 
            else if( weight[i-1] <= w) {
                K[i][w] = max(value[i-1] + K[i-1][w-weight[i-1]],  K[i-1][w]);
            }
            else {
                K[i][w] = K[i-1][w];
            }
        }
    }

    // visualize table with computed values
    for(int i = 0; i <= n; i++) {
        cout << endl;
        for(int w = 0; w <= W; w++) {
            cout.width(4);
            cout << K[i][w];
        }
        cout << endl;
    }

    return K[n][W];
}