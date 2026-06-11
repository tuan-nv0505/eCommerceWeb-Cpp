//
// Created by Nguyễn Tuấn on 09/06/2026.
//

#include "BaseController.h"
#include "../exceptions/ValidationException.h"
#include "../exceptions/ProductException.h"
#include "../dto/ErrorDTO.h"
#include "../exceptions/JsonFormatException.h"


drogon::Task<drogon::HttpResponsePtr> BaseController::handleRequest(std::function<drogon::Task<drogon::HttpResponsePtr>()> &&function)
{
    try
    {
        co_return co_await function();
    }
    catch (const ValidationException& e)
    {
        ErrorDTO error;
        error.statusCode = "400 Bad Request";
        error.errorMessage = e.what();

        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(error.toJson());
        response->setStatusCode(drogon::k400BadRequest);

        co_return response;
    }
    catch (const ProductException& e)
    {
        ErrorDTO error;
        error.statusCode = "400 Bad Request";
        error.errorMessage = e.what();

        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(error.toJson());
        response->setStatusCode(drogon::k400BadRequest);

        co_return response;
    }
    catch (const JsonFormatException& e)
    {
        ErrorDTO error;
        error.statusCode = "400 Bad Request";
        error.errorMessage = e.what();

        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(error.toJson());
        response->setStatusCode(drogon::k400BadRequest);

        co_return response;
    }
    catch (const std::exception& e)
    {
        ErrorDTO error;
        error.statusCode = "500 Internal Server Error";
        error.errorMessage = e.what();

        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(error.toJson());
        response->setStatusCode(drogon::k500InternalServerError);

        co_return response;
    }
}
