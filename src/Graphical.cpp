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
    texture.create(1920, 1080);
    sprite.setTexture(texture);
    sprite.scale(2, 2);
    font.loadFromFile("assets/font.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    this->path = path;
}

Graphical::~Graphical()
{
    window.close();
}

void Graphical::eventLoop()
{

}

void Graphical::run()
{
    RayTracer::LibLoader libLoader;
    libLoader.loadPlugins();
    RayTracer::Parser parser(path, libLoader);
    parser.parse();
    scene = std::move(parser.getScene());
    std::unique_ptr<RayTracer::Render::IRender> render = parser.getRender();
    render->setSamples(1);
    render->setMaxDepth(0);
    
    sf::Image image;
    sf::Sprite RenderedImage;
    sf::Texture RenderedTexture;
    
    //Camera
    RayTracer::Camera *camera = scene->getCamera();
    camera->setResolution(1920, 1080);
    camera->setFov(90);
    // camera->setOrigin(0, 0, 0);
    camera->setRotation(0, 0, 0);

    image = render->renderVideo(*scene, *camera);



    RenderedTexture.create(1920, 1080);
    RenderedImage.setTexture(RenderedTexture);
    RenderedTexture.update(image);

    Point3D pos = camera->getOrigin();

    
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();

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
                camera->setOrigin(pos._x, pos._y, pos._z - 100);
                image = render->renderVideo(*scene, *camera);
                RenderedTexture.update(image);
            }
        }
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

        


        // image = render->renderVideo(*scene, *camera);
        // RenderedTexture.update(image);
        // RenderedImage.setTexture(RenderedTexture);

        window.display();
        texture.update(image);
    }
}