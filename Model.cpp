#include "Model.h"

Model::Model(char* filepath)
{
	std::ifstream is(filepath);
	if (is.bad()) { print("Error opening obj file"); pause(); exit(-1); }

	std::string garbagestring;
	char garbagechar;

	std::vector<glm::vec3> tempVerts;
	std::vector<glm::vec2> tempUVS;
	std::vector<glm::vec3> tempNormals;

	std::vector<uint32> vertIndices;
	std::vector<uint32> uvIndices;
	std::vector<uint32> normalIndices;

	std::string line;
	while (std::getline(is, line))
	{
		std::istringstream iss(line);
		if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 vertex;
			iss >> garbagestring >> vertex.x >> vertex.y >> vertex.z;
			tempVerts.push_back(vertex);
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			glm::vec3 normal;
			iss >> garbagestring >> normal.x >> normal.y >> normal.z;
			tempNormals.push_back(normal);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			glm::vec2 uv;
			iss >> garbagestring >> uv.x >> uv.y;
			tempUVS.push_back(uv);
		}
		if (line[0] == 'f')
		{
			uint32 vertIndex[3];
			uint32 uvIndex[3];
			uint32 normalIndex[3];
			iss >> garbagechar >> vertIndex[0] >> garbagechar >> uvIndex[0] >> garbagechar >> normalIndex[0] 
							   >> vertIndex[1] >> garbagechar >> uvIndex[1] >> garbagechar >> normalIndex[1] 
							   >> vertIndex[2] >> garbagechar >> uvIndex[2] >> garbagechar >> normalIndex[2];
			
			vertIndices.push_back(vertIndex[0]);
			vertIndices.push_back(vertIndex[1]);
			vertIndices.push_back(vertIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for(int i = 0; i < vertIndices.size(); i++)
	{
		uint32 vertexIndex = vertIndices.at(i);
		glm::vec3 vertex = tempVerts.at(vertexIndex - 1);
		verts.push_back(vertex);

		uint32 uvIndex = uvIndices.at(i);
		glm::vec2 uv = tempUVS.at(uvIndex - 1);
		uvs.push_back(uv);

		uint32 normalIndex = normalIndices.at(i);
		glm::vec3 normal = tempNormals.at(normalIndex - 1);
		normals.push_back(normal);
	}
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvbo);
	glGenBuffers(1, &nbo);
	// Not necessary right now
	glGenBuffers(1, &ibo);

	bind();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);	
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	unbind();
}

void 
Model::bind()
{
	glBindVertexArray(vao);
}

void 
Model::unbind()
{
	glBindVertexArray(0);
}

uint32 
Model::vertCount()
{
	return(verts.size());
}