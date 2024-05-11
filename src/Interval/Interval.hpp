/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Interval
*/

#ifndef INTERVAL_HPP_
#define INTERVAL_HPP_

#include <limits>
#include <algorithm>

const double infinity = std::numeric_limits<double>::infinity();
//TODO : Delete this const
class Interval {
    public:
        Interval();
        Interval(double min, double max);
        ~Interval() = default;

        double min() const;
        double max() const;

        double size() const;
        bool contains(double x) const;
        bool surrounds(double x) const;
        double clamp(double x) const;

        // static const Interval empty, universe;
    protected:
    private:
        double _min;
        double _max;
};

#endif /* !INTERVAL_HPP_ */
