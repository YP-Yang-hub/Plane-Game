#include "renderer.h"
#include <iostream>
#include <string>
#include <thread>
#include "car.h"
#include "obstacle.h"
#include "mycontroller.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";


  }

  // Create Window
  sdl_window = SDL_CreateWindow("Duality Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
   sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Hardware Renderer could not be created.\n";
    //std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    std::cerr << "Using Software Renderer";
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
    if (nullptr == sdl_renderer){
       std::cerr << "Renderer could not be created.\n";
       std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
  }

  // creaete the textures that will holdl the images
  winSurface = SDL_GetWindowSurface(sdl_window);
  endbmp = SDL_LoadBMP("./flag.bmp");
  tex = SDL_CreateTextureFromSurface(sdl_renderer,endbmp);
  carBmp = SDL_LoadBMP("./plane.bmp");
  texCar = SDL_CreateTextureFromSurface(sdl_renderer,carBmp);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render( std::vector<Obstacle>& obst, std::vector<std::shared_ptr<Car>> carObjects) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect texRect;// hold the flag image
  texRect.x = 0;
  texRect.y = 0;
  texRect.w = 50;
  texRect.h = 50;

  //render the flag
  SDL_RenderCopy(sdl_renderer,tex,NULL, &texRect);
  SDL_RenderPresent(sdl_renderer);
  if(endbmp == NULL)std::cout<<"error rendering the flag";

 


  //render obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0xCC, 0xFF, 0xCC, 0xFF);
  for ( auto& m : obst){
    //std::cout << m <<std::endl;
    block.x = m.get_xpos();
    block.y = m.get_ypos();
    SDL_RenderFillRect(sdl_renderer, &block);
  }


  //render cars
  //SDL_SetRenderDrawColor(sdl_renderer, 0x99, 0x00, 0xFF, 0xFF);
  for ( auto c : carObjects){
    //std::cout << "car location =" <<c->get_xpos();
    block.x = c->get_xpos();
    block.y = c->get_ypos();
    //SDL_RenderFillRect(sdl_renderer, &block);

    block.h = 40;
    block.w = 40;
    SDL_RenderCopy(sdl_renderer,texCar,NULL, &block);
    SDL_RenderPresent(sdl_renderer);

  }


  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Your Score: [" + std::to_string(score) + "]  highst score = ["+ std::to_string(Mycontroller::highestScore) + "] FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
