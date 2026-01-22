#ifndef SHAPE_H
#define SHAPE_H

#include <tuple>
#include <glm/glm.hpp>

#include "mesh.h"

typedef glm::vec3 Point3D;
typedef std::tuple<glm::vec3, glm::vec3> Line3D;
typedef std::tuple<glm::vec3, glm::vec3, glm::vec3> Triangle3D;

struct Box
{
        glm::vec3 size;
};
struct Sphere
{
        float radius;
        int segments, rings;
};
struct Cylinder
{
        float radius, height;
        int segments, rings;
};
struct Cone
{
        float radius, height;
        int segments, rings;
};

Mesh *GenerateMesh(const Box &box);
Mesh *GenerateMesh(const Sphere &sphere);
Mesh *GenerateMesh(const Cylinder &cylinder);
Mesh *GenerateMesh(const Cone &cone);

#endif