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
m_track(5), m_in_pause(false)
{
    m_file_music = {

        "../assets/audio/mass_effect.mp3",
        "../assets/audio/ArCorp_Theme.mp3",
        "../assets/audio/Space_Suit_generic3.mp3",
        "../assets/audio/The_darkness_SC.mp3",
        "../assets/audio/Into_the_void_SC.mp3",
        "../assets/audio/natural_splender.mp3"
    };

    m_track_music = {

        "Mass Effect - Vigil",
        "Star Citizen - ArcCorp Theme",
        "Space Suite Generic 02",
        "The Darkness",
        "Into the Void",
        "Natural Splendor"
    };
}

Audio::~Audio()
{
    if(m_music != NULL)
    {
        Mix_FreeMusic(m_music);
    }
    
    //Mix_FreeMusic(m_music);

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* loadMusic ***************************************************************************/
/***********************************************************************************************************************************************************************/
bool Audio::loadMusic()
{
    if(m_track < m_file_music.size()) //indices go through 0 to n-1, with n the number of elements
    {
        if(m_music != NULL)
        {
            Mix_FreeMusic(m_music);
        }
        /************************************************* load the file ********************************************************/
        m_music = Mix_LoadMUS(m_file_music[m_track].c_str());
        if(m_music == NULL)
        {
            std::cout << ">> Loading file music : ERROR : " << Mix_GetError() << std::endl;
            return false;
        }
        std::cout << ">> Loading file music : SUCCESS : " << m_file_music[m_track] << std::endl;
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
        if(Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
            m_in_pause = false;

        }
        else
        {
            Mix_PauseMusic();
            m_in_pause = true;
        }
    }
    
}

void Audio::volume(int change)
{
    if( (m_volume >= 0) && (m_volume <= 128) )
    {
        m_volume += change;
        Mix_VolumeMusic(m_volume);
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* updateTrack *************************************************************************/
/***********************************************************************************************************************************************************************/
void Audio::updateTrack()
{
    if(Mix_PlayingMusic() == 1)
    {
        //do nothing
    }
    else if( (Mix_PlayingMusic() != 1) && (m_in_pause == false) )
    {
        m_track++;
        if( m_track >= m_file_music.size() )
        {
            m_track = 0;
        }

        loadMusic();
        playMusic();
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** getTrack ***************************************************************************/
/***********************************************************************************************************************************************************************/
std::string Audio::getTrack() const
{
    return m_track_music[m_track];
}