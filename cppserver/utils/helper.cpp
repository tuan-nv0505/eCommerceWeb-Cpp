//
// Created by Nguyễn Tuấn on 11/06/2026.
//

#include "helper.h"

#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <fstream>



std::string getExtension(std::string fileName) {
    size_t idx = fileName.find_last_of('.');
    if (idx != std::string::npos) {
        return std::string(fileName.substr(idx + 1));
    }
    return "";
}

std::string sha1(const std::string &input)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::ostringstream ss;

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

Json::Value loadJson(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open: " + path);
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    if (!Json::parseFromStream(builder, file, &root, &errs))
    {
        throw std::runtime_error(errs);
    }

    return root;
}
