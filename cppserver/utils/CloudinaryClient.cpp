//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#include "CloudinaryClient.h"
#include "helper.h"

#include <drogon/drogon.h>


CloudinaryClient::CloudinaryClient()
{
    Json::Value cloudinaryConfig = loadJson("../secret/cloudinary.json");
    this->cloudName = cloudinaryConfig["cloud_name"].asString();
    this->apiKey = cloudinaryConfig["api_key"].asString();
    this->apiSecret = cloudinaryConfig["api_secret"].asString();
}

const std::string & CloudinaryClient::getCloudName() const
{
    return this->cloudName;
}

const std::string & CloudinaryClient::getAPIKey() const
{
    return this->apiKey;
}

const std::string & CloudinaryClient::getAPISecret() const
{
    return this->apiSecret;
}
