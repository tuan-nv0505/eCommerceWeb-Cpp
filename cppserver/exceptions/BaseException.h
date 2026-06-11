//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef DROGONSERVER_BASEEXCEPTION_H
#define DROGONSERVER_BASEEXCEPTION_H

#include <exception>
#include <string>

class BaseException : public std::exception
{
protected:
    std::string message;
public:
    explicit BaseException(const std::string &message)
    {
        this->message = message;
    }

    const char* what() const noexcept override
    {
        return this->message.c_str();
    }

};

#endif //DROGONSERVER_BASEEXCEPTION_H
