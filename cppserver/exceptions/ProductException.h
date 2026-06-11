//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef DROGONSERVER_DUPLICATEEXCEPTION_H
#define DROGONSERVER_DUPLICATEEXCEPTION_H

#include "BaseException.h"

#include <string>

class ProductException : public BaseException
{
public:
    ProductException(std::string msg) : BaseException(msg)
    {
        this->message = msg;
    }
};

#endif //DROGONSERVER_DUPLICATEEXCEPTION_H
