//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#ifndef DROGONSERVER_APPLICATIONCONTEXT_H
#define DROGONSERVER_APPLICATIONCONTEXT_H

#include "../services/ProductService.h"
#include "../services/CloudinaryService.h"

#include <memory>

class ApplicationContext
{
private:
    std::shared_ptr<ProductService> productService;
    std::shared_ptr<CloudinaryService> cloudinaryService;

    ApplicationContext() = default;
    ApplicationContext(const ApplicationContext &) = delete;
    ApplicationContext &operator=(const ApplicationContext &) = delete;

public:
    static ApplicationContext &getInstance();
    void init();

    std::shared_ptr<ProductService> getProductService();
    std::shared_ptr<CloudinaryService> getCloudinaryService();
};

#endif // DROGONSERVER_APPLICATIONCONTEXT_H
