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

    PNGRender::~PNGRender()
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
                    _mutex.unlock();
                }
            }
            {
                std::lock_guard<std::mutex> lock(_mutex);
                updateProgress(_pixelsRendered, width * height, "Rendering");
                _mutex.unlock();
            }
        }
    }

    void PNGRender::render(Scene &scene) {
        Camera camera = *scene.getCamera();
        int height = camera.getResolution()._y;
        int width = camera.getResolution()._x;
        std::vector<std::thread> threads;
        int numThreads = 1;
        sf::Image image;
        log("\033[1;31mStarting threads\033[0m");
        for (std::size_t i = 1; i <= std::thread::hardware_concurrency(); i++) {
            log("\033[33mStarting thread n°" + std::to_string(i) + "\033[0m");
            if (height % i == 0)
                numThreads = i;
        }
        const int tileSize = height / numThreads;
        log("Number of threads: " + std::to_string(numThreads) + ", tile size: " + std::to_string(tileSize));
        int rowProgress = 0;

        image.create(width, height);
        log("Creating image of size " + std::to_string(width) + "x" + std::to_string(height));

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
        std::cout << std::endl;
        log("Saving image to file " + _filename);
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
