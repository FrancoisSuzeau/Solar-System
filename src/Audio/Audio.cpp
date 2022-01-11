/*
AUTHOR : SUZEAU François

DATE : 27/05/2021

MODULE : Audio

NAMEFILE : Audio.h

PURPOSE :   - load music file
            - display file
            - change volume
            - pause/resume music
*/

#include "Audio.hpp"


/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Audio::Audio(): m_volume(MIX_MAX_VOLUME / 2), 
m_music(0), //create a warning but needed after
m_in_pause(false)
{
    m_file_music = {

        "../assets/audio/mass_effect.mp3",
        "../assets/audio/natural_splender.mp3",
        "../assets/audio/dying-star.mp3",
        "../assets/audio/SC-Orizon-theme.mp3"
    };
}

Audio::~Audio()
{
    if(m_music != NULL)
    {
        Mix_FreeMusic(m_music);
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* loadMusic ***************************************************************************/
/***********************************************************************************************************************************************************************/
bool Audio::loadMusic(RenderData &render_data)
{
    if(render_data.getTrack() < (int) m_file_music.size())
    {
        if(m_music != NULL)
        {
            Mix_FreeMusic(m_music);
        }
        /************************************************* load the file ********************************************************/
        m_music = Mix_LoadMUS(m_file_music[render_data.getTrack()].c_str());
        if(m_music == NULL)
        {
            std::cout << ">> Loading file music : ERROR : " << Mix_GetError() << std::endl;
            return false;
        }
        std::cout << ">> Loading file music : SUCCESS : " << m_file_music[render_data.getTrack()] << std::endl;
        ancient_track = render_data.getTrack();
        //===================================================================================================================   
    }
    else
    {
        return false;
    }

    return true;

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* manage music ************************************************************************/
/***********************************************************************************************************************************************************************/
void Audio::playMusic() const
{
    /************************************************* launch playlist ********************************************************/
    if(Mix_PlayMusic(m_music, 1) == -1)
    {
        std::cout << ">> Play music : ERROR : " << Mix_GetError() << std::endl;
    }
    //===================================================================================================================
}

void Audio::pause(bool pause)
{
    if(pause)
    {
        if(Mix_PausedMusic() == 0)
        {
            Mix_PauseMusic();
        }
    }
    else
    {
        if(Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }
    }


    
}

void Audio::changeVolume(int change)
{
    if(m_volume != change)
    {
        Mix_VolumeMusic(m_volume);
        m_volume = change;
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* updateTrack *************************************************************************/
/***********************************************************************************************************************************************************************/
void Audio::updateTrack(RenderData &render_data)
{
    int new_track = render_data.getTrack();

    if(Mix_PlayingMusic() == 1)
    {
        if(new_track >= (int) m_file_music.size())
        {
            render_data.setTrackMusic(0);
        }
        if(new_track < 0)
        {
            render_data.setTrackMusic(m_file_music.size() - 1);
            std::cout << "HERE " << std::endl;
        }

        if(ancient_track != render_data.getTrack())
        {
            loadMusic(render_data);
            playMusic();
        }
    }
    else if( (Mix_PlayingMusic() != 1) && (m_in_pause == false) )
    {
        render_data.setTrackMusic(new_track + 1);
        if( render_data.getTrack() >= (int) m_file_music.size() )
        {
            render_data.setTrackMusic(0);
        }

        loadMusic(render_data);
        playMusic();
    }
}