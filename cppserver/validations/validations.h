//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#ifndef DROGONSERVER_UTILS_H
#define DROGONSERVER_UTILS_H

#include <drogon/drogon.h>

#include <string>

// Json
std::string validateString(const Json::Value &json, const std::string &fieldName, bool required = false,
                           size_t maxLength = 0);

int32_t validateInt32(const Json::Value &json, const std::string &fieldName, bool required = false,
                      std::optional<int32_t> minValue = std::nullopt);

double validateDouble(const Json::Value &json, const std::string &fieldName, bool required = false,
                      std::optional<double> minValue = std::nullopt);

std::optional<bool> validateBool(const Json::Value &json, const std::string &fieldName);

// Form (std::unordered_map)
std::string validateString(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName,
                           bool required = false, size_t maxLength = 0);

int32_t validateInt32(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName,
                      bool required = false, std::optional<int32_t> minValue = std::nullopt);

double validateDouble(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName,
                      bool required = false, std::optional<double> minValue = std::nullopt);

std::optional<bool> validateBool(const std::unordered_map<std::string, std::string> &form,
                                 const std::string &fieldName);

std::optional<drogon::HttpFile> validateFile(const std::vector<drogon::HttpFile> &files, const std::string &fieldName,
                  std::vector<std::string> fileTypes, bool required = false, size_t maxSize = 0);



#endif //DROGONSERVER_UTILS_H
