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

			//Triangle tri;
			tri.v0 = Vec3d(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]);
			tri.v1 = Vec3d(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]);
			tri.v2 = Vec3d(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2]);
			//normal = (v1 - v0).Cross(v2 - v0).Normalize();
			if(tri.GetIntersection(ray))
				return tri.GetIntersection(ray);
			index_offset += fv;
		}
	}
}

Vector3d TriangleMesh::GetNormalAt(const Vector3d &)
{
	return (v1 - v0).Cross(v2 - v0).Normalize();
}
