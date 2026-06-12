//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef CPPSERVER_DUPLICATEEXCEPTION_H
#define CPPSERVER_DUPLICATEEXCEPTION_H

#include "BaseException.h"

#include <string>

class ProductException : public BaseException {
public:
  ProductException(std::string msg) : BaseException(msg) {
    this->message = msg;
  }
};

#endif // CPPSERVER_DUPLICATEEXCEPTION_H
