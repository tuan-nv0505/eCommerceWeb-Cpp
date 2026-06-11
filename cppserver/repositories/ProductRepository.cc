//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#include "ProductRepository.h"
#include "../paginators/ProductPaginator.h"
#include "../exceptions/ProductException.h"
#include "../utils/database.h"
#include "../models/Category.h"
#include "../utils/helper.h"

#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>
#include <drogon/utils/coroutine.h>

using namespace drogon_model;

drogon::Task<std::vector<ProductWithCategory>>ProductRepository::list(const std::unordered_map<std::string, std::string> &params)
{
    drogon::orm::DbClientPtr client = getDbClient();

    std::string sql =
        "SELECT *, c.name AS category_name "
        "FROM product p "
        "LEFT JOIN category c ON p.category_id = c.id "
        "WHERE 1=1 ";

    std::vector<std::string> binds;
    std::vector<std::string> conditions;

    std::unordered_map<std::string, std::string>::const_iterator it;

    it = params.find("name");
    if (it != params.end())
    {
        std::string name = it->second;

        for (int i = 0; i < name.size(); ++i)
            name[i] = static_cast<char>(std::tolower(name[i]));

        conditions.push_back("LOWER(p.name) LIKE $" + std::to_string(binds.size() + 1));
        binds.push_back("%" + name + "%");
    }

    it = params.find("minPrice");
    if (it != params.end())
    {
        conditions.push_back("p.price >= $" + std::to_string(binds.size() + 1));
        binds.push_back(it->second);
    }

    it = params.find("maxPrice");
    if (it != params.end())
    {
        conditions.push_back("p.price <= $" + std::to_string(binds.size() + 1));
        binds.push_back(it->second);
    }

    if (!conditions.empty())
    {
        sql += " AND ";
        for (int i = 0; i < conditions.size(); ++i)
        {
            sql += conditions[i];
            if (i + 1 < conditions.size())
                sql += " AND ";
        }
    }

    int page = 1;
    it = params.find("page");
    if (it != params.end())
    {
        try { page = std::stoi(it->second); } catch (...) { page = 1; }
    }

    int offset = (page - 1) * ProductPaginator::PAGE_SIZE;

    sql += " ORDER BY p.id DESC";
    sql += " LIMIT " + std::to_string(ProductPaginator::PAGE_SIZE);
    sql += " OFFSET " + std::to_string(offset);


    drogon::orm::Result result = co_await drogon_co_bind<10>(client, sql, binds);

    std::vector<ProductWithCategory> out;
    out.reserve(result.size());

    for (drogon::orm::Row const &row : result)
    {
        ProductWithCategory item;

        item.product.setId(row["id"].as<int>());
        item.product.setName(row["name"].as<std::string>());
        item.product.setPrice(row["price"].as<std::string>());
        item.product.setDescription(row["description"].as<std::string>());
        item.product.setManufacturer(row["manufacturer"].as<std::string>());
        item.product.setActive(row["active"].as<bool>());
        item.product.setImage(row["image"].as<std::string>());
        item.product.setCategoryId(row["category_id"].as<int>());

        item.categoryName =
            row["category_name"].isNull()
                ? ""
                : row["category_name"].as<std::string>();

        out.push_back(item);
    }

    co_return out;
}

drogon::Task<ProductWithCategory> ProductRepository::add(saledb::Product &product)
{
    drogon::orm::DbClientPtr client = getDbClient();
    std::shared_ptr<drogon::orm::Transaction> transaction = client->newTransaction();


    try
    {
        drogon::orm::CoroMapper<saledb::Product> mapper(transaction);
        saledb::Product productRes = co_await mapper.insert(product);
        drogon::orm::CoroMapper<saledb::Category> catMapper(client);
        saledb::Category category = co_await catMapper.findByPrimaryKey(productRes.getValueOfCategoryId());

        ProductWithCategory item;
        item.product = product;
        item.categoryName = category.getValueOfName();

        co_return item;

    } catch (const drogon::orm::DrogonDbException &e)
    {
        transaction->rollback();
        throw;
    }
}

drogon::Task<std::optional<ProductWithCategory>> ProductRepository::get(int id)
{
    drogon::orm::DbClientPtr client = getDbClient();
    drogon::orm::CoroMapper<saledb::Product> mapper(client);


    saledb::Product product = co_await mapper.findByPrimaryKey(id);
    if (!product.getId()) 
    {
        co_return std::nullopt;
    }

    drogon::orm::CoroMapper<saledb::Category> catMapper(client);
    saledb::Category category = co_await catMapper.findByPrimaryKey(product.getValueOfCategoryId());

    ProductWithCategory item;
    item.product = product;
    item.categoryName = category.getValueOfName();

    co_return item;
}

drogon::Task<bool> ProductRepository::remove(int id)
{
    drogon::orm::DbClientPtr client = getDbClient();
    std::shared_ptr<drogon::orm::Transaction> transaction = client->newTransaction();
    drogon::orm::CoroMapper<saledb::Product> mapper(transaction);

    try {
    {
        saledb::Product product = co_await mapper.findByPrimaryKey(id);
        if (!product.getId()) 
        {
            LOG_ERROR << __FUNCTION__ << " Product not found with id: " << id;
            co_return false;
        }
        co_await mapper.deleteByPrimaryKey(id);
    }
    } 
    catch (const drogon::orm::DrogonDbException &e) 
    {
        transaction->rollback();
        throw;
    
    }
    
    co_return true;
}
