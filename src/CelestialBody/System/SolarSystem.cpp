/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : SolarSystem.cpp

PURPOSE : class SolarSystem
*/

#include "SolarSystem.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
SolarSystem::SolarSystem(std::string name, TTF_Font *police, int celestial_object_count, Shader *model_shader)
{
    m_planete_info = new PlaneteInformation("None", police);
    if(m_planete_info == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    m_system_name = name;
    m_companion_count = celestial_object_count;
    m_planetarySYS_count = 3;
    m_simple_planete_count = 5;
    // m_amount = 2500;

    skybox = new Skybox();
    if(skybox == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    sun = new Star(1, 70, 70, "../assets/textures/CelestialBody/SunMap.jpg", "Sun", 3270);
    if(sun == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    m_asteroid_field = new AsteroidField(model_shader);
    if(m_asteroid_field == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    // asteroid = new Model("../assets/model/rock/rock.obj");
    // if(asteroid == nullptr)
    // {
    //     exit(EXIT_FAILURE);
    // }
    // this->initModel();

    m_body_shader.push_back(new Shader("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/oneTexturePlanete.frag"));
    if(m_body_shader[0] == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_body_shader[0]->loadShader();

    m_body_shader.push_back(new Shader("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/MultiPlaneteTexture.frag"));
    if(m_body_shader[1] == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_body_shader[1]->loadShader();

    m_body_shader.push_back(new Shader("../src/Shader/Shaders/sunShader.vert", "../src/Shader/Shaders/sunShader.frag"));
    if(m_body_shader[2] == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_body_shader[2]->loadShader();

    m_ring_shader = new Shader("../src/Shader/Shaders/texture.vert", "../src/Shader/Shaders/texture.frag");
    if(m_ring_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_ring_shader->loadShader();

    m_sphere_shader = new Shader("../src/Shader/Shaders/sphereShader.vert", "../src/Shader/Shaders/sphereShader.frag");
    if(m_sphere_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_sphere_shader->loadShader();

    m_sun_atmo_shader = new Shader("../src/Shader/Shaders/sunAtmo.vert", "../src/Shader/Shaders/sunAtmo.frag");
    if(m_sun_atmo_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_sun_atmo_shader->loadShader();

    if(model_shader != nullptr)
    {
        m_model_shader = model_shader;
    }
    

}

SolarSystem::SolarSystem() : sun()
{

}

SolarSystem::~SolarSystem()
{
    for (int i(0); i < m_planetarySYS_count; i++)
    {
        if(m_planetary_system[i] != nullptr)
        {
            delete m_planetary_system[i];
        }
        
    }

    for (int i(0); i < m_simple_planete_count; i++)
    {
        if(m_planete_creator[i] != nullptr)
        {
            delete m_planete_creator[i];
        }
        
    }
    
    if(skybox != nullptr)
    {
        delete skybox;
    }
    
    if(sun != nullptr)
    {
        delete sun;
    }

    if(m_asteroid_field != nullptr)
    {
        delete m_asteroid_field;
    }

    // if(asteroid != nullptr)
    // {
    //     delete asteroid;
    // }
    

    if(m_planete_info != nullptr)
    {
        delete m_planete_info;
    }

    for (int i(0); i < 3; i++)
    {
        if(m_body_shader[i] != nullptr)
        {
            delete m_body_shader[i];
        }
    }

    if(m_ring_shader != nullptr)
    {
        delete m_ring_shader;
    }

    if(m_sphere_shader != nullptr)
    {
        delete m_sphere_shader;
    }

    if(m_sun_atmo_shader != nullptr)
    {
        delete m_sun_atmo_shader;
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* loadSystem ****************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::loadSystem(int count, TTF_Font *police)
{
    if(police == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    /************************************************* loading planetary system ********************************************************/
    //Earth System
    if(count == 1)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        if(m_planetary_system[0] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planetary_system[0]->MakingSystem("Earth System", 1, police);
        m_planetary_system[0]->loadSystem(count, police);
    }

    //Jovian System
    if(count == 2)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        if(m_planetary_system[1] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planetary_system[1]->MakingSystem("Jovian System", 4, police);
        m_planetary_system[1]->loadSystem(count, police);
    }

    //Saturian System
    if(count == 3)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        if(m_planetary_system[2] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planetary_system[2]->MakingSystem("Saturnian System", 3, police);
        m_planetary_system[2]->loadSystem(count, police);
    }  
    //===================================================================================================================

    /************************************************* loading simple planete ********************************************************/

    if(count == 4)
    {
        m_planete_creator.push_back(new SimplePlaneteCreator());
        if(m_planete_creator[0] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planete_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MercuryMap.jpg", "Mercury", 11.49f, 0.01f, glm::vec3(5790.0f, 0.0f, 0.0f), police);
    }
    
    if(count == 5)
    {
        m_planete_creator.push_back(new AtmoPlaneteCreator());
        if(m_planete_creator[1] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planete_creator[1]->MakingPlanete("../assets/textures/CelestialBody/VenusMap.jpg", "Venus", 28.47f, 177.3f, glm::vec3(0.0f, -10820.0f, 0.0f), police);
    }

    if(count == 6)
    {
        m_planete_creator.push_back(new AtmoPlaneteCreator());
        if(m_planete_creator[2] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planete_creator[2]->MakingPlanete("../assets/textures/CelestialBody/MarsMap.jpg", "Mars", 15.99f, 25.19f, glm::vec3(0, 22790, 0), police);
    }

    if(count == 7)
    {
        m_planete_creator.push_back(new PlaneteRingCreator());
        if(m_planete_creator[3] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planete_creator[3]->MakingPlanete("../assets/textures/CelestialBody/UranusCloud.jpg", "Uranus", 120.21f, 97.77f, glm::vec3(-287070.0f, 0.0f, 0.0f), police);
    }
    if(count == 8)
    {
        m_planete_creator.push_back(new PlaneteRingCreator());
        if(m_planete_creator[4] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_planete_creator[4]->MakingPlanete("../assets/textures/CelestialBody/NeptuneCloud.jpg", "Neptune", 116.49f, 26.32f, glm::vec3(0.0f, 449840.0f, 0.0f), police);
    }
    //===================================================================================================================

}
/***********************************************************************************************************************************************************************/
/*********************************************************************************** displaySkybox *********************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{
    glm::mat4 save = modelview;

        if(skybox != nullptr)
        {
            skybox->display(projection, modelview, hdr);
        }
        

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAsteroidField ******************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr)
{
    glm::mat4 save = projection_view_mat[1];

    if(m_asteroid_field != nullptr)
    {
        m_asteroid_field->drawAsteroidField(projection_view_mat, hdr);
    }
        
    projection_view_mat[1] = save;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos, Shader *host_shader, Shader *companion_shader, Shader *ring_shader)
{
    glm::mat4 save = modelview;

    /************************************************* SUN RENDER ********************************************************/
        if(sun == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        glm::vec3 m_position = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(m_position, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 save_light_src = light_src;

        if(sun != nullptr)
        {
            sun->updatePosition(projection, modelview, 0.0f);
            sun->updatePositionLight(projection, light_src);
        
            if(m_body_shader[2] != nullptr)
            {
                sun->display(projection, modelview, light_src, camPos, hdr, m_body_shader[2]);
            }
        }
        
    /************************************************* MERCURY RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planete_creator[0] != nullptr)
        {
            m_planete_creator[0]->UpdatePositionPlan(projection, modelview);
            m_planete_creator[0]->updatePosLight(projection, light_src);

            if(m_body_shader[0] != nullptr)
            {
                m_planete_creator[0]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[0]);
            }
        }
        
    /************************************************* VENUS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planete_creator[1] != nullptr)
        {
            m_planete_creator[1]->UpdatePositionPlan(projection, modelview);
            m_planete_creator[1]->updatePosLight(projection, light_src);

            if(m_body_shader[1] != nullptr)
            {
                m_planete_creator[1]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[1]);
            }
        }
        
    /************************************************* EARTH RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planetary_system[0] != nullptr)
        {
            if( (m_body_shader[1] != nullptr) && (m_body_shader[0] != nullptr) )
            {
                m_planetary_system[0]->drawSystem(projection, modelview, camPos, hdr, m_position, m_body_shader[1], m_body_shader[0]);
            }
        }

    /************************************************* MARS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planete_creator[2] != nullptr)
        {
            m_planete_creator[2]->UpdatePositionPlan(projection, modelview);
            m_planete_creator[2]->updatePosLight(projection, light_src);
    
            if(m_body_shader[1] != nullptr)
            {
                m_planete_creator[2]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[1]);
            }
        }
        
    /************************************************* JUPITER RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planetary_system[1] != nullptr)
        {
            if( m_body_shader[0] != nullptr )
            {
                m_planetary_system[1]->drawSystem(projection, modelview, camPos, hdr, m_position, m_body_shader[0], m_body_shader[0]);
            }
        }
        
    /************************************************* SATURN RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planetary_system[2] != nullptr)
        {
            if( (m_body_shader[0] != nullptr) && (m_ring_shader != nullptr) )
            {
                m_planetary_system[2]->drawSystem(projection, modelview, camPos, hdr, m_position, m_body_shader[0], m_body_shader[0], m_ring_shader);
            }
        }
        
    /************************************************* URANUS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planete_creator[3] != nullptr)
        {
            m_planete_creator[3]->UpdatePositionPlan(projection, modelview);
            m_planete_creator[3]->updatePosLight(projection, light_src);
            
            if( (m_body_shader[0] != nullptr) && (m_ring_shader != nullptr) )
            {
                m_planete_creator[3]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[0], m_ring_shader);
            }
        }
        
    /************************************************* NEPTUNE RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planete_creator[4] != nullptr)
        {
            m_planete_creator[4]->UpdatePositionPlan(projection, modelview);
            m_planete_creator[4]->updatePosLight(projection, light_src);

            if( (m_body_shader[0] != nullptr) && (m_ring_shader != nullptr) )
            {
                m_planete_creator[4]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[0], m_ring_shader);
            }
        }
        
    //restaure the modelview matrix
    modelview = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader)
{
    
    glm::mat4 save = modelview;

    for (int i(0); i < m_planetarySYS_count; i++)
    {
        if(m_planetary_system[i] != nullptr)
        {
            if(name_render_shader != nullptr)
            {
                m_planetary_system[i]->drawName(projection, modelview, camPos, name_render_shader);
            }
        }

        modelview = save;
    }

    modelview = save;


    for (int i(0); i < m_simple_planete_count; i++)
    {
       if(m_planete_creator[i] != nullptr)
       {
           if(name_render_shader != nullptr)
            {
                m_planete_creator[i]->displayName2(projection, modelview, camPos, name_render_shader);
            }
       }

        modelview = save;
    }

    modelview = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    glm::mat4 save = modelview;

    /************************************************* SUN ATMO RENDER ********************************************************/
        if(sun == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        glm::vec3 position_sun = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(position_sun, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
        
        // if(sun != nullptr)
        // {
        //     if(m_sun_atmo_shader != nullptr)
        //     {
        //         sun->displayAtmo(projection, modelview, hdr, m_sun_atmo_shader);
        //     }
            
        // }

    modelview = save;
    glm::mat4 save_light_src = light_src;

    /************************************************* OTHER ATMO RENDER ********************************************************/

    for(int i(0); i < m_planetarySYS_count; i++)
    {
        if(m_planetary_system[i] != nullptr)
        {
            if(m_sphere_shader != nullptr)
            {
                m_planetary_system[i]->drawAtmo(projection, modelview, camPos, hdr, m_sphere_shader);
            }
            
        }
        
        modelview = save;
    }

    modelview = save;

    for(int i(0); i < m_simple_planete_count; i++)
    {
        if(m_planete_creator[i] != nullptr)
        {
            m_planete_creator[i]->UpdatePositionPlan(projection, modelview);
            m_planete_creator[i]->updatePosLight(projection, light_src);

            if((m_sphere_shader != nullptr) && (m_planete_creator[i] != nullptr))
            {
                m_planete_creator[i]->drawAtmoPlanete(projection, modelview, light_src, camPos, hdr, m_sphere_shader);
            }
            
        }

        modelview = save;
        light_src = save_light_src;
    }

    modelview = save;
    light_src = save_light_src;

    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *plan_info, Shader *text_shader, Shader *square_shader)
{
    
    glm::mat4 save = modelview;

    for(int i(0); i < m_simple_planete_count; i++)
    {
        if( (m_planete_creator[i] != nullptr) && (m_planete_info != nullptr))
        {
            glm::vec3 planete_pos = m_planete_creator[i]->getPostion();
            float size_plan = m_planete_creator[i]->getSizePlan();
    

            float x = camPos[0] - planete_pos[0]; //doesn't know why I have to use the reverse value
            float y = camPos[1] - planete_pos[1];
            float z = camPos[2] - planete_pos[2];
                
                
            float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
                
            float r = std::sqrt(r_squarre);

            if(r <= 10 * size_plan)
            {
                modelview = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
                //m_planete_creator[i]->drawInfoPlan(projection, modelview, hdr);
                std::string tmp_name = m_planete_creator[i]->getName();
                
                if(tmp_name != m_planete_info->getInfoName())
                {
                    m_planete_info->changeNamePlan(tmp_name);
                }


                if((text_shader != nullptr) && (square_shader != nullptr))
                {
                    m_planete_info->renderInfo(projection, modelview, hdr, text_shader, square_shader);
                }
            }
        }
        
        modelview = save;
    
    }

    modelview = save;

    //display information of planetof the planetary system
    for (int i(0); i < m_planetarySYS_count; i++)
    {
        if(m_planetary_system[i] != nullptr)
        {
            if((text_shader != nullptr) && (square_shader != nullptr))
            {
                m_planetary_system[i]->drawInfo(projection, modelview, camPos, hdr, m_planete_info, text_shader, square_shader);
            }
        }
        
        modelview = save;
    }

    modelview = save;
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** initModel **************************************************************************/
/***********************************************************************************************************************************************************************/
// void SolarSystem::initModel()
// {
//     if(sun == nullptr)
//     {
//         exit(EXIT_FAILURE);
//     }
                        
//     glm::vec3 m_position = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
//     glm::mat4 light_src = glm::lookAt(m_position, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
//     glm::mat4 save_light_src = light_src;

//     modelMatrices = new glm::mat4[m_amount];
//     modelLights = new glm::mat4[m_amount];

//     float radius = 9000.0f;
//     float offset = 100.0f;

//     for (unsigned int i = 0; i < m_amount; i++)
//     {
//         glm::mat4 model(1.0f);

//         float angle = (float) i / (float) m_amount * 360.0f;
//         float displacement = (rand() % (int)(2*offset * 100)) / 100.0f - offset;
//         float x = cos(glm::radians(angle)) * radius + displacement;

//         displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//         float y = sin(glm::radians(angle)) * radius + displacement;

//         displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//         float z = displacement * 0.4f;

//         model = glm::translate(model, glm::vec3(x, y, z));
//         light_src = glm::translate(light_src, glm::vec3(x, y, z));

//         float rotAngle = (rand() % 360);
//         model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//         light_src = glm::rotate(light_src, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

//         float scaleM = (rand() % 20) / 100.0f + 5.0f;
//         model = glm::scale(model, glm::vec3(scaleM));
//         light_src = glm::scale(light_src, glm::vec3(scaleM));

//         modelMatrices[i] = model;
//         modelLights[i] = light_src;

//         light_src = save_light_src;

//     }
// }