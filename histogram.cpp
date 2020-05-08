#include "histogram.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct Input
{vector<double>numbers;
size_t bin_count;
};
void find_minmax(struct Input Input,double& min,double& max)
{
    int q=Input.numbers.size();
    if(q!=0)
    {
        min = Input.numbers[0];
        max = Input.numbers[0];
        for (double number : Input.numbers)
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
