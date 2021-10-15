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
    //destroy VBO
    // glDeleteBuffers(1, &m_vbo);
    // glDeleteBuffers(1, &m_ebo);
    
    // //destroy VAO
    // glDeleteVertexArrays(1, &m_vao);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** setupMesh ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Mesh::setupMesh()
{
    //destroy a possible ancient VAO
    // if(glIsVertexArray(m_vao) == GL_TRUE)
    // {
    //     glDeleteVertexArrays(1, &m_vao);
    // }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &m_vao);

    //destroy a possible ancient VBO
    // if(glIsBuffer(m_vbo) == GL_TRUE)
    // {
    //     glDeleteBuffers(1, &m_vbo);
    // }
    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vbo);

    //destroy a possible ancient EBO
    // if(glIsBuffer(m_ebo) == GL_TRUE)
    // {
    //     glDeleteBuffers(1, &m_ebo);
    // }
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
void Mesh::draw(Shader *mesh_shader)
{
    if(mesh_shader != nullptr)
    {
        
        glUseProgram(mesh_shader->getProgramID());
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
                
                std::cout << "diffuse : " << diffuseNr << std::endl;
                std::cout << "specular : " << specularNr << std::endl;
                std::cout << "normal : " << normalNr << std::endl;
                std::cout << "height : " << heightNr << std::endl;
                mesh_shader->setTexture((name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
            }

            //mesh_shader->setFloat("material.shininess", 16.0f);

            // glActiveTexture(GL_TEXTURE0);

            

                glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);

            // for (GLuint i = 0; i < this->m_textures.size(); i++)
            // {
            //     glActiveTexture(GL_TEXTURE0 + i);
            //     glBindTexture(GL_TEXTURE_2D, 0);
            // }
            
            glActiveTexture(GL_TEXTURE0);
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