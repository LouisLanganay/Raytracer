/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Interval
*/

#include "Interval.hpp"

Interval::Interval() : _min(+infinity), _max(-infinity)
{
}

Interval::Interval(double min, double max) : _min(min), _max(max)
{
}

double Interval::min() const
{
    return _min;
}

double Interval::max() const
{
    return _max;
}

double Interval::size() const
{
    return _max - _min;
}

bool Interval::contains(double x) const
{
    return _min <= x && x <= _max;
}

bool Interval::surrounds(double x) const
{
    return _min < x && x < _max;
}

double Interval::clamp(double x) const
{
    if (x < _min)
        return _min;
    if (x > _max)
        return _max;
    return x;
}
