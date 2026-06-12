//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#ifndef CPPSERVER_PRODUCTCONTROLLER_H
#define CPPSERVER_PRODUCTCONTROLLER_H

#include <drogon/HttpController.h>
#include <drogon/drogon.h>

#include "../models/Product.h"
#include "../services/ProductService.h"
#include "BaseController.h"

class ProductController : public drogon::HttpController<ProductController>,
                          BaseController {
private:
  std::shared_ptr<ProductService> productService;

public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ProductController::list, "/api/products", drogon::Get);
  ADD_METHOD_TO(ProductController::add, "/api/products", drogon::Post);
  ADD_METHOD_TO(ProductController::detail, "/api/products/{id}", drogon::Get);
  ADD_METHOD_TO(ProductController::remove, "/api/products/{id}",
                drogon::Delete);
  METHOD_LIST_END

  ProductController();

  drogon::Task<drogon::HttpResponsePtr> list(drogon::HttpRequestPtr request);
  drogon::Task<drogon::HttpResponsePtr> add(drogon::HttpRequestPtr request);
  drogon::Task<drogon::HttpResponsePtr> detail(drogon::HttpRequestPtr request,
                                               int id);
  drogon::Task<drogon::HttpResponsePtr> remove(drogon::HttpRequestPtr request,
                                               int id);
};

#endif
