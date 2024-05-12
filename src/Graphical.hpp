/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#ifndef GRAPHICAL_HPP_
#define GRAPHICAL_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "LibLoader.hpp"
#include "Parser.hpp"
#include "Exceptions.hpp"

class Graphical {
    public:
        Graphical(char *path);
        ~Graphical();
        void run();
        void eventLoop();
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Clock clock;
        sf::Time time;
        sf::Font font;
        sf::Text text;
        char *path;
        std::unique_ptr<RayTracer::Scene> scene;
};

#endif /* !GRAPHICAL_HPP_ */