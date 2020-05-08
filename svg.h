#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <string>
#include <vector>
using namespace std;
void svg_rect(const auto x, double y,const auto width, double height);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left,double baseline, string text);

void show_histogram_svg(const vector<size_t>& bins);
void show_histogram_text(const vector<size_t>& bins);

#endif // SVG_H_INCLUDED
