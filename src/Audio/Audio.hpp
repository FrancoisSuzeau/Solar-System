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

        #include <SDL2/SDL_mixer.h>


/********************************************************************* class definition *********************************************************************/

        class Audio
        {
            
            private:

                std::vector<std::string>        m_file_music;
                std::vector<std::string>        m_track_music;
                Mix_Music                       *m_music;
                int                             m_volume;
                bool                            m_in_pause;
                unsigned int                    m_track;
                
                
            public:

                Audio();
                ~Audio();


                bool loadMusic();
                void playMusic() const;
                void updateTrack();
                void pause(bool pause); 
                void volume(int change);
                std::string getTrack() const;

                
        };


#endif