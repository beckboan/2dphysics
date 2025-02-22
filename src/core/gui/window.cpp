//
// Created by beckm on 1/20/2024.
//
#include "window.h"
#include "SDL_render.h"
#include <iostream>

Window::Window(const Window::WindowSettings &settings) {
  // Set window flags and create window
  const auto window_init_flags{
      static_cast<SDL_WindowFlags>(SDL_WINDOW_RESIZABLE)};

  sdl_window = SDL_CreateWindow(settings.title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, settings.width,
                                settings.height, window_init_flags);

  // Set render flags and create rendering
  auto renderer_init_flags{
      static_cast<SDL_RendererFlags>(SDL_RENDERER_SOFTWARE)};
  // auto
  // renderer_init_flags{static_cast<SDL_RendererFlags>(SDL_RENDERER_PRESENTVSYNC
  // | SDL_RENDERER_ACCELERATED)};
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, renderer_init_flags);

  if (sdl_renderer == nullptr) {
    std::cout << "Error creating SDL_Renderer!" << std::endl;
  }
}

Window::~Window() {
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
}

SDL_Window *Window::get_window() const { return sdl_window; }

SDL_Renderer *Window::get_renderer() const { return sdl_renderer; }
