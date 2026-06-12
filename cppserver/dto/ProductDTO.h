//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#ifndef CPPSERVER_PRODUCTDTO_H
#define CPPSERVER_PRODUCTDTO_H

#include "../models/Product.h"
#include <drogon/drogon.h>
#include <memory>

#include "DTOAdapter.h"

struct ProductDTO : public DTOAdapter<ProductDTO> {
  std::optional<int32_t> id;
  std::string name;
  std::optional<std::string> description;
  std::optional<std::string> price;
  std::optional<std::string> manufacturer;
  std::optional<std::string> image;
  std::optional<std::string> createdDate;
  std::optional<bool> active;
  std::optional<drogon::HttpFile> file;
  int32_t categoryId;
  std::optional<std::string> categoryName;

  static ProductDTO
  fromForm(const std::unordered_map<std::string, std::string> &form,
           std::vector<drogon::HttpFile> files);
  static ProductDTO fromModel(const drogon_model::saledb::Product &model,
                              const std::optional<std::string> &categoryName);
  Json::Value toJson() const;
  static ProductDTO fromJson(const Json::Value &json);
};

#endif // CPPSERVER_PRODUCTDTO_H
