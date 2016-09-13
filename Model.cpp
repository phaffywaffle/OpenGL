#include "Model.h"

//#define USE_ONE_BUFFER

#ifdef	USE_ONE_BUFFER 
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
	0, -1, 0
};
#else
static real32 tempverts[] = {
	-1, -1, 1, //0

	1, 1, 1, //1

	-1, 1, 1, //2

	1, -1, 1, //3

	/************/

	-1, -1, -1, //4

	-1, 1, -1, //5

	1, 1, -1, //6

	1, -1, -1, //7

	/************/

	1, -1, 1, //8

	1, 1, -1, //9

	1, 1, 1, //10

	1, -1, -1, //11

	/************/

	-1, -1, 1, //12

	-1, 1, 1, //13

	-1, 1, -1, //14

	-1, -1, -1, //15

	/************/

	-1, 1, 1, //16

	1, 1, -1, //17

	-1, 1, -1, //18

	1, 1, 1, //19

	/************/

	-1, -1, 1, //20

	-1, -1, -1, //21

	1, -1, -1, //22

	1, -1, 1 //23
};
#endif

static real32 tempcolors[] = {
	1, 0, 0,

	0, 1, 0,

	0, 0, 1,

	1, 0, 1,

	/************/

	0, 1, 0,

	1, 0, 1,

	1, 0, 0,

	0, 0, 1,

	/************/

	1, 0, 1,

	1, 0, 0,

	0, 1, 0,

	0, 0, 1,

	/************/

	1, 0, 0,

	0, 0, 1,

	1, 0, 1,

	0, 1, 0,

	/************/

	0, 0, 1,

	1, 0, 0,

	1, 0, 1,

	0, 1, 0,

	/************/

	1, 0, 0,

	0, 1, 0,

	0, 0, 1,

	1, 0, 1
};

static real32 tempnormals[] = 
{
	0, 0, 1,

	0, 0, 1,

	0, 0, 1,

	0, 0, 1,

	/************/

	0, 0, -1,

	0, 0, -1,

	0, 0, -1,

	0, 0, -1,

	/************/

	1, 0, 0,

	1, 0, 0,

	1, 0, 0,

	1, 0, 0,

	/************/

	-1, 0, 0,

	-1, 0, 0,

	-1, 0, 0,

	-1, 0, 0,

	/************/

	0, 1, 0,

	0, 1, 0,

	0, 1, 0,

	0, 1, 0,

	/************/

	0, -1, 0,

	0, -1, 0,

	0, -1, 0,

	0, -1, 0
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
	std::vector<Vertex> vs;
	std::vector<Vertex> ns;
	// Remember Vector.z is garbage here
	std::vector<Vertex> uvss;
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
			vs.push_back(vertex);
		}
		if(line[0] =='v' && line[1] == 'n')
		{
			Vertex normal;
			char garbage;
			iss >> garbage >> normal.x >> normal.y >> normal.z;
			ns.push_back(normal);
		}
		if(line[0] =='v' && line[1] == 't')
		{
			Vertex uv;
			char garbage;
			iss >> garbage >> uv.x >> uv.y;
			uvss.push_back(uv);
		}
	}

	for(int i = 0; i < vs.size(); i++)
	{
		print("Vertex: (" << vs.at(i).x << ", " << vs.at(i).y << ", " << vs.at(i).z << ")");
	}

	for(int i = 0; i < ns.size(); i++)
	{
		print("Normal: (" << ns.at(i).x << ", " << ns.at(i).y << ", " << ns.at(i).z << ")");
	}

	for(int i = 0; i < uvss.size(); i++)
	{
		print("UVs: (" << uvss.at(i).x << ", " << uvss.at(i).y << ")");
	}

	num_verts = NUM_ARRAY_ELEMENTS(tempverts);
	verts = new real32[num_verts];
	for (int i = 0; i < num_verts;)
		verts[i] = tempverts[i++];

	num_uvs = NUM_ARRAY_ELEMENTS(tempcolors);
	uvs = new real32[num_uvs];
	for (int i = 0; i < num_uvs;)
		uvs[i] = tempcolors[i++];


	num_normals = NUM_ARRAY_ELEMENTS(tempnormals);
	normals = new real32[num_normals];
	for (int i = 0; i < num_normals;)
		normals[i] = tempnormals[i++];

	num_indices = NUM_ARRAY_ELEMENTS(tempindices);
	indices = new GLushort[num_indices];
	for (int i = 0; i < num_indices;)
		indices[i] = tempindices[i++];

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvbo);
	glGenBuffers(1, &nbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_verts * sizeof(real32), verts, GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, num_uvs * sizeof(real32), uvs, GL_STATIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, num_normals * sizeof(real32), normals, GL_STATIC_DRAW); 
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

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