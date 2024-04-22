/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "PPMRender.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include <thread>

namespace RayTracer::Render {
    PPMRender::PPMRender()
    {
    }

    void PPMRender::render(Scene &scene) {
        std::fstream file(_filename, std::ios::out | std::ios::trunc);
        Camera camera = *scene.getCamera();
        int height = camera.getResolution()._y;
        int width = camera.getResolution()._x;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file" << std::endl;
            return;
        }
        file << "P3\n" << width << " " << height << "\n255\n";

        const int totalPixels = height * width;
        int pixelsRendered = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                double u = static_cast<double>(x) / width;
                double v = static_cast<double>(y) / height;
                Ray ray = camera.generateRay(u, v);
                Vector3D color = scene.traceRay(ray);
                int ir = static_cast<int>(color._x);
                int ig = static_cast<int>(color._y);
                int ib = static_cast<int>(color._z);
                file << ir << " " << ig << " " << ib << "\n";
                pixelsRendered++;
                updateProgress(pixelsRendered, totalPixels);
            }
        }
        file.close();
        std::cout << std::endl; // End the loading bar line
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
