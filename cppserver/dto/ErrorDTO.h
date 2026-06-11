//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef DROGONSERVER_ERRORDTO_H
#define DROGONSERVER_ERRORDTO_H

#include <string>
#include <json/json.h>

struct ErrorDTO
{
    std::string statusCode;
    std::string errorMessage;

    Json::Value toJson()
    {
        Json::Value json;
        json["statusCode"] = statusCode;
        json["errorMessage"] = errorMessage;
        return json;
    }
};

#endif //DROGONSERVER_ERRORDTO_H
