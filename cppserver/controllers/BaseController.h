//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef CPPSERVER_BASECONTROLLER_H
#define CPPSERVER_BASECONTROLLER_H

#include <drogon/drogon.h>
#include <unordered_map>

class BaseController {
protected:
  drogon::Task<drogon::HttpResponsePtr> handleRequest(
      std::function<drogon::Task<drogon::HttpResponsePtr>()> &&function);
};

#endif // CPPSERVER_BASECONTROLLER_H
