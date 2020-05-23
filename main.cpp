#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
#include <stdio.h>

using namespace std;
string
make_info_text( DWORD version_major , DWORD version_minor , DWORD build ) {
stringstream buffer;

buffer << "Windows v" << version_major << "." << version_minor <<" " << "build(" << build << ")" ;
return buffer.str();
}
struct Input {
    vector<double> numbers;
    size_t bin_count;
};
vector<double>
input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in , bool prompt ) {
    Input data;
if ( prompt == true ){
    cerr << "Enter number count: ";
}
    size_t number_count;
    cin >> number_count;

   if ( prompt == true ){ cerr << "Enter numbers: ";
   }
    data.numbers = input_numbers(in, number_count);
 cerr << "Enter bin ncount: ";
    size_t bin_count;
    cin >> bin_count;
    data.bin_count = bin_count  ;

    return data;
}


vector <size_t>  make_histogram(struct Input input)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    double min;
    double max;
    find_minmax(input,min,max);
    vector<size_t> bins(input.bin_count,0);
    for (double number : input.numbers)
    {
        size_t bin;
        bin = (number - min) / (max - min) * input.bin_count;
        if (bin == input.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }

    return bins;
}
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}
 Input download(const string& address)
 {
     stringstream buffer;
     curl_off_t speed;
     CURL* curl =curl_easy_init();
        CURLcode res;
        CURLcode downl;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        downl= curl_easy_getinfo(curl,CURLINFO_SPEED_DOWNLOAD_T,speed);
        if(res!=CURLE_OK)
        {
            cout<<curl_easy_strerror(res)<<endl;
            cerr<<"Download speed %"<<speed<<"bytes/sec\n";
            exit(1);
        }
        curl_easy_cleanup(curl);
     return read_input(buffer,false);
 }
    int main(int argc, char* argv[])
    {


        Input input ;
         if(argc>1)
    {
        input = download(argv[1]);
    }
    else
    {
        input=read_input(cin,true);
    }

        double length_ch,length_pr;
    const auto bins = make_histogram(input);

        show_histogram_svg(bins,length_ch,length_pr );
        return 0;
    }
