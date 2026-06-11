
#ifndef CPPSERVER_PRODUCTWITHCATEGORY_H
#define CPPSERVER_PRODUCTWITHCATEGORY_H

#include "../Product.h"
#include <string>

struct ProductWithCategory {
    drogon_model::saledb::Product product;
    std::string categoryName;
};

#endif