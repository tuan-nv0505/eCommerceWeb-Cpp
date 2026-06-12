//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef CPPSERVER_JSONFORMATEXCEPTION_H
#define CPPSERVER_JSONFORMATEXCEPTION_H

#include "BaseException.h"

class JsonFormatException : public BaseException {
public:
  JsonFormatException(std::string msg) : BaseException(msg) {
    this->message = msg;
  }
};

#endif // CPPSERVER_JSONFORMATEXCEPTION_H
