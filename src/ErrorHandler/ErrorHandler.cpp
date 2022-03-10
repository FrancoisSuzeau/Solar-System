/*
    AUTHOR : SUZEAU François

    DATE : 09/03/2021

    MODULE : ErrorHandler

    NAMEFILE : ErrorHandler.hpp

    PURPOSE :   - 

*/

#include "ErrorHandler.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
ErrorHandler::ErrorHandler(const char *description, short code) throw() : m_description(description), m_code(code)
{
    
}

ErrorHandler::ErrorHandler(ErrorHandler&& ref) : m_description(ref.m_description), m_code(ref.m_code)
{

}

ErrorHandler& ErrorHandler::operator=(ErrorHandler&&)
{
    return *this;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** what ******************************************************************************/
/***********************************************************************************************************************************************************************/
const char* ErrorHandler::what() const throw()
{
    return m_description;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** Code ******************************************************************************/
/***********************************************************************************************************************************************************************/
short ErrorHandler::Code() const throw()
{
    return m_code;
}


std::wstring stringToWstring(const std::string &t_str)
{
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.from_bytes(t_str);
}