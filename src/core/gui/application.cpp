//
// Created by beckm on 1/20/2024.
//

#include "application.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_error.h>
#include <SDL_filesystem.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <memory>
#include <iostream>
#include "mathfuncs.h"

Application::Application(const std::string &title) {
    const unsigned int app_flags{SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER};
    if (SDL_Init(app_flags) != 0) {
        std::cout << SDL_GetError() << std::endl;
        m_exit_status = ExitStatus::FAILURE;
    }

    m_window = std::make_unique<Window>(Window::WindowSettings{title});
    m_world = std::make_unique<World>(9.8);
}

Application::~Application() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}

ExitStatus Application::run() {
    if (m_exit_status == ExitStatus::FAILURE) {
        return m_exit_status;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()};

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //Set up backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_window->get_window(), m_window->get_renderer());
    ImGui_ImplSDLRenderer2_Init(m_window->get_renderer());

    //Main Loop
    m_running = true;
    while (m_running) {
        m_runtimedata.updateClock();
        //Check for SDL Event
        SDL_Event event{};
        while (SDL_PollEvent(&event) == 1) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT) stop();
            if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(m_window->get_window())) {
                on_event(event.window);
            }
        }

        while (m_runtimedata.goPhysics()) {
            // if (m_world->contact_list.size() > 0) {
            //   m_scene->setActive(0);
            //   return;
            // }
//            m_world->worldStep(m_runtimedata.getDTFloat());
            m_runtimedata.updateInternalTimers();
        }

        //Start ImGui Frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (!m_minimize) {
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Exit", "Ctrl + Q")) {
                        stop();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("View")) {
                    ImGui::MenuItem("Engine View", nullptr, &m_show_main_panel);
                    ImGui::MenuItem("Tools Panel", nullptr, &m_show_tools_panel);
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }


            if (m_show_main_panel) {
                ImGui::Begin("Some panel", &m_show_main_panel);
                ImGui::Text("Hello World");
                ImGui::End();
            }

            if (m_show_tools_panel) {}

            ImGui::Render();
            SDL_SetRenderDrawColor(m_window->get_renderer(), 100, 100, 100, 255);
            SDL_RenderClear(m_window->get_renderer());
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(m_window->get_renderer());
        }
    }

    return m_exit_status;
}

void Application::on_event(const SDL_WindowEvent &event) {
    switch (event.event) {
        case SDL_WINDOWEVENT_CLOSE:
            return on_close();
        case SDL_WINDOWEVENT_MINIMIZED:
            return on_minimize();
        case SDL_WINDOWEVENT_SHOWN:
            return on_show();
        default:
            return;
    }
}

void Application::stop() { m_running = false; }

void Application::on_minimize() { m_minimize = true; }

void Application::on_show() { m_minimize = false; }

void Application::on_close() { stop(); }