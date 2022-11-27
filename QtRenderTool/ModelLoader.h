#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL.h>

using namespace std;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec3 Bitangents;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    string type;
    aiString path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture);
    void Draw(Shader shader);

private:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};


class Model
{
public:
    /*  Functions   */
    // Constructor, expects a filepath to a 3D model.
    Model(const char* path);

    // Draws the model, and thus all its meshes
    void Draw(Shader shader);

private:
    /*  Model Data  */
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    /*  Functions   */
    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string path);

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};