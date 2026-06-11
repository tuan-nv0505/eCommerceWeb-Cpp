//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#ifndef DROGONSERVER_PRODUCTSERVICE_H
#define DROGONSERVER_PRODUCTSERVICE_H

#include "../repositories/ProductRepository.h"
#include "../dto/ProductDTO.h"
#include "CloudinaryService.h"

#include <drogon/drogon.h>


class ProductService
{
private:
    std::shared_ptr<ProductRepository> productRepository;
    std::shared_ptr<CloudinaryService> cloudinaryService;
public:
    ProductService(const std::shared_ptr<ProductRepository> &productRepository);
    drogon::Task<std::vector<ProductDTO>> list(const std::unordered_map<std::string, std::string> &params);
    drogon::Task<ProductDTO> add(ProductDTO productDTO);
    drogon::Task<ProductDTO> get(int id);
    drogon::Task<> remove(int id);
};


#endif
