/*
AUTHOR : SUZEAU François

DATE : 14/01/2022

MODULE : Saving

NAMEFILE : Saving.hpp

PURPOSE : Interface Saving
*/

#ifndef SAVING_H
#define SAVING_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>
        #include <string>
        #include <fstream>

        #include "../OpenGlSketch/RenderData.hpp"

/********************************************************************* class definition *********************************************************************/
        
        class Saving
        {
            private:
            
                static std::ofstream        flux_out;
                static std::ifstream        flux_in;

                static void writeBool(bool val, std::string explaination);
                static bool readBool();

                static void writeNumber(float val, std::string explanation);
                static float readNumber();
                

            public:

                Saving();
                ~Saving();

                static bool verifingFileExistence();
                static void writeConfig(RenderData &render_data);
                static void setSettings(RenderData &render_data);
                
                // static void writeBool(bool val, std::string explaination);
                // static bool readBool();
            
        };


#endif