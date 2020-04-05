#include "mycontroller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"


bool Mycontroller::switchCars = true;
bool Mycontroller::quit = false;
int Mycontroller::highestScore =0;

void Mycontroller::HandleInput(bool &running, std::shared_ptr<Car> car1, std::shared_ptr<Car> car2)  {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
        running = false;
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        //std::cout << "Mycontroller::switchCars ="<< Mycontroller::switchCars << std::endl;
          if(Mycontroller::switchCars){
            Mycontroller::control(car1, e);
          }else{
            Mycontroller::control(car2, e);
          }
  }
}
}

void Mycontroller::control( std::shared_ptr<Car>  car,  SDL_Event& e){


      switch (e.key.keysym.sym) {
        case SDLK_UP:
          car->setAxis("vertical");
          car->setDirection(-1);
          break;

        case SDLK_DOWN:
          car->setAxis("vertical");
          car->setDirection(1);   
          break;

        case SDLK_LEFT:
          car->setAxis("horizontal");    
          car->setDirection(-1);
          break;

        case SDLK_RIGHT:
          car->setAxis("horizontal");
          car->setDirection(1);
        
        break;        
        
        case SDLK_RCTRL:
          Mycontroller::switchCars = !Mycontroller::switchCars;
        break;
                
        case SDLK_LCTRL:
          Mycontroller::switchCars = !Mycontroller::switchCars;
        break;
      }
    }
  
