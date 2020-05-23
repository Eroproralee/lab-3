#include "histogram.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct Input
{vector<double>numbers;
size_t bin_count;
};
void find_minmax(struct Input input, double& min, double& max)
    {
    if (input.numbers.size()==0)
    {
        return;
    }
    else
    {

    min = input.numbers[0];
    max = input.numbers[0];
    for (double number : input.numbers)
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
