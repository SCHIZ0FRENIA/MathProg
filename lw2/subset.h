#pragma once

namespace subset
{
    struct subset
    {
        public:
            short n, sn;
            subset(short n)
            {
                this -> n = n;
                this -> sbset = new short[n];
                this -> reset(); 
            };
            
            void reset()
            {
                this -> sn = 0;
                this -> mask = 0;
            };

            short getfirst()
            {
                int buff = this -> mask;
                this -> sn = 0;
                for(short i = 0; i < n; i++)
                {
                    if (buff & 0x1) this -> sbset[ this -> sn++ ] = i;
                    buff >>= 1;
                }
                return this -> sn;
            }

            short getnext()
            {
                int rc = -1;
                this -> sn = 0;
                if (++this -> mask < this -> count()) rc = getfirst();
                return rc;
            }

            short ntx(short i)
            {
                return this -> sbset[i];
            };

            unsigned int count ()
            {
                return (unsigned int) (1<<this -> n);
            }
        private: 
            short *sbset;
            unsigned int mask;
    };
}