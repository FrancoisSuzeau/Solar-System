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
Spaceship::Spaceship() : m_yaw(0.0f), m_pitch(90.0f), m_speed(0.0f), speed_limit(0.05f)
{   

    file_paths.push_back("../../assets/model/spaceship/untitled.obj");
    // file_paths.push_back("../../assets/model/donut/donut.obj");
    // file_paths.push_back("../../assets/model/spaceshuttle/spaceshuttle.obj");

    m_spaceship_models = nullptr;

    m_scales.push_back(0.1f);
    // m_scales.push_back(3.0f);
    // m_scales.push_back(0.1f);

    m_model_mat = glm::mat4(1.f);

    // m_current_pos = glm::vec3(0.0f, 9000.0f, 0.0f);
    m_current_pos = glm::vec3(0.f, 0.f, 0.f);
    directions[0] = false;
    directions[1] = false;
    directions[2] = false;
    directions[3] = false;
    directions[4] = false;
    directions[5] = false;

    m_sensibility[0] = 0.0f;
    m_sensibility[1] = 0.0f;

    y_dir = 0.0f;
    x_dir = 0.0f;
}

Spaceship::~Spaceship()
{
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* transform *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::transform()
{
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* clean *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::clean()
{
    if(m_spaceship_models != nullptr)
    {
        m_spaceship_models->clean();
        delete m_spaceship_models;
        m_spaceship_models = nullptr;

    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* drawSpaceship *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::drawSpaceship(DataManager &data_manager, Input input)
{
    if((m_spaceship_models != nullptr) && ((data_manager.getShader("model") != nullptr)))
    {
        
        this->move(input);

        m_model_mat = glm::mat4(1.0f);
        
        this->orientateShip(input);
        this->positioningShip();
        // this->scalingShip(render_data.getIndexShip());
        this->scalingShip(0);
        
        m_spaceship_models->draw(data_manager, m_model_mat);
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
        if(m_speed < speed_limit)
        {
            m_speed += 5.0f;
        }
        directions[0] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_W) && directions[0])
    {
        if(m_speed >= 5.0f)
        {
            m_speed -= 5.0f;
            m_current_pos += m_ship_orientation * m_speed;
        }
        else
        {
            directions[0] = false;
        }
        
    }

    if(input.getKey(SDL_SCANCODE_S))
    {
        m_current_pos -= m_ship_orientation * m_speed;
        if(m_speed < speed_limit)
        {
            m_speed += 5.0f;
        }
        directions[1] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_S) && directions[1])
    {
        if(m_speed >= 5.0f)
        {
            m_speed -= 5.0f;
            m_current_pos -= m_ship_orientation * m_speed;
        }
        else
        {
            directions[1] = false;
        }
    }

    if(input.getKey(SDL_SCANCODE_A))
    {
       m_current_pos += m_lateral_move * m_speed;
       if(m_speed < speed_limit)
        {
            m_speed += 5.0f;
        }

        directions[2] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_A) && directions[2])
    {
        if(m_speed >= 5.0f)
        {
            m_speed -= 5.0f;
            m_current_pos += m_lateral_move * m_speed;
        }
        else
        {
            directions[2] = false;
        }
    }

    if(input.getKey(SDL_SCANCODE_D))
    {
       m_current_pos -= m_lateral_move * m_speed;
       if(m_speed < speed_limit)
        {
            m_speed += 5.0f;
        }
        directions[3] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_D) && directions[3])
    {
        if(m_speed >= 5.0f)
        {
            m_speed -= 5.0f;
            m_current_pos -= m_lateral_move * m_speed;
        }
        else
        {
            directions[3] = false;
        }
    }

    if(input.getKey(SDL_SCANCODE_LSHIFT))
    {
       m_current_pos += glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * m_speed;
       if(m_speed < speed_limit)
       {
           m_speed += 5.0f;
       }
       directions[4] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_LSHIFT) && directions[4])
    {
        if(m_speed >= 5.0f)
        {
            m_speed -= 5.0f;
            m_current_pos += glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * m_speed;
        }
        else
        {
            directions[4] = false;
        }
    }

    if(input.getKey(SDL_SCANCODE_LCTRL))
    {
        m_current_pos -= glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * m_speed;
        if(m_speed < speed_limit)
        {
            m_speed += 5.0f;
        }
        directions[5] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_LCTRL) && directions[5])
    {
        if(m_speed >= 5.0f)
        {
            m_speed -= 5.0f;
            m_current_pos -= glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * m_speed;
        }
        else
        {
            directions[5] = false;
        }
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** positioningShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::positioningShip()
{
    //it is important to reintitialise the model matrice, if not all the calculation are made by the ancient calculation and we loose the space ship
    m_model_mat = glm::mat4(1.0f);

    m_model_mat = glm::translate(m_model_mat, m_current_pos);

    m_model_mat *= (yaw_mat * pitch_mat);

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
        y_dir = input.getYRel();
        m_pitch += y_dir * m_sensibility[0];
        if(m_sensibility[0] < 0.3)
        {
            m_sensibility[0] += 0.01;
        }

        if(m_pitch > 179.0f)
        {
            m_pitch = 179.0f;
        }
        else if (m_pitch < -0.1f)
        {
            m_pitch = -0.1f;
        }
    }
    else if(!input.getMouseButton(SDL_BUTTON_LEFT))
    {
        if(m_sensibility[0] >= 0.01)
        {
            m_sensibility[0] -= 0.01;
        }

        m_pitch += y_dir * m_sensibility[0];

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
        x_dir = input.getXRel();
        m_yaw -= x_dir * m_sensibility[1];

        if(m_sensibility[1] < 0.3)
        {
            m_sensibility[1] += 0.01;
        }
    }
    else if(!input.getMouseButton(SDL_BUTTON_LEFT))
    {
        if(m_sensibility[1] >= 0.01)
        {
            m_sensibility[1] -= 0.01;
        }

        m_yaw -= x_dir * m_sensibility[1];
    }
    
    yaw_mat = glm::rotate(yaw_mat, glm::radians(m_yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* scalingShip ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::scalingShip(int index)
{
    // std::cout << m_scales[index] << std::endl;
    // m_model_mat = glm::scale(m_model_mat, glm::vec3(m_scales[index]));
    m_model_mat = glm::scale(m_model_mat, glm::vec3(0.1f));
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* loadModelShip *************************************************************************/
/***********************************************************************************************************************************************************************/
void Spaceship::loadModelShip(DataManager &data_manager)
{
    // if(render_data.getChangeModel())
    if(true)
    {
        // std::cout << file_paths[render_data.getIndexShip()] << std::endl;
        std::cout << file_paths[0] << std::endl;

        if(m_spaceship_models != nullptr)
        {
            delete m_spaceship_models;
            m_spaceship_models = nullptr;
        }

        // m_spaceship_models = new Model(file_paths[render_data.getIndexShip()]);
        m_spaceship_models = new Model(file_paths[0]);
        // render_data.setChangeModel(false);

        
    }
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
    speed_limit = speed_limit + speed;
    if(speed_limit < 0.0f)
    {
        speed_limit = 0.0f;
    }

    if(speed_limit > 200.0f)
    {
        speed_limit = 200.0f;
    }
}

void Spaceship::setMinimumSpeed()
{
    speed_limit = 5.0f;

    if(m_speed > speed_limit)
    {
        m_speed = speed_limit;
    }
}

void Spaceship::setMaximumSpeed()
{
    speed_limit = 200.0f;
}

float Spaceship::getRotY() const
{
    return m_pitch;
}

float Spaceship::getRotX() const
{
    return m_yaw;
}

void Spaceship::updateSpeed(float const new_val)
{
    if((new_val >= 0.0) && (new_val <= 200.0))
    {
        speed_limit = new_val;
    }
}