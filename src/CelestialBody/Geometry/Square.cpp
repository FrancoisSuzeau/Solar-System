/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : CelestialObject.Geometry

NAMEFILE : Square.h

PURPOSE : class Square
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Square.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Square::Square(float size, float const color) : m_vboID(0),
m_bytes_colors_size(18 * sizeof(float))
{

    m_bytes_vertices_size = 18 * sizeof(float);
    m_size = size;
    m_size /= 2;
    float verticesTmp[] = {-m_size, -m_size, -m_size,   m_size, -m_size, -m_size,   m_size, m_size, -m_size,   
                        -m_size, -m_size, -m_size,   -m_size, m_size, -m_size,   m_size, m_size, -m_size  

                        };


    float colorsTmp[] = {color, color, color,   color, color, color,   color, color, color,
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

Square::Square()
{
    
}

Square::~Square()
{
    //destroy VBO
    glDeleteBuffers(1, &m_vboID);
    
    //destroy VAO
    glDeleteVertexArrays(1, &m_vaoID);
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* display *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 color, bool hdr, Shader *square_shader)
{
    if(square_shader != nullptr)
    {
        //Activate the shader
        glUseProgram(square_shader->getProgramID());

            //lock vao
            glBindVertexArray(m_vaoID);

            //send matrices to shader
            glUniformMatrix4fv(glGetUniformLocation(square_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
            glUniformMatrix4fv(glGetUniformLocation(square_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

            square_shader->setInt("hdr", hdr);
            square_shader->setVec3("color2", color);

            //display the form
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // glDisableVertexAttribArray(1);
            // glDisableVertexAttribArray(0);


            //unlock vao
            glBindVertexArray(0);

        glUseProgram(0);
    }
    
}



/***********************************************************************************************************************************************************************/
/*********************************************************************************** load ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::load()
{
    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vboID);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_colors_size, 0, GL_DYNAMIC_DRAW);
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
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &m_vaoID);
    }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &m_vaoID);

    //lock VAO
    glBindVertexArray(m_vaoID);

        //lock VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

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
/********************************************************************************* updateVBO ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::updateVBO(void *data, int size_bytes, int offset)
{
    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        //take the VBO adress
        void *VBO_adress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        /*
            - GL_READ_ONLY
            - GL_WRITE_ONLY
            - GL_READ_WRITE
        */
       if(VBO_adress == NULL)
       {
           std::cout << ">> Load VBO adress : ERROR" << std::endl;
           glBindBuffer(GL_ARRAY_BUFFER, 0);

           return;

       }

       //update data
       memcpy((char*)VBO_adress + offset, data, size_bytes);

       //cancel VBO pointer
       glUnmapBuffer(GL_ARRAY_BUFFER);
       VBO_adress = 0;

    //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** drawLoad **********************************************************************/
/***********************************************************************************************************************************************************************/
void Square::drawLoad(int count, glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 color, Shader *square_shader)
{
    glm::mat4 save = modelview;
    

    if(square_shader != nullptr)
    {
        if(count == 0)
        {
                modelview = translate(modelview, vec3((count - 12.2f) * 0.05f, -0.3f, 0.0f));
                display(projection, modelview, color, false, square_shader);

            //restaure the modelview matrix
            modelview = save;

                modelview = translate(modelview, vec3((count - 11.2f) * 0.05f, -0.3f, 0.0f));
                display(projection, modelview, color, false, square_shader);

            //restaure the modelview matrix
            modelview = save;

                modelview = translate(modelview, vec3((count - 10.2f) * 0.05f, -0.3f, 0.0f));
                display(projection, modelview, color, false, square_shader);

            //restaure the modelview matrix
            modelview = save;
        }
        else
        {
            for (int i = 0; i < count * 3; i++)
            {
                    modelview = translate(modelview, vec3((i - 12.2f) * 0.05f, -0.3f, 0.0f));
                    display(projection, modelview, color, false, square_shader);

                modelview = save;

                    modelview = translate(modelview, vec3((i - 11.2f) * 0.05f, -0.3f, 0.0f));
                    display(projection, modelview, color, false, square_shader);

                modelview = save;

                    modelview = translate(modelview, vec3((i - 10.2f) * 0.05f, -0.3f, 0.0f));
                    display(projection, modelview, color, false, square_shader);

                modelview = save;
            }
        }
    }

    
}

//NOT CONCERN
void Square::displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 color, bool hdr, Shader *square_shader)
{

}