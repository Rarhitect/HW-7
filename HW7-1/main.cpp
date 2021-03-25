//
//  main.cpp
//  HW7-1
//
//  Created by Alyaev Roman on 25.03.2021.
//

#include <iostream>
#include <thread>
#include <random>

double not_parallel_pi(int number_of_points)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<double> uni(0.0, 1.0);
    
    int couter_included = 0; //счетчик попавших в окружность точек
    
    for(auto i = 0; i < number_of_points; ++i)
    {
        double x = uni(mersenne);
        double y = uni(mersenne);
        
        if( (x * x + y * y) <= 1 )
            couter_included++;
    }
    
    double pi = 4 * static_cast<double>(couter_included) / static_cast<double>(number_of_points);
    
    return pi;
}

int main(int argc, const char * argv[])
{
    int number_of_points;
    std::cout << "Insert the number of points: ";
    std::cin >> number_of_points;
    
    std::cout << "Not parallel pi: " << not_parallel_pi(number_of_points) << std::endl;
    
    return 0;
}
