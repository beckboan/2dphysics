//
// Created by beckm on 1/20/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "scene.h"
#include "runtimedata.h"
#include "window.h"
#include "world.h"
#include <SDL.h>
#include <memory>
#include <string>
#include "engine.h"

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

    void updateEnginePanel();

    std::unique_ptr<Scene> m_scene{nullptr};
    std::unique_ptr<Engine> m_engine{nullptr};

private:
    ExitStatus m_exit_status{ExitStatus::SUCCESS};
    std::unique_ptr<Window> m_window{nullptr};

    bool m_running{true};
    bool m_minimize{true};
    bool m_show_main_panel{true};
    bool m_show_tools_panel{true};
    bool m_show_log_panel{false};
};


#endif//APPLICATION_H
