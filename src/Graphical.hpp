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

enum mode {
    VIDEO = 0,
    MENU = 1
};

class Graphical {
    public:
        Graphical(char *path);
        ~Graphical();
        void run();
        void renderVideo();
        void renderMenu();
        void handleEvents();
        void handleMenuEvents();
        void handleVideoEvents();
    private:
        sf::RenderWindow window;
        sf::Clock clock;
        sf::Clock RenderClock;
        sf::Time time;
        sf::Font font;
        sf::Text text;
        sf::Event event;
        sf::Image image;
        sf::Sprite RenderedImage;
        sf::Texture RenderedTexture;
        std::unique_ptr<RayTracer::Scene> scene;
        RayTracer::LibLoader libLoader;
        std::unique_ptr<RayTracer::Render::IRender> render;
        mode currentMode;
        char *path;
        RayTracer::Camera *camera;
};

#endif /* !GRAPHICAL_HPP_ */