/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include "Graphical.hpp"
#include "../libs/render/PNG/PNGRender.hpp"

Graphical::Graphical(char *path)
{
    window.create(sf::VideoMode(1920, 1080), "Raytracer");

    font.loadFromFile("assets/font.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    RenderedImage.setScale(4, 4);
    this->path = path;
    currentMode = mode::VIDEO;
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
    text.setString("Samples: " + std::to_string(render->getSamples()));
    text.setPosition(0, 0);
    window.draw(text);
    text.setString("Max Depth: " + std::to_string(render->getMaxDepth()));
    text.setPosition(0, 50);
    window.draw(text);
    window.display();
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
        }
    }
    (currentMode == mode::VIDEO) ? handleVideoEvents() : handleMenuEvents();
}

void Graphical::handleMenuEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (render->getSamples() < 16)
            render->setSamples(render->getSamples() + 1);
        sf::sleep(sf::milliseconds(100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (render->getSamples() > 1)
            render->setSamples(render->getSamples() - 1);
        sf::sleep(sf::milliseconds(100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (render->getMaxDepth() < 16)
            render->setMaxDepth(render->getMaxDepth() + 1);
        sf::sleep(sf::milliseconds(100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (render->getMaxDepth() > 1)
            render->setMaxDepth(render->getMaxDepth() - 1);
        sf::sleep(sf::milliseconds(100));
    }
}

void Graphical::handleVideoEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        Point3D pos = camera->getOrigin();
        camera->setOrigin(pos._x + 100, pos._y, pos._z);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Point3D pos = camera->getOrigin();
        camera->setOrigin(pos._x - 100, pos._y, pos._z);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Point3D pos = camera->getOrigin();
        camera->setOrigin(pos._x, pos._y + 100, pos._z);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        Point3D pos = camera->getOrigin();
        camera->setOrigin(pos._x, pos._y - 100, pos._z);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Point3D pos = camera->getOrigin();
        camera->setOrigin(pos._x, pos._y, pos._z + 100);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        Point3D pos = camera->getOrigin();
        camera->setRotation(0, 0, 0);
        camera->setOrigin(pos._x, pos._y, pos._z - 100);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        double fov = camera->getFov();
        camera->setFov(fov + 10);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        double fov = camera->getFov();
        camera->setFov(fov - 10);
        image = render->renderVideo(*scene, *camera);
        RenderedTexture.update(image);
    }
}

void Graphical::run()
{
    libLoader.loadPlugins();
    RayTracer::Parser parser(path, libLoader);
    parser.parse();
    scene = std::move(parser.getScene());
    render = parser.getRender();
    render->setSamples(1);
    render->setMaxDepth(0);
        
    camera = scene->getCamera();
    camera->setResolution(1920 / 4, 1080 / 4);

    image = render->renderVideo(*scene, *camera);

    RenderedTexture.create(1920, 1080);
    RenderedImage.setTexture(RenderedTexture);
    RenderedTexture.update(image);

    Point3D pos = camera->getOrigin();
    
    while (window.isOpen()) {
        if (clock.getElapsedTime().asSeconds() > 0.3) {
            clock.restart();
        }
        handleEvents();
        (currentMode == mode::VIDEO) ? renderVideo() : renderMenu();
    }
}