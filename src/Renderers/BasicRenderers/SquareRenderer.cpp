/*
AUTHOR : SUZEAU François

DATE : 06/03/2022

MODULE : Renderers::BasicRenderers

NAMEFILE : SquareRenderer.cpp

PURPOSE : class SquareRenderer
*/

#include "SquareRenderer.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
SquareRenderer::SquareRenderer(float const color)
{
    super::m_vboID = 0;
    super::m_vaoID = 0;
    m_bytes_vertices_size = 18 * sizeof(float);
    m_bytes_colors_size = 18 * sizeof(float);

    float verticesTmp[] = {
                            -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, 0.5f, -0.5f,   
                            -0.5f, -0.5f, -0.5f,   -0.5f, 0.5f, -0.5f,   0.5f, 0.5f, -0.5f  
                        };


    float colorsTmp[] = {
                            color, color, color,   color, color, color,   color, color, color,
                            color, color, color,   color, color, color,   color, color, color,
                        };

    //copying all value in our tab
    for (int i(0); i < 18; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_colors[i] = colorsTmp[i];
    }

    this->load();

}

SquareRenderer::~SquareRenderer()
{
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void SquareRenderer::clean()
{
    //destroy VBO
    if(glIsBuffer(super::m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
        super::m_vboID = 0;
    }

    if(glIsVertexArray(super::m_vaoID) == GL_TRUE)
    {
        //destroy VAO
        glDeleteVertexArrays(1, &m_vaoID);
        super::m_vaoID = 0;
    }

    std::cout << ">> SQUARE RENDERER : DESTROY COMPLETE" << std::endl;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** load ******************************************************************************/
/***********************************************************************************************************************************************************************/
void SquareRenderer::load()
{
    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(super::m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
        super::m_vboID = 0;
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vboID);
    assert(super::m_vboID != 0);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, super::m_vboID);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_colors_size, 0, GL_STATIC_DRAW);
        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices);
       glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_colors_size, m_colors);


    //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //===================================================================================================================

    /************************************************* VAO management ********************************************************/
    //destroy a possible ancient VAO
    if(glIsVertexArray(super::m_vaoID) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &m_vaoID);
        super::m_vaoID = 0;
    }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &m_vaoID);
    assert(super::m_vaoID != 0);

    //lock VAO
    glBindVertexArray(super::m_vaoID);

        //lock VBO
        glBindBuffer(GL_ARRAY_BUFFER, super::m_vboID);

        //acces to the vertices in video memory
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //acces to the colors in video memory
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
        glEnableVertexAttribArray(1);

        //unlock VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unlock VAO
    glBindVertexArray(0);
    //===================================================================================================================

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* render ******************************************************************************/
/***********************************************************************************************************************************************************************/
void SquareRenderer::render(DataManager &data_manager, Object *square)
{
    if(data_manager.getShader(square->getType()) != nullptr)
    {
        //Activate the shader
        glUseProgram(data_manager.getShader(square->getType())->getProgramID());

            //lock vao
            glBindVertexArray(super::m_vaoID);

            //display the form
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //unlock vao
            glBindVertexArray(0);

        glUseProgram(0);
    }
    
}