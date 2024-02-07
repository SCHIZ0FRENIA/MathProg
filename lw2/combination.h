#pragma once 
namespace combinations
{
    struct Combinations
    {
        public:
            short m, n;
            Combinations(short n, short m)
            {
                this -> n = n;
                this -> m = m;
                this -> sbset = new short[m+2];
                this -> reset();
            }
            
            void reset()
            {
                // this -> nc = 0;
                for(int i = 0; i < this -> m; i++) this -> sbset[i] = i; 
                this -> sbset[m] = this -> n;
                this -> sbset[m+1] = 0;
            };

            short getfirst()
            {
                return (this -> n >= this -> m) ? this -> m : -1;
            };

            short getnext()
            {
                short rc = getfirst();

                if (rc > 0)
                {
                    short j;
                    for (j = 0; this->sbset[j]+1 == this->sbset[j+1]; ++j) 
                        this->sbset[j] = j;
                    if (j >= this->m) rc = -1;
                    else {
                        this->sbset[j]++;
                        // this->nc++;
                    };
                }

                return rc;
            };

            short ntx(short i)
            {
                return this -> sbset[i];
            };
        private:
            short *sbset;
    };
}