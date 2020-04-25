#include <iostream>
#include "test1.h"
#include <cassert>
#include "histogram.h"
#include "svg.h"
const auto BIN_HEIGHT = 30;
using namespace std;
void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_similar ()
{
    double min = 0;
    double max = 0;
    find_minmax({2, 2, 2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_one_number()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min ==0);
    assert(max == 0);
}
void test_lishnya_liniya()
{
    double top = 0;
    show_histogram_svg({1,2,3},3,20,10);
    assert (top=BIN_HEIGHT);
}
void test_bins0()
{
    double top=0;
    show_histogram_svg({},3,20,10);
    assert (top=0);
}
