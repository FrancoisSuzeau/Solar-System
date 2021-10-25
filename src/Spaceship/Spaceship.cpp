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
Spaceship::Spaceship(std::string const path) : m_yaw(0.0f), m_pitch(90.0f), m_speed(0.1f), m_sensibility(0.5f)
{
    m_spaceship_model = new Model(path);
    if(m_spaceship_model == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    glm::mat4 model(1.0f);
    glm::mat4 light_src(1.0f);

    m_model_light_matrice.push_back(model);
    m_model_light_matrice.push_back(light_src);

    m_current_pos = glm::vec3(1.0f, 9000.0f, 1.0f);
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
void Spaceship::drawSpaceship(std::vector<glm::mat4> projection_view_mat, bool hdr, Shader *model_shader, Input input, glm::vec3 camPos)
{
    
    if((m_spaceship_model != nullptr) && ((model_shader != nullptr)))
    {
        
        this->move(input);

        this->positioningShip();
        this->scalingShip();
        this->orientateShip(input);
        

        m_spaceship_model->draw(projection_view_mat, m_model_light_matrice, hdr, model_shader, camPos);

        
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
        if(m_speed < 1.0f)
        {
            m_speed += 0.1f;
        }
    }
    if(input.getKey(SDL_SCANCODE_S))
    {
        m_current_pos -= m_ship_orientation * m_speed;
        if(m_speed < 1.0f)
        {
            m_speed += 0.1f;
        }
    }

    if(input.getKey(SDL_SCANCODE_A))
    {
       
    }

    if(input.getKey(SDL_SCANCODE_D))
    {
       
    }
    if(input.getKey(SDL_SCANCODE_LCTRL))
    {
       
    }
    if(input.getKey(SDL_SCANCODE_LSHIFT))
    {
        
    }

    if(m_speed > 0.1 && input.getEvent().type == SDL_KEYUP)
    {
        m_current_pos += m_ship_orientation * m_speed;
        m_speed -= 0.1;
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** positioningShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::positioningShip()
{
    //it is important to reintitialise the model matrice, if not all the calculation are made by the ancient calculation and we loose the space ship
    m_model_light_matrice[0] = glm::mat4(1.0f);

    glm::vec3 sun_pos = glm::vec3(0.01f, 0.0f, 0.0f);
    m_model_light_matrice[1] = glm::lookAt(sun_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    m_model_light_matrice[0] = glm::translate(m_model_light_matrice[0], m_current_pos);
    m_model_light_matrice[1] = glm::translate(m_model_light_matrice[1], m_current_pos);

    m_model_light_matrice[0] *= (yaw_mat * pitch_mat);
    m_model_light_matrice[1] *= (yaw_mat * pitch_mat);

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

    // m_ship_orientation = glm::normalize(dir);
    m_ship_orientation = dir;
}

void Spaceship::rotateFromPitch(Input input)
{
    pitch_mat = glm::mat4(1.0f);

    if( input.getMouseButton(SDL_BUTTON_LEFT) )
    {
        m_pitch += input.getYRel() * 0.1f;

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

void Spaceship::rotateFromYaw(Input input)
{
    yaw_mat = glm::mat4(1.0f);

    if(input.getMouseButton(SDL_BUTTON_LEFT))
    {
        m_yaw += input.getXRel() * 0.1f;

    }
    
    yaw_mat = glm::rotate(yaw_mat, glm::radians(m_yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* scalingShip ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::scalingShip()
{
    m_model_light_matrice[0] = glm::scale(m_model_light_matrice[0], glm::vec3(0.3f));
    m_model_light_matrice[1] = glm::scale(m_model_light_matrice[1], glm::vec3(1.0f));
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