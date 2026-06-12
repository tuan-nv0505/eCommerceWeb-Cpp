//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#ifndef CPPSERVER_DTOADAPTER_H
#define CPPSERVER_DTOADAPTER_H

#include <drogon/drogon.h>

template <typename T> class DTOAdapter {
public:
  virtual ~DTOAdapter() = default;
  static T toDTO(const drogon::HttpRequestPtr &request);
};

#endif // CPPSERVER_DTOADAPTER_H
