/*
AUTHOR : SUZEAU François

DATE : 23/11/2021

MODULE : DataManager

NAMEFILE : DataManager.hpp

PURPOSE : header of the DataManager class
*/

#ifndef DATA_H
#define DATA_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>
       
        

/********************************************************************* class definition *********************************************************************/

        class DataManager
        {
            
            private:
                
                int             m_width;
                int             m_height;
                bool            m_terminate;
                unsigned int    m_fps;
                

            public:

                DataManager(int width, int height);
                ~DataManager();
                
                void            setTerminate(bool const terminate);
                int             getWidth() const;
                int             getHeight() const; 
                bool            getTerminate() const;
                void            setFps(unsigned int const fps);
                unsigned int    getFps() const;

                
 
        };


#endif