#pragma once
//#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <memory>
#include "Globals.h"
#include "Triangle.h"
#include "tiny_obj_loader.h"

class TriangleMesh : public Object {
 public:
  TriangleMesh(const char *file);
  double GetIntersection(const Ray &ray);
  Vector3d GetNormalAt(const Vector3d &intersectionPosition);
  Vector3d GetTexCoords(Vector3d &normal, const Vector3d &hitPoint);

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;
  Triangle tri;
  Vector3d n0, n1, n2, normal;
  Vector3d uv;
  Vector3d st0, st1, st2, texCoords;
};
