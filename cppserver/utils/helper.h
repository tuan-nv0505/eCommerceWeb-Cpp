//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#ifndef DROGONSERVER_HELPER_H
#define DROGONSERVER_HELPER_H

#include <string>

#include <json/json.h>
#include <drogon/drogon.h>

std::string getExtension(std::string fileName);
std::string sha1(const std::string &input);
Json::Value loadJson(const std::string &path);


template <size_t... Is>
inline drogon::Task<drogon::orm::Result> drogon_exec_coro_impl(
    const std::shared_ptr<drogon::orm::DbClient>& dbClient,
    const std::string& sql,
    const std::vector<std::string>& bindValues,
    std::index_sequence<Is...>) 
{
    co_return co_await dbClient->execSqlCoro(sql, bindValues[Is]...);
}

template <size_t MaxArgs>
inline drogon::Task<drogon::orm::Result> drogon_co_bind(
    const std::shared_ptr<drogon::orm::DbClient>& dbClient,
    const std::string& sql,
    const std::vector<std::string>& bindValues) 
{
    if (bindValues.size() > MaxArgs) 
    {
        throw std::out_of_range("Can only bind up to " + std::to_string(MaxArgs) + " values");
    }

    using ReturnType = drogon::Task<drogon::orm::Result>;
    using FnPtr = ReturnType(*)(const std::shared_ptr<drogon::orm::DbClient>&, 
                                const std::string&, 
                                const std::vector<std::string>&);

    static constexpr auto table = []<size_t... Is>(std::index_sequence<Is...>) 
    {
        return std::array<FnPtr, sizeof...(Is)>
        {
            [](const std::shared_ptr<drogon::orm::DbClient>& client, const std::string& q, const std::vector<std::string>& v) {
                return drogon_exec_coro_impl(client, q, v, std::make_index_sequence<Is>{}); 
            }...
        };
    }(std::make_index_sequence<MaxArgs + 1>{});

    return table[bindValues.size()](dbClient, sql, bindValues);
}

inline std::string build_placeholder_sql(const std::string& baseSql, size_t count, bool isPostgres = true) 
{
    if (count == 0) 
    {
        return baseSql + "()";
    }

    std::stringstream ss;
    ss << baseSql << "(";
    for (size_t i = 0; i < count; ++i) 
    {
        if (isPostgres) 
        {
            ss << "$" << (i + 1);
        } else {
            ss << "?";
        }
        
        if (i < count - 1) {
            ss << ", ";
        }
    }
    ss << ")";
    return ss.str();
}


#endif
