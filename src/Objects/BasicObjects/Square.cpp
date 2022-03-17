/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Square.cpp

PURPOSE : class Square
*/

#include "Square.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Square::Square(float size) : Object()
{
    m_size = glm::vec3(size);
    m_model_mat = glm::mat4(1.0);
}

Square::~Square()
{
    
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::transform(Input *input)
{
    m_model_mat = glm::mat4(1.0);

    this->scaleObject(m_model_mat, m_size);
    this->translateObject(m_model_mat, m_position);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::sendToShader(DataManager &data_manager)
{
    if(data_manager.getShader("square") != nullptr)
    {
        //Activate the shader
        glUseProgram(data_manager.getShader("square")->getProgramID());

            //send matrices to shader
            data_manager.getShader("square")->setMat4("projection", data_manager.getProjMat());
            data_manager.getShader("square")->setMat4("view", data_manager.getViewMat());
            data_manager.getShader("square")->setMat4("model", this->getModelMat());
            data_manager.getShader("square")->setFloat("color", this->getColor());

            // data_manager.getShader("square")->setInt("hdr", data_manager.getHDR());

        glUseProgram(0);
    }
}