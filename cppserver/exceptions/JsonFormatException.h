//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef DROGONSERVER_JSONFORMATEXCEPTION_H
#define DROGONSERVER_JSONFORMATEXCEPTION_H

#include "BaseException.h"

class JsonFormatException : public BaseException
{
public:
    JsonFormatException(std::string msg) : BaseException(msg)
    {
        this->message = msg;
    }
};

#endif //DROGONSERVER_JSONFORMATEXCEPTION_H
