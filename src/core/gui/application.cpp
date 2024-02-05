//
// Created by beckm on 1/20/2024.
//

#include "application.h"
#include "mathfuncs.h"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_filesystem.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <memory>

Application::Application(const std::string &title) {
    const unsigned int app_flags{SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER};
    if (SDL_Init(app_flags) != 0) {
        std::cout << SDL_GetError() << std::endl;
        m_exit_status = ExitStatus::FAILURE;
    }

    m_window = std::make_unique<Window>(Window::WindowSettings{title});
    m_world = std::make_unique<World>(9.8);
    m_scene = std::make_unique<ImGuiScene>();
}

Application::~Application() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}


void Application::addTestParams() const {
    vec2d position = vec2d(0.0, 0.0);
    float density = 1000.0;

    std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50), vec2d(0, 50), vec2d(75, 100)};

    std::vector<vec2d> box_verts = {vec2d(0, 0), vec2d(100, 0), vec2d(0, 100), vec2d(100, 100)};

    std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20),
                                      vec2d(-10, 5)};
    std::vector<vec2d> verticies_3 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20)};

    m_world->addCircle(10, vec2d(0, 50), 500, false);
    //    m_world->addCircle(10, vec2d(5, 30), 1000, false);
    //    m_world->addCircle(10, vec2d(-5, 55), 1000, false);
    //    m_world->addCircle(10, vec2d(0, 90), 1000, false);
    //    m_world->addPoly(verticies_2, vec2d(0, -35), density, false);
    //    m_world->addPoly(verticies_2, vec2d(0, 60), density, false);
    //    m_world->addPoly(verticies_2, vec2d(0, 90), density, false);
    //    m_world->addPoly(verticies_2, vec2d(0, 120), density, false);
    m_world->addEdge(vec2d(-200, -50), vec2d(500, -50));
    m_world->addEdge(vec2d(-200, -50), vec2d(-200, 500));
    m_world->addEdge(vec2d(500, -50), vec2d(500, 500));
}


void Application::updateEnginePanel() {
    if (m_show_main_panel) {
        ImVec2 screen_size = ImGui::GetIO().DisplaySize;
        float menu_bar_height = ImGui::GetFrameHeight();
//        ImGui::SetNextWindowPos(ImVec2(0, menu_bar_height));
//        ImGui::SetNextWindowSize(ImVec2(screen_size.x, screen_size.y - menu_bar_height));

        ImGui::Begin("Engine Panel", &m_show_main_panel, ImGuiWindowFlags_NoCollapse);
        //                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        //                             ImGuiWindowFlags_NoCollapse
        m_scene->m_hw_x = screen_size.x / 2;
        m_scene->m_hw_y = (screen_size.y - menu_bar_height) / 2;
        m_scene->drawImGuiObjects(m_world->getBodies());
        ImGui::End();
    }
}


ExitStatus Application::run() {
    if (m_exit_status == ExitStatus::FAILURE) {
        return m_exit_status;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()};

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //Set up backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_window->get_window(), m_window->get_renderer());
    ImGui_ImplSDLRenderer2_Init(m_window->get_renderer());

    addTestParams();

    bool first_loop = true;

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
            m_world->worldStep(m_runtimedata.getDTFloat());
            m_runtimedata.updateInternalTimers();
        }

        if (!m_minimize) {

            //Start ImGui Frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);

            ImGui::Begin("Root", nullptr, window_flags);

//            ImGuiDockNode *main_node = nullptr;

            if (first_loop) {
                ImGuiID main_node_ID = ImGui::GetID("MainDock");
                ImGui::DockBuilderRemoveNode(main_node_ID);
                ImGui::DockBuilderAddNode(main_node_ID, ImGuiDockNodeFlags_None);

                ImGui::DockBuilderSetNodeSize(main_node_ID, ImGui::GetMainViewport()->WorkSize);
                ImGui::DockBuilderSetNodePos(main_node_ID, ImGui::GetMainViewport()->WorkPos);

                ImGuiID dock_main_id = main_node_ID;
                ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr,
                                                                   &dock_main_id);
                ImGui::DockBuilderDockWindow("Engine Panel", dock_main_id);
                ImGui::DockBuilderDockWindow("Tools Panel", dock_left_id);

                ImGui::DockBuilderFinish(dock_main_id);
                first_loop = false;
            }

            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = ImGui::GetID("MainDock");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            ImGui::End();

            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Exit", "Ctrl + Q")) {
                        stop();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("View")) {
                    ImGui::MenuItem("Engine Panel", nullptr, &m_show_main_panel);
                    ImGui::MenuItem("Tools Panel", nullptr, &m_show_tools_panel);
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            updateEnginePanel();

            if (m_show_tools_panel) {
                ImGui::Begin("Tools Panel", &m_show_tools_panel);
                ImGui::End();
            }

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
