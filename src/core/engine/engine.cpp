#include "engine.h"
#include <yaml-cpp/yaml.h>

Engine::Engine() {
    world = std::make_unique<World>(9.8);
//    addTestParams();
    addLevelParams("../../../scenes/template.yaml");
}

void Engine::clear() const {
    world->contact_list.clear();
    world->clearBodies();
}

void Engine::run() {
    runtimedata.updateClock();
    while (runtimedata.goPhysics()) {
        world->worldStep(runtimedata.getDTFloat());
        runtimedata.updateInternalTimers();
    }
}

void Engine::addTestParams() const {

    vec2d position = vec2d(0.0, 0.0);
    float density = 1000.0;

    std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50), vec2d(0, 50), vec2d(75, 100)};

    std::vector<vec2d> box_verts = {vec2d(0, 0), vec2d(100, 0), vec2d(0, 100), vec2d(100, 100)};

    std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20),
                                      vec2d(-10, 5)};
    std::vector<vec2d> verticies_3 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20)};

    world->addCircle(10, vec2d(0, 50), 500, false);
    //    world->addCircle(10, vec2d(5, 30), 1000, false);
    //    world->addCircle(10, vec2d(-5, 55), 1000, false);
    //    world->addCircle(10, vec2d(0, 90), 1000, false);
    //    world->addPoly(verticies_2, vec2d(0, -35), density, false);
    //    world->addPoly(verticies_2, vec2d(0, 60), density, false);
    //    world->addPoly(verticies_2, vec2d(0, 90), density, false);
    //    world->addPoly(verticies_2, vec2d(0, 120), density, false);
    world->addEdge(vec2d(-200, -50), vec2d(500, -50));
    world->addEdge(vec2d(-200, -50), vec2d(-200, 500));
    world->addEdge(vec2d(500, -50), vec2d(500, 500));
}

void Engine::refreshLevelParams() {
    clear();
    addLevelParams("../../../scenes/template.yaml");
}

void Engine::addLevelParams(const std::string& filename){
    ///Check if the file is a .yaml file before loading
    if (filename.substr(filename.find_last_of('.') + 1) != "yaml") {
        std::cerr << "File is not a .yaml file" << std::endl;
        return;
    }

    try {
        YAML::Node config = YAML::LoadFile(filename);

        // Check if the file is empty
        if (config.IsNull()) {
            std::cerr << "Error: File is empty" << std::endl;
            return;
        }

        level_name = config["scene_info"]["name"].as<std::string>();
        std::cout << "Level name: " << level_name << std::endl;

        // Check if the file has a "bodies" key and if it is empty or not
        if (config["bodies"].IsNull()) {
            std::cerr << "Error: No bodies or boundaries found in the file" << std::endl;
            if (config["boundaries"].IsNull()) {
                std::cerr << "Error: No boundaries found in the file" << std::endl;
                return;
            }
        }

        for (const auto& body : config["bodies"]) {
            auto shape_type = body["shape"].as<std::string>();
            std::cout << "Body type: " << shape_type << std::endl;

            if (shape_type == "circle") {
                auto temp_radius = body["radius"].as<float>();
                auto temp_position = vec2d(body["position"][0].as<float>(), body["position"][1].as<float>());
                auto temp_density = body["density"].as<float>();
                std::cout << temp_density << std::endl;
                bool temp_static;
                if (body["static"].as<std::string>() == "false") {
                    temp_static = false;
                } else {
                    temp_static = true;
                }
                world->addCircle(temp_radius, temp_position, temp_density, temp_static);
            }
            else if (shape_type == "polygon") {
                auto temp_position = vec2d(body["position"][0].as<float>(), body["position"][1].as<float>());
                auto temp_density = body["density"].as<float>();
                bool temp_static;
                if (body["static"].as<std::string>() == "false") {
                    temp_static = false;
                } else {
                    temp_static = true;
                }
                std::vector<vec2d> temp_verts;
                for (const auto& vertex : body["points"]) {
                    temp_verts.emplace_back(vertex[0].as<float>(), vertex[1].as<float>());
                }
                world->addPoly(temp_verts, temp_position, temp_density, temp_static);
            }

        }

        for (const auto& boundary : config["boundaries"]) {
            auto temp_start = vec2d(boundary["start"][0].as<float>(), boundary["start"][1].as<float>());
            auto temp_end = vec2d(boundary["end"][0].as<float>(), boundary["end"][1].as<float>());
            world->addEdge(temp_start, temp_end);
        }


    } catch (const YAML::Exception& e) {
        std::cerr << "Error: Exception while loading the YAML file - " << e.what() << std::endl;
    }
}
