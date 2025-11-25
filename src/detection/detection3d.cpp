#include "detection3d.h"
#include <numeric>

bool RayTriangleIntersect(const Point3D &rayOrigin, const Point3D &rayDirection,
                          const Triangle3D &triangle, Point3D &outIntersectionPoint)
{
        outIntersectionPoint = glm::vec3(std::numeric_limits<float>::quiet_NaN());

        constexpr float epsilon = 1e-8f;

        glm::vec3 edge1 = std::get<1>(triangle) - std::get<0>(triangle),
                  edge2 = std::get<2>(triangle) - std::get<0>(triangle),
                  rayCrossEdge2 = glm::cross(rayDirection, edge2);
        float det = glm::dot(edge1, rayCrossEdge2);

        if (fabs(det) < epsilon)
                return false;

        float invDet = 1.0f / det;

        glm::vec3 s = rayOrigin - std::get<0>(triangle);
        float u = glm::dot(s, rayCrossEdge2) * invDet;

        if (u < 0.0f || u > 1.0f)
                return false;

        glm::vec3 sCrossEdge1 = glm::cross(s, edge1);
        float v = glm::dot(rayDirection, sCrossEdge1) * invDet;

        if (v < 0.0f || u + v > 1.0f)
                return false;

        float t = glm::dot(edge2, sCrossEdge1) * invDet;
        if (t < epsilon)
                return false;

        outIntersectionPoint = rayOrigin + rayDirection * t;
        return true;
}