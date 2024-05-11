/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** RayHit
*/

#ifndef RAYHIT_HPP_
#define RAYHIT_HPP_

#include "../Point/Point3D.hpp"
#include "../Vector/Vector3D.hpp"
#include "../../libs/materials/AMaterial.hpp"
#include <memory>

namespace RayTracer::Materials {
    class AMaterial;
}
class HitRecord {
    public:
        Point3D p;
        Vector3D normal;
        std::shared_ptr<RayTracer::Materials::AMaterial> material;
        double t;
        bool front_face;
        void set_face_normal(const Ray &r, const Vector3D &outward_normal);
};

namespace RayTracer {
    namespace Primitives {
        class IPrimitive;
    }
    struct RayHit {
        Point3D point;
        Vector3D normal;
        Primitives::IPrimitive *primitive;
        double distance;
    };
}

#endif /* !RAYHIT_HPP_ */
