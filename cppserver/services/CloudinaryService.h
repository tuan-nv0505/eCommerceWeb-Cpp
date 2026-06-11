//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#ifndef DROGONSERVER_CLOUDINARYSERVICE_H
#define DROGONSERVER_CLOUDINARYSERVICE_H

#include <string>
#include <memory>

#include "../utils/CloudinaryClient.h"

struct UploadResult
{
    std::string secureUrl;
    std::string publicId;
};

class CloudinaryService
{
private:
    std::shared_ptr<CloudinaryClient> cloudinaryClient;;

public:
    explicit CloudinaryService(std::shared_ptr<CloudinaryClient> cloudinaryClient);

    UploadResult upload(const std::string &filePath);

};


#endif //DROGONSERVER_CLOUDINARYSERVICE_H
