#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
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
 in >> number_count;
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
 in>>bin_count;
 data.bin_count=bin_count;
 return data;
 }
 size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
 {  stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    const char* char_items = reinterpret_cast<const char*>(items);
    size_t data_size;
    data_size=item_size* item_count;
    buffer->write(char_items, data_size);
    return data_size;
}
 Input download(const string& address)
 {
     stringstream buffer;
     CURL* curl =curl_easy_init();
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            cout<<curl_easy_strerror(curl_easy_perform(curl));
            exit(1);
        }
        curl_easy_cleanup(curl);
     return read_input(buffer,false);
 }

int main(int argc,char*argv[])
{   Input input;
    if(argc>1)
    {
     input = download(argv[1]);
    }
    else
    {
     input=read_input(cin,true);
    }
    const auto bins =make_histogram(input);
    show_histogram_svg(bins);
    return 0;
}


