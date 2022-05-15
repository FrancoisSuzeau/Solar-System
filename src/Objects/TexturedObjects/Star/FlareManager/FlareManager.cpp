/*
AUTHOR : SUZEAU François

DATE : 06/02/2021

MODULE : FlareManager

NAMEFILE : FlareManager.cpp

PURPOSE : class FlareManager
*/

#include "FlareManager.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
FlareManager::FlareManager(SquareTexturedRenderer  *square_textured_renderer, std::string const type) : m_flares_type(type)
{
    m_square_textured_renderer = square_textured_renderer;
    spacing = 0.f;

    if(m_flares_type == "cam_dirt")
    {
        m_flares.push_back({new FlareTexture(0.8f, "flare_texture", "../../assets/textures/lensFlareTextures/tex8.png"), -0.53, 0.03f});
        m_flares.push_back({new FlareTexture(0.3f, "flare_texture", "../../assets/textures/lensFlareTextures/Ghost2.png"), -0.51, 0.1});
        m_flares.push_back({new FlareTexture(0.3f, "flare_texture", "../../assets/textures/lensFlareTextures/Ghost2.png"), -0.49, 0.1});
        m_flares.push_back({new FlareTexture(0.3f, "flare_texture", "../../assets/textures/lensFlareTextures/Ghost2.png"), -0.47, 0.1});
        m_flares.push_back({new FlareTexture(0.3f, "flare_texture", "../../assets/textures/lensFlareTextures/Ghost2.png"), -0.45, 0.1});
        m_flares.push_back({new FlareTexture(0.5f, "flare_texture", "../../assets/textures/lensFlareTextures/Ghost1.png"), -0.43, 0.15});
        m_flares.push_back({new FlareTexture(0.5f, "flare_texture", "../../assets/textures/lensFlareTextures/tex4.png"), -0.4, 0.05});
        spacing = 0.4f;
    }

    if(m_flares_type == "sun_rays")
    {
        m_flares.push_back({new FlareTexture(0.3f, "flare_texture", "../../assets/textures/lensFlareTextures/sunSpikes.png"), 0.f, 0.5});
        // m_flares.push_back({new FlareTexture(0.33f, "flare_texture", "../../assets/textures/lensFlareTextures/Ghost2.png"), -0.2, 0.008});
    }
    
    
   
   for(std::vector<flare_datas>::iterator it = m_flares.begin(); it != m_flares.end(); it++)
   {
       assert(it[0].flare);
   }
}

FlareManager::~FlareManager()
{

}

/***********************************************************************************************************************************************************************/
/**************************************************************************** renderLensFlare **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareManager::clean()
{
    if((m_square_textured_renderer != nullptr) && (m_flares_type == "cam_dirt"))
    {
        m_square_textured_renderer->clean();
        delete m_square_textured_renderer;
        m_square_textured_renderer = nullptr;
    }
    for(std::vector<flare_datas>::iterator it = m_flares.begin(); it != m_flares.end(); it++)
    {
        if(it[0].flare != nullptr)
        {
            it[0].flare->clean();
            delete it[0].flare;
            it[0].flare = nullptr;
        }
    }
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** makeChanges **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareManager::makeChanges(DataManager &data_manager)
{
    glm::vec2 sunScreenCoords = data_manager.convertToScreenSpace(data_manager.getSunPos());
    if(sunScreenCoords == glm::vec2(-100.f))
    {
        return;
    }

    //calculate line form sun through center screen
    glm::vec2 sunToCenter;
    float brightness;
    if(m_flares_type == "cam_dirt")
    {
        sunToCenter = glm::vec2(0.5f) - sunScreenCoords;
        brightness = 1 - (glm::length(sunToCenter) / 0.6f);
    }
    if(m_flares_type == "sun_rays")
    {
        sunToCenter = sunScreenCoords;
        brightness = 1 - (glm::length(sunToCenter) / 1.f);
    }

    if(brightness > 0)
    {
        int i = 0;
        for (std::vector<flare_datas>::iterator it = m_flares.begin(); it != m_flares.end(); it++)
        {
            glm::vec2 flarePos;
            if(m_flares_type == "cam_dirt")
            {
                /*
                    Just a reminder : we calculate the sun coord on the screen with origin at the left hight corner of the screen (with 0.5, 0.5 as the center)
                    but the position of the m_flares are calculate with the OpenGL screen coord with origin in the center of the screen because of the lock on the view matrice
                    so we had to substract 0.5 at each calculation of the flare position
                */
                glm::vec2 direction = glm::vec2(sunToCenter);
                direction = direction * (i * spacing);
                flarePos = glm::vec2(sunScreenCoords + direction - glm::vec2(0.5));
                flarePos.x *= -1;
            }
            if(m_flares_type == "sun_rays")
            {
                flarePos = glm::vec2(sunScreenCoords) - glm::vec2(0.50f);
                flarePos.y *= -1;
            }

            it[0].flare->updatePosition(glm::vec3(flarePos, it[0].depth_size));
            it[0].flare->updateBrightness(brightness*it[0].strength);
            it[0].flare->transform();
            i++;
        }
    }
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** renderLensFlare **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareManager::renderLensFlare(DataManager &data_manager)
{
    glm::mat4 save_view_matrix = data_manager.getViewMat();

        data_manager.lockView(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
        
        for(std::vector<flare_datas>::iterator it = m_flares.begin(); it != m_flares.end(); ++it)
        {
            if((it[0].flare != nullptr) && (m_square_textured_renderer != nullptr))
            {
                it[0].flare->sendToShader(data_manager);
                m_square_textured_renderer->render(data_manager, it[0].flare);
            }
        }

    data_manager.resetViewMat(save_view_matrix);
}