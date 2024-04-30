/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** CameraBuilder
*/

#ifndef CAMERABUILDER_HPP_
#define CAMERABUILDER_HPP_

#include "Camera.hpp"
#include <iostream>

namespace RayTracer::Builders {
    class CameraBuilder {
        private:
            Point3D position;
            Point3D resolution;
            double fieldOfView;
            Point3D rotation;

        public:
            CameraBuilder() {}

            CameraBuilder& set(const std::string &key, Point3D value)
            {
                if (key == "position")
                    position = value;
                if (key == "resolution")
                    resolution = value;
                if (key == "rotation")
                    rotation = value;
                return *this;
            }

            CameraBuilder& set(const std::string &key, double fov)
            {
                if (key == "fov")
                    fieldOfView = fov;
                return *this;
            }

            Camera build() {
                Camera camera(position, resolution);
                camera.setFov(fieldOfView);
                camera.setRotation(rotation._x, rotation._y, rotation._z);
                return camera;
            }
        };

}

#endif /* !CAMERABUILDER_HPP_ */
