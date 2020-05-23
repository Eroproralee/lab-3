#include <iostream>
#include "svg.h"
#include <windows.h>
#include <stdio.h>
#include <sstream>
using namespace std;
string make_info_text( double top  ) {

stringstream buffer;
DWORD WINAPI GetVersion(void);
int printf(const char* format, ...);
DWORD CompVersion = GetVersion();
DWORD mask = 0x0000ffff;
DWORD version = CompVersion & mask;
DWORD platform = CompVersion >> 16;

// младщий
DWORD mask_major = 0b00000000'00000000'00000000'11111111;
DWORD version_major = version & mask_major;
// cтарший
DWORD version_minor = version >> 8 ;
//cout << version_major <<" " <<version_minor ;
DWORD build;
if ((CompVersion & 0x40000000) == 0) {

 build = platform;

cout << "build " << build ;
char system_dir[MAX_PATH];
GetSystemDirectory(system_dir, MAX_PATH);

//printf("System directory: %s", system_dir);
char Computername[MAX_PATH];
DWORD memory ;
memory =sizeof(Computername);
GetComputerName(Computername,&memory);

//printf("Computer name : %s", Computername);
const auto TEXT_LEFT = 20;
int X=TEXT_LEFT ;
    buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")  "<<'\n' ;
    buffer << "Computer Name:" <<  Computername;
return buffer.str();
}

}
void svg_text_histogram(string buffer,double top,double left)
{

 cout<<"'>"<<buffer <<  "<text x='" << left << "' y='"<<top+10<<"'>";
}
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end()
{
    cout << "</svg>\n";

}
void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline <<"'>" <<text <<"</text>";

}
void svg_rect(double x, double y, double width, double height,string stroke,string fill)
{
    cout << "<rect x='"<<x<< "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}
void svg_line(double x1,double y1,double x2,double y2,double length_ch,double length_pr,string stroke_1)
{
    cout << "<line x1='"<<x1<<"' y1='"<<y1<<"' x2='"<<x2<<"' y2='"<<y2<<"' stroke='"<<stroke_1<<"' stroke-dasharray='"<<10<<" "<<10<<"' />";
}

void show_histogram_svg(const vector<size_t>& bins  ,  double length_ch , double  length_pr )
{
    size_t lenght = 0 ;
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    double top = 0;
    svg_begin(400, 300);
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    if ( max_count < SCREEN_WIDTH - 4 - 1 )
    {

        for (size_t bin : bins)
        {
            size_t height = bin;
            if (scaling_needed)
            {
                const double scaling_factor = (double)MAX_ASTERISK / max_count;
                 double  height = (size_t)(bin * scaling_factor);

            }

            double bin_width = BLOCK_WIDTH * height;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"blue","#aaffaa");

            if ( lenght < bin_width)
                lenght = bin_width ;

            top += BIN_HEIGHT;
        }
svg_line(BLOCK_WIDTH,top ,TEXT_WIDTH+lenght+5,top ,length_ch,length_pr,"red");
svg_line(BLOCK_WIDTH ,0 ,BLOCK_WIDTH ,top ,length_ch,length_pr,"red");
// ëåâàÿ ÷àñòü
svg_line(TEXT_WIDTH+lenght+5,0 ,TEXT_WIDTH+lenght+5 ,top ,length_ch,length_pr,"red");
//
svg_line(BLOCK_WIDTH,0,TEXT_WIDTH+lenght+5,0,length_ch,length_pr,"red");

string buffer;
    buffer=make_info_text(top);
    cout <<endl;
    svg_text_histogram(buffer,top,TEXT_LEFT);
    svg_end();


    svg_end();
    }

    else
    {
//(SCREEN_WIDTH - 3 - 1 - 2*2) * (static_cast<double>(bins[i]) / max4ucel)
        for ( int j =0 ; j < bins[j] ; j++ )
        {
            size_t height = bins[j];

            if (scaling_needed)
            {
                const double scaling_factor = (double)MAX_ASTERISK / max_count;
                height = (size_t)((SCREEN_WIDTH-30-2*2)*bins[j] * scaling_factor/max_count);
            }

            const double bin_width = BLOCK_WIDTH * height;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[j]));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"blue","#aaffaa");

            if ( lenght < bin_width)
                lenght = bin_width ;

            top += BIN_HEIGHT;
        }

svg_line(BLOCK_WIDTH,top ,TEXT_WIDTH+lenght+5,top ,length_ch,length_pr,"red");
svg_line(BLOCK_WIDTH ,0 ,BLOCK_WIDTH ,top ,length_ch,length_pr,"red");
// ëåâàÿ ÷àñòü
svg_line(TEXT_WIDTH+lenght+5,0 ,TEXT_WIDTH+lenght+5 ,top ,length_ch,length_pr,"red");
//
svg_line(BLOCK_WIDTH,0,TEXT_WIDTH+lenght+5,0,length_ch,length_pr,"red");
    }
svg_text(TEXT_LEFT , top+30 , make_info_text(top)  ) ;
string buffer;
    buffer=make_info_text(top);
    cout <<endl;
    svg_text_histogram(buffer,top,TEXT_LEFT);
    svg_end();

}

