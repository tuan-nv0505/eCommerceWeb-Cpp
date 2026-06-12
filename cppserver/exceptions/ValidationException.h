//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef CPPSERVER_VALIDATIONEXCEPTION_H
#define CPPSERVER_VALIDATIONEXCEPTION_H

#include "BaseException.h"

#include <string>

class ValidationException : public BaseException {
public:
  ValidationException(std::string msg) : BaseException(msg) {
    this->message = msg;
  }
};

#endif // CPPSERVER_VALIDATIONEXCEPTION_H
