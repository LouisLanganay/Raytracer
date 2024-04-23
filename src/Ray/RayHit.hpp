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
