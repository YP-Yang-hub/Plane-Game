#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "car.h"
#include "SDL.h"
#include <memory>

class Mycontroller {
public:

    static void HandleInput(bool &running, std::shared_ptr<Car> car1,std::shared_ptr<Car> car2)  ;
    static void control( std::shared_ptr<Car> car, SDL_Event& e);
    static bool switchCars ;
    static bool quit ;
    static int highestScore;
};



//bool Mycontroller::switchCars;

#endif