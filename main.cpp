#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
using namespace std;
struct Input
{vector<double>numbers;
size_t bin_count;
};
vector<double> input_numbers(istream&in,size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(struct Input Input)
{   double min=0;
    double max=0;
    find_minmax(Input,min,max);
    vector<size_t> bins(Input.bin_count);
    for (double number : Input.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * Input.bin_count);
        if (bin == Input.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
Input read_input(istream& in,bool prompt)
{
 Input data;
 if(prompt==1)
 {
     cerr << "Enter number count: ";
 }
 size_t number_count;
 cin >> number_count;
 if(prompt==1)
 {
     cerr <<"Enter numbers:";
 }
 data.numbers = input_numbers(in,number_count);
 size_t bin_count;
 if(prompt==1)
 {
  cerr <<"Enter bin_count";
 }
 cin>>bin_count;
 data.bin_count=bin_count;
 return data;
 }
int main(int argc,char*argv[])
{   if(argc>1)
    {   CURL* curl =curl_easy_init();
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        if(CURLE_OK==1)
        {
            cout<<curl_easy_strerror(curl_easy_perform(curl));
            exit(1);
        }
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
     return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    const auto Input=read_input(cin,true);
    const auto bins =make_histogram(Input);
    show_histogram_svg(bins);
    return 0;
}
