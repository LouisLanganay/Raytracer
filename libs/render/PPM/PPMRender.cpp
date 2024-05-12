/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "PPMRender.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <iostream>
#include <fstream>
#include <thread>

namespace RayTracer::Render {
    PPMRender::PPMRender() : _mutex(), _pixelsRendered(0), _image()
    {
    }

    void PPMRender::renderTile(Scene& scene, int start, int end, int width, int height, int samplesPerPixel)
    {
        for (int y = start; y < end; ++y) {
            for (int x = 0; x < width; ++x) {
                Vector3D color(0, 0, 0);
                for (std::size_t k = 0; k < samplesPerPixel; k++) {
                    for (std::size_t l = 0; l < samplesPerPixel; l++) {
                        double u = (x + (k / static_cast<double>(samplesPerPixel))) / width;
                        double v = 1.0 - (y + (l / static_cast<double>(samplesPerPixel))) / height;
                        color += castRay(u, v, scene, _maxDepth);
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

    void PPMRender::render(Scene &scene)
    {
        std::fstream file(_filename, std::ios::out | std::ios::trunc);
        Camera camera = *scene.getCamera();
        int height = camera.getResolution()._y;
        int width = camera.getResolution()._x;
        int numThreads = 1;
        std::vector<std::thread> threads;
        log("\033[1;31mStarting threads\033[0m");
        for (std::size_t i = 1; i <= std::thread::hardware_concurrency(); i++) {
            log("\033[33mStarting thread n°" + std::to_string(i) + "\033[0m");
            if (height % i == 0)
                numThreads = i;
        }
        const int tileSize = height / numThreads;
        log("Number of threads: " + std::to_string(numThreads) + ", tile size: " + std::to_string(tileSize));
        int rowProgress = 0;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file" << std::endl;
            return;
        }
        log("Writing header");
        file << "P3\n" << width << " " << height << "\n255\n";
        _image.resize(height);
        for (int i = 0; i < numThreads; ++i)
            threads.emplace_back(&PPMRender::renderTile, this, std::ref(scene), i * tileSize, (i + 1) * tileSize, width, height, _samples);
        for (auto& thread : threads)
            thread.join();
        for (std::vector<Vector3D>& row : _image) {
            for (Vector3D& color : row) {
                int ir = static_cast<int>(color._x);
                int ig = static_cast<int>(color._y);
                int ib = static_cast<int>(color._z);
                file << ir << " " << ig << " " << ib << "\n";
            }
            rowProgress++;
            updateProgress(rowProgress, height, "Generating .ppm image");
        }
        std::cout << std::endl;
        log("Saving image to file " + _filename);
        file.close();
    }

    sf::Image PPMRender::renderVideo(Scene &scene, Camera &camera)
    {
        sf::Image image;
        image.create(1920 / _quality, 1080 / _quality);
        scene.setCamera(&camera);

        for (int y = 0; y < 1080 / _quality; ++y) {
            for (int x = 0; x < 1920 / _quality; ++x) {
                Vector3D color = castRay(x / (1920 / (double)_quality), 1.0 - y / (1080 / (double)_quality), scene, _maxDepth);
                int ir = static_cast<int>(color._x);
                int ig = static_cast<int>(color._y);
                int ib = static_cast<int>(color._z);
                sf::Color pixelColor(ir, ig, ib);
                image.setPixel(x, y, pixelColor);
            }
        }
        return image;
    }

    sf::Image PPMRender::renderPreview(Scene &scene, Camera &camera)
    {
        sf::Image image;

        return image;
    }


    extern "C" std::unique_ptr<IRender> getEntryPoint()
    {
        return std::make_unique<PPMRender>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::RENDER);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("ppm");
    }
}
