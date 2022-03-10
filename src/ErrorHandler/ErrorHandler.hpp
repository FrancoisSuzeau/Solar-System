/*
    AUTHOR : SUZEAU François

    DATE : 09/03/2022

    MODULE : ErrorHandler

    NAMEFILE : ErrorHandler.hpp

    PURPOSE : header of the ErrorHandler class
*/

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H


/********************************************************************* includes *********************************************************************/

        #include <exception>
        #include <cstring>
        #include <string>
        #include <windows.h>
        #include <codecvt>
        #include <locale>
        #include <comdef.h>

        #define __FILENAME__ (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)


/********************************************************************* class definition *********************************************************************/


        class ErrorHandler final : public std::exception
        {
            
            private:

                const char      *m_description;
                const short     m_code;
                ErrorHandler& operator=(const ErrorHandler&) = delete;

            public:

                ErrorHandler(const char *description, short code = -1) throw();
                ErrorHandler(ErrorHandler&& ref);
                
                const char* what() const throw() override;
                short Code() const throw();

                ErrorHandler& operator=(ErrorHandler&&);
                
        };


        std::wstring stringToWstring(const std::string &t_str);
        
        template <typename ExceptionClass> void showError(HWND hWnd, ExceptionClass exception, const char *file, const char *func, int line, long info = MB_ICONERROR)
        {
            std::string error_type = TEXT("Runtime error");
            std::string error_message = TEXT("File:\t");
            error_message.append(file);
            error_message.append(TEXT("\r\nFunction:\t"));
            error_message.append(func);
            error_message.append(TEXT("\r\nLine:\t"));
            error_message.append(std::to_string(line));
            error_message.append(TEXT("\r\nERROR:\t"));
            error_message.append(exception.what());

            MessageBox(hWnd, error_message.c_str(), error_type.c_str(), static_cast<UINT>(MB_OK | info));
        }


#endif