/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include "Graphical.hpp"
#include "../libs/render/PNG/PNGRender.hpp"

namespace RayTracer::Graphical {
    Graphical::Graphical(char *path, int quality)
    {
        window.create(sf::VideoMode(1920, 1080), "Raytracer");

        font.loadFromFile("assets/font.ttf");
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        this->path = path;
        currentMode = mode::MENU;

        libLoader.loadPlugins();
        RayTracer::Parser parser(path, libLoader);
        parser.parse();
        scene = std::move(parser.getScene());
        render = parser.getRender();
        render->setSamples(4);
        render->setMaxDepth(4);
        render->setQuality(quality);
        camera = scene->getCamera();
        camera->setResolution(1920 / render->getQuality(), 1080 / render->getQuality());

        image = render->renderVideo(*scene, *camera);

        RenderedTexture.create(1920 / render->getQuality(), 1080 / render->getQuality());
        RenderedTexture.update(image);
        RenderedImage.setTexture(RenderedTexture);
        RenderedImage.setScale(render->getQuality(), render->getQuality());
    }

    Graphical::~Graphical()
    {
        window.close();
    }

    void Graphical::renderVideo()
    {
        window.clear(sf::Color::Black);
        window.draw(RenderedImage);
        time = clock.getElapsedTime();
        text.setString("FPS: " + std::to_string(1.0f / time.asSeconds()));
        clock.restart();
        text.setPosition(0, 0);
        window.draw(text);
        text.setPosition(500, 0);
        text.setString("X: " + std::to_string(camera->getOrigin()._x) + " Y: " + std::to_string(camera->getOrigin()._y) + " Z: " + std::to_string(camera->getOrigin()._z));
        window.draw(text);
        window.display();
    }

    void Graphical::renderMenu()
    {
        window.clear(sf::Color::Black);
        sf::RenderTexture backgroundTexture;
        backgroundTexture.create(1920, 1080);
        backgroundTexture.clear();
        backgroundTexture.draw(RenderedImage);
        backgroundTexture.display();
        sf::Shader blurShader;
        blurShader.loadFromMemory(vertexShader, gaussianBlurFragmentShader);
        blurShader.setUniform("texture", backgroundTexture.getTexture());
        blurShader.setUniform("offset", sf::Vector2f(1.f / 1920, 0.f));
        sf::Sprite blurredBackground(backgroundTexture.getTexture());
        window.draw(blurredBackground, &blurShader);
        sf::RectangleShape MenuRect(sf::Vector2f(600, 500));
        MenuRect.setFillColor(sf::Color::White);
        MenuRect.setPosition(1920 / 2 - 300, 1080 / 2 - 250);
        window.draw(MenuRect);

        text.setFillColor(sf::Color::Black);
        text.setString("Quality: " + std::to_string(render->getQuality()));
        int textWidth = text.getLocalBounds().width;
        text.setPosition(1920 / 2 - textWidth / 2, 1080 / 2);
        window.draw(text);
        text.setString("Max Depth: " + std::to_string(render->getMaxDepth()));
        textWidth = text.getLocalBounds().width;
        text.setPosition(1920 / 2 - textWidth / 2, 1080 / 2 - 50);
        window.draw(text);
        text.setString("Press ESC to return to video mode");
        textWidth = text.getLocalBounds().width;
        text.setPosition(1920 / 2 - textWidth / 2, 1080 / 2 - 200);
        window.draw(text);
        window.display();
        text.setFillColor(sf::Color::White);
    }

    void Graphical::handleEvents()
    {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
                    (currentMode == mode::VIDEO) ? currentMode = mode::MENU : currentMode = mode::VIDEO;
                }
                if (currentMode == mode::VIDEO)
                    handleVideoEvents();
            }
        }
    }

    void Graphical::handleVideoEvents()
    {
        if (event.key.code == sf::Keyboard::Q) {
            Point3D pos = camera->getOrigin();
            camera->setOrigin(pos._x + 100, pos._y, pos._z);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::D) {
            Point3D pos = camera->getOrigin();
            camera->setOrigin(pos._x - 100, pos._y, pos._z);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::S) {
            Point3D pos = camera->getOrigin();
            camera->setOrigin(pos._x, pos._y + 100, pos._z);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::Z) {
            Point3D pos = camera->getOrigin();
            camera->setOrigin(pos._x, pos._y - 100, pos._z);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::A) {
            Point3D pos = camera->getOrigin();
            camera->setOrigin(pos._x, pos._y, pos._z + 100);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::E) {
            Point3D pos = camera->getOrigin();
            camera->setRotation(0, 0, 0);
            camera->setOrigin(pos._x, pos._y, pos._z - 100);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::Up) {
            double fov = camera->getFov();
            camera->setFov(fov + 10);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
        if (event.key.code == sf::Keyboard::Down) {
            double fov = camera->getFov();
            camera->setFov(fov - 10);
            image = render->renderVideo(*scene, *camera);
            RenderedTexture.update(image);
        }
    }

    void Graphical::handleMenuEvents()
    {
        if (event.key.code == sf::Keyboard::Up) {
            if (render->getQuality() < 16)
                render->setQuality(render->getQuality() * 2);
        }
        if (event.key.code == sf::Keyboard::Down) {
            if (render->getQuality() > 1)
                render->setQuality(render->getQuality() / 2);
        }
        if (event.key.code == sf::Keyboard::Right) {
            if (render->getMaxDepth() < 16)
                render->setMaxDepth(render->getMaxDepth() + 1);
        }
        if (event.key.code == sf::Keyboard::Left) {
            if (render->getMaxDepth() > 1)
                render->setMaxDepth(render->getMaxDepth() - 1);
        }
    }

    void Graphical::run()
    {
        while (window.isOpen()) {
            handleEvents();
            (currentMode == mode::VIDEO) ? renderVideo() : renderMenu();
        }
    }
}
