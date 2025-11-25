#ifndef DETECTION3D_H
#define DETECTION3D_H

#include "../geometry/shape3d.h"

bool RayTriangleIntersect(const Point3D &rayOrigin, const Point3D &rayDirection,
                          const Triangle3D &triangle, Point3D &outIntersectionPoint);

#endif