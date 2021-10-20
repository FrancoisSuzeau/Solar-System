/*
AUTHOR : SUZEAU François

DATE : 17/10/2021

MODULE : Spaceship

NAMEFILE : Spaceship.cpp

PURPOSE : class Spaceship
*/

#include "Spaceship.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Spaceship::Spaceship(std::string const path) : cam_phi(0.0f), cam_theta(-90.0f)
{
    m_spaceship_model = new Model(path);

    glm::mat4 model(1.0f);
    glm::mat4 light_src(1.0f);

    m_model_light_matrice.push_back(model);
    m_model_light_matrice.push_back(light_src);
}

Spaceship::~Spaceship()
{
    if(m_spaceship_model != nullptr)
    {
        delete m_spaceship_model;
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* drawSpaceship *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::drawSpaceship(std::vector<glm::mat4> projection_view_mat, bool hdr, Shader *model_shader, Camera *camera, Input input)
{
    
    if((m_spaceship_model != nullptr) && ((model_shader != nullptr)))
    {
        this->positioningShip(camera);
        this->orientateShip(camera, input);
        this->scalingShip();

        m_spaceship_model->draw(projection_view_mat, m_model_light_matrice, hdr, model_shader);
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** positioningShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::positioningShip(Camera *camera)
{
    glm::vec3 cam_position = camera->getPosition();
    m_current_pos = glm::vec3(0.0f + cam_position.x, -4.8f + cam_position.y, -1.2f + cam_position.z);

    //it is important to reintitialise the model matrice, if not all the calculation are made by the ancient calculation and we loose the space ship
    m_model_light_matrice[0] = glm::mat4(1.0f);

    glm::vec3 sun_pos = glm::vec3(0.01f, 0.0f, 0.0f);
    m_model_light_matrice[1] = glm::lookAt(sun_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    m_model_light_matrice[0] = glm::translate(m_model_light_matrice[0], m_current_pos);
    m_model_light_matrice[1] = glm::translate(m_model_light_matrice[1], m_current_pos);

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* orientateShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::orientateShip(Camera *camera, Input input)
{
    if( (input.getMouseButton(SDL_MOUSEBUTTONDOWN)) && input.getMouseButton(SDL_BUTTON_LEFT) )
    {
        cam_phi = camera->getPhi();
        cam_theta = camera->getTheta();
    }

    m_model_light_matrice[0] = glm::rotate(m_model_light_matrice[0], glm::radians(90.0f - cam_phi), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model_light_matrice[1] = glm::rotate(m_model_light_matrice[1], glm::radians(90.0f - cam_phi), glm::vec3(1.0f, 0.0f, 0.0f));

    m_model_light_matrice[0] = glm::rotate(m_model_light_matrice[0], glm::radians(90.0f + cam_theta), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model_light_matrice[1] = glm::rotate(m_model_light_matrice[1], glm::radians(90.0f + cam_theta), glm::vec3(0.0f, 1.0f, 0.0f));
    

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* scalingShip ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::scalingShip()
{
    m_model_light_matrice[0] = glm::scale(m_model_light_matrice[0], glm::vec3(0.3f));
    m_model_light_matrice[1] = glm::scale(m_model_light_matrice[1], glm::vec3(1.0f));
}