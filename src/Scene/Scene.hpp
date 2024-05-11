/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include <memory>
#include "../../libs/primitives/IPrimitive.hpp"
#include "../../libs/lights/ILight.hpp"
#include "../Camera/Camera.hpp"
#include "../Interval/Interval.hpp"
#include "../../libs/materials/AMaterial.hpp"

namespace RayTracer {
    // class HitRecord {
    //     public:
    //         Point3D p;
    //         Vector3D normal;
    //         std::shared_ptr<Materials::AMaterial> mat_ptr;
    //         double t;
    //         bool front_face;

    //         void set_face_normal(const Ray &r, const Vector3D &outward_normal); 
    // };
    class Scene {
        public:
            Scene();
            ~Scene();

            void addPrimitive(std::unique_ptr<Primitives::IPrimitive> &primitive);
            void addLight(std::unique_ptr<Lights::ILight> &light);
            void setCamera(std::unique_ptr<Camera> &camera);

            const std::vector<Primitives::IPrimitive *> &getPrimitives() const;
            const std::vector<Lights::ILight *> &getLights() const;
            Camera *getCamera() const;

            Vector3D ray_Color(const Ray &ray, int depth, const Scene &scene);
            Ray get_ray(double u, double v) const;
            bool hit(const Ray &r, const Interval interval, HitRecord &rec) const;
        protected:
        private:
            std::vector<Primitives::IPrimitive *> _primitives;
            std::vector<Lights::ILight *> _lights;
            Camera *_camera;
    };
}

#endif /* !SCENE_HPP_ */
