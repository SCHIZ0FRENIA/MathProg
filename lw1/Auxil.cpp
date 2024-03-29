#include <iostream>
#include "Auxil.h"
#include <ctime>
#include <locale>

int main() 
{
    clock_t Time1, Time2;
    int t = 20;
    while (t--)
    {
        int CYCLE = 1000000  * ( 20 - t );
        double DoubleAverage = 0, IntAverage = 0;

        auxil::start();
        Time1 = clock();
        for ( int i = 0 ; i < CYCLE; i++)
        {
            IntAverage += (double) auxil::iget(-100, 100);
            DoubleAverage += auxil::dget(-100,100);
        }
        Time2 = clock();

        std::cout << "Int average    :   " << IntAverage / CYCLE << std::endl 
                << "Cycle number   :   " << CYCLE << std::endl
                << "Double average :   " << DoubleAverage / CYCLE << std::endl
                << "DeltaTime      :   " << (double) (Time2 - Time1) << std::endl
                << "               :   " << ((double) ( (double) (Time2 - Time1) ) / (double) CLOCKS_PER_SEC ) << std::endl << std::endl;
    }

    std::cout<< "Factorial" << std::endl;
    
    t = 10;
    while (t--)
    {
        int CYCLE = 10000000;

        Time1 = clock();
        
        for ( int i = 0 ; i < CYCLE; i++)
        {
            auxil::fact((10-t)*10);
        }

        Time2 = clock();

        std::cout << "Number   :   " << 10-t << std::endl
                << "DeltaTime      :   " << (double) (Time2 - Time1) << std::endl
                << "               :   " << ((double) ( (double) (Time2 - Time1) ) / (double) CLOCKS_PER_SEC ) << std::endl << std::endl;
    }

    return 0;
}