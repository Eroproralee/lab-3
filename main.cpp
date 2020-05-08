#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;
vector<double> input_numbers(istream&in,size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(size_t count,const vector<double>& numbers)
{   double min=0;
    double max=0;
    find_minmax(numbers,min,max);
    vector<size_t> bins(count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * count);
        if (bin == count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
struct Input
{vector<double>numbers;
size_t bin_count;
};
Input read_input(istream& in)
{
 Input data;
 cerr << "Enter number count: ";
 size_t number_count;
 cin >> number_count;
 cerr <<"Enter numbers:";
 data.numbers = input_numbers(in,number_count);
 size_t bin_count;
 cin >>data.bin_count;
 return data;
 }
int main()
{
    double length_ch,length_pr;
    Input data;
    data=read_input(cin);
    const auto bins =make_histogram(data.bin_count,data.numbers);

    show_histogram_svg(bins,data.bin_count,length_ch,length_pr);
    return 0;
}
