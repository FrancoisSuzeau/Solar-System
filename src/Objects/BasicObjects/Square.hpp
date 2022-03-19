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

                Square(float size);
                ~Square();

                void transform(Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;
                
        };


#endif