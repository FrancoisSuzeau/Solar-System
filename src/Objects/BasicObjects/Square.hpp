/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Square.hpp

PURPOSE : header of the Square class
*/

#ifndef SQUARE_H
#define SQUARE_H


/********************************************************************* includes *********************************************************************/

        #include "../Object.hpp"

/********************************************************************* class definition *********************************************************************/

        class Square : public Object
        {
            
            private:

                typedef Object super;
                
                
            public:

                Square(float size, std::string const type);
                ~Square();

                void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;
                void clean();
                
        };


#endif