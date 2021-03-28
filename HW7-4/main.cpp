//
//  main.cpp
//  HW7-4
//
//  Created by Alyaev Roman on 29.03.2021.
//

#include <iostream>
#include <chrono>
#include <algorithm>
#include <execution>
#include <vector>
#include <random>

template<typename Container, class Algorithm, class Functor>
void time_of_work(Container v, Algorithm algorithm, Functor function)
{
    auto begin = std::chrono::system_clock::now();
    
    algorithm(v, std::begin(v), std::end(v), function);
    
    auto end = std::chrono::system_clock::now();
    
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    std::cout << "Time of work: " << elapsed.count() << " nanoseconds" << std::endl;
}

int main(int argc, const char * argv[])
{
    std::vector< int > v(10);
    
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution< int > uni(1, 100);
    for(auto & element: v)
        element = uni(mersenne);
    
    std::cout << "'Accumulate' algorithm:" << std::endl << "Not parallel --- ";
    time_of_work(v, std::accumulate(std::begin(v), std::end(v), 0, [](int mult, int elem){return mult *= elem;}), [](int mult, int elem){return mult *= elem;});
    
    std::cout << "Parallel --- ";
    time_of_work(v, std::accumulate(std::execution::par, std::begin(v), std::end(v), 0, [](int mult, int elem){return mult *= elem;}), [](int mult, int elem){return mult *= elem;});
    std::cout << "=====================================" << std::endl;

    std::cout << "'For each' algorithm:" << std::endl << "Not parallel --- ";
    time_of_work(v, std::for_each(std::begin(v), std::end(v), [](auto & element){element += 11;}), [](auto & element){element += 11;});
    
    std::cout << "Parallel --- ";
    time_of_work(v, std::for_each(std::execution::par, std::begin(v), std::end(v), [](auto & element){element += 11;}), [](auto & element){element += 11;});
    std::cout << "=====================================" << std::endl;

    std::cout << "'Transform' algorithm:" << std::endl << "Not parallel --- ";
    time_of_work(v, std::transform(std::begin(v), std::end(v), std::begin(v), [](auto & element){element += 11;}), [](auto & element){element += 11;});
    
    std::cout << "Parallel --- ";
    time_of_work(v, std::transform(std::execution::par, std::begin(v), std::end(v), std::begin(v), [](auto & element){element += 11;}), [](auto & element){element += 11;});
    std::cout << "=====================================" << std::endl;

    return 0;
}
