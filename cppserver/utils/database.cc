//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#include "database.h"

drogon::orm::DbClientPtr getDbClient()
{
    drogon::orm::DbClientPtr client = drogon::app().getDbClient();
    if (!client)
        throw std::runtime_error("Database connection failed");
    return client;
}
