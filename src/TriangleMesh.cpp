#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(const char *file)
{
	std::string inputfile = file;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if(!err.empty())
		std::cerr << err << std::endl;

	if(!ret)
		exit(1);
	std::cout << "Num of triangles in model: " << shapes[0].mesh.num_face_vertices.size() << std::endl;
}

FPType TriangleMesh::GetIntersection(const Ray &ray)
{
	for(auto &shape : shapes)
	{
		size_t index_offset = 0;
		for(size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) // faces (triangles)
		{
			int fv = shape.mesh.num_face_vertices[f];
			tinyobj::index_t &idx0 = shape.mesh.indices[index_offset + 0]; // v0
			tinyobj::index_t &idx1 = shape.mesh.indices[index_offset + 1]; // v1
			tinyobj::index_t &idx2 = shape.mesh.indices[index_offset + 2]; // v2

			Vec3d &v0 = Vec3d(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]);
			Vec3d &v1 = Vec3d(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]);
			Vec3d &v2 = Vec3d(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2]);
			Triangle tri(v0, v1, v2);
			if(tri.GetIntersection(ray))
				return tri.GetIntersection(ray);
			index_offset += fv;
		}
	}
}

Vector3d TriangleMesh::GetNormalAt(const Vector3d &)
{
	return normal;
}
