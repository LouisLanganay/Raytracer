/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../Point/Point3D.hpp"
#include "../Vector/Vector3D.hpp"
#include "../Rectangle/Rectangle3D.hpp"
#include "../Ray/Ray.hpp"
#include <cmath>
#define M_PI 3.14159265358979323846

namespace RayTracer {
    class Camera {
        public:
            Camera(
                Point3D origin,
                Point3D resolution
            );
            ~Camera() = default;

            void setResolution(int x, int y);
            void setOrigin(double x, double y, double z);
            void setRotation(double x, double y, double z);
            void setFov(double fov);

            Point3D getResolution() const;
            Point3D getOrigin() const;
            Point3D getRotation() const;
            double getFov() const;
            void moveCamera(double x, double y, double z);
            void rotateCamera(double x, double y, double z);

            Ray generateRay(double u, double v) const;

        protected:
        private:
            Point3D _origin;

            Rectangle3D _screen;

            Point3D _resolution;
            Point3D _rotation;

            double _fov;
    };
}

#endif /* !CAMERA_HPP_ */
