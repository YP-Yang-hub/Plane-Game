#include <iostream>
#include <sstream>

#include "game.h"
#include "renderer.h"
#include "mycontroller.h"
#include <fstream>
#include <condition_variable>
#include <mutex>
#include <exception>

int level = 1;
int score = 0;

std::mutex mtx;
std::condition_variable con_var;

//Read the previous result
void getHighestScore(int& score){
  int r{0};
  std::string  input;
  std::fstream previous_result;
 std::fstream result;
 while(!Mycontroller::quit){

  std::unique_lock<std::mutex> lck(mtx);
  con_var.wait(lck );

  previous_result.open("result.txt", std::ios::in);
  if(!previous_result){
    std::cerr << "\n Can't read the previous record \n" ;
    previous_result.clear();
  } else{
    try{  
      std::getline(previous_result,input);
      r = std::stoi(input);
      std::cout<<"\nDone reading from file\n";

      Mycontroller::highestScore = r;
    }catch(std::exception& e){
      std::cout << e.what();
    }

   previous_result.close();
  }

 
bool newScore = r < score;
// std::cout << "\nnew score is " << newScore <<std::endl;
// std::cout << "r = " << r << std::endl;

std::cout << "score = " << score << std::endl;

  if(newScore){
    result.open("result.txt", std::ios::out);
    if(!result){
      std::cerr << "\nfailed to create ..file not available\n" ;
    }
    else{
      result << score;
      std::cout<<"\nwrote into file\n";
    }
    result.close();
  }


  }
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::thread t(getHighestScore, std::ref(score));
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);


  Game game;
  while (true){
    score = game.GetScore();
    
    con_var.notify_all();
    game.Run( renderer, kMsPerFrame, level);
    std::cout << "finished level = " << level << std::endl;
    level++;
    if(Mycontroller::quit)break;
  }
  

  con_var.notify_all();
  t.join();


  std::cout << "Game has terminated successfully!\n";
  return 0;
}