//
// Created by beckm on 1/20/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <string>

class Window {
public:
    struct WindowSettings {
        std::string title;
        int width{1280};
        int height{720};
    };

    explicit Window(const WindowSettings &settings);

    ~Window();

    Window(const Window &) = delete;

    Window(Window &&) = delete;

    Window &operator=(Window other) = delete;

    Window &operator=(Window &&other) = delete;

    [[nodiscard]] SDL_Window *get_window() const;

    [[nodiscard]] SDL_Renderer *get_renderer() const;

private:
    SDL_Window *sdl_window{nullptr};
    SDL_Renderer *sdl_renderer{nullptr};
};


#endif //WINDOW_H
