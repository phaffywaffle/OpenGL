// Fix the texture loading to work my way

#include "Model.h"

Model::Model(char* obj_path, char* bmp_path)
{
	name = obj_path;

	std::ifstream os(obj_path);
	if (os.bad()) { print("Error opening obj file"); pause(); exit(-1); }

	std::string garbagestring;
	char garbagechar;

	std::vector<glm::vec3> tempVerts;
	std::vector<glm::vec2> tempUVS;
	std::vector<glm::vec3> tempNormals;

	std::vector<uint32> vertIndices;
	std::vector<uint32> uvIndices;
	std::vector<uint32> normalIndices;

	std::string line;
	while (std::getline(os, line))
	{
		std::istringstream oss(line);
		if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 vertex;
			oss >> garbagestring >> vertex.x >> vertex.y >> vertex.z;
			tempVerts.push_back(vertex);
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			glm::vec3 normal;
			oss >> garbagestring >> normal.x >> normal.y >> normal.z;
			tempNormals.push_back(normal);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			glm::vec2 uv;
			oss >> garbagestring >> uv.x >> uv.y;
			tempUVS.push_back(uv);
		}
		if (line[0] == 'f')
		{
			uint32 vertIndex[3];
			uint32 uvIndex[3];
			uint32 normalIndex[3];
			oss >> garbagechar >> vertIndex[0] >> garbagechar >> uvIndex[0] >> garbagechar >> normalIndex[0] 
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

// My way: Broken
//	std::ifstream bs(bmp_path);
//	if (bs.bad()) { print("Error opening bmp file"); pause(); exit(-1); }
//
//	std::getline(bs, line);
//	std::istringstream bss(line);

// Copy/paste from online tutorials: working 
	FILE * file = fopen(bmp_path,"rb");
	if (!file){ print("Image could not be opened\n\t: Line 88"); pause(); exit(-1); }

//	for(uint32 i = 0; i < 54; i++)
//	{
//		bss >> garbagechar;
//		//if(garbagechar == ' ') garbagechar = 'f';
//		header[i] = garbagechar;
//	}

	unsigned char header[54];
	if (fread(header, 1, 54, file)!=54 ) { print("Not a correct BMP file\n\t: Line 90"); pause(); exit(-1); }

	if(header[0] != 'B' || header[1] != 'M') { print("Error reading bmp file " << bmp_path << ": not a bmp file"); pause(); exit(-1); }

	uint32 dataPos = *(uint32*)&(header[0x0A]);
	uint32 imageSize = *(uint32*)&(header[0x22]);
	uint32 width = *(uint32*)&(header[0x12]);
	uint32 height = *(uint32*)&(header[0x16]);

	if (imageSize==0) { imageSize=width*height*3; }
	if (dataPos==0) { dataPos=54; }

	unsigned char* data = new unsigned char[imageSize];

//	for(uint32 i = 0; i < imageSize; i++)
//	{
//		bss >> data[i];
//	}

	fread(data,1,imageSize,file);
	fclose(file);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvbo);
	glGenBuffers(1, &nbo);
	// Not necessary right now
	//glGenBuffers(1, &ibo);
	glGenTextures(1, &texture);

	bind();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);	
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unbind();

	delete[] data;
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