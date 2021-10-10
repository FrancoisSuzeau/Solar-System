/*
AUTHOR : SUZEAU François

DATE : 09/10/2021

MODULE : Model

NAMEFILE : Model.hpp

PURPOSE : header of the Model class
*/

#ifndef MODEL_H
#define MODEL_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <GL/glew.h>

        #include <assimp/Importer.hpp>
        #include <assimp/scene.h>
        #include <assimp/postprocess.h>

        

        #include <iostream>
        #include <string>
        #include <math.h>
        #include <vector>
        #include <Windows.h>
        

        #include "../Shader/Shader.hpp"
        #include "Mesh.hpp"

       

/********************************************************************* class definition *********************************************************************/

        class Model
        {
            
            private:

                std::vector<Mesh>               m_meshes;
                std::vector<Texturate>          textures_loaded;
                std::string                     m_directory;


                void loadModel(std::string const path);
                void processNode(aiNode *node, const aiScene *scene);
                unsigned int textureFromFile(const char *path, const std::string &directory);

                Mesh processMesh(aiMesh *mesh, const aiScene *scene);

                std::vector<Texturate> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string const typeName);

                
            public:
            
                Model(std::string const path);
                ~Model();

                void draw(Shader *model_shader);

        };


#endif