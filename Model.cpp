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
struct Vertex { real32 x; real32 y; real32 z; };

// 6fix this later
static std::vector<Vertex> vs;
static std::vector<Vertex> ns;
// Remember Vector.z is garbage here
static std::vector<Vertex> uvss;
static std::vector<uint32> isv;
void
Model::processLine(std::string line)
{
	// fix this later
	std::string garbagestring;
	char garbagechar;

	std::istringstream iss(line);

	uint32 v1, v2, v3;
	uint32 t1, t2, t3;
	uint32 n1, n2, n3;

	iss >> garbagestring;

	iss >> v1;
	iss >> garbagechar;
	iss >> t1;
	iss >> garbagechar;
	iss >> n1;

	isv.push_back(v1);
	print("Putting " << uvss.at(t1 - 1).x << " into uvs[" << (v1 - 1) * FLOATS_PER_UV + 0 << "], replacing " << uvs[(v1 - 1) * FLOATS_PER_UV + 0]);
	uvs[(v1 - 1) * FLOATS_PER_UV + 0] = uvss.at(t1 - 1).x;
	print("Putting " << uvss.at(t1 - 1).y << " into uvs[" << (v1 - 1) * FLOATS_PER_UV + 1 << "], replacing " << uvs[(v1 - 1) * FLOATS_PER_UV + 1]);
	uvs[(v1 - 1) * FLOATS_PER_UV + 1] = uvss.at(t1 - 1).y;
	print("Putting " << ns.at(n1 - 1).x << " into normals[" << (v1 - 1) * FLOATS_PER_UV + 0 << "], replacing "<< normals[(v1 - 1) * FLOATS_PER_UV + 0]);
	normals[(v1 - 1) * FLOATS_PER_NORMAL + 0] = ns.at(n1 - 1).x;
	print("Putting " << ns.at(n1 - 1).y << " into normals[" << (v1 - 1) * FLOATS_PER_UV + 1 << "], replacing "<< normals[(v1 - 1) * FLOATS_PER_UV + 1]);
	normals[(v1 - 1) * FLOATS_PER_NORMAL + 1] = ns.at(n1 - 1).y;
	print("Putting " << ns.at(n1 - 1).z << " into normals[" << (v1 - 1) * FLOATS_PER_UV + 2 << "], replacing "<< normals[(v1 - 1) * FLOATS_PER_UV + 2]);
	normals[(v1 - 1) * FLOATS_PER_NORMAL + 2] = ns.at(n1 - 1).z;

	iss >> v2;
	iss >> garbagechar;
	iss >> t2;
	iss >> garbagechar;
	iss >> n2;

	isv.push_back(v2);
	print("Putting " << uvss.at(t2 - 1).x << " into uvs[" << (v2 - 1) * FLOATS_PER_UV + 0 << "], replacing" << uvs[(v2 - 1) * FLOATS_PER_UV + 0]);
	uvs[(v2 - 1) * FLOATS_PER_UV + 0] = uvss.at(t2 - 1).x;
	print("Putting " << uvss.at(t2 - 1).y << " into uvs[" << (v2 - 1) * FLOATS_PER_UV + 1 << "], replacing " << uvs[(v2 - 1) * FLOATS_PER_UV + 1]);
	uvs[(v2 - 1) * FLOATS_PER_UV + 1] = uvss.at(t2 - 1).y;
	print("Putting " << ns.at(n2 - 1).x << " into normals[" << (v2 - 1) * FLOATS_PER_NORMAL + 0 << "], replacing "<< normals[(v2 - 1) * FLOATS_PER_NORMAL + 0]);
	normals[(v2 - 1) * FLOATS_PER_NORMAL + 0] = ns.at(n2 - 1).x;
	print("Putting " << ns.at(n2 - 1).y << " into normals[" << (v2 - 1) * FLOATS_PER_NORMAL + 1 << "], replacing "<< normals[(v2 - 1) * FLOATS_PER_NORMAL + 1]);
	normals[(v2 - 1) * FLOATS_PER_NORMAL + 1] = ns.at(n2 - 1).y;
	print("Putting " << ns.at(n2 - 1).z << " into normals[" << (v2 - 1) * FLOATS_PER_NORMAL + 2 << "], replacing "<< normals[(v2 - 1) * FLOATS_PER_NORMAL + 2]);
	normals[(v2 -1) * FLOATS_PER_NORMAL + 2] = ns.at(n2 - 1).z;

	iss >> v3;
	iss >> garbagechar;
	iss >> t3;
	iss >> garbagechar;
	iss >> n3;

	isv.push_back(v3);
	print("Putting " << uvss.at(t3 - 1).x << " into uvs[" << (v3 - 1) * FLOATS_PER_UV + 0 << "], replacing "<< uvs[(v3 - 1) * FLOATS_PER_UV + 0]);
	uvs[(v3 - 1) * FLOATS_PER_UV + 0] = uvss.at(t3 - 1).x;
	print("Putting " << uvss.at(t3 - 1).y << " into uvs[" << (v3 - 1) * FLOATS_PER_UV + 1 << "], replacing " << uvs[(v3 - 1) * FLOATS_PER_UV + 1]);
	uvs[(v3 - 1) * FLOATS_PER_UV + 1] = uvss.at(t3 - 1).y;
	print("Putting " << ns.at(n3 - 1).x << " into normals[" << (v3 - 1) * FLOATS_PER_NORMAL + 0 << "], replacing "<< normals[(v3 - 1) * FLOATS_PER_NORMAL + 0]);
	normals[(v3 - 1) * FLOATS_PER_NORMAL + 0] = ns.at(n3 - 1).x;
	print("Putting " << ns.at(n3 - 1).y << " into normals[" << (v3 - 1) * FLOATS_PER_NORMAL + 1 << "], replacing "<< normals[(v3 -1 ) * FLOATS_PER_NORMAL + 1]);
	normals[(v3 - 1) * FLOATS_PER_NORMAL + 1] = ns.at(n3 - 1).y;
	print("Putting " << ns.at(n3 - 1).z << " into normals[" << (v3 - 1) * FLOATS_PER_NORMAL + 2 << "], replacing "<< normals[(v3 - 1) * FLOATS_PER_NORMAL + 2]);
	normals[(v3 - 1) * FLOATS_PER_NORMAL + 2] = ns.at(n3 - 1).z;

	num_indices += 3;
}

Model::Model()
{
	std::ifstream is("cube.obj");
	if (is.bad()) { print("Error opening obj file"); pause(); exit(-1); }

	std::string garbagestring;
	char garbagechar;

	num_verts = 0;
	std::string line;
	while (std::getline(is, line))
	{
		std::istringstream iss(line);
		if (line[0] == 'v' && line[1] == ' ')
		{
			Vertex vertex;
			iss >> garbagestring >> vertex.x >> vertex.y >> vertex.z;
			vs.push_back(vertex);
			num_verts++;
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			Vertex normal;
			iss >> garbagestring >> normal.x >> normal.y >> normal.z;
			ns.push_back(normal);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			Vertex uv;
			iss >> garbagestring >> uv.x >> uv.y;
			uvss.push_back(uv);
		}
		if (line[0] == 'f') break;
	}
	verts = new real32[num_verts * FLOATS_PER_VERTEX];
	for (int i = 0; i < num_verts; i++)
	{
		Vertex v = vs.at(i);
		verts[i * 3] = v.x;
		verts[i * 3 + 1] = v.y;
		verts[i * 3 + 2] = v.z;
	}

	uvs = new real32[num_verts * FLOATS_PER_UV];
	normals = new real32[num_verts * FLOATS_PER_NORMAL];
	memset(uvs, 0, num_verts * FLOATS_PER_UV * sizeof(real32));
	memset(normals, 0, num_verts * FLOATS_PER_NORMAL * sizeof(real32));
	num_indices = 0;

	processLine(line);
	while (std::getline(is, line))
	{
		if (line[0] != 'f') continue;
		
		processLine(line);
	} 

	for (int i = 0; i < isv.size(); i++)
		print("index[" << i << "] is: " << isv.at(i));
	indices = new GLushort[num_indices];
	for (int i = 0; i < num_indices;)
		indices[i] = isv.at(i++);

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