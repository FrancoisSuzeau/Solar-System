/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Square.hpp

PURPOSE : class Square
*/

#include "Square.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Square::Square(float size, float const color) : Object()
{
    m_bytes_vertices_size = 18 * sizeof(float);
    m_bytes_colors_size = 18 * sizeof(float);
    m_size = glm::vec3(size);
    m_model_mat = glm::mat4(1.0);

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

Square::~Square()
{
    //destroy VBO
    glDeleteBuffers(1, &m_vboID);
    
    //destroy VAO
    glDeleteVertexArrays(1, &m_vaoID);

    if( (glIsBuffer(m_vboID) == GL_FALSE) && (glIsVertexArray(m_vaoID) == GL_FALSE))
    {
        std::cout << "SQUARE :: delete >>> SUCESS" << std::endl;
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
/********************************************************************************* render ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::render(DataManager &data_manager)
{
    if(data_manager.getShader("square") != nullptr)
    {
        //Activate the shader
        glUseProgram(data_manager.getShader("square")->getProgramID());

            //lock vao
            glBindVertexArray(m_vaoID);

            //send matrices to shader
            data_manager.getShader("square")->setMat4("projection", data_manager.getProjMat());
            data_manager.getShader("square")->setMat4("view", data_manager.getViewMat());
            data_manager.getShader("square")->setMat4("model", m_model_mat);

            // data_manager.getShader("square")->setInt("hdr", data_manager.getHDR());

            //display the form
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //unlock vao
            glBindVertexArray(0);

        glUseProgram(0);
    }
    
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::transform()
{
    m_model_mat = glm::mat4(1.0);

    this->translateObject(m_model_mat, m_position);
    // this->scaleObject(m_model_mat, m_size);
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** drawLoad **********************************************************************/
/***********************************************************************************************************************************************************************/
// void Square::drawLoad(int count, RenderData &render_data, glm::vec3 color)
// {
//     glm::mat4 save = render_data.getViewMat();
    
//     bool save_hdr = render_data.getHDR();
//     render_data.updateHDR(false);

//     if(render_data.getShader("square") != nullptr)
//     {
        

//         glUseProgram(render_data.getShader("square")->getProgramID());

//             render_data.getShader("square")->setInt("load", true);

//         glUseProgram(0);
//         if(count == 0)
//         {
//                 this->updatePosition(glm::vec3((count - 12.2f) * 0.05f, -0.3f, 0.0f));
//                 display(render_data, color);

//             //restaure the view matrix
//             render_data.updateView(save);

//                 this->updatePosition(glm::vec3((count - 11.2f) * 0.05f, -0.3f, 0.0f));
//                 display(render_data, color);

//             //restaure the view matrix
//             render_data.updateView(save);

//                 this->updatePosition(glm::vec3((count - 10.2f) * 0.05f, -0.3f, 0.0f));
//                 display(render_data, color);

//             //restaure the view matrix
//             render_data.updateView(save);
//         }
//         else
//         {
//             for (int i = 0; i < count * 3; i++)
//             {
//                     this->updatePosition(glm::vec3((i - 12.2f) * 0.05f, -0.3f, 0.0f));
//                     display(render_data, color);

//                 render_data.updateView(save);

//                     this->updatePosition(glm::vec3((i - 11.2f) * 0.05f, -0.3f, 0.0f));
//                     display(render_data, color);

//                 render_data.updateView(save);

//                     this->updatePosition(glm::vec3((i - 10.2f) * 0.05f, -0.3f, 0.0f));
//                     display(render_data, color);

//                 render_data.updateView(save);
//             }
//         }
//     }

//     render_data.updateHDR(save_hdr);
    
// }