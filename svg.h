#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <vector>
#include <string>
#include <windows.h>
#include <stdio.h>

using namespace std;

DWORD WINAPI GetVersion(void);

string make_info_text( double top  );
string make_info_text1();
string make_info_text2();
void svg_text1(double left, double baseline, string text);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,string stroke = "black",string fill = "black");
void svg_line(double x1,double y1,double x2,double y2,double length_ch,double length_pr,string stroke_1 = "red");
string make_info_text( double top  ) ;
void show_histogram_svg(const vector<size_t>& bins  ,   double length_pr , double  length_ch) ;




#endif // SVG_H_INCLUDED
