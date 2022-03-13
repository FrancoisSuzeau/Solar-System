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