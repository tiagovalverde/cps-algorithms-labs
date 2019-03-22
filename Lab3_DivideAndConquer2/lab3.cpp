#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std::chrono;
using namespace std;

static bool PRINT_TIME_COMPLEXITY = false;
static int ARRAY_SIZE = 4;
static int NUM_INT_TO_MULTIPLY = 2;

long multiply4(string a, string b);
long multiply3(string a, string b);
void normalizeInteger(long n, string &num);

int main(int argc, char *argv[])
{
    string multiplyList[ARRAY_SIZE][NUM_INT_TO_MULTIPLY] = {  
        {"1234", "4321"},
        {"110", "220"},
        {"14589", "912"},
        {"7777777", "88888888"}
    };

    for(int i = 0; i < ARRAY_SIZE; i++) {

        auto start = system_clock::now();
        printf("%ld\n", multiply4(multiplyList[i][0], multiplyList[i][1]));
        auto stop = system_clock::now();
        auto duration_ms = duration_cast<nanoseconds>(stop - start);
        auto duration_sec = duration_cast<seconds>(stop - start);

        auto start2 = system_clock::now();
        printf("%ld\n", multiply3(multiplyList[i][0], multiplyList[i][1]));
        auto stop2 = system_clock::now();
        auto duration2_ms = duration_cast<nanoseconds>(stop2 - start2);
        auto duration2_sec = duration_cast<seconds>(stop2 - start2);

        if (PRINT_TIME_COMPLEXITY)
        {
            cout << "Time Comlexity for each algorithm:\n";
            cout << "multiply4: " << duration_ms.count() << " nanoseconds (" << duration_sec.count() << " seconds)" << endl;
            cout << "multiply3: " << duration2_ms.count() << " nanoseconds (" << duration2_sec.count() << " seconds)" << endl;
        }
        cout << "===============\n";
    }

    return 0;
}

/*
* Obvious Algorithm
* O(n^2)
* T(n) = 4T(n/2) + O(n)
*/
long multiply4(string a, string b)
{
    // int size
    long a_size = a.size();
    long b_size = b.size();
    // parse
    long int_a = atol(a.c_str());
    long int_b = atol(b.c_str());
    // check base case
    if (a_size == 0 || b_size == 0)
    {
        return 0;
    }
    // no dividing needed
    if (a_size == 1 || b_size == 1)
    {
        return int_a * int_b;
    }
    else
    {
        long n = max(a_size, b_size);
        if((n%2) != 0 ) {
            n++;
        }
        normalizeInteger(n, a);
        normalizeInteger(n, b);

        // split up 2 integers in half
        string a_left = a.substr(0, a.length() / 2);
        string a_right = a.substr(a.length() / 2);
        string b_left = b.substr(0, b.length() / 2);
        string b_right = b.substr(b.length() / 2);
        // keep multiplying down
        long x1 = multiply4(a_left, b_left);
        long x2 = multiply4(a_left, b_right);
        long x3 = multiply4(a_right, b_left);
        long x4 = multiply4(a_right, b_right);

        return x1 * pow(10, n) + (x2 + x3) * pow(10, n / 2) + x4;
    }
}

/*
* Karatsuba Algorithm
* O(n^1.585)
* T(n) = 3T(n/2) + O(n)
*/
long multiply3(string a, string b)
{
    // int size
    long a_size = a.size();
    long b_size = b.size();
    // parse
    long int_a = atol(a.c_str());
    long int_b = atol(b.c_str());
    // check base case
    if (a_size == 0 || b_size == 0)
    {
        return 0;
    }
    // no dividing needed
    if (a_size == 1 || b_size == 1)
    {
        return int_a * int_b;
    }
    else
    {
        long n = max(a_size, b_size);
        if((n%2) != 0 ) {
            n++;
        }
        normalizeInteger(n, a);
        normalizeInteger(n, b);

        string a_left = a.substr(0, a.length() / 2);
        string a_right = a.substr(a.length() / 2);
        string b_left = b.substr(0, b.length() / 2);
        string b_right = b.substr(b.length() / 2);

        string a_lr = to_string(atol(a_left.c_str()) + atoi(a_right.c_str()));
        string b_lr = to_string(atol(b_left.c_str()) + atoi(b_right.c_str()));

        long x1 = multiply3(a_left, b_left);
        long x2 = multiply3(a_lr, b_lr);
        long x3 = multiply3(a_right, b_right);

        return x1 * pow(10, n) + (x2 - x1 - x3) * pow(10, n / 2) + x3;
    }
}

/*
* Add leading 0's to the integer
*/
void normalizeInteger(long n, string &num) {
    if(num.size() < n) {
        int numLeadingZeros = n - num.size();
        for(int i = 0; i < numLeadingZeros; i++) {
            num = "0" + num;
        }
    }
}
