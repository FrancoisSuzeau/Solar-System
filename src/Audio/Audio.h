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

        #include <SDL2/SDL_mixer.h>


/********************************************************************* class definition *********************************************************************/

        class Audio
        {
            
            private:

                std::string m_file_music;
                Mix_Music *m_music;
                int m_volume;
                
                
            public:

                Audio(std::string file_music);
                ~Audio();


                bool loadMusic();
                void playMusic() const;
                void pause(bool pause) const; 
                void volume(int change);

                
        };


#endif