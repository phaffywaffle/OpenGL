#include "Model.h"

// Make this a union for vector. Or just use glm::vec3
struct Vertex {	real32 x; real32 y; real32 z; };

// fix this later
internal std::vector<Vertex> vertices_vector;
internal std::vector<Vertex> normals_vector;
// Remember Vector.z is garbage here
internal std::vector<Vertex> uv_vector;
internal std::vector<uint32> indices_vector;
internal std::vector<Vertex> faces_vector;
internal std::string garbagestring;
internal char garbagechar;

// Fucked for uvs
internal bool
checkEqual(Vertex v1, Vertex v2)
{
	return(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

internal void
processFace(std::string line)
{
	std::istringstream iss(line);

	uint32 numbers[3 * 3];

	iss >> garbagechar >> numbers[0] >> garbagechar >> numbers[1] >> garbagechar >> numbers[2] >> numbers[3] >> garbagechar >> numbers[4] >> garbagechar >> numbers[5] >> numbers[6] >> garbagechar >> numbers[7] >> garbagechar >> numbers[8];

	Vertex v1 = {numbers[0], numbers[1], numbers[2]};
	Vertex v2 = {numbers[3], numbers[4], numbers[5]};
	Vertex v3 = {numbers[6], numbers[7], numbers[8]};

	faces_vector.push_back(v1);
	faces_vector.push_back(v2);
	faces_vector.push_back(v3);
}

Model::Model()
{
	std::ifstream is("cube.obj");
	if (is.bad()) { print("Error opening obj file"); pause(); exit(-1); }

	num_verts = 0;
	std::string line;
	while (std::getline(is, line))
	{
		std::istringstream iss(line);
		if (line[0] == 'v' && line[1] == ' ')
		{
			Vertex vertex;
			iss >> garbagestring >> vertex.x >> vertex.y >> vertex.z;
			vertices_vector.push_back(vertex);
			num_verts++;
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			Vertex normal;
			iss >> garbagestring >> normal.x >> normal.y >> normal.z;
			normals_vector.push_back(normal);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			Vertex uv;
			iss >> garbagestring >> uv.x >> uv.y;
			uv_vector.push_back(uv);
		}
		if (line[0] == 'f')
		{
			processFace(line);
		}
	}

	for(int i = 0; i < faces_vector.size(); i++)
	{
		print("Face: " << faces_vector.at(i).x << "/" << faces_vector.at(i).y << "/" << faces_vector.at(i).z);	
	}



	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvbo);
	glGenBuffers(1, &nbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_verts * FLOATS_PER_VERTEX * sizeof(real32), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(real32), 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, num_verts * FLOATS_PER_UV * sizeof(real32), uvs, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_UV * sizeof(real32), 0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, num_verts * FLOATS_PER_NORMAL * sizeof(real32), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_NORMAL * sizeof(real32), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), indices, GL_STATIC_DRAW);//

	unbind();
}
// Check to see if I need to bind the vbo or just the vao here
void Model::bind()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Model::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::~Model()
{
	delete[] verts;
	delete[] indices;
}