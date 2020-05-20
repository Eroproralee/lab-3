#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct Input
{vector<double>numbers;
size_t bin_count;
};
void find_minmax(struct Input data , double& min, double& max)
    {
    if (data.numbers.size()==0)
    {
        return;
    }
    else
    {

    min = data.numbers[0];
    max = data.numbers[0];
    for (double number : data.numbers)
        {
        if (number < min)
            {
            min = number;
        }
        if (number > max)
        {
            max = number;
        }
        }
    }
    }
