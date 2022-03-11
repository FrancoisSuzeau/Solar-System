/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : Shader

NAMEFILE : Shader.cpp

PURPOSE : compiling shaders object
*/

#include "Shader.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Shader::Shader() : m_vertex_ID(0), m_fragment_ID(0), m_program_ID(0), m_vertex_src(), m_fragment_src()
{

}

Shader::Shader(std::string vertex_src, std::string fragment_src) :  m_vertex_ID(0), m_fragment_ID(0), m_program_ID(0), m_vertex_src(vertex_src), m_fragment_src(fragment_src)
{

}

Shader::Shader(Shader const &shader_to_copy) //copy constructor
{
    //copying source files
    m_vertex_src = shader_to_copy.m_vertex_src;
    m_fragment_src = shader_to_copy.m_fragment_src;

    //loading new shader
    loadShader();
}

Shader& Shader::operator=(Shader const &shader_to_copy)
{
    //copying source files
    m_vertex_src = shader_to_copy.m_vertex_src;
    m_fragment_src = shader_to_copy.m_fragment_src;

    //loading new shader
    loadShader();

    return *this;
}

Shader::~Shader()
{
    deleteProgram();

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* getProgramID **************************************************************************/
/***********************************************************************************************************************************************************************/
GLuint Shader::getProgramID() const
{
    return m_program_ID;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* loadShader **************************************************************************/
/***********************************************************************************************************************************************************************/
bool Shader::loadShader()
{
    deleteShader(m_vertex_ID, GL_FALSE);
    deleteShader(m_fragment_ID, GL_FALSE);
    deleteProgram();
    /************************************************* compiling shader source code ********************************************************/
    if( !compileShader(m_vertex_ID, GL_VERTEX_SHADER, m_vertex_src))
    {
        //std::cout << ">> Compiling shader during load : ERROR" << std::endl;
        return false;
    }
    //std::cout << ">> Compiling shader during load : SUCCESS" << std::endl;
    //======================================================================================================================================

    /************************************************* compiling fragment source code ********************************************************/
    if( !compileShader(m_fragment_ID, GL_FRAGMENT_SHADER, m_fragment_src))
    {
        //std::cout << ">> Compiling fragment during load : ERROR" << std::endl;
        return false;
    }
    //std::cout << ">> Compiling fragment during load : SUCCESS" << std::endl;
    //======================================================================================================================================

    /************************************************* creating program for GPU ********************************************************/
    m_program_ID = glCreateProgram();

    //shader association
    glAttachShader(m_program_ID, m_vertex_ID);
    glAttachShader(m_program_ID, m_fragment_ID);
    //======================================================================================================================================

    /**************************************** lock entrees shader (vertices, colors, texture's coordonates *****************************/
    glBindAttribLocation(m_program_ID, 0, "in_Vertex");
    glBindAttribLocation(m_program_ID, 1, "in_Color");
    glBindAttribLocation(m_program_ID, 2, "in_TexCoord0");
    //======================================================================================================================================

    /************************************************* linkage ********************************************************/
    glLinkProgram(m_program_ID);

    //linkage verification
    GLint link_error = checkStatus(m_program_ID, "linking");

    if( link_error != GL_TRUE)//there is an link error
    {
        //size error recovery
        GLint   size_error(0);
        glGetProgramiv(m_program_ID, GL_INFO_LOG_LENGTH, &size_error);

        //memory allocation
        char *error = new char[size_error + 1]; // '\0' character needed

        //error recovery
        glGetShaderInfoLog(m_program_ID, size_error, &size_error, error);
        error[size_error] = '\0';

        //displayiong error message
        std::cout << ">> Linking program error : " << error << std::endl;

        //memory release
        delete[] error;
        deleteProgram();
        deleteShader(m_vertex_ID, link_error);
        deleteShader(m_fragment_ID, link_error);

        return false;
    }
    else
    {
        std::cout << ">> Linking program : SUCCESS" << std::endl;
        deleteShader(m_vertex_ID, link_error);
        deleteShader(m_fragment_ID, link_error);
    
        std::cout << ">> SHADER :: delete >>> SUCCESS" << m_vertex_src << std::endl;
        std::cout << ">> SHADER :: delete >>> SUCCESS" << m_fragment_src << std::endl;
        return true;
    }
    //======================================================================================================================================

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* compileShader ***********************************************************************/
/***********************************************************************************************************************************************************************/
bool Shader::compileShader(GLuint &shader, GLenum type, std::string const &file_src)
{
    /************************************************* creating shader/fragment ********************************************************/
    shader = glCreateShader(type);
    if( shader == 0)
    {
        std::cout << ">> Compiling (" << type << ") : ERROR" << std::endl;
        return false;
    }
    std::cout << ">> Compiling (" << type << ") : SUCCESS" << std::endl;
    //======================================================================================================================================

    /************************************************* read flow ********************************************************/
    std::ifstream file(file_src.c_str());
    if( !file)
    {
        std::cout << ">> Read file (" << file_src << ") : ERROR" << std::endl;
        deleteShader(shader, false);
        return false;
    }
    std::cout << ">> Read file (" << file_src << ") : SUCCESS" << std::endl;
    //======================================================================================================================================


    /************************************************* copying src code ********************************************************/
    std::string line;
    std::string src_code;

    while(std::getline(file, line))
    {
        src_code += line + '\n';
    }
    file.close();
    //============================================================================================================================

    /************************************************* compile shader ********************************************************/
    //string C recovery by source code
    const GLchar *string_src_code = src_code.c_str();

    //send source code to shader
    glShaderSource(shader, 1, &string_src_code, 0);

    //compile shader
    glCompileShader(shader);
    //======================================================================================================================================

    /************************************************* compile verification ********************************************************/
    //status recovery
    GLint   compile_error = checkStatus(shader, "compiling");
    if(compile_error != GL_TRUE) //there is an error
    {
        //size error recovery
        GLint error_size(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_size);

        //memory allocation
        char *error = new char[error_size + 1]; //need the '\0' character

        //error recovery
        glGetShaderInfoLog(shader, error_size, &error_size, error);
        error[error_size] = '\0';

        //error displaying
        std::cout << ">> Compiling source code shader : " << error << std::endl;

        //memory release
        delete[] error;
        deleteShader(shader, false);

        return false;

    }
    else
    {
        std::cout << ">> Compiling source code shader : SUCCESS" << std::endl;
        return true;
    }
    //======================================================================================================================================

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* deleteShader ************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::deleteShader(GLuint &shader, GLint detach_shader)
{
    if(glIsShader(shader) == GL_TRUE)
    {
        if(detach_shader == GL_TRUE)
        {
            glDetachShader(m_program_ID, shader);
        }
        glDeleteShader(shader);
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* deleteProgram ************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::deleteProgram()
{
    if(glIsProgram(m_program_ID) == GL_TRUE)
    {
        glDeleteProgram(m_program_ID);
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* checkStatus ************************************************************************/
/***********************************************************************************************************************************************************************/
GLint Shader::checkStatus(GLuint obj_id, std::string type)
{
    GLint error(0);

    if(type == "linking")
    {
        glGetProgramiv(obj_id, GL_LINK_STATUS, &error);
    }

    if(type == "compiling")
    {
        glGetShaderiv(obj_id, GL_COMPILE_STATUS, &error);
    }

    return error;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setVec3 *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::setVec3(std::string const location, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_program_ID, location.c_str()), x, y, z);
}

void Shader::setVec3(std::string const location, glm::vec3 const &vec_to_add)
{
    glUniform3fv(glGetUniformLocation(m_program_ID, location.c_str()), 1, &vec_to_add[0]);
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setMat4 *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::setMat4(std::string const location, glm::mat4 const &matrice_to_add)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program_ID, location.c_str()), 1, GL_FALSE, glm::value_ptr(matrice_to_add));
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setTexture **************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::setTexture(std::string const location, int const count)
{
    glUniform1i(glGetUniformLocation(m_program_ID, location.c_str()), count);
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setFloat ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::setFloat(std::string const location, float const to_add)
{
    glUniform1f(glGetUniformLocation(m_program_ID, location.c_str()), to_add);
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setInt ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Shader::setInt(std::string const location, int const to_add)
{
    glUniform1i(glGetUniformLocation(m_program_ID, location.c_str()), to_add);
}