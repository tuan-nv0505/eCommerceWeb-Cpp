//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#ifndef DROGONSERVER_PRODUCTREPOSITORY_H
#define DROGONSERVER_PRODUCTREPOSITORY_H

#include "../models/Product.h"
#include "../models/custom/ProductWithCategory.h"

#include <drogon/drogon.h>
#include <drogon/orm/Criteria.h>

#include <vector>
#include <unordered_map>

class ProductRepository
{
public:
    drogon::Task<std::vector<ProductWithCategory>> list(const std::unordered_map<std::string, std::string> &params);
    drogon::Task<std::optional<ProductWithCategory>> get(int id);
    drogon::Task<ProductWithCategory> add(drogon_model::saledb::Product &item);
    drogon::Task<bool> remove(int id);
};


#endif
