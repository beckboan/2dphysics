//
// Created by beckm on 1/20/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "imgui_scene.h"
#include "runtimedata.h"
#include "window.h"
#include "world.h"
#include <SDL.h>
#include <memory>
#include <string>

enum class ExitStatus : int {
    SUCCESS = 0,
    FAILURE = 1
};

class Application {
public:
    explicit Application(const std::string &title);

    ~Application();

    Application(const Application &) = delete;

    Application(Application &&) = delete;

    Application &operator=(Application other) = delete;

    Application &operator=(Application &&other) = delete;

    ExitStatus run();

    void stop();

    void on_event(const SDL_WindowEvent &event);

    void on_minimize();

    void on_show();

    void on_close();

    void addTestParams() const;

    void updateEnginePanel();

    std::unique_ptr<World> m_world{nullptr};
    std::unique_ptr<ImGuiScene> m_scene{nullptr};

private:
    ExitStatus m_exit_status{ExitStatus::SUCCESS};
    std::unique_ptr<Window> m_window{nullptr};
    RunTimeData m_runtimedata;

    bool m_running{true};
    bool m_minimize{true};
    bool m_show_main_panel{true};
    bool m_show_tools_panel{true};
};


#endif//APPLICATION_H
