//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#include "ProductService.h"
#include "../exceptions/ProductException.h"
#include "../app_configs/ApplicationContext.h"

#include <stdexcept>

using namespace drogon_model;

ProductService::ProductService(const std::shared_ptr<ProductRepository> &productRepository)
{
    this->productRepository = productRepository;
}

drogon::Task<std::vector<ProductDTO>> ProductService::list(const std::unordered_map<std::string, std::string> &params)
{
    try
    {
        std::vector<ProductWithCategory> items = co_await this->productRepository->list(params);
        std::vector<ProductDTO> productDTOs;
        for (std::vector<ProductWithCategory>::iterator it = items.begin(); it != items.end(); ++it)
        {
            productDTOs.push_back(ProductDTO::fromModel(it->product, it->categoryName));
        }

        co_return productDTOs;

    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        throw ProductException("Database error: " + std::string(e.base().what()));
    }
    catch (const std::exception &e)
    {
        throw ProductException("Load list service failed: " + std::string(e.what()));
    }

}

drogon::Task<ProductDTO> ProductService::add(ProductDTO productDTO)
{

    saledb::Product product;
    product.setName(productDTO.name);

    if (productDTO.price)
        product.setPrice(productDTO.price.value());
    else
        product.setPriceToNull();

    if (productDTO.description)
        product.setDescription(productDTO.description.value());
    else
        product.setDescriptionToNull();

    if (productDTO.manufacturer)
        product.setManufacturer(productDTO.manufacturer.value());
    else
        product.setManufacturerToNull();

    if (productDTO.active)
        product.setActive(productDTO.active.value());
    else
        product.setActiveToNull();

    if (productDTO.categoryId)
        product.setCategoryId(productDTO.categoryId);

    try
    {
        if (productDTO.file->save("../uploads") == 0)
        {
            std::string filePath = "../uploads/" + productDTO.file->getFileName();
            std::shared_ptr<CloudinaryService> cloudinaryService = ApplicationContext::getInstance().getCloudinaryService();
            UploadResult result = cloudinaryService->upload(filePath);
            product.setImage(result.secureUrl);
            std::filesystem::remove("../uploads/" + productDTO.file->getFileName());
        }

        ProductWithCategory item =  co_await this->productRepository->add(product);
        ProductDTO productDTORes = ProductDTO::fromModel(item.product, item.categoryName);

        co_return productDTORes;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        throw ProductException("Database error: " + std::string(e.base().what()));
    } 
    catch (const std::exception &e)
    {
        throw ProductException("Add product failed: " + std::string(e.what()));
    }
}

drogon::Task<ProductDTO> ProductService::get(int id)
{
    try
    {
        auto product = co_await productRepository->get(id);

        if (!product)
            throw ProductException("Product not found");

        co_return ProductDTO::fromModel(
            product->product,
            product->categoryName
        );
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        throw ProductException("Database error: " + std::string(e.base().what()));
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Get product id: " + std::to_string(id) + " failed: " + std::string(e.what()));
    }
}

drogon::Task<> ProductService::remove(int id)
{
    try
    {
        bool result = co_await this->productRepository->remove(id);
        if (!result)
        {
            throw ProductException("Product not found");
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        throw ProductException("Database error: " + std::string(e.base().what()));
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Get product failed: " + std::string(e.what()));
    }
}
