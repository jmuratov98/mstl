#include <iostream>
#include <chrono>
#include <string>
#include <array>
#include <mstl/array.h>
#include "mstl/internal/config.h"


class Timer
{
public:
    Timer(const std::string& name)
        : m_name(name), m_start(std::chrono::high_resolution_clock::now())
    {}

    ~Timer() {
        auto now = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(now - m_start).count();
        
        // std::cout << m_name << ":\t\t" << us << "us" << std::endl;
        printf("%s:\t\t%llu us", m_name.c_str(), us);
    }

private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_start;
};

void test_array() {
    Timer t("test_array 10 elements");
    mstl::array<int, 5> a = { 0, 1, 2, 3, 4 };
    printf("a: [");
    for(size_t i = 0; i < a.size(); i++)
        printf("%d, ", a[i]);
    printf("]\n");

    a[0] = 5;
    printf("a: [");
    for(mstl::array<int, 5>::iterator it = a.begin(); it != a.end(); it++)
        printf("%d, ", *it);
    printf("]\n");
    
    a[2] = 3;
    printf("a: [");
    for(const int v : a)
        printf("%d, ", v);
    printf("]\n");

    int &front = a.front();
    int &back = a.back();

    printf("front: %i, back: %i\n", front, back);

    mstl::array<int, 5> b = {5, 4, 3, 2, 1};
    mstl::swap(a, b);
    printf("a: [");
    for(mstl::array<int, 5>::const_iterator cit = a.begin(); cit != a.end(); ++cit)
        printf("%d, ", *cit);
    printf("]\n");
    printf("b: [");
    for(mstl::array<int, 5>::const_iterator cit = b.begin(); cit != b.end(); ++cit)
        printf("%d, ", *cit);
    printf("]\n");

    a.swap(b);
    printf("a: [");
    for(mstl::array<int, 5>::const_iterator cit = a.begin(); cit != a.end(); ++cit)
        printf("%d, ", *cit);
    printf("]\n");
    printf("b: [");
    for(mstl::array<int, 5>::const_iterator cit = b.begin(); cit != b.end(); ++cit)
        printf("%d, ", *cit);
    printf("]\n");

#ifdef MSTL_CPP20
    int c[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto carray = mstl::to_array(c);
    printf("carray: [");
    for(mstl::array<int, 10>::const_iterator cit = carray.begin(); cit != carray.end(); ++cit)
        printf("%d, ", *cit);
    printf("]\n");
#endif

    printf("reverse iterator");
    printf("b: [");
    for(mstl::array<int, 5>::reverse_iterator rit = b.rbegin(); rit != b.rend(); ++rit)
        printf("%d, ", *rit);
    printf("]\n");
}

int main(int argc, char **argv) {
    test_array();
    return 0;
}
