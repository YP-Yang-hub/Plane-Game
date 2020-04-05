#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>

class Randomizer

{
private:
    /* data */
public:
    template<typename T>
    static T genRand(T min, T max);
  
  
};
template<typename T>
T Randomizer::genRand(T min, T max){

    std::random_device dev;
    std::mt19937 eng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(min,max);
    return distribution(eng);
}


#endif