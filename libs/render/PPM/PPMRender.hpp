/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "../ARender.hpp"
#include "../../../src/Camera/Camera.hpp"

namespace RayTracer::Render {
    class PPMRender : public ARender {
        public:
            PPMRender();
            virtual ~PPMRender() = default;

            virtual void render(Scene &scene) override;
        protected:
        private:
    };

}


#endif /* !SPHERE_HPP_ */
