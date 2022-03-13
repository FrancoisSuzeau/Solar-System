/*
AUTHOR : SUZEAU François

DATE : 27/05/2021

MODULE : InOut::Audio

NAMEFILE : Audio.cpp

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
m_music(NULL),
m_in_pause(false)
{
    m_file_music = {

        "../../assets/audio/mass_effect.mp3",
        "../../assets/audio/critical-mass.mp3",
        "../../assets/audio/natural_splender.mp3",
        "../../assets/audio/dying-star.mp3",
        "../../assets/audio/SC-Orizon-theme.mp3",
        "../../assets/audio/engine-of-creation.mp3",
        "../../assets/audio/mass-effect_map-theme.mp3",
        "../../assets/audio/unbound.mp3",
        "../../assets/audio/dreamscape.mp3",
        "../../assets/audio/two-moons.mp3"
    };
}

Audio::~Audio()
{
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* clean ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Audio::clean()
{
    if(m_music != NULL)
    {
        Mix_FreeMusic(m_music);
    }

    std::cout << ">> AUDIO : DESTROY COMPLETE" << std::endl;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* manage music ************************************************************************/
/***********************************************************************************************************************************************************************/
void Audio::playMusic() const
{
    /************************************************* launch playlist ********************************************************/
    if(Mix_PlayMusic(m_music, 1) == -1)
    {
        std::string err_msg = "Playing music : ";
        err_msg.append(Mix_GetError());
        showError(nullptr, ErrorHandler(err_msg.c_str()), __FILENAME__, __FUNCTION__, __LINE__);
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
void Audio::updateTrack(DataManager &data_manager)
{
    int new_track = data_manager.getTrack();

    if(Mix_PlayingMusic() == 1)
    {
        if(new_track >= (int) m_file_music.size())
        {
            data_manager.setTrack(0);
        }
        if(new_track < 0)
        {
            data_manager.setTrack(m_file_music.size() - 1);
        }

        if(ancient_track != data_manager.getTrack())
        {
            if(data_manager.getTrack() < (int) m_file_music.size())
            {
                ancient_track = data_manager.getTrack();
                m_music = Loader::loadWithSDLMixer(m_file_music[data_manager.getTrack()], m_music);
            }
            playMusic();
        }
    }
    else if( (Mix_PlayingMusic() != 1) && (m_in_pause == false) )
    {
        data_manager.setTrack(new_track + 1);
        if( data_manager.getTrack() >= (int) m_file_music.size() )
        {
            data_manager.setTrack(0);
        }

        if(data_manager.getTrack() < (int) m_file_music.size())
        {
            ancient_track = data_manager.getTrack();
            m_music = Loader::loadWithSDLMixer(m_file_music[data_manager.getTrack()], m_music);
        }
        playMusic();
    }
}