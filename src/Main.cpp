/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <iostream>
#include "LibLoader.hpp"
#include "Parser.hpp"
#include "Exceptions.hpp"

void displayHelp()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tSCENE_FILE\tfile describing the scene" << std::endl;
}

int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw RayTracer::MainException("Invalid number of arguments");
        std::string arg1 = av[1];
        if (arg1 == "-h" || arg1 == "--help") {
            displayHelp();
            return 0;
        }
        RayTracer::LibLoader libLoader;
        libLoader.loadPlugins();
        RayTracer::Parser parser(av[1], libLoader);
        parser.parse();
        std::unique_ptr<RayTracer::Scene> scene = std::move(parser.getScene());
        std::unique_ptr<RayTracer::Render::IRender> render = std::move(parser.getRender());
        render->render(*scene);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 84;
    }
}
