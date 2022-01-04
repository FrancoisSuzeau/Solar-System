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
Spaceship::Spaceship(std::string const path, float scale) : m_yaw(0.0f), m_pitch(90.0f), m_speed(200.0f), m_sensibility(0.3f), m_scale(scale)
{
    m_spaceship_model = new Model(path);
    assert(m_spaceship_model);

    glm::mat4 model(1.0f);

    m_model_matrice = model;

    m_current_pos = glm::vec3(0.0f, 9000.0f, 0.0f);
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
void Spaceship::drawSpaceship(RenderData &render_data, Input input)
{
    
    if((m_spaceship_model != nullptr) && ((render_data.getShader("model") != nullptr)))
    {
        
        this->move(input);

        m_model_matrice = glm::mat4(1.0f);
        
        this->orientateShip(input);
        this->positioningShip();
        this->scalingShip();
        
        m_spaceship_model->draw(render_data, m_model_matrice);

        
    }
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** move **************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::move(Input input)
{
    if(input.getKey(SDL_SCANCODE_W))
    {
        m_current_pos += m_ship_orientation * m_speed;
    }
    if(input.getKey(SDL_SCANCODE_S))
    {
        m_current_pos -= m_ship_orientation * m_speed;
    }

    if(input.getKey(SDL_SCANCODE_A))
    {
       m_current_pos += m_lateral_move * m_speed;
    }

    if(input.getKey(SDL_SCANCODE_D))
    {
       m_current_pos -= m_lateral_move * m_speed;
    }
    if(input.getKey(SDL_SCANCODE_LSHIFT))
    {
       m_current_pos += glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * m_speed;
    }
    if(input.getKey(SDL_SCANCODE_LCTRL))
    {
        m_current_pos -= glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * m_speed;
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** positioningShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::positioningShip()
{
    //it is important to reintitialise the model matrice, if not all the calculation are made by the ancient calculation and we loose the space ship
    m_model_matrice = glm::mat4(1.0f);

    // m_model_matrice = glm::translate(m_model_matrice, m_current_pos);

    m_model_matrice *= (yaw_mat * pitch_mat);

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* orientateShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::orientateShip(Input input)
{
    this->rotateFromPitch(input);
    this->rotateFromYaw(input);

    glm::vec3 dir;
    dir.x = sin(glm::radians(m_yaw));
    dir.y = -cos(glm::radians(m_yaw));
    dir.z = cos(glm::radians(m_pitch));

    m_ship_orientation = glm::normalize(dir);

    //TODO : modify to an other method
    m_lateral_move = cross(glm::vec3(0.0f, 0.0f, 1.0f), m_ship_orientation);
    m_lateral_move = normalize(m_lateral_move);

}

/***********************************************************************************************************************************************************************/
/*************************************************************************** rotateFromPitch ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::rotateFromPitch(Input input)
{
    pitch_mat = glm::mat4(1.0f);

    if( input.getMouseButton(SDL_BUTTON_LEFT) )
    {
        m_pitch += input.getYRel() * m_sensibility;

        if(m_pitch > 179.0f)
        {
            m_pitch = 179.0f;
        }
        else if (m_pitch < -0.1f)
        {
            m_pitch = -0.1f;
        }
    }

    pitch_mat = glm::rotate(pitch_mat, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** rotateFromYaw ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::rotateFromYaw(Input input)
{
    yaw_mat = glm::mat4(1.0f);

    if(input.getMouseButton(SDL_BUTTON_LEFT))
    {
        m_yaw -= input.getXRel() * m_sensibility;

    }
    
    yaw_mat = glm::rotate(yaw_mat, glm::radians(m_yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* scalingShip ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::scalingShip()
{
    m_model_matrice = glm::scale(m_model_matrice, glm::vec3(m_scale));
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* getters ***************************************************************************/
/***********************************************************************************************************************************************************************/
glm::vec3 Spaceship::getPosition() const
{
    return m_current_pos;
}

glm::vec3 Spaceship::getOrientation() const
{
    return m_ship_orientation;
}

glm::vec3 Spaceship::getLateralMove() const
{
    return m_lateral_move;
}

float Spaceship::getSpeed() const
{
    return m_speed;
}

void Spaceship::setSpeed(float speed)
{
    m_speed = m_speed + speed;
    if(m_speed < 0.0f)
    {
        m_speed = 0.0f;
    }

    if(m_speed > 200.0f)
    {
        m_speed = 200.0f;
    }
}

void Spaceship::setMinimumSpeed()
{
    m_speed = 0.6f;
}

void Spaceship::setMaximumSpeed()
{
    m_speed = 200.0f;
}

float Spaceship::getRotY() const
{
    return m_pitch;
}

float Spaceship::getRotX() const
{
    return m_yaw;
}