/*
AUTHOR : SUZEAU François

DATE : 27/05/2021

MODULE : Audio

NAMEFILE : Audio.h

PURPOSE : header of the Audio class
*/

#ifndef AUDIO_H
#define AUDIO_H


/********************************************************************* includes *********************************************************************/
        
        #include <iostream>
        #include <string>
        #include <vector>

        #include "../../Application/DataManager.hpp"

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
                
                
            public:

                Audio();
                ~Audio();

                void    clean();


                bool loadMusic(DataManager &data_manager);
                void playMusic() const;
                void updateTrack(DataManager &data_manager);
                void pause(bool pause); 
                void changeVolume(int change);
        };


#endif