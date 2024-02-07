#include <iostream> 
#include "subset.h"

int main() 
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
    return 0;
}
