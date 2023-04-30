#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include <SDL.h>

using namespace std;

class Display
{
public:
    Display(const std::size_t screen_width, const std::size_t screen_height,
            const std::size_t grid_width, const std::size_t grid_height);
    ~Display();
    void VisualizeMeasurement(vector<vector<double>> &);
    void UpdateWindowTitle(string);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif