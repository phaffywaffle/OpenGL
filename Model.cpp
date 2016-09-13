#include "Model.h"

static real32 tempverts[] = {
	-1, -1, 1, //0
	1, 0, 0,
	0, 0, 1,

	1, 1, 1, //1
	0, 1, 0,
	0, 0, 1,

	-1, 1, 1, //2
	0, 0, 1,
	0, 0, 1,

	1, -1, 1, //3
	1, 0, 1,
	0, 0, 1,

	/************/

	-1, -1, -1, //4
	0, 1, 0,
	0, 0, -1,

	-1, 1, -1, //5
	1, 0, 1,
	0, 0, -1,

	1, 1, -1, //6
	1, 0, 0,
	0, 0, -1,

	1, -1, -1, //7
	0, 0, 1,
	0, 0, -1,

	/************/

	1, -1, 1, //8
	1, 0, 1,
	1, 0, 0,

	1, 1, -1, //9
	1, 0, 0,
	1, 0, 0,

	1, 1, 1, //10
	0, 1, 0,
	1, 0, 0,

	1, -1, -1, //11
	0, 0, 1,
	1, 0, 0,

	/************/

	-1, -1, 1, //12
	1, 0, 0,
	-1, 0, 0,

	-1, 1, 1, //13
	0, 0, 1,
	-1, 0, 0,

	-1, 1, -1, //14
	1, 0, 1,
	-1, 0, 0,

	-1, -1, -1, //15
	0, 1, 0,
	-1, 0, 0,

	/************/

	-1, 1, 1, //16
	0, 0, 1,
	0, 1, 0,

	1, 1, -1, //17
	1, 0, 0,
	0, 1, 0,

	-1, 1, -1, //18
	1, 0, 1,
	0, 1, 0,

	1, 1, 1, //19
	0, 1, 0,
	0, 1, 0,

	/************/

	-1, -1, 1, //20
	1, 0, 0,
	0, -1, 0,

	-1, -1, -1, //21
	0, 1, 0,
	0, -1, 0,

	1, -1, -1, //22
	0, 0, 1,
	0, -1, 0,

	1, -1, 1, //23
	1, 0, 1,
	0, -1, 0,
};

static GLushort tempindices[] = {
	0, 1, 2, 0, 3, 1,
	4, 5, 6, 4, 6, 7,
	8, 9, 10, 8, 11, 9,
	12, 13, 14, 12, 14, 15,
	16, 17, 18, 16, 19, 17,
	20, 21, 22, 20, 22, 23
};

// Make this a union for vector. Or just use glm::vec3
struct Vertex {	float x; float y; float z; };

Model::Model()
{
	std::vector<Vertex> vertices;
	std::vector<Vertex> normals;
	// Remember Vector.z is garbage here
	std::vector<Vertex> uvs;
	std::ifstream is("test.obj");
	if(is.bad()) {	print("Error opening obj file"); pause(); exit(-1);	}

	std::string line;
	while(std::getline(is, line))
	{
		std::istringstream iss(line);
		if(line[0] =='v' && line[1] == ' ')
		{
			Vertex vertex;
			char garbage;
			iss >> garbage >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		if(line[0] =='v' && line[1] == 'n')
		{
			Vertex normal;
			char garbage;
			iss >> garbage >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		if(line[0] =='v' && line[1] == 't')
		{
			Vertex uv;
			char garbage;
			iss >> garbage >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
	}

	for(int i = 0; i < vertices.size(); i++)
	{
		print("Vertex: (" << vertices.at(i).x << ", " << vertices.at(i).y << ", " << vertices.at(i).z << ")");
	}

	for(int i = 0; i < normals.size(); i++)
	{
		print("Normal: (" << normals.at(i).x << ", " << normals.at(i).y << ", " << normals.at(i).z << ")");
	}

	for(int i = 0; i < uvs.size(); i++)
	{
		print("UVs: (" << uvs.at(i).x << ", " << uvs.at(i).y << ")");
	}

	num_verts = NUM_ARRAY_ELEMENTS(tempverts);
	verts = new real32[num_verts];
	for (int i = 0; i < num_verts;)
		verts[i] = tempverts[i++];

	num_indices = NUM_ARRAY_ELEMENTS(tempindices);
	indices = new GLushort[num_indices];
	for (int i = 0; i < num_indices;)
		indices[i] = tempindices[i++];

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	bind();

	glBufferData(GL_ARRAY_BUFFER, num_verts * sizeof(real32), verts, GL_STATIC_DRAW); //
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), indices, GL_STATIC_DRAW);//

	unbind();
}

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