#pragma once 

#include "combination.h"
#include "permutation.h"

namespace accomodation
{
    struct  accomodation
    {
        short  n, m, *sset;  
        combi::Combination  *cgen;
        permutation::permutation *pgen;

        accomodation(short n, short m)
        {
            this->n = n;
            this->m = m;
            this->cgen = new combi::Combination(n,m);  
            this->pgen = new permutation::permutation(m);  
            this->sset = new short[m];
            this->reset();  
        };

        void reset()
        {
            this->na = 0;
            this->cgen->reset();     
            this->pgen->reset();     
            this->cgen->getfirst();
        }; 

        short getfirst()
        {
            short rc = (this->n >= this->m)?this->m:-1;

            if (rc > 0) 
            {
                for (int i = 0; i <= this->m; i++) 
                this->sset[i] = this->cgen->sbset[this->pgen->ntx(i)];
            };

            return rc; 
        };
  
        short getnext()
        {
            short rc;
            this->na++;
            if ((this->pgen->getnext())> 0) rc = this->getfirst();
            else  if ((rc = this->cgen->getnext())> 0) 
                {this->pgen->reset();  rc = this->getfirst();};  
            return rc;  
        };
 
        short ntx(short i)
            { return this->sset[i];  };   

        unsigned __int64 fact(unsigned __int64 x){ return (x == 0)?1:(x*fact(x-1));};

        unsigned __int64 na;
        unsigned __int64 count() {
            return (this->n >= this->m)?
                fact(this->n)/fact(this->n - this->m):0;  
        };
    };
}
