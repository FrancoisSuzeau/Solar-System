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
        #include <fstream>
        #include <sstream>
        #include <iostream>
        #include <map>
        #include <string>
        #include <math.h>
        #include <vector>
        #include <Windows.h>
        
        #include "../Application/DataManager.hpp"
        #include "../ErrorHandler/ErrorHandler.hpp"
        #include "Mesh.hpp"

       

/********************************************************************* class definition *********************************************************************/

        class Model
        {
            
            private:

                std::vector<Mesh>               m_meshes;
                std::vector<Texturate>          textures_loaded;
                std::string                     m_directory;
                bool                            m_gammaCorrection;
                

                void loadModel(std::string const &path);
                void processNode(aiNode *node, const aiScene *scene);
                unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);

                Mesh processMesh(aiMesh *mesh, const aiScene *scene);

                std::vector<Texturate> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string const typeName);

                
            public:
            
                Model(std::string const &path, bool gamma = false);
                ~Model();

                void draw(DataManager &data_manager, glm::mat4 model_mat);
                unsigned int getMeshVAO(int index) const;
                size_t getSizeMeshesVector() const;
                unsigned int getTextureLoadedID(int index) const;
                size_t getMeshVectorIndiceSize(int index) const;

                void    clean();
                
        };


#endif