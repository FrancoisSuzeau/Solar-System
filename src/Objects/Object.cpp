/*
AUTHOR : SUZEAU François

DATE : 29/05/2021

MODULE : Objects

NAMEFILE : Object.hpp

PURPOSE : class Object
*/

#include "Object.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Object::Object()
{
    
}

Object::~Object()
{
   
}

/***********************************************************************************************************************************************************************/
/************************************************************************** shared methods *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Object::updatePosition(glm::vec3 const new_pos)
{
    m_position = new_pos;
}

void Object::rotateObject(glm::mat4 &model, float angle)
{
    model = glm::rotate(model, glm::radians(angle), m_rotation_vector);
}

void Object::inclineObject(glm::mat4 &model, float angle)
{
    model = glm::rotate(model, glm::radians(angle), m_inclinaison_vector);
}

void Object::translateObject(glm::mat4 &model, glm::vec3 pos)
{
    model = glm::translate(model, pos);
}

void Object::scaleObject(glm::mat4 &model, glm::vec3 size)
{
    model = glm::scale(model, size);
}

glm::vec3 Object::getPosition() const
{
    return m_position;
}

glm::vec3 Object::getSize() const
{
    return m_size;
}

glm::mat4 Object::getModelMat()
{
    return m_model_mat;
}