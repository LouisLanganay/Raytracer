/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ARender
*/

#ifndef ARENDER_HPP_
#define ARENDER_HPP_

#include "IRender.hpp"
#include "../../src/Camera/Camera.hpp"
#include "../lights/DirectionalLight/DirectionalLight.hpp"
#include "../lights/ALight.hpp"
#include <memory>

namespace RayTracer::Render {

    class ARender : public IRender {
        public:
            ARender();
            virtual ~ARender() = default;

            virtual void render(Scene &scene) = 0;
            void setFilename(const std::string &filename) override;
            Vector3D castRay(double u, double v, const RayTracer::Scene &scene, std::size_t depth);
            Vector3D castRay(
                const Ray &ray,
                const RayTracer::Scene &scene,
                std::size_t depth,
                Primitives::IPrimitive *lastPrimitive = nullptr
            );

            void setMaxDepth(int maxDepth) override;
            void setSamples(int samples) override;
            int getMaxDepth() const override;
            int getSamples() const override;

        protected:
            std::string _filename;
            int _maxDepth;
            int _samples;
            void updateProgress(int pixelsRendered, int totalPixels, std::string message = "");
        private:
            std::string _message;
            RayTracer::Lights::DirectionalLight *_light;
            Vector3D randomInUnitSphere();
            double _lastProgress = -1.0;
            time_t _startTime;
            std::size_t _seed;
    };

}


#endif /* !ARENDER_HPP_ */
