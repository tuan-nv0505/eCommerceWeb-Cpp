//
// Created by Nguyễn Tuấn on 10/06/2026.
//


#include "validations.h"
#include "../exceptions/ValidationException.h"
#include "../utils/helper.h"

// ==========================================
// Json
// ==========================================
std::string validateString(const Json::Value &json, const std::string &fieldName, bool required, size_t maxLength)
{
    if (json[fieldName].isNull())
    {
        if (required) throw ValidationException("Field '" + fieldName + "' is required.");
        return "";
    }
    if (!json[fieldName].isString())
    {
        throw ValidationException("Field '" + fieldName + "' must be a string.");
    }

    std::string val = json[fieldName].asString();
    if (required && val.empty())
    {
        throw ValidationException("Field '" + fieldName + "' must not be empty.");
    }
    if (maxLength > 0 && val.length() > maxLength)
    {
        throw ValidationException(
            "Field '" + fieldName + "' must not exceed " + std::to_string(maxLength) + " characters.");
    }
    return val;
}

int32_t validateInt32(const Json::Value &json, const std::string &fieldName, bool required,
                      std::optional<int32_t> minValue)
{
    if (json[fieldName].isNull())
    {
        if (required) throw ValidationException("Field '" + fieldName + "' is required.");
        return 0;
    }

    int32_t val = 0;
    if (json[fieldName].isNumeric())
    {
        val = json[fieldName].asInt();
    } else if (json[fieldName].isString())
    {
        std::string str = json[fieldName].asString();
        if (str.empty() && !required) return 0;
        try
        {
            size_t idx = 0;
            val = std::stoi(str, &idx);
            if (idx != str.length())
                throw ValidationException(
                    "Field '" + fieldName + "' contains invalid characters.");
        } catch (...)
        {
            throw ValidationException("Field '" + fieldName + "' must be a valid integer.");
        }
    } else
    {
        throw ValidationException("Field '" + fieldName + "' cannot be converted to integer.");
    }

    if (minValue.has_value() && val < minValue.value())
    {
        throw ValidationException(
            "Field '" + fieldName + "' must be greater than or equal to " + std::to_string(minValue.value()) + ".");
    }
    return val;
}

double validateDouble(const Json::Value &json, const std::string &fieldName, bool required,
                      std::optional<double> minValue)
{
    if (json[fieldName].isNull())
    {
        if (required) throw ValidationException("Field '" + fieldName + "' is required.");
        return 0.0;
    }

    double val = 0.0;
    if (json[fieldName].isNumeric())
    {
        val = json[fieldName].asDouble();
    } else if (json[fieldName].isString())
    {
        std::string str = json[fieldName].asString();
        if (str.empty() && !required) return 0.0;
        try
        {
            size_t idx = 0;
            val = std::stod(str, &idx);
            if (idx != str.length())
                throw ValidationException(
                    "Field '" + fieldName + "' contains invalid characters.");
        } catch (...)
        {
            throw ValidationException("Field '" + fieldName + "' must be a valid decimal number.");
        }
    } else
    {
        throw ValidationException("Field '" + fieldName + "' cannot be converted to decimal.");
    }

    if (minValue.has_value() && val < minValue.value())
    {
        throw ValidationException(
            "Field '" + fieldName + "' cannot be less than " + std::to_string(minValue.value()) + ".");
    }
    return val;
}

std::optional<bool> validateBool(const Json::Value &json, const std::string &fieldName)
{
    if (json[fieldName].isNull()) return std::nullopt;
    if (!json[fieldName].isBool())
    {
        throw ValidationException("Field '" + fieldName + "' must be a boolean (true/false).");
    }
    return json[fieldName].asBool();
}

// ==========================================
// FORM (std::unordered_map)
// ==========================================
std::string validateString(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName,
                           bool required, size_t maxLength)
{
    auto it = form.find(fieldName);
    bool missing = (it == form.end());

    if (missing || it->second.empty())
    {
        if (required) throw ValidationException("Field '" + fieldName + "' is required and cannot be empty.");
        return "";
    }

    if (maxLength > 0 && it->second.length() > maxLength)
    {
        throw ValidationException(
            "Field '" + fieldName + "' must not exceed " + std::to_string(maxLength) + " characters.");
    }
    return it->second;
}

int32_t validateInt32(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName,
                      bool required, std::optional<int32_t> minValue)
{
    auto it = form.find(fieldName);
    if (it == form.end() || it->second.empty())
    {
        if (required) throw ValidationException("Field '" + fieldName + "' is required.");
        return 0;
    }

    int32_t val = 0;
    try
    {
        size_t idx = 0;
        val = std::stoi(it->second, &idx);
        if (idx != it->second.length()) throw std::invalid_argument("");
    } catch (...)
    {
        throw ValidationException("Field '" + fieldName + "' must be a valid number.");
    }

    if (minValue.has_value() && val < minValue.value())
    {
        throw ValidationException("Field '" + fieldName + "' must be >= " + std::to_string(minValue.value()) + ".");
    }
    return val;
}

double validateDouble(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName,
                      bool required, std::optional<double> minValue)
{
    auto it = form.find(fieldName);
    if (it == form.end() || it->second.empty())
    {
        if (required) throw ValidationException("Field '" + fieldName + "' is required.");
        return 0.0;
    }

    double val = 0.0;
    try
    {
        size_t idx = 0;
        val = std::stod(it->second, &idx);
        if (idx != it->second.length()) throw std::invalid_argument("");
    } catch (...)
    {
        throw ValidationException("Field '" + fieldName + "' must be a valid decimal number.");
    }

    if (minValue.has_value() && val < minValue.value())
    {
        throw ValidationException("Field '" + fieldName + "' must be >= " + std::to_string(minValue.value()) + ".");
    }
    return val;
}

std::optional<bool> validateBool(const std::unordered_map<std::string, std::string> &form, const std::string &fieldName)
{
    auto it = form.find(fieldName);
    if (it == form.end() || it->second.empty())
    {
        return std::nullopt;
    }

    std::string val = it->second;
    std::transform(val.begin(), val.end(), val.begin(),
                   [](unsigned char c)
                   {
                       return std::tolower(c);
                   });

    if (val == "true" || val == "1" || val == "on" || val == "yes")
    {
        return true;
    } else if (val == "false" || val == "0" || val == "off" || val == "no")
    {
        return false;
    }

    throw ValidationException("Field '" + fieldName + "' must be a boolean (true/false, 1/0, on/off).");
}

std::optional<drogon::HttpFile> validateFile(const std::vector<drogon::HttpFile> &files, const std::string &fieldName,
                  std::vector<std::string> fileTypes, bool required, size_t maxSize)
{
    auto it = std::find_if(files.begin(), files.end(), [&fieldName](const drogon::HttpFile &file) {
        return file.getItemName() == fieldName;
    });

    if (it == files.end())
    {
        if (required)
        {
            throw ValidationException("Field '" + fieldName + "' is required but no file was uploaded.");
        }
        return std::nullopt;
    }

    const drogon::HttpFile &file = *it;

    if (file.getFileName().empty() || file.fileContent().empty())
    {
        if (required)
        {
            throw ValidationException("Required file in field '" + fieldName + "' is missing or empty.");
        }
        return std::nullopt;
    }

    if (maxSize > 0 && file.fileLength() > maxSize)
    {
        throw ValidationException("File '" + file.getFileName() + "' in field '" + fieldName +
                                  "' exceeds the maximum allowed size of " +
                                  std::to_string(maxSize / 1024 / 1024) + " MB.");
    }

    std::string ext = getExtension(file.getFileName());
    if (ext.empty())
    {
        throw ValidationException("File '" + file.getFileName() + "' in field '" + fieldName + "' has no valid extension.");
    }

    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    bool isValid = false;
    for (std::string type : fileTypes)
    {
        std::transform(type.begin(), type.end(), type.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (ext == type)
        {
            isValid = true;
            break;
        }
    }

    if (!isValid)
    {
        std::string allowedStr = "";
        for (size_t i = 0; i < fileTypes.size(); ++i)
        {
            allowedStr += fileTypes[i] + (i == fileTypes.size() - 1 ? "" : ", ");
        }
        throw ValidationException("File '" + file.getFileName() + "' extension is invalid. Allowed types: [" + allowedStr + "]");
    }

    return file;
}
