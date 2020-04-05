#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>
#include "car.h"
#include "mycontroller.h"
#include "randomizer.h"
#include "obstacle.h"
#include <string>


// Game::Game(std::size_t grid_width, std::size_t grid_height)
//     : engine(dev()),
//       random_w(0, static_cast<int>(grid_width)),
//       random_h(0, static_cast<int>(grid_height)) {
  
  
// }

void Game::Run( Renderer &renderer,
               std::size_t target_frame_duration, int level) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;


//---------Cars ---------------
  std::shared_ptr<Car> car1( new Car {470, 510, 640,-1, "horizontal"});
  std::shared_ptr<Car> car2 (new Car {605, 515, 640, -1, "vertical"});

  std::vector<std::thread> cars ;
  cars.emplace_back(std::thread(&Car::move, car1));
  cars.emplace_back(std::thread(&Car::move, car2));
  std::vector<std::shared_ptr<Car>> carObjects {car1,car2};
//-------------------------------



//--------Obstacles --------------
  std::vector<Obstacle> obstacles;

  for( int i = 0 ; i < level * 3; i++){
    int x = Randomizer::genRand(1,600);
    int y = Randomizer::genRand(1,600);
    int d = Randomizer::genRand(1,2);
    std::string direction = "vertical";

    if(d==1){
      direction = "horizontal";
    }
    //creating more obstacles (in every level)
    Obstacle obstacle {x,y, 600,1,direction,carObjects};
    obstacles.emplace_back(std::move(obstacle));
  }
  std::vector<std::thread> obstacleThreads;

  for ( auto& o : obstacles){
    obstacleThreads.emplace_back(std::thread(&Obstacle::move,&o));
  }
//-------------------------------



  while (running) {
    frame_start = SDL_GetTicks();

    // Input, [Update,] Render - the main game loop.
    //notice that the controller is automatically updating the object positions
    //so no need to create a method update()
    Mycontroller::HandleInput(running,car1,car2);

    
  // if cars are deactivated, then either reset or move to a new level
    if(car1->isActive()==false && car2->isActive() ==false){
       if(car1->get_success()==true && car2->get_success() ==true){
          running = false;
          score++;
          score *= level;
          for(auto& o : obstacles){
            o.deactivate();
          }
      }else{

      for(auto& c : cars){
        //std::cout <<"trying to join\n"<<std::endl;
        c.join();
        //std::cout <<"success  join\n"<<std::endl;
      }

      car1->set_xpos(500);
      car1->set_ypos(500);
      car2->set_xpos(450);
      car2->set_ypos(600);
      car1->set_active(true);
      car2->set_active(true);
       
      cars.pop_back();
      cars.pop_back();
       
      cars.emplace_back(std::thread(&Car::move, car1));
      cars.emplace_back(std::thread(&Car::move, car2));
      }

    }

    
    renderer.Render(obstacles, carObjects);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }


// make sure that all threads will stop and join
  for(auto& o : obstacles){
    o.deactivate();
  }
  
  car1->deactivate();
  car2->deactivate();

for( auto& t : cars){
  t.join();
}

for(auto& t : obstacleThreads){
  t.join();
}
}





int Game::GetScore() const { return score; }
