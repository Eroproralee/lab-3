#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double> input_numbers( istream& in ,  size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

vector <size_t>  make_histogram(const vector<double> &numbers,size_t bin_count)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    double min;
    double max;
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count,0);
    for (double number : numbers)
    {
        size_t bin;
        bin = (number - min) / (max - min) * bin_count;
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }

    return bins;
}
    int main()
    {
        double length_ch,length_pr;
        size_t number_count;
        cerr << "Enter number count: ";
        cin >> number_count;
        const auto numbers = input_numbers(cin ,number_count);
        size_t bin_count;
        cerr << "Enter column count: ";
        cin >> bin_count;
        double min, max;
        find_minmax(numbers,min,max);
        const auto bins = make_histogram(numbers, bin_count);
        show_histogram_svg(bins,bin_count,length_ch,length_pr);
        return 0;
    }
