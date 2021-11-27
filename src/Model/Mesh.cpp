/*
AUTHOR : SUZEAU François

DATE : 09/10/2021

MODULE : Mesh

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
void Mesh::draw(RenderData &render_data, glm::mat4 &model_mat, glm::vec3 camPos)
{
    if(render_data.getShader("model") != nullptr)
    {
        glUseProgram(render_data.getShader("model")->getProgramID());

        render_data.getShader("model")->setMat4("projection", render_data.getProjectionMat());
        render_data.getShader("model")->setMat4("view", render_data.getViewMat());
        render_data.getShader("model")->setMat4("model", model_mat);
        render_data.getShader("model")->setVec3("viewPos", camPos);

        render_data.getShader("model")->setInt("hdr", render_data.getHDR());
        
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
                
                render_data.getShader("model")->setTexture((name + number).c_str(), i);
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