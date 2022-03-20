/*
AUTHOR : SUZEAU François

DATE : 16/06/2021

MODULE : Objects::TexturedObjects::Star

NAMEFILE : Star.cpp

PURPOSE : class Star

*/



#include "Star.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
// Star::Star(const float radius, const unsigned int longSegs, const unsigned int latSegs, std::string const texture, std::string const name, float const real_size) :
// Sphere(radius, longSegs, latSegs), m_cloud_texture(texture),
// m_name(name)
// {
//     assert(m_cloud_texture.loadTexture());

//     m_real_size = real_size;
//     m_initial_pos = vec3(0.01f, 0.0f, 0.0f);
//     m_current_position = m_initial_pos;
//     m_speed_rotation = 0.1f;
//     m_rotation_angle = 0.0f;

//     m_flares.push_back({new FlareTexture(0.33f, "../../assets/textures/lensFlareTextures/sunSpikes.png"), glm::vec3(2.0, 0.8, 0.8), -0.3, 0.09});
//     // m_flares.push_back({new FlareTexture(0.33f, "../../assets/textures/lensFlareTextures/Ghost2.png"), glm::vec3(1.0, 1.0, 1.0), -0.2, 0.008});
//     for(std::vector<flare_data>::iterator it = m_flares.begin(); it != m_flares.end(); ++it)
//     {
//         assert(it[0].flare);
//     }
// }

Star::Star(float size, std::string surface_path, std::string const type) : super(size, type)
{
    // super::m_type = "sun";
    // super::m_position = glm::vec3(0.f);
    super::surface_tex_ids.push_back(Loader::loadTextureWithSDL(surface_path));
    assert(super::surface_tex_ids[0] != 0);

}

Star::~Star()
{
    // for(std::vector<flare_data>::iterator it = m_flares.begin(); it != m_flares.end(); ++it)
    // {
    //     if(it[0].flare != nullptr)
    //     {
    //         delete it[0].flare;
    //     }
    // }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::transform(glm::vec3 ship_pos, Input *input)
{
    super::transform(ship_pos, input);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::sendToShader(DataManager &data_manager)
{
    if(data_manager.getShader(super::m_type) != nullptr)
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());

            data_manager.getShader(super::m_type)->setTexture("texture0", 0);
            data_manager.getShader(super::m_type)->setFloat("far", data_manager.getFar());
            data_manager.getShader(super::m_type)->setFloat("near", data_manager.getNear());
            data_manager.getShader(super::m_type)->setInt("render_depth", data_manager.getDepthRender());


        glUseProgram(0);
        
    }

    super::sendToShader(data_manager);
}

/***********************************************************************************************************************************************************************/
/************************************************************************ renderFlare *******************************************************************************/
/***********************************************************************************************************************************************************************/
// void Star::renderFlare(RenderData &render_data)
// {

//         glm::mat4 tmp_view_mat = render_data.getViewMat();
//         render_data.initSaveMat();

//         render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

//         //calculate sun position on the screen
//         glm::vec2 sunScreenCoords = convertToScreenSpace(render_data.getSunPos(), tmp_view_mat, render_data.getProjectionMat());

//         if(sunScreenCoords == glm::vec2(-100))
//         {
//             return;
//         }

//         //calculate line form sun through center screen
//         glm::vec2 sunToCenter = sunScreenCoords;

//         float brightness = 1 - (glm::length(sunToCenter) / 1.0f);
        
//         if(brightness > 0)
//         {
//             for(std::vector<flare_data>::iterator it = m_flares.begin(); it != m_flares.end(); ++it)
//             {
//                 if(it[0].flare != nullptr)
//                 {
//                     calculateFlarePos(sunToCenter, sunScreenCoords, it[0]);
//                     it[0].flare->display(render_data, brightness * it[0].strenght);
//                 }
//             }
            
//         }

//         render_data.saveViewMat();
// }

/***********************************************************************************************************************************************************************/
/**************************************************************************** calculateFlarePos **************************************************************************/
/***********************************************************************************************************************************************************************/
// void Star::calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords, flare_data f_d)
// {
//     if(f_d.flare != nullptr)
//     {
//         glm::vec2 flarePos = glm::vec2(sunCoords);

//         // if(sunToCenter.x > 0)
//         // {
//         //     flarePos.x = flarePos.x - 0.01;
//         // }

//         // if(sunToCenter.x < 0)
//         // {
//         //     flarePos.x = flarePos.x + 0.01;
//         // }

//         f_d.flare->setPositionFlareText(glm::vec3(flarePos, f_d.depth_size));
//         f_d.flare->transformMat(true, f_d.size);
        
//     }
// }

/***********************************************************************************************************************************************************************/
/*********************************************************************** convertToScreenSpace **************************************************************************/
/***********************************************************************************************************************************************************************/
// glm::vec2 Star::convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat)
// {

//     glm::vec4 clipSpacePos = projMat * (viewMat * glm::vec4(sunPos, 1.0f));

//     if(clipSpacePos.w <= 0)
//     {
//         return glm::vec2(-100); // NULL
//     }

//     float x = (float) clipSpacePos.x / (float) clipSpacePos.w;
//     float y = ((float) clipSpacePos.y / (float) clipSpacePos.w) / (float) 2.0;

//     return glm::vec2(x, y);
// }