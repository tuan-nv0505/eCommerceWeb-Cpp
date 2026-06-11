//
// Created by Nguyễn Tuấn on 10/06/2026.
//

#include "ProductDTO.h"
#include "../validations/validations.h"
#include "../utils/image_extensions.h"

using namespace drogon_model;

ProductDTO ProductDTO::fromForm(const std::unordered_map<std::string, std::string> &form, std::vector<drogon::HttpFile> files)
{
    ProductDTO productDTO;

    productDTO.name = validateString(form, "name", true, 50);
    productDTO.categoryId = validateInt32(form, "category_id", true, 1);

    std::string priceStr = std::to_string(validateDouble(form, "price"));
    if (!priceStr.empty()) productDTO.price = priceStr;

    std::string manuStr = validateString(form, "manufacturer");
    if (!manuStr.empty()) productDTO.manufacturer = manuStr;

    std::string descStr = validateString(form, "description");
    if (!descStr.empty()) productDTO.description = descStr;

    productDTO.active = validateBool(form, "active").value();

    productDTO.file = validateFile(files, "file", ImageType::getAll(), false, 0.5 * 1024 * 1024);

    return productDTO;
}

ProductDTO ProductDTO::fromModel(const saledb::Product &model, const std::optional<std::string> &categoryName)
{
    ProductDTO dto;

    if (model.getId())
        dto.id = model.getValueOfId();

    if (model.getName())
        dto.name = model.getValueOfName();

    if (model.getDescription())
        dto.description = model.getValueOfDescription();

    if (model.getPrice())
        dto.price = model.getValueOfPrice();

    if (model.getManufacturer())
        dto.manufacturer = model.getValueOfManufacturer();

    if (model.getImage())
        dto.image = model.getValueOfImage();

    if (model.getCreatedDate())
    {
        dto.createdDate = model.getValueOfCreatedDate().toDbStringLocal();
    }

    if (model.getActive())
        dto.active = model.getValueOfActive();

    if (model.getCategoryId())
        dto.categoryId = model.getValueOfCategoryId();

    if (categoryName)
        dto.categoryName = categoryName.value();

    return dto;
}

Json::Value ProductDTO::toJson() const
{
    Json::Value json;

    if (this->id)
        json["id"] = this->id.value();

    json["name"] = this->name;

    if (this->description)
        json["description"] = this->description.value();
    else
        json["description"] = Json::nullValue;
    if (this->price)
        json["price"] = this->price.value();
    else json["price"] = Json::nullValue;
    if (this->manufacturer)
        json["manufacturer"] = this->manufacturer.value();
    else json["manufacturer"] = Json::nullValue;
    if (this->image)
        json["image"] = this->image.value();
    else
        json["image"] = Json::nullValue;
    if (this->createdDate)
        json["created_date"] = this->createdDate.value();
    else json["created_date"] = Json::nullValue;
    if (this->active)
        json["active"] = this->active.value();
    else json["active"] = Json::nullValue;

    json["category_id"] = this->categoryId;

    if (this->categoryName)
        json["category_name"] = this->categoryName.value();
    else
        json["category_name"] = Json::nullValue;

    return json;
}

ProductDTO ProductDTO::fromJson(const Json::Value &json)
{
    ProductDTO productDTO;

    productDTO.name = validateString(json, "name", true, 50);
    productDTO.categoryId = validateInt32(json, "category_id", true, 1);

    if (!json["price"].isNull())
    {
        double p = validateDouble(json, "price", false, 0.0);
        productDTO.price = std::to_string(p);
    }

    productDTO.active = validateBool(json, "active");

    if (!json["description"].isNull()) productDTO.description = validateString(json, "description");
    if (!json["manufacturer"].isNull())
        productDTO.manufacturer = validateString(
            json, "manufacturer");
    if (!json["image"].isNull()) productDTO.image = validateString(json, "image");
    if (!json["created_date"].isNull())
        productDTO.createdDate = validateString(
            json, "created_date");

    return productDTO;
}
