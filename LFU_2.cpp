#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "Cache_2.h"


template <typename T>
struct page_t
{
    T id;
    int freq;
};

void count_hits();
void test_cache(std::ifstream& fin, std::ofstream& fout);

int main()
{
    std::ifstream in_tests;
    std::ofstream out_tests;

    in_tests. open("Input_Tests.txt");
    out_tests.open("Output_Tests.txt");

    //test_cache(in_tests, out_tests);

    count_hits();
}

void count_hits()
{
    size_t _size;
    int num_elts, hits = 0;
    std::cin >> _size >> num_elts;
    cache_t <page_t <int> > test_cache {_size};
    for (int i = 0; i < num_elts; ++i)
    {
        page_t <int> page;
        std::cin >> page.id;
        page.freq = 1;
        if (test_cache.lookup(&page))
            hits += 1;
    }
    std::cout << "Hits: " << hits << "\n";
}

void test_cache(std::ifstream& fin, std::ofstream& fout)
{
    size_t _size;
    int num_elts, hits;
    for(int i = 0; i < 5; ++i)
    {
        hits = 0;
        fin >> _size >> num_elts;
        cache_t <page_t <int> > test_cache {_size};
        fout << "Cache steps:\n";
        for (int i = 0; i < num_elts; ++i)
        {
            page_t <int> page;
            fin >> page.id;
            page.freq = 1;
            if (test_cache.lookup(&page))
                hits += 1;
            test_cache.print_list(fout);
        }
        fout << "Hits: " << hits << "\n\n\n";
    }
}
