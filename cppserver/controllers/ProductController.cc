//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#include "ProductController.h"
#include "../app_configs/ApplicationContext.h"

#include <vector>

using namespace drogon_model::saledb;

ProductController::ProductController()
{
    this->productService = ApplicationContext::getInstance().getProductService();
}

drogon::Task<drogon::HttpResponsePtr> ProductController::list(drogon::HttpRequestPtr request)
{
    co_return co_await this->handleRequest([&]() -> drogon::Task<drogon::HttpResponsePtr>
    {
        drogon::SafeStringMap<std::string> drogonParams = request->getParameters();
        auto params = std::unordered_map<std::string, std::string>(drogonParams.begin(), drogonParams.end());

        std::vector<ProductDTO> productDTOs = co_await this->productService->list(params);

        Json::Value jsonArray(Json::arrayValue);
        for (const ProductDTO &productDTO: productDTOs)
        {
            jsonArray.append(productDTO.toJson());
        }

        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(jsonArray);
        response->setStatusCode(drogon::k200OK);
        co_return response;
    });
}


drogon::Task<drogon::HttpResponsePtr> ProductController::add(drogon::HttpRequestPtr request)
{
    co_return co_await this->handleRequest([&]()-> drogon::Task<drogon::HttpResponsePtr>
    {
        ProductDTO productDTO = ProductDTO::toDTO(request);

        ProductDTO serviceResult = co_await this->productService->add(productDTO);

        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(serviceResult.toJson());
        response->setStatusCode(drogon::k201Created);
        co_return response;
    });
}

drogon::Task<drogon::HttpResponsePtr> ProductController::detail(drogon::HttpRequestPtr request, int id)
{
    co_return co_await this->handleRequest([&]()-> drogon::Task<drogon::HttpResponsePtr>
    {
        ProductDTO productDTO = co_await this->productService->get(id);
        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(productDTO.toJson());
        response->setStatusCode(drogon::k200OK);
        co_return response;
    });
}

drogon::Task<drogon::HttpResponsePtr> ProductController::remove(drogon::HttpRequestPtr request, int id)
{
    co_return co_await this->handleRequest([&]()-> drogon::Task<drogon::HttpResponsePtr>
    {
        co_await this->productService->remove(id);
        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k204NoContent);
        co_return response;
    });
}