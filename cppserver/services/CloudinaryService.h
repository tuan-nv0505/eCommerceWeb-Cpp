//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#ifndef CPPSERVER_CLOUDINARYSERVICE_H
#define CPPSERVER_CLOUDINARYSERVICE_H

#include <memory>
#include <string>

#include "../utils/CloudinaryClient.h"

struct UploadResult {
  std::string secureUrl;
  std::string publicId;
};

class CloudinaryService {
private:
  std::shared_ptr<CloudinaryClient> cloudinaryClient;
  ;

public:
  explicit CloudinaryService(
      std::shared_ptr<CloudinaryClient> cloudinaryClient);

  UploadResult upload(const std::string &filePath);
};

#endif // CPPSERVER_CLOUDINARYSERVICE_H
