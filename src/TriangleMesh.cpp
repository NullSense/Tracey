#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(const char *file)
{
	std::string inputfile = file;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if(!err.empty())
		std::cerr << err << std::endl;

	if(!ret)
		exit(1);

	int triangleCount = 0;
	for(const auto &shape : shapes)
		for(int i = 0; i < shape.mesh.num_face_vertices.size(); ++i)
			triangleCount++;

	std::cout << std::endl << "Triangles: " << triangleCount << std::endl;
}

FPType TriangleMesh::GetIntersection(const Ray &ray)
{
	FPType distLowest = 1000000, intersection, u=0, v=0;
	bool polygon_hit = false;
	for(auto &shape : shapes)
	{
		size_t index_offset = 0;
		for(size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) // faces (triangles)
		{
			int fv = shape.mesh.num_face_vertices[f];
			tinyobj::index_t &idx0 = shape.mesh.indices[index_offset + 0]; // v0
			tinyobj::index_t &idx1 = shape.mesh.indices[index_offset + 1]; // v1
			tinyobj::index_t &idx2 = shape.mesh.indices[index_offset + 2]; // v2

			// Vertices;
			tri.v0 = Vec3d(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]);
			tri.v1 = Vec3d(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]);
			tri.v2 = Vec3d(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2]);

			// Vertex normals
			n0 = Vec3d(attrib.normals[3 * idx0.normal_index + 0], attrib.normals[3 * idx0.normal_index + 1], attrib.normals[3 * idx0.normal_index + 2]);
			n1 = Vec3d(attrib.normals[3 * idx1.normal_index + 0], attrib.normals[3 * idx1.normal_index + 1], attrib.normals[3 * idx1.normal_index + 2]);
			n2 = Vec3d(attrib.normals[3 * idx2.normal_index + 0], attrib.normals[3 * idx2.normal_index + 1], attrib.normals[3 * idx2.normal_index + 2]);

			st0 = Vec3d(attrib.texcoords[3 * idx0.texcoord_index + 0], attrib.texcoords[3 * idx0.texcoord_index + 1], attrib.texcoords[3 * idx0.texcoord_index + 2]);
			st1 = Vec3d(attrib.texcoords[3 * idx1.texcoord_index + 0], attrib.texcoords[3 * idx1.texcoord_index + 1], attrib.texcoords[3 * idx1.texcoord_index + 2]);
			st2 = Vec3d(attrib.texcoords[3 * idx2.texcoord_index + 0], attrib.texcoords[3 * idx2.texcoord_index + 1], attrib.texcoords[3 * idx2.texcoord_index + 2]);
			texCoords = st0 * (1 - uv.x - uv.y) + st1 * uv.x + st2 * uv.y;

			if(intersection = tri.GetIntersection(ray, u, v))
			{
				if(intersection < distLowest)
				{
					polygon_hit = true;
					distLowest = intersection;
				}
			}
			index_offset += fv;
			normal = n0 * (1 - uv.x - uv.y)+ n1 * uv.x + n2 * uv.y;
		}
	}
	if(polygon_hit)
		return distLowest;
	else
		return -1;
}

Vector3d TriangleMesh::GetNormalAt(const Vector3d &)
{
	return normal;
	//return ((tri.v1 - tri.v0).Cross(tri.v2 - tri.v0).Normalize());
}
