//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#ifndef CPPSERVER_DATABASE_H
#define CPPSERVER_DATABASE_H
#include <drogon/drogon.h>

drogon::orm::DbClientPtr getDbClient();

#endif // CPPSERVER_DATABASE_H
