/*
AUTHOR : SUZEAU François

DATE : 27/11/2021

MODULE : CelestialBody.Planete

NAMEFILE : Planete.cpp

PURPOSE : class Planete
*/


#include "Planete.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
// Planete::Planete(init_data data, TTF_Font *police) :
// m_name(data.name)
// {
//     heighhtScale = 0.000001f;

//     for (size_t i = 0; i < data.texture_path.size(); i++)
//     {
//         m_textures.push_back(new Texture(data.texture_path[i]));
//         assert(m_textures[i]);
//         assert(m_textures[i]->loadTexture());
//         RenderData::renderLog(data.texture_path[i]);
//     }
    
//     assert(police);
//     m_name_renderer = new Text(3.0f, 0.2f, 6.0f, "../assets/font/aAtmospheric.ttf", police);
//     assert(m_name_renderer);
//     assert(m_name_renderer->loadTTF(m_name));
//     // RenderData::renderLog("../assets/font/aAtmospheric.ttf");


//     m_normal_surface = new Texture(data.nom_disp_path[0]);
//     assert(m_normal_surface);
//     assert(m_normal_surface->loadTexture());
//     // RenderData::renderLog(data.nom_disp_path[0]);

//     displacement_map = new Texture(data.nom_disp_path[1]);
//     assert(displacement_map);
//     assert(displacement_map->loadTexture());
//     // RenderData::renderLog(data.nom_disp_path[1]);
    
//     //TODO : changing it to a special method
//     m_inclinaison_angle = data.inclinaison_angle;
//     m_real_size = data.size;
//     m_initial_pos = data.position;
//     m_current_position = m_initial_pos;
//     m_rotation_angle = 0.0f;
//     m_inclinaison_angle = data.inclinaison_angle;
//     m_speed_rotation = data.speed_rotation;
//     m_type_plan = data.type_plan;
//     is_near = false;

//     if(m_name == "Mars")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_oppacity = 0.3f;

//         m_ring = nullptr;
//     }
//     else if(m_name == "Earth")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_oppacity = 0.3f;

//         m_ring = nullptr;

//     }
//     else if(m_name == "Venus")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_oppacity = 0.115f;

//         m_ring = nullptr;

//     }
//     else if(m_name == "Jupiter")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_ring = nullptr;

//     }
//     else if(m_name == "Saturn")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_ring = new Ring(4, "../../assets/textures/CelestialBody/SaturnRing.png", data);
//         assert(m_ring);

//     }
//     else if(m_name == "Uranus")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_ring = new Ring(4, "../../assets/textures/CelestialBody/UranusRing.png", data);
//         assert(m_ring);
//     }
//     else if(m_name == "Neptune")
//     {
//         m_atmosphere = new Atmosphere(1.05f, m_name);
//         assert(m_atmosphere);

//         m_ring = new Ring(4, "../../assets/textures/CelestialBody/NeptuneRing.png", data);
//         assert(m_ring);
//     }
//     else
//     {
//         m_atmosphere = nullptr;
//         m_ring = nullptr;
//     }
// }

Planete::Planete(float size, std::vector<std::string> surface_tex_paths, std::string const type, int shininess, float const oppacity) : super(size, type),
m_oppacity(oppacity), m_shininess(shininess)
{
    int i = 0;
    for(std::vector<std::string>::iterator it = surface_tex_paths.begin(); it != surface_tex_paths.end(); ++it)
    {
        super::surface_tex_ids.push_back(Loader::loadTextureWithSDL(it[0]));
        assert(super::surface_tex_ids[i] != 0);
        i++;
    }

    m_rotation_angle = 0.f;
    m_speed_rotation = 0.1f;
}

Planete::~Planete()
{
    // for (std::vector<Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
    // {
    //     if(it[0] != nullptr)
    //     {
    //         delete it[0];
    //     }
    // }

    // if(m_atmosphere != nullptr)
    // {
    //     delete m_atmosphere;
    // }

    // if(m_ring != nullptr)
    // {
    //     delete m_ring;
    // }
    

    // if(m_name_renderer != nullptr)
    // {
    //     delete m_name_renderer;
    // }

    // if(m_normal_surface != nullptr)
    // {
    //     delete m_normal_surface;
    // }

    // if(displacement_map != nullptr)
    // {
    //     delete displacement_map;
    // }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::transform(glm::vec3 ship_pos, Input *input)
{
    super::transform(ship_pos, input);
    super::m_rotation_vector = glm::vec3(0.f, 0.f, 1.f);

    super::m_rotation_angle += super::m_speed_rotation;
    if(super::m_rotation_angle >= 360)
    {
        super::m_rotation_angle -= 360;
    }
    super::rotateObject(super::m_model_mat, super::m_rotation_angle);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::sendToShader(DataManager &data_manager)
{
    if(data_manager.getShader(super::m_type) != nullptr)
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());

            data_manager.getShader(super::m_type)->setVec3("viewPos", data_manager.getCamPos());
            data_manager.getShader(super::m_type)->setVec3("sunPos", data_manager.getSunPos());
            data_manager.getShader(super::m_type)->setTexture("material.texture0", 0);
            data_manager.getShader(super::m_type)->setInt("material.shininess", m_shininess);
            data_manager.getShader(super::m_type)->setFloat("far", data_manager.getFar());
            data_manager.getShader(super::m_type)->setFloat("near", data_manager.getNear());
            data_manager.getShader(super::m_type)->setInt("render_depth", data_manager.getDepthRender());

            if(super::m_type == "double_textured_planete")
            {
                data_manager.getShader(super::m_type)->setTexture("material.texture1", 1);
                data_manager.getShader(super::m_type)->setFloat("oppacity", m_oppacity);
            }

        glUseProgram(0);
    }
    
    super::sendToShader(data_manager);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** updatePosition *************************************************************************/
/***********************************************************************************************************************************************************************/
// void Planete::updatePosition(glm::vec3 shipPos)
// {
//     m_model_mat = glm::mat4(1.0f);
//     m_model_mat = glm::translate(m_model_mat, (m_current_position - shipPos));

//     m_model_mat = rotate(m_model_mat, glm::radians(m_inclinaison_angle), vec3(0.0, 1.0, 0.0));

//                     //making the planete rotation
//     m_rotation_angle += m_speed_rotation;
//     if(m_rotation_angle >= 360)
//     {
//         m_rotation_angle -= 360;
//     }

//     m_model_mat = rotate(m_model_mat, glm::radians(m_rotation_angle), vec3(0.0, 0.0, 1.0));

//     m_model_mat = glm::scale(m_model_mat, vec3(m_real_size));
// }

// /***********************************************************************************************************************************************************************/
// /********************************************************************************** getters ****************************************************************************/
// /***********************************************************************************************************************************************************************/
// std::string Planete::getName() const
// {
//     return m_name;
// }

// float Planete::getRadiusFromCam(glm::vec3 camPos)
// {
//     float x = camPos[0] - m_current_position[0];
//     float y = camPos[1] - m_current_position[1];
//     float z = camPos[2] - m_current_position[2];

//     float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
//     return std::sqrt(r_squarre);

// }

// float Planete::getPhiFromCam(glm::vec3 camPos)
// {
//     float x = camPos[0] - m_current_position[0];
//     float y = camPos[1] - m_current_position[1];

//     return atan(y/x);
// }

// float Planete::getThetaFromCam(glm::vec3 camPos, float r)
// {
//     float z = camPos[2] - m_current_position[2];

//     return acos(z/r);
// }

// std::string Planete::getTypePlan() const
// {
//     return m_type_plan;
// }

// std::vector<Texture*> Planete::getPlanTexture() const
// {
//     return m_textures;
// }

// Texture* Planete::getNormalTexture() const
// {
//     return m_normal_surface;
// }

// Texture* Planete::getDispTexture() const
// {
//     return displacement_map;
// }

// glm::mat4 Planete::getModelMat() const
// {
//     return m_model_mat;
// }

// Text* Planete::getNameRender() const
// {
//     return m_name_renderer;
// }

// glm::vec3 Planete::getPosition() const
// {
//     return m_current_position;
// }

// float Planete::getOppacity() const
// {
//     return m_oppacity;
// }

// Atmosphere* Planete::getAtmosphere() const
// {
//     return m_atmosphere;
// }

// Ring* Planete::getRing() const
// {
//     return m_ring;
// }

// float Planete::getSize() const
// {
//     return m_real_size;
// }

// bool Planete::getProximity() const
// {
//     return is_near;
// }

// void Planete::setProximity(bool change)
// {
//     is_near = change;
// }

// void Planete::updateHeightScale()
// {
//     heighhtScale += 0.000001f;
//     if(heighhtScale >=  0.01f)
//     {
//         heighhtScale = 0.000001f;
//     }
// }

// float Planete::getHeightScale() const
// {
//     return heighhtScale;
// }