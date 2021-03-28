//
//  main.cpp
//  HW7-3
//
//  Created by Alyaev Roman on 28.03.2021.
//

#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

template<typename Iterator, class Functor>
void parallel_for_each(Iterator begin, Iterator end, Functor function, int number_of_threads)
{
    const std::size_t length = std::distance(begin, end);
    const std::size_t block_size = length / number_of_threads;
    
    Iterator here = begin;
    Iterator special_begin = begin;
    int summary = 0;
    
    for (auto i = 0; i < number_of_threads; ++i)
    {
        std::advance(here, block_size);
        
        std::future < int > here_result = std::async(parallel_for_each< Iterator, Functor >, special_begin, here, function);
        
        special_begin = here;
        
        summary += here_result.get();
    }
}

int main(int argc, const char * argv[])
{
    
    return 0;
}
