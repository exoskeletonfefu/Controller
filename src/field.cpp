#include "field.h"

using namespace rapidjson;

Message::Type::Type Message::Field::getType() const {
    return type;
}

std::string Message::Field::getTitle() const {
    return title;
}

int Message::Field::getSize() const {
    return size;
}

void *Message::Field::getDataPoint() const {
    return dataPoint;
}

Message::Field::Field(int size, void* dataPoint) :size(size), dataPoint(dataPoint) {}

rapidjson::Value Message::Field::toJson(Document *document) {
    Document::AllocatorType& alloc = document->GetAllocator();
    Value field(kObjectType);
    field.AddMember("type", type, alloc);
    Value str(kStringType);
    str.SetString(title.data(), alloc);
    field.AddMember("title", str, alloc);
    return field;
}

Message::Number::Number(int value, int size, void *dataPoint) : Field(size, dataPoint), value(value) {
    type = Type::NUMBER;
}

rapidjson::Value Message::Number::toJson(Document *document) {
    Document::AllocatorType& alloc = document->GetAllocator();
    Value numb(kObjectType);
    numb = Field::toJson(document);
    numb.AddMember("value", value, alloc);
    numb.AddMember("min", min, alloc);
    numb.AddMember("max", max, alloc);
    return numb;
}

int Message::Number::getValue() const {
    return value;
}

Message::Number &Message::Number::setTitle(std::string title) {
    this->title = title;
    return *this;
}

Message::Number &Message::Number::setMin(int min) {
    this->min = min;
    return *this;
}

Message::Number &Message::Number::setMax(int max) {
    this->max = max;
    return *this;
}

Message::Enum::Enum(int currentItem, int size, void *dataPoint) : Field(size, dataPoint), currentItem(currentItem) {
    type = Type::ENUM;
};

rapidjson::Value Message::Enum::toJson(Document *document) {
    Document::AllocatorType& alloc = document->GetAllocator();
    Value en(kObjectType);
    en = Field::toJson(document);
    Value arr(kArrayType);
    for (auto &it: items) {
        Item &item = it;
        Value val(kObjectType);
        val.AddMember("value", item.value, alloc);
        Value str(kStringType);
        str.SetString(item.title.data(), alloc);
        val.AddMember("title", str, alloc);
        arr.PushBack(val, alloc);
    }
    en.AddMember("items", arr, alloc);
    en.AddMember("currentItem", currentItem, alloc);
    return en;
}

int Message::Enum::getCurrentItem() const {
    return currentItem;
}

Message::Enum &Message::Enum::add(int value, std::string title) {
    Item item;
    item.value = value;
    item.title = title;
    items.push_back(item);
    return *this;
}

Message::Enum &Message::Enum::setTitle(std::string title) {
    this->title = title;
    return *this;
}
