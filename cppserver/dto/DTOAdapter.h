//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#ifndef DROGONSERVER_DTOADAPTER_H
#define DROGONSERVER_DTOADAPTER_H

#include <drogon/drogon.h>

template <typename T>
class DTOAdapter
{
public:
    virtual ~DTOAdapter() = default;
    static T toDTO(const drogon::HttpRequestPtr &request);
};

#endif //DROGONSERVER_DTOADAPTER_H
