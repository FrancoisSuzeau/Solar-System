/*
AUTHOR : SUZEAU François

DATE : 09/10/2021

MODULE : Model

NAMEFILE : Model.cpp

PURPOSE : class Model
*/
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Model.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Model::Model(std::string const path)
{
    this->loadModel(path)   ;
}

Model::~Model()
{

}

/***********************************************************************************************************************************************************************/
/****************************************************************************** loadModel ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Model::loadModel(std::string const path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << ">> Loading Model ASSIMP : ERROR" << import.GetErrorString() << std::endl;
    }
    std::cout << ">> Loading Model ASSIMP : SUCCESS" << std::endl;

    m_directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** processNode ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Model::processNode(aiNode *node, const aiScene *scene)
{
    std::cout << " In process node " << std::endl;
    if((node !=nullptr) && (scene != nullptr))
    {
        std::cout << " pass if "  << std::endl;

        for (GLuint i(0); i < node->mNumMeshes; i++)
        {
            std::cout << " in first for " << i << std::endl;

            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back(processMesh(mesh, scene));
        }

        for (GLuint i(0); i < node->mNumChildren; i++)
        {
            std::cout << " in second for " << i << std::endl;

            processNode(node->mChildren[i], scene);
        }
    }
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** processMesh ******************************************************************************/
/***********************************************************************************************************************************************************************/
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    if((mesh != nullptr) && (scene != nullptr))
    {
        
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texturate> textures;

        for(GLuint i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
                glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                // positions
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
                // normals
                if (mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    vertex.Normal = vector;

                    // std::cout << mesh << std::endl;

                }
                
            
                // texture coordinates
                if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    // std::cout << mesh << std::endl;
                    glm::vec2 vec;
                    // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vec.x = mesh->mTextureCoords[0][i].x; 
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                    // std::cout << mesh->mTextureCoords[0][i].x << std::endl;
                    // tangent
                    // vector.x = mesh->mTangents[i].x;
                    // vector.y = mesh->mTangents[i].y;
                    // vector.z = mesh->mTangents[i].z;
                    // vertex.Tangent = vector;
                    // std::cout << mesh << std::endl;
                    // // bitangent
                    // vector.x = mesh->mBitangents[i].x;
                    // vector.y = mesh->mBitangents[i].y;
                    // vector.z = mesh->mBitangents[i].z;
                    // vertex.Bitangent = vector;
                }
                else
                {
                    
                    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
                }
                    
                
                vertices.push_back(vertex);
        }

        for(GLuint i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(GLuint j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);   
            }
                         
        }
        if(mesh->mMaterialIndex >= 0)
        {
            // process materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
            // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
            // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
            // Same applies to other texture as the following list summarizes:
            // diffuse: texture_diffuseN
            // specular: texture_specularN
            // normal: texture_normalN

            // 1. diffuse maps
            std::vector<Texturate> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            // 2. specular maps
            std::vector<Texturate> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            // 3. normal maps
            // std::vector<Texturate> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, "texture_normal");
            // textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            // // 4. height maps
            // std::vector<Texturate> heightMaps = loadMaterialTexture(material, aiTextureType_AMBIENT, "texture_height");
            // textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        }
            
            
            // return a mesh object created from the extracted mesh data
            return Mesh(vertices, indices, textures);
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************** loadMaterialTexture ****************************************************************************/
/***********************************************************************************************************************************************************************/
std::vector<Texturate> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string const typeName)
{
    // std::cout << " LOAD MATERIAL TEXTURE"  << std::endl;
    if(mat != nullptr)
    {
        std::vector<Texturate> textures;
        for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            GLboolean skip = false;

            for (GLuint j = 0; j < textures_loaded.size(); i++)
            {
                if(textures_loaded[j].path == str)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }

            if(!skip)
            {
                Texturate texture;
                texture.id = textureFromFile(str.C_Str(), m_directory);
                texture.type = typeName;
                texture.path = str;
                textures.push_back(texture);
            }
            
            // mat->GetTexture(type, i, &str);
            // Texturate texture;
            // texture.id = textureFromFile(str.C_Str(), m_directory);
            // texture.type = typeName;
            // texture.path = str.C_Str();
            // textures.push_back(texture);
        }
        return textures;
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************** textureFromFile ********************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Model::textureFromFile(const char *path, const std::string &directory)
{
    // std::cout << "IN TEXTURE FROM FILE" << std::endl;
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** draw *********************************************************************************/
/***********************************************************************************************************************************************************************/
void Model::draw(Shader *model_shader)
{
    
    if(model_shader != nullptr)
    {
        for (unsigned int i(0); i < m_meshes.size(); i++)
        {
            m_meshes[i].draw(model_shader);
        }
        
    }
}