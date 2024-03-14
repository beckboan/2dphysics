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
//#include "imguifiledialog.h"

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

    void handleLevelLoader() const;

    std::unique_ptr<Scene> scene{nullptr};
    std::unique_ptr<Engine> engine{nullptr};

private:
    ExitStatus status{ExitStatus::SUCCESS};
    std::unique_ptr<Window> window{nullptr};


    bool running{true};
    bool minimize{true};

    bool show_main_panel{true};

    bool show_tools_panel{true};
    bool engine_active{true};

    bool show_log_panel{false};
};


#endif//APPLICATION_H
