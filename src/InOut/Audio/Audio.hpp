/*
AUTHOR : SUZEAU François

DATE : 27/05/2021

MODULE : InOut::Audio

NAMEFILE : Audio.hpp

PURPOSE : header of the Audio class
*/

#ifndef AUDIO_H
#define AUDIO_H


/********************************************************************* includes *********************************************************************/
        
        #include <iostream>
        #include <string>
        #include <vector>

        #include "../../Application/DataManager.hpp"
        #include "../../Loader/Loader.hpp"

        #include <SDL2/SDL_mixer.h>


/********************************************************************* class definition *********************************************************************/

        class Audio
        {
            
            private:

                std::vector<std::string>        m_file_music;

                Mix_Music                       *m_music;
                int                             m_volume;
                bool                            m_in_pause;
                int                             ancient_track;
                
                void playMusic() const;
                
                
            public:

                Audio();
                ~Audio();

                void    clean();

                void updateTrack(DataManager &data_manager);
                void pause(bool pause); 
                void changeVolume(int change);
        };


#endif