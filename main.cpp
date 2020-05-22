#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <sstream>
#include <string>
using namespace std;
int printf(const char* format, ...);

string
make_info_text() {
    stringstream buffer;
    string Windows = "Windows v6.3" ;
    string name = "Egor" ;
    buffer << "versin " << Windows ;
    buffer << "name " << name ;
    // TODO: получить имя компьютера, записать в буфер.
    return buffer.str();
}
struct Input {
    vector<double> numbers;
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

vector<size_t> make_histogram(struct Input data)
{   double min=0;
    double max=0;
    find_minmax(data,min,max);
    vector<size_t> bins(data.bin_count);
    for (double number : data.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
Input read_input(istream& in, bool prompt)
{
Input data;
if(prompt == true )
{cerr << "Enter number count: ";
cerr << "Enter bin_count : " ;
}
size_t number_count;
cin >> number_count;
data.numbers = input_numbers(cin,number_count);
size_t bin_count;
cin >>data.bin_count;
return data;
}
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
 {

     stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    const char* item = reinterpret_cast<const char*>(items);
    size_t data_size;

    data_size=item_size* item_count;


    buffer->write(item, data_size);
    return data_size;

}
Input download(const string& address)
 {
     stringstream buffer;
 CURL *curl = curl_easy_init();

    CURLcode res;
  curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
  res = curl_easy_perform(curl) ;
  if(res!=0)
    {
    cout<<curl_easy_strerror(curl_easy_perform(curl));
    exit(1);
    }
    curl_easy_cleanup(curl);

    return read_input(buffer, false) ;
}



int
main(int argc, char* argv[])
{
    const char* name = "Commander Shepard";
int year = 2154;
printf("%s was born in %d.\n", name, year);
printf("n = %08x\n", 0x1234567);
return 0 ;
Input input;
    if(argc>1)
    {
     input = download(argv[1]);
    }
    else
    {
     input=read_input(cin,true);
    }
    curl_global_init(CURL_GLOBAL_ALL);
    double length_pr , length_ch ;
const auto data=read_input(cin, true);
const auto bins =make_histogram(data);
show_histogram_svg(bins , length_pr , length_ch );
return 0;
}
