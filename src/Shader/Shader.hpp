/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : Shader

NAMEFILE : Shader.h

PURPOSE : header of the Shader class
*/

#ifndef SHADER_H
#define SHADER_H

/********************************************************************* includes *********************************************************************/
        #include <GL/glew.h>
        #include <iostream>
        #include <string>
        #include <fstream>

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

/********************************************************************* class definition *********************************************************************/

        class Shader
        {
            private:

                GLuint          m_vertex_ID;
                GLuint          m_fragment_ID;
                GLuint          m_geometry_ID;
                GLuint          m_program_ID;

                std::string     m_vertex_path;
                std::string     m_fragment_path;
                std::string     m_geometry_path = "NONE";

                void            deleteShader(GLuint &shader, GLint detach_shader);
                void            deleteProgram();
                GLint           checkStatus(GLuint obj_id, std::string type);

            public:

                Shader();
                Shader(std::string vertex_path, std::string fragment_path, std::string geometry_path = "NONE");
                ~Shader();

                Shader(Shader const &shader_to_copy);
                Shader& operator=(Shader const &shader_to_copy);

                GLuint          getProgramID() const;
                bool            loadShader();
                bool            compileShader(GLuint &shader, GLenum type, std::string const &file_src);
                void            setVec3(std::string const location, float x, float y, float z);
                void            setVec3(std::string const location, glm::vec3 const &vec_to_add);
                void            setMat4(std::string const location, glm::mat4 const &matrice_to_add);
                void            setTexture(std::string const location, int const count);
                void            setFloat(std::string const location, float const to_ad);
                void            setInt(std::string const location, int const to_ad);

            
        };

#endif
