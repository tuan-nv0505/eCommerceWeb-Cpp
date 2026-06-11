//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#include "CloudinaryService.h"
#include "../utils/helper.h"

#include <cpr/cpr.h>
#include <json/json.h>

CloudinaryService::CloudinaryService(std::shared_ptr<CloudinaryClient> cloudinaryClient)
{
    this->cloudinaryClient = cloudinaryClient;
}

UploadResult CloudinaryService::upload(const std::string &filePath)
{
    std::string timestamp = std::to_string(std::time(nullptr));

    std::string signatureBase ="timestamp=" + timestamp + this->cloudinaryClient->getAPISecret();

    std::string signature = sha1(signatureBase);

    std::string url ="https://api.cloudinary.com/v1_1/" + this->cloudinaryClient->getCloudName() + "/image/upload";

    auto response = cpr::Post(
        cpr::Url{url},
        cpr::Multipart{
            {"file", cpr::File{filePath}},
            {"api_key", this->cloudinaryClient->getAPIKey()},
            {"timestamp", timestamp},
            {"signature", signature}
        });

    if (response.status_code != 200)
    {
        throw std::runtime_error(response.text);
    }

    Json::Value json;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream iss(response.text);

    Json::parseFromStream(builder, iss, &json, &errs);

    return {
        json["secure_url"].asString(),
        json["public_id"].asString()
    };
}