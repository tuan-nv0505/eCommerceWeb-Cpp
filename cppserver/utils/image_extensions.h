//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#ifndef DROGONSERVER_IMAGE_EXTENSIONS_H
#define DROGONSERVER_IMAGE_EXTENSIONS_H

#include <vector>

namespace ImageType
{
    inline constexpr const char* PNG = "png";
    inline constexpr const char* JPG = "jpg";
    inline constexpr const char* JPEG = "jpeg";
    inline constexpr const char* WEBP = "webp";
    inline constexpr const char* GIF = "gif";

    inline std::vector<std::string> getAll() {
        return {PNG, JPG, JPEG, WEBP, GIF};
    }
}

#endif //DROGONSERVER_IMAGE_EXTENSIONS_H
