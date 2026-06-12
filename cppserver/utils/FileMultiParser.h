//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#ifndef CPPSERVER_FILEMULTIPARSER_H
#define CPPSERVER_FILEMULTIPARSER_H

#include <vector>

#include <drogon/drogon.h>

class FileMultiParser {
private:
  std::vector<drogon::HttpFile> files;

public:
  FileMultiParser(const drogon::HttpRequestPtr &request) {
    drogon::MultiPartParser parser;
    if (parser.parse(request) != 0)
      throw std::runtime_error("Parsing failed");
    this->files = parser.getFiles();
  }

  std::optional<drogon::HttpFile> getFileByField(std::string fieldName) const {
    for (const drogon::HttpFile &file : this->files) {
      if (file.getFileName() == fieldName) {

        return file;
      }
    }
    return std::nullopt;
  }

  std::vector<drogon::HttpFile>
  getMultipleFilesByField(std::string fieldName) const {
    std::vector<drogon::HttpFile> result;
    for (const drogon::HttpFile &file : this->files) {
      if (file.getFileName() == fieldName) {
        result.push_back(file);
      }
    }
    return result;
  }

  const std::vector<drogon::HttpFile> &getAllFiles() const {
    return this->files;
  }
};

#endif
