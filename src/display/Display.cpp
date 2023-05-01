// builds upon: https://github.com/udacity/CppND-Capstone-Snake-Game

#include <iostream>
#include "Display.h"
#include "SDL.h"

Display::Display(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) 
{
          // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Sensor Simulation", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Display::~Display() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Display::VisualizeMeasurement(vector<vector<double>>& measurement) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect block;
  block.w = 2;
  block.h = 2;

  for(auto& point : measurement){
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = int(point[0]);
    block.y = int(point[1]);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  SDL_RenderPresent(sdl_renderer);
}

void Display::UpdateWindowTitle(string s) {
  std::string title{"Measurements: "};
}

