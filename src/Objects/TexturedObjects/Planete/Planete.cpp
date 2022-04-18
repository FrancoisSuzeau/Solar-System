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

Planete::Planete(body_data datas) : super(datas.size, datas.type),
m_oppacity(datas.oppacity), m_name(datas.name)
{
    super::height_scale = 0.000001f;
    int i = 0;
    for(std::vector<std::string>::iterator it = Loader::textures_path[datas.name].begin(); it != Loader::textures_path[datas.name].end(); ++it)
    {
        super::surface_tex_ids.push_back(Loader::loadTextureWithSDL(it[0]));
        assert(super::surface_tex_ids[i] != 0);
        i++;
    }

    std::string normals_path = "../../assets/textures/normalMap/" + m_name + "_normalMap.jpg";
    super::normal_texture_id = Loader::loadTextureWithSDL(normals_path);
    assert(normal_texture_id != 0);

    // normals_path = "../../assets/textures/displacementMap/" + m_name + "_dispMap.jpg";
    // super::displacement_texture_id = Loader::loadTextureWithSDL(normals_path);
    // assert(displacement_texture_id != 0);

    super::m_rotation_angle = 0.f;
    super::m_speed_rotation = 0.1f;
    super::m_shininess = datas.shininess;
    super::m_position = datas.initial_pos;
    super::m_inclinaison_angle = datas.inclinaison_angle;

    if(m_name == "Saturn")
    {
        std::vector<std::string> texture_path;
        texture_path.push_back("../../assets/textures/CelestialBody/SaturnRing.png");
        m_ring = new Ring(25.f,  texture_path, "ring", 32, super::m_inclinaison_angle);
        assert(m_ring);
    }

    if(m_name == "Uranus")
    {
        std::vector<std::string> texture_path;
        texture_path.push_back("../../assets/textures/CelestialBody/UranusRing.png");
        m_ring = new Ring(25.f,  texture_path, "ring", 32, super::m_inclinaison_angle);
        assert(m_ring);
    }

    if(m_name == "Neptune")
    {
        std::vector<std::string> texture_path;
        texture_path.push_back("../../assets/textures/CelestialBody/NeptuneRing.png");
        m_ring = new Ring(25.f,  texture_path, "ring", 32, super::m_inclinaison_angle);
        assert(m_ring);
    }
}

Planete::~Planete()
{

    // if(m_atmosphere != nullptr)
    // {
    //     delete m_atmosphere;
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
/****************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::clean()
{
    if(m_ring != nullptr)
    {
        m_ring->clean();
        delete m_ring;
        m_ring = nullptr;
    }

    super::clean();
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::transform(glm::vec3 ship_pos, Input *input)
{
    super::transform(ship_pos, input);

    super::inclineObject(super::m_model_mat, super::m_inclinaison_angle);

    super::m_rotation_angle += super::m_speed_rotation;
    if(super::m_rotation_angle >= 360)
    {
        super::m_rotation_angle -= 360;
    }
    super::rotateObject(super::m_model_mat, super::m_rotation_angle);

    // super::height_scale += 0.000001f;
    // if(super::height_scale >=  0.01f)
    // {
    //     super::height_scale = 0.000001f;
    // }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::sendToShader(DataManager &data_manager)
{
    if((data_manager.getShader(super::m_type) != nullptr) && (data_manager.getPass() == COLOR_FBO))
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());
            data_manager.getShader(super::m_type)->setVec3("viewPos", data_manager.getCamPos());
            data_manager.getShader(super::m_type)->setVec3("sunPos", data_manager.getSunPos());
            data_manager.getShader(super::m_type)->setTexture("material.surface", 0);
            data_manager.getShader(super::m_type)->setTexture("material.depthMap", 1);
            data_manager.getShader(super::m_type)->setTexture("material.normalMap", 2);
            // data_manager.getShader(super::m_type)->setTexture("material.dispMap", 3);
            data_manager.getShader(super::m_type)->setInt("material.shininess", m_shininess);
            data_manager.getShader(super::m_type)->setInt("shadows", true);
            data_manager.getShader(super::m_type)->setFloat("far_plane", data_manager.getFar());
            // data_manager.getShader(super::m_type)->setFloat("heightScale", super::height_scale);
                
            if((super::m_type == "double_textured_planete") || (super::m_type == "earth"))
            {
                data_manager.getShader(super::m_type)->setTexture("material.cloud", 4);
                data_manager.getShader(super::m_type)->setFloat("oppacity", m_oppacity);
            }

            if(super::m_type == "earth")
            {
                data_manager.getShader(super::m_type)->setTexture("material.night", 5);
            }   

        glUseProgram(0);
    }
    super::sendToShader(data_manager);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** makeRingChanges *************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::makeRingChanges(DataManager &data_manager)
{
    if(m_ring != nullptr)
    {
        m_ring->updatePosition(super::getPosition());
        m_ring->transform(-data_manager.getShipPos());
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** renderName *************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::renderName(DataManager &data_manager)
{
    glm::vec2 planete_screen_position = data_manager.convertToScreenSpace(this->m_position - data_manager.getShipPos());

    ImGuiWindowFlags window_flags = 0;
        
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowPos(ImVec2((data_manager.getWidth() * planete_screen_position.x) - 30, 
                                        (data_manager.getHeight() * planete_screen_position.y) - 70));
    ImGui::SetNextWindowSize(ImVec2(100.f, 80.f));

    ImGui::Begin(this->m_name.c_str(), NULL, window_flags);
    ImGui::Text(this->m_name.c_str());
    ImGui::End();
    
}

// /***********************************************************************************************************************************************************************/
// /********************************************************************************** getters ****************************************************************************/
// /***********************************************************************************************************************************************************************/
Ring* Planete::getRing() const
{
    return m_ring;
}


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

// Text* Planete::getNameRender() const
// {
//     return m_name_renderer;
// }

// float Planete::getOppacity() const
// {
//     return m_oppacity;
// }

// Atmosphere* Planete::getAtmosphere() const
// {
//     return m_atmosphere;
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