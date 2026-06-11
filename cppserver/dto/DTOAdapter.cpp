//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#include "DTOAdapter.h"
#include "../exceptions/JsonFormatException.h"
#include "../utils/FileMultiParser.h"
#include "ProductDTO.h"

#include <memory>
#include <unordered_map>

template<typename T>
T DTOAdapter<T>::toDTO(const drogon::HttpRequestPtr &request)
{
    std::shared_ptr<Json::Value> jsonPtr = request->getJsonObject();

    if (jsonPtr != nullptr) {
        return T::fromJson(*jsonPtr);
    }

    drogon::MultiPartParser parser;

    if (parser.parse(request) == 0)
    {
        auto drogonMap = parser.getParameters();
        auto map = std::unordered_map<std::string, std::string>(drogonMap.begin(), drogonMap.end());

        FileMultiParser fileMultiParser(request);

        return T::fromForm(map, fileMultiParser.getAllFiles());
    }
    throw JsonFormatException("Invalid request");
}

template class DTOAdapter<ProductDTO>;