//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#ifndef CPPSERVER_CLOUDINARYCLIENT_H
#define CPPSERVER_CLOUDINARYCLIENT_H

#include <string>

class CloudinaryClient {
private:
  std::string cloudName;
  std::string apiKey;
  std::string apiSecret;

public:
  CloudinaryClient();

  const std::string &getCloudName() const;
  const std::string &getAPIKey() const;
  const std::string &getAPISecret() const;
};

#endif // CPPSERVER_CLOUDINARYCLIENT_H
