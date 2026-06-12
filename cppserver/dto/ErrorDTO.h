//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef CPPSERVER_ERRORDTO_H
#define CPPSERVER_ERRORDTO_H

#include <json/json.h>
#include <string>

struct ErrorDTO {
  std::string statusCode;
  std::string errorMessage;

  Json::Value toJson() {
    Json::Value json;
    json["statusCode"] = statusCode;
    json["errorMessage"] = errorMessage;
    return json;
  }
};

#endif // CPPSERVER_ERRORDTO_H
