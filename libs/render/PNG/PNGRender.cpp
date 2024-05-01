/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "PNGRender.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <SFML/Graphics.hpp>

namespace RayTracer::Render {
    PNGRender::PNGRender() : _mutex(), _pixelsRendered(0)
    {
    }

    void PNGRender::renderTile(Scene& scene, int start, int end, int width, int height, int samplesPerPixel) {
        for (int y = start; y < end; ++y) {
            for (int x = 0; x < width; ++x) {
                Vector3D color(0, 0, 0);
                for (std::size_t k = 0; k < samplesPerPixel; k++) {
                    for (std::size_t l = 0; l < samplesPerPixel; l++) {
                        double u = (x + (k / static_cast<double>(samplesPerPixel))) / width;
                        double v = 1.0 - (y + (l / static_cast<double>(samplesPerPixel))) / height;
                        color += castRay(u, v, scene, 4);
                    }
                }
                {
                    std::lock_guard<std::mutex> lock(_mutex);
                    _image[y].push_back(color / (samplesPerPixel * samplesPerPixel));
                    _pixelsRendered++;
                }
            }
            {
                std::lock_guard<std::mutex> lock(_mutex);
                updateProgress(_pixelsRendered, width * height, "Rendering");
            }
        }
    }

    void PNGRender::render(Scene &scene) {
        Camera camera = *scene.getCamera();
        int height = camera.getResolution()._y;
        int width = camera.getResolution()._x;
        const int numThreads = std::thread::hardware_concurrency();
        const int tileSize = height / numThreads;
        std::vector<std::thread> threads;
        std::vector<int> threadProgress(numThreads, 0);
        int rowProgress = 0;

        sf::Image image;
        image.create(width, height);

        _image.resize(height);
        for (int i = 0; i < numThreads; ++i)
            threads.emplace_back(&PNGRender::renderTile, this, std::ref(scene), i * tileSize, (i + 1) * tileSize, width, height, _samples);
        for (auto& thread : threads)
            thread.join();
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Vector3D color = _image[y][x];
                int ir = static_cast<int>(color._x);
                int ig = static_cast<int>(color._y);
                int ib = static_cast<int>(color._z);
                sf::Color pixelColor(ir, ig, ib);
                image.setPixel(x, y, pixelColor);
            }
            rowProgress++;
            updateProgress(rowProgress, height, "Generating .png image");
        }
        image.saveToFile(_filename);
    }



    extern "C" std::unique_ptr<IRender> getEntryPoint()
    {
        return std::make_unique<PNGRender>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::RENDER);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("png");
    }
}
