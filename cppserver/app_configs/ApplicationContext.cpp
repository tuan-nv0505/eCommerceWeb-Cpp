//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#include "../app_configs/ApplicationContext.h"


void ApplicationContext::init()
{
    this->productService = std::make_shared<ProductService>(std::make_shared<ProductRepository>());
    this->cloudinaryService = std::make_shared<CloudinaryService>(std::make_shared<CloudinaryClient>());
}

ApplicationContext& ApplicationContext::getInstance()
{
    static ApplicationContext applicationContext;
    return applicationContext;
}


std::shared_ptr<ProductService> ApplicationContext::getProductService()
{
    return this->productService;
}

std::shared_ptr<CloudinaryService> ApplicationContext::getCloudinaryService()
{
    return this->cloudinaryService;
}
