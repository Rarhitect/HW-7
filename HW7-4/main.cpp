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

int main(int argc, const char * argv[])
{
    std::vector< int > v(10);
    
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution< int > uni(1, 100);
    for(auto & element: v)
        element = uni(mersenne);
    
    //---------------------------------------------------------------------------------------------
    std::cout << "'Accumulate' algorithm:" << std::endl << "Not parallel --- ";
    
    auto begin_1 = std::chrono::system_clock::now();
    
    std::accumulate(std::begin(v), std::end(v), 0, [](int mult, int elem){return mult *= elem;});
    
    auto end_1 = std::chrono::system_clock::now();
    auto elapsed1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_1 - begin_1);
    
    std::cout << "Time of work: " << elapsed1.count() << " nanoseconds" << std::endl;
    
    std::cout << "Parallel --- ";
    
    auto begin_2 = std::chrono::system_clock::now();
    
    std::accumulate(std::execution::par, std::begin(v), std::end(v), 0, [](int mult, int elem){return mult *= elem;});
    
    auto end_2 = std::chrono::system_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_2 - begin_2);
    
    std::cout << "Time of work: " << elapsed2.count() << " nanoseconds" << std::endl;
    
    std::cout << "=====================================" << std::endl;
    
    //---------------------------------------------------------------------------------------------
    
    std::cout << "'For each' algorithm:" << std::endl << "Not parallel --- ";
    
    auto begin_3 = std::chrono::system_clock::now();
    
    std::for_each(std::begin(v), std::end(v), [](auto& elem){elem += 11;});
    
    auto end_3 = std::chrono::system_clock::now();
    auto elapsed3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_3 - begin_3);
    
    std::cout << "Time of work: " << elapsed3.count() << " nanoseconds" << std::endl;
    
    std::cout << "Parallel --- ";
    
    auto begin_4 = std::chrono::system_clock::now();
    
    std::accumulate(std::execution::par, std::begin(v), std::end(v), [](auto& elem){elem += 11;});
    
    auto end_4 = std::chrono::system_clock::now();
    auto elapsed4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_4 - begin_4);
    
    std::cout << "Time of work: " << elapsed4.count() << " nanoseconds" << std::endl;
    
    std::cout << "=====================================" << std::endl;
    
    //---------------------------------------------------------------------------------------------

    std::cout << "'Transform' algorithm:" << std::endl << "Not parallel --- ";
    
    auto begin_5 = std::chrono::system_clock::now();
    
    std::transform(std::begin(v), std::end(v), std::begin(v), [](auto& elem){elem += 11;});
    
    auto end_5 = std::chrono::system_clock::now();
    auto elapsed5 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_5 - begin_5);
    
    std::cout << "Time of work: " << elapsed5.count() << " nanoseconds" << std::endl;
    
    std::cout << "Parallel --- ";
    
    auto begin_6 = std::chrono::system_clock::now();
    
    std::accumulate(std::execution::par, std::begin(v), std::end(v), std::begin(v), [](auto& elem){elem += 11;});
    
    auto end_6 = std::chrono::system_clock::now();
    auto elapsed6 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_6 - begin_6);
    
    std::cout << "Time of work: " << elapsed6.count() << " nanoseconds" << std::endl;
    
    std::cout << "=====================================" << std::endl;
    
    return 0;
}
