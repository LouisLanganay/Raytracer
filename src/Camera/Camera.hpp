/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Point3D.hpp"

namespace RayTracer {
    class Camera {
        public:
            Camera();
            ~Camera() = default;

            void setResolution(int x, int y);
            void setOrigin(double x, double y, double z);
            void setRotation(double x, double y, double z);
            void setFov(double fov);

            Point3D getResolution() const;
            Point3D getOrigin() const;
            Point3D getRotation() const;
            double getFov() const;

        protected:
        private:
            Point3D _resolution;
            Point3D _origin;
            Point3D _rotation;
            double _fov;
    };
}

#endif /* !CAMERA_HPP_ */
