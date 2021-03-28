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

template < typename Iterator, class Functor >
struct for_each_block
{
    void operator()(Iterator begin, Iterator end, Functor function)
    {
        std::for_each(begin, end, function);
    }
};

template<typename Iterator, class Functor>
int parallel_for_each(Iterator begin, Iterator end, Functor function, int number_of_threads)
{
    const std::size_t length = std::distance(begin, end);
    const std::size_t block_size = length / number_of_threads;
    
    std::vector < std::thread > threads(number_of_threads);
    
    Iterator block_start = begin;
    
    for (auto i = 0; i < number_of_threads; ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);

            threads[i] = std::thread(
                for_each_block < Iterator, Functor > (),
                block_start, block_end, std::ref(function));

            block_start = block_end;
        }
    
    for_each_block < Iterator, Functor > ()(block_start, end, function);
    
    std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join));
    
    return 0;
}

int main(int argc, const char * argv[])
{
    std::vector< int > vector(20);
    
    std::iota(std::begin(vector), std::end(vector), 11);
    
    std::cout << "Here is our data:" << std::endl;
    
    int counter = 0;
    for(auto & element: vector)
    {
        std::cout << element << " ";
        
        ++counter;
        if(counter % 4 == 0)
            std::cout << std::endl;
    }
    
    std::cout << "==========================================" << std::endl << "Let's use the parallel for_each algorithm" << std::endl;
    
    int number_of_threads = 0;
    std::cout << "Enter the number of threads: ";
    std::cin >> number_of_threads;
    
    parallel_for_each(std::begin(vector), std::end(vector), [](auto & element){element += 9;}, number_of_threads);
    
    std::cout << "Our new data:" << std::endl;
    for(auto & element: vector)
    {
        std::cout << element << " ";
        
        ++counter;
        if(counter % 4 == 0)
            std::cout << std::endl;
    }
    
    return 0;
}
