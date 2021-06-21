/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : CelestialObject.Ring

NAMEFILE : Ring.h

PURPOSE : header of the Ring class
*/

#ifndef RING_H
#define RING_H


/********************************************************************* includes *********************************************************************/

        #include "../../Texture/Texture.h"
        #include "../Geometry/Disk.h"
        

/********************************************************************* class definition *********************************************************************/

        class Ring: public Disk
        {

            private:

                Texture         m_texture;
                float           m_coord[12];
                int             m_bytes_coord_size;

            public:
            
                Ring(float size, std::string const texture);
                Ring();
                ~Ring();

                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src);
                void load();
                
        };


#endif