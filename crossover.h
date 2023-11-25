#ifndef CROSSOVER_H
#define CROSSOVER_H

#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

template<typename T>
class Crossover
{

    T max;
    T min;

public:
    Crossover(T max,T min)
    {
        this->max=max;
        this->min=min;
    }

    T random_val()
    {
        return std::rand()%(this->max-this->min) + this->min;
    }

    void fill(std::vector<T>& img,size_t size)
    {
        std::srand(time(NULL));

        for(std::size_t i=0;i<size;i++)
        {
            img.push_back(this->random_val());
        }
    }

    std::vector<T> cross(const std::vector<T>& A,const std::vector<T>& B)
    {
        std::vector<T> output;

        size_t total=std::min(A.size(),B.size());

        size_t chunk_size=total/4 + 1;

        auto A_iter=A.begin();
        auto B_iter=B.begin();

        while((A_iter<A.end())&&(B_iter<B.end()))
        {

            output.insert(output.begin(),A_iter,A_iter+chunk_size);
            output.insert(output.begin(),B_iter,B_iter+chunk_size);


            A_iter+=chunk_size;
            B_iter+=chunk_size;
        }

        return output;
    }

    void mutate(std::vector<T>& A)
    {
        std::size_t len=A.size();

        std::srand(time(NULL));

        std::size_t to_mutate=std::rand()%len;

        for(size_t i=0;i<to_mutate;++i)
        {
            size_t o=std::rand()%len;

            A[o]+=this->random_val();
        }
    }
};

#endif // CROSSOVER_H
