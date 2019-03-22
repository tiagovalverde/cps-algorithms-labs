#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std::chrono;

using namespace std;

float linearPower(float x, int y);
float divideAndConquerPower(float x, int y);
void printResult(float z, float x, int y, string runningTimeType);
void isExponentNegative(float &x, int &y);

static bool PRINT_TIME_COMPLEXITY = false;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Missing parameters: provide base(x) and exponent(y)" << endl;
        cout << "Example: ./lab2 2 8" << endl;
        return 1;
    }

    // assuming correct parameters are given
    float x = atof(argv[1]);
    int y = atoi(argv[2]);

    isExponentNegative(x, y);

    auto start = system_clock::now();
    float linearResult = linearPower(x, y);
    auto stop = system_clock::now();
    auto duration_ms = duration_cast<nanoseconds>(stop - start);
    auto duration_sec = duration_cast<seconds>(stop - start);
    
    printResult(linearResult, x, y, "Linear time");

    auto start2 = system_clock::now();
    float lognResult = divideAndConquerPower(x, y);
    auto stop2 = system_clock::now();
    auto duration2_ms = duration_cast<nanoseconds>(stop2 - start2);
    auto duration2_sec = duration_cast<seconds>(stop2 - start2);
    
    printResult(lognResult, x, y, "Log N time");

    if(PRINT_TIME_COMPLEXITY) {
        cout << "===============\nTime Comlexity for each algorithm:\n";
        cout << "Linear time: " << duration_ms.count() << " nanoseconds (" << duration_sec.count() << " seconds)" << endl;
        cout << "Log N time:     " << duration2_ms.count() << " nanoseconds (" << duration2_sec.count() << " seconds)" << endl;
    }
    
    return 0;
}

/* Time complexity: O(n)
 * Linear (Iterative)
 */
float linearPower(float x, int y)
{
    float result = 1;
    for (int i = 1; i <= y; i++)
    {
        result *= x;
    }
    return result;
}

/* Time complexity: O(log n)
 * Divide and Conquer
 * Number of multiplications reduced comparing to linearPow fn
*/
float divideAndConquerPower(float x, int y)
{
    float result = 1;
    // base case: a^0 = 1
    if (y == 0)
    {
        return 1;
    }
    result = divideAndConquerPower(x, y / 2);
    // even power
    if ((y % 2) == 0)
    {
        return (result * result);
    }
    // odd power
    else
    {
        return x * result * result;
    }
}

void printResult(float z, float x, int y, string runningTimeType)
{
    cout << runningTimeType << " pow(" << x << "," << y << ") = " << z << endl;
}

void printTimeComplexity() {
    
}

/* if expoenent provided is negative this function
 * will invert the base(x) to 1/x
 * and will turn the exponent to positive
*/
void isExponentNegative(float &x, int &y)
{
    //exponent is negative
    if (y < 0)
    {
        y = -y;    // turn exponent to positive
        x = 1 / x; // invert base to 1/x
    }
}
