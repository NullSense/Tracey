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
	FPType distLowest = 1000, intersection;
	for(auto &shape : shapes)
	{
		size_t index_offset = 0;
		bool polygon_hit = false;
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

			if(intersection = tri.GetIntersection(ray))
			{
				if(intersection < distLowest)
				{
					polygon_hit = true;
					distLowest = intersection;
				}
			}
			index_offset += fv;
		}
		if(polygon_hit)
			return distLowest;
		else
			return -1;
	}
}

Vector3d TriangleMesh::GetNormalAt(const Vector3d &)
{
	return ((tri.v1 - tri.v0).Cross(tri.v2 - tri.v0).Normalize());
}
