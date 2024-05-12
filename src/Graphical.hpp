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

namespace RayTracer::Graphical {
    const std::string vertexShader = R"(
        void main()
        {
            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
        }
    )";

    const std::string gaussianBlurFragmentShader = R"(
        uniform sampler2D texture;
        uniform vec2 offset;

        #define KERNEL_SIZE 9

        void main()
        {
            vec2 texCoord = gl_TexCoord[0].xy;
            vec4 color = texture2D(texture, texCoord) * 0.0625; // Center weight

            for (int i = -KERNEL_SIZE/2; i <= KERNEL_SIZE/2; ++i)
            {
                float weight = 1.0 / float(KERNEL_SIZE);
                vec2 blurOffset = offset * float(i);
                color += texture2D(texture, texCoord + blurOffset) * weight;
            }

            gl_FragColor = color;
        }
    )";
    class Graphical {
        public:
            Graphical(char *path, int quality);
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
}

#endif /* !GRAPHICAL_HPP_ */