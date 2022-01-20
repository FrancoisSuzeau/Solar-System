/*
AUTHOR : SUZEAU François

DATE : 14/01/2021

MODULE : Saving

NAMEFILE : Saving.cpp

PURPOSE : class Saving
*/

#include "Saving.hpp"

std::ofstream Saving::flux_out;
std::ifstream Saving::flux_in;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Saving::Saving()
{

}

Saving::~Saving()
{

}

/***********************************************************************************************************************************************************************/
/*********************************************************************** verifingFileExistence *************************************************************************/
/***********************************************************************************************************************************************************************/
bool Saving::verifingFileExistence()
{
    flux_in.open("config.save");

    if(flux_in)
    {
        flux_in.close();
        return true;
    }
    else //First launch so there is no file of that name so we create one
    {
        std::cout << ">>> No config file" << std::endl;
        flux_out.open("config.save");

        if(flux_out)
        {
            std::cout << ">>> Creating a config file .... " << std::endl;
            flux_out.close();
        }
        else
        {
            std::cout << ">>> ERROR : Impossible to create file" << std::endl;
        }
    }

    return false;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** writeConfig **************************************************************************/
/***********************************************************************************************************************************************************************/
void Saving::writeConfig(RenderData &render_data)
{   
    bool hdr = render_data.getHDR();
    float exposure = render_data.getExposure();
    bool bloom = render_data.getBloom();
    float bloom_str = render_data.getBloomStr();
    bool render_shadow = render_data.getShadowGround();
    bool render_parallax = render_data.getDispMapRender();
    float asteroid_count = render_data.getAsteroidCount();
    float fps_count = render_data.getFPS();
    bool render_overlay = render_data.getOverlayRender();
    bool render_name = render_data.getRenderName();
    bool render_info = render_data.getRenderInfo();
    bool pause_music = render_data.getPauseMusic();
    float volume = render_data.getVolume();
    float track = render_data.getTrack();
    float ship_index = render_data.getIndexShip();

    flux_out.open("config.save");
    if(flux_out)
    {
        writeBool(hdr, "HDR : (Enabled/Disabled)");
        writeNumber(exposure, "Exposure : (min : 0.5, max : 0.8)");
        writeBool(bloom, "Bloom : (Enabled/Disabled)");
        writeNumber(bloom_str, "Bloom strength : (min : 2, max : 10)");
        writeBool(render_shadow, "Ground Shadow : (Enabled/Disabled)");
        writeBool(render_parallax, "Parallax : (Enabled/Disabled)");
        writeNumber(asteroid_count, "Asteroid count : (min : 2000, max : 10000)");
        writeNumber(fps_count, "Asteroid count : [25, 60, 120, 144, 240]");
        writeBool(render_overlay, "Display Overlay : (Enabled/Disabled)");
        writeBool(render_name, "Display Name : (Enabled/Disabled)");
        writeBool(render_info, "Display Info : (Enabled/Disabled)");
        writeBool(pause_music, "Mute music : (Enabled/Disabled)");
        writeNumber(volume, "Volume : (min : 0, max : 128)");
        writeNumber(track, "Track : ");
        writeNumber(ship_index, "Ship skin : [0, max available]");

        flux_out.close();
    }
    else
    {
        std::cout << ">>> ERROR : Impossible to write configurations" << std::endl;
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** setSettings **************************************************************************/
/***********************************************************************************************************************************************************************/
void Saving::setSettings(RenderData &render_data)
{
    flux_in.open("config.save");
    if(flux_in)
    {
        bool tmp = readBool();
        render_data.updateHDR(tmp);
        float exposure = readNumber();
        render_data.updateExposure(exposure);
        bool bloom = readBool();
        render_data.updateBloom(bloom);
        int bloom_str = (int) readNumber();
        render_data.setBloomStr(bloom_str);
        bool render_shadow = readBool();
        render_data.setRenderShadowGround(render_shadow);
        bool render_parallax = readBool();
        render_data.setDispMapRender(render_parallax);
        int asteroid_count = (int) readNumber();
        render_data.setAsteroidCount(asteroid_count);
        int fps_count = readNumber();
        render_data.setFPS(fps_count);
        bool render_overlay = readBool();
        render_data.setRenderOverlay(render_overlay);
        bool render_name = readBool();
        render_data.setRenderName(render_name);
        bool render_info = readBool();
        render_data.setRenderInfo(render_info);
        bool pause_music = readBool();
        render_data.setPauseMusic(pause_music);
        int volume = (int) readNumber();
        render_data.setVolume(volume);
        int track = (int) readNumber();
        render_data.setTrackMusic(track);
        int ship_index = readNumber();
        render_data.setIndexShip(ship_index);

        flux_in.close();
    }
    else
    {
        std::cout << ">>> ERROR : Impossible to load configurations" << std::endl;
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** writeBool **************************************************************************/
/***********************************************************************************************************************************************************************/
void Saving::writeBool(bool val, std::string explaination)
{
    flux_out << explaination << std::endl;
    if(val)
    {
        flux_out << "Enabled" << std::endl;
    }
    else
    {
        flux_out << "Disabled" << std::endl;
    }

    flux_out << "\n";
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** readBool ***************************************************************************/
/***********************************************************************************************************************************************************************/
bool Saving::readBool()
{
    std::string line;
    std::getline(flux_in, line);
    std::cout << line << std::endl;
    std::getline(flux_in, line);
    std::cout << line << std::endl;
    if((line != "Enabled") && (line != "Disabled"))
    {
        std::getline(flux_in, line);
        std::cout << line << std::endl;
    }

    bool ret = true;
    if(line == "Enabled")
    {
        ret = true;
    }
    else if(line == "Disabled")
    {
        ret = false;
    }

    return ret;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** writeNumber ************************************************************************/
/***********************************************************************************************************************************************************************/
void Saving::writeNumber(float val, std::string explaination)
{
    flux_out << explaination << std::endl;
    flux_out << val << std::endl;
    flux_out << "\n";
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** readNumber *************************************************************************/
/***********************************************************************************************************************************************************************/
float Saving::readNumber()
{
    std::string line;
    float number;

    //as a remind we have an empty line and then an explanation line
    std::getline(flux_in, line);
    std::cout << line << std::endl;
    std::getline(flux_in, line);
    std::cout << line << std::endl;
    std::getline(flux_in, line);
    std::cout << line << std::endl;

    number = std::stof(line);

    return number;
}