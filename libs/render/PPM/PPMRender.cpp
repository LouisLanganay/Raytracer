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
    PPMRender::PPMRender() : _mutex(), _pixelsRendered(0)
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
        const int numThreads = std::thread::hardware_concurrency();
        const int tileSize = height / numThreads;
        std::vector<std::thread> threads;
        std::vector<int> threadProgress(numThreads, 0);
        int rowProgress = 0;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file" << std::endl;
            return;
        }
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
        file.close();
        std::cout << std::endl;
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
