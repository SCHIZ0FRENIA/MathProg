#include <iostream> 
#include <vector> 
#include "subset.h"
#include "combination.h"
#include "permutation.h"
#include "accomodation.h"
#include "salesman.h"
#include <ctime>
#define N (sizeof(AA)/2)
#define M 3


void SubsetDemo() 
{
    char testSet[][2] = {"1", "2", "3", "4"};
    for (int i = 0; i < sizeof(testSet)/2; i++)
    {
        std::cout << testSet[i] << ((i < sizeof(testSet)/2-1)?", ":" ");  
    }

    std::cout << std::endl << "All subsets :  " << std::endl;

    subset::subset SubSet(sizeof(testSet)/2);

    int n = SubSet.getfirst();

    while (n >= 0)
    {
        std::cout << "{ ";

        for (int i = 0; i < n; i++)
            std::cout<< testSet[SubSet.ntx(i)]<<((i< n-1)?", ":" ");   
        
        std::cout << "}" << std::endl;
        n = SubSet.getnext();
    };

    std::cout << std::endl << "Subset amount  :  " << SubSet.count() << std::endl;
}

void CombinationDemo() 
{
    char Combination[][2] = { "1", "2", "3", "4", "5"};

    std::cout << "Set  :  " << std::endl; 

    std::cout<<"{ ";
    for (int i = 0; i < sizeof(Combination)/2; i++) 
         std::cout<<Combination[i]<<((i< sizeof(Combination)/2-1)?", ":" ");  
    std::cout<< "}" << std::endl;

    combi::Combination xc(sizeof(Combination)/2, 3);
    std::cout << "Cominations from " << xc.n << " to " << xc.m << std::endl;

    int n = xc.getfirst();
    while ( n >= 0 )
    {
        std::cout << "{ ";
        
        for (int i = 0; i < n; i++)
            std::cout<< Combination[xc.ntx(i)]<<((i< n-1)?", ":" ");  

        std::cout << "}" << std::endl;

        n = xc.getnext();    
    }

    std::cout<<std::endl<<"Combinations amount: " << xc.count() <<std::endl; 
}

void PermutationDemo() 
{
    char  AA[][2]= {"1", "2", "3", "4"}; 
    std::cout << std::endl << "Permutations  :  ";

    std::cout<<"{ ";
    for (int i = 0; i < sizeof(AA)/2; i++) 
         std::cout<<AA[i]<<((i< sizeof(AA)/2-1)?", ":" ");  
    std::cout<<"}";

    std::cout<<std::endl<<"Permutation generation  :  ";
    permutation::permutation p(sizeof(AA)/2);               
    int  n  = p.getfirst();   

    while (n >= 0)
    {
        std::cout << std::endl << p.np << ": { ";
        for (int i = 0; i < p.n; i++)  
            std::cout<<AA[p.ntx(i)]<<((i< p.n-1)?", ":" ");   
        std::cout<<"}";

        n = p.getnext();                      
    };

     std::cout << std::endl << "Permutation amount  : " << p.count() << std::endl;  
}

void AccomodationDemo() 
{
    char  AA[][2]= {"4", "3", "2", "1"}; 
    std::cout<<std::endl<<"Accomodation Generator: ";

    std::cout<<"{ ";
    for (int i = 0; i < N; i++) 
        std::cout<<AA[i]<<((i< N-1)?", ":" ");  
    std::cout<<"}";

    std::cout<<std::endl<<"ГAccomodations from   "<< N <<" of "<<M;
    accomodation::accomodation s(N,M);
    int  n  = s.getfirst();      
    while (n >= 0)
    {
        std::cout << std::endl << s.na << ": { ";

        for (int i = 0; i < 3; i++)  
            std::cout<<AA[s.ntx(i)]<<((i< n-1)?", ":" "); 

        std::cout<<"}";

        n = s.getnext();    
    };

    std::cout<<std::endl<<"Acomadations amount  :  "<<s.count()<<std::endl;
}

void SalesmanDemo()
{ 
    int Length = 10;
    srand ( (unsigned int) time(NULL));

    int d[10][10];

    for( int i = 0; i < 10; i++)
    {
        for(int o = 0; o < 10; o++)
        {
            d[i][o] = rand() % 290 + 10;
        }
    }

    d[1][4] = INT_MAX;
    d[4][0] = INT_MAX;
    d[3][8] = INT_MAX;

    int r[10];  
    int s = salesman (Length, (int*)d, r); 
    std::cout<<std::endl<<"-- Salesman task -- ";
    std::cout<<std::endl<<"-- Cities amount: "<<Length;
    std::cout<<std::endl<<"-- Matrix: ";
    for(int i = 0; i < Length; i++)
    { 
        std::cout<<std::endl;
        for (int j = 0; j < Length; j++)
            if (d[i][j]!= INT_MAX) std::cout<<d[i][j]<< " ";
            else std::cout<<"INF"<<" ";
    }
    std::cout<<std::endl<<"-- Shoterst length: "; 
    for(int i = 0; i < Length; i++) std::cout<<r[i]<<"-->"; 
    std::cout<<0;
    std::cout<<std::endl<<"-- Path length     : "<<s;  
    std::cout<<std::endl;
}

void SalesmanTimeDemo()
{

    clock_t Time1, Time2;
    int CYCLE = 100;

    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 6;
        srand ( (unsigned int) time(NULL));

        int d[6][6];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[6];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';
 
    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 7;
        srand ( (unsigned int) time(NULL));

        int d[7][7];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[7];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';
    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 8;
        srand ( (unsigned int) time(NULL));

        int d[8][8];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[8];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';
    
    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 9;
        srand ( (unsigned int) time(NULL));

        int d[9][9];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[9];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';
    
    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 10;
        srand ( (unsigned int) time(NULL));

        int d[10][10];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[10];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';
    
    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 11;
        srand ( (unsigned int) time(NULL));

        int d[11][11];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[11];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';
    
    Time1 = clock();

    for (int o = 0; o < CYCLE; o++)
    {
        int Length = 12;
        srand ( (unsigned int) time(NULL));

        int d[12][12];

        for( int i = 0; i < Length; i++)
        {
            for(int o = 0; o < Length; o++)
            {
                d[i][o] = rand() % 290 + 10;
            }
        }

        int r[12];
        int s = salesman (Length, (int*)d, r);
    }

    Time2 = clock();

    std::cout << Time2 - Time1 << ' ';    
}

int main()
{
    // SubsetDemo();
    // CombinationDemo();
    // PermutationDemo();
    // AccomodationDemo();
    // SalesmanDemo();
    // SalesmanTimeDemo();
    return 0;
}