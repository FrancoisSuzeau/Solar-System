/*
AUTHOR : SUZEAU François

DATE : 09/10/2021

MODULE : Renderers::ModelRenderer

NAMEFILE : Mesh.cpp

PURPOSE : class Mesh
*/

#include "Mesh.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texturate> textures)
//  apply move-semantics using rvalue refs + std::move()
{
    this->m_vertices = vertices;
    this->m_indices = indices;
    this->m_textures = textures;

    setupMesh();
}

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    //REMEMBER : DO NOT DESTROY VAO, VBO and EBO
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** setupMesh ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Mesh::setupMesh()
{

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);


    glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

        
    // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glEnableVertexAttribArray(3);	
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

        glEnableVertexAttribArray(4);	
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        // ids
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

		// weights
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
            
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


}

/***********************************************************************************************************************************************************************/
/******************************************************************************** draw *********************************************************************************/
/***********************************************************************************************************************************************************************/
void Mesh::draw(DataManager &data_manager, glm::mat4 model_mat)
{
    if(data_manager.getShader("model") != nullptr)
    {
        glUseProgram(data_manager.getShader("model")->getProgramID());

        data_manager.getShader("model")->setMat4("projection", data_manager.getProjMat());
        data_manager.getShader("model")->setMat4("view", data_manager.getViewMat());
        data_manager.getShader("model")->setMat4("model", model_mat);
        // data_manager.getShader("model")->setVec3("viewPos", data_manager.getCamPos());
        // data_manager.getShader("model")->setVec3("sunPos", data_manager.getSunPos());

        // data_manager.getShader("model")->setInt("hdr", data_manager.getHDR());
        
        glBindVertexArray(m_vao);

            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;

            for (unsigned int i(0); i < m_textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                std::string number;
                std::string name = m_textures[i].type;

                if(name == "texture_diffuse")
                {
                    number = std::to_string(diffuseNr++);
                }
                else if(name == "texture_specular")
                {
                    number = std::to_string(specularNr++);
                }
                else if(name == "texture_normal")
                {
                    number = std::to_string(normalNr++);
                }
                else if(name == "texture_height")
                {
                    number = std::to_string(heightNr++);
                }
                
                data_manager.getShader("model")->setTexture((name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
            }

            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);

            for (unsigned int i(0); i < m_textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, 0);

            }
            

            glUseProgram(0);
        
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** getters ********************************************************************************/
/***********************************************************************************************************************************************************************/
std::vector <Vertex> Mesh::getVertices() const
{
    return m_vertices;
}

std::vector <unsigned int> Mesh::getIndices() const
{
    return m_indices;
}

std::vector <Texturate> Mesh::getTextures() const
{
    return m_textures;
}

unsigned int Mesh::getVAO() const
{
    return m_vao;
}