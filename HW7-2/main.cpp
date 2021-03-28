//
//  main.cpp
//  HW7-2
//
//  Created by Alyaev Roman on 25.03.2021.
//

#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename T >
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T & result)
    {
        result = std::accumulate(first, last, result); // !
    }
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int number_of_threads)
{
    const std::size_t length = std::distance(first, last);

    if (!length)
        return init;

    const std::size_t block_size = length / number_of_threads;

    std::vector < T > results(number_of_threads);
    std::vector < std::thread > threads(number_of_threads);

    Iterator block_start = first;

    for (std::size_t i = 0; i < number_of_threads; ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        threads[i] = std::thread(
            accumulate_block < Iterator, T > (),
            block_start, block_end, std::ref(results[i])); // !

        block_start = block_end;
    }

    accumulate_block < Iterator, T > ()(block_start, last, results[number_of_threads - 1]);

    std::for_each(threads.begin(), threads.end(),
        std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, const char * argv[])
{
    std::vector < int > v(100);

    std::iota(v.begin(), v.end(), 1);

    int number_of_threads;
    std::cout << "Enter the number of threads: ";
    std::cin >> number_of_threads;
    
    std::cout << parallel_accumulate(std::begin(v), std::end(v), 0, number_of_threads) << std::endl;
    
    return 0;
}
