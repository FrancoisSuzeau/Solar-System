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
Planete::Planete(body_data datas) : super(datas.size, datas.type),
m_oppacity(datas.oppacity), m_name(datas.name), light_strength(datas.light_strength)
{
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

    super::m_rotation_angle = 0.f;
    super::m_speed_rotation = 0.1f;
    super::m_shininess = datas.shininess;
    super::m_position = datas.initial_pos;
    super::m_inclinaison_angle = datas.inclinaison_angle;

    if(m_name == "Venus")
    {
        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(1.f, 1.f, 224.f/255.f));
    }
    if(m_name == "Earth")
    {
        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(147.f/255.f, 188.f/255.f, 251.f/255.f));
    }
    if(m_name == "Mars")
    {
        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(255.f/255.f, 160.f/255.f, 122.f/255.f));
    }
    if(m_name == "Jupiter")
    {
        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(255.f/255.f, 228.f/255.f, 196.f/255.f));
    }
    if(m_name == "Saturn")
    {
        std::vector<std::string> texture_path;
        texture_path.push_back("../../assets/textures/CelestialBody/SaturnRing.png");
        m_ring = new Ring(25.f,  texture_path, "ring", 32, super::m_inclinaison_angle);
        assert(m_ring);

        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(255.f/255.f, 235.0/255.f, 205.f/255.f));
    }
    if(m_name == "Titan")
    {
        m_atmosphere = new Sphere(datas.size + 0.04f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(253.f/255.f, 241.0/255.f, 184.f/255.f));
    }

    if(m_name == "Uranus")
    {
        std::vector<std::string> texture_path;
        texture_path.push_back("../../assets/textures/CelestialBody/UranusRing.png");
        m_ring = new Ring(25.f,  texture_path, "ring", 32, super::m_inclinaison_angle);
        assert(m_ring);

        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(173.f/255.f, 216.f/255.f, 230.f/255.f));
    }

    if(m_name == "Neptune")
    {
        std::vector<std::string> texture_path;
        texture_path.push_back("../../assets/textures/CelestialBody/UranusRing.png");
        m_ring = new Ring(25.f,  texture_path, "ring", 32, super::m_inclinaison_angle);
        assert(m_ring);

        m_atmosphere = new Sphere(datas.size + 0.2f, "atmosphere");
        assert(m_atmosphere);
        m_atmosphere->updateColor(glm::vec3(65.f/255.f, 105.f/255.f, 255.f/255.f));
    }
}

Planete::~Planete()
{

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
    if(m_atmosphere != nullptr)
    {
        m_atmosphere->clean();
        delete m_atmosphere;
        m_atmosphere = nullptr;
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
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::sendToShader(DataManager &data_manager)
{
    if((data_manager.getShader("depth_map") != nullptr) && (data_manager.getPass() == DEPTH_FBO))
    {
        glUseProgram(data_manager.getShader("depth_map")->getProgramID());
                data_manager.getShader("depth_map")->setMat4("model", super::getModelMat());
        glUseProgram(0);
    }
    if((data_manager.getShader(super::m_type) != nullptr) && (data_manager.getPass() == COLOR_FBO))
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());
            data_manager.getShader(super::m_type)->setVec3("viewPos", data_manager.getCamPos());
            data_manager.getShader(super::m_type)->setVec3("sunPos", data_manager.getSunPos());
            data_manager.getShader(super::m_type)->setTexture("material.surface", 0);
            data_manager.getShader(super::m_type)->setTexture("material.depthMap", 1);
            data_manager.getShader(super::m_type)->setTexture("material.normalMap", 2);
            data_manager.getShader(super::m_type)->setInt("material.shininess", m_shininess);
            data_manager.getShader(super::m_type)->setInt("render_normal", data_manager.getRenderNormal());
            data_manager.getShader(super::m_type)->setInt("shadows", data_manager.getRenderShadow());
            data_manager.getShader(super::m_type)->setFloat("far_plane", data_manager.getFar());
            data_manager.getShader(super::m_type)->setFloat("material.light_strength", this->light_strength);
                
            if((super::m_type == "double_textured_planete") || (super::m_type == "earth"))
            {
                data_manager.getShader(super::m_type)->setTexture("material.cloud", 3);
                data_manager.getShader(super::m_type)->setFloat("oppacity", m_oppacity);
            }

            if(super::m_type == "earth")
            {
                data_manager.getShader(super::m_type)->setTexture("material.night", 4);
            }   

        glUseProgram(0);
    }
    super::sendToShader(data_manager);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** makeOtherChanges *************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::makeOtherChanges(DataManager &data_manager)
{
    if(m_ring != nullptr)
    {
        m_ring->updatePosition(super::getPosition());
        m_ring->transform(-data_manager.getShipPos());
    }

    if(m_atmosphere != nullptr)
    {
        m_atmosphere->updatePosition(super::getPosition());
        m_atmosphere->transform(-data_manager.getShipPos());
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** renderName *************************************************************************/
/***********************************************************************************************************************************************************************/
void Planete::renderName(DataManager &data_manager)
{
    if(data_manager.getRenderName())
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
    
    
}

// /***********************************************************************************************************************************************************************/
// /********************************************************************************** getters ****************************************************************************/
// /***********************************************************************************************************************************************************************/
Ring* Planete::getRing() const
{
    return m_ring;
}

Sphere* Planete::getAmosphere() const
{
    return m_atmosphere;
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