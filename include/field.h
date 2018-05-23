#pragma once
#include <string>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace Message {

namespace Type {
enum Type {
    NUMBER = 0,
    ENUM = 1
};
}

class Field {
public:
    Field(int size, void* dataPoint);
//    int getDescriptor() const;
    std::string getTitle() const;
    Type::Type getType() const;
    int getSize() const;
    void *getDataPoint() const;
    virtual rapidjson::Value toJson(rapidjson::Document *document);
protected:
    std::string title;
    Type::Type type;
    int size;
    void *dataPoint;
};

class Number : public Field {
public:
    Number(int value, int size, void *dataPoint);
    int getValue() const;
    Number &setTitle(std::string title);
    Number &setMin(int min);
    Number &setMax(int max);
    rapidjson::Value toJson(rapidjson::Document *document) override;
private:
    int value = 0;
    int min = 0;
    int max = 0;
};

class Enum : public Field {
private:
    class Item {
    public:
        int value;
        std::string title;
    };
public:
    Enum(int currentItem, int size, void *dataPoint);
    Enum &add(int value, std::string title);
    int getCurrentItem() const;
    rapidjson::Value toJson(rapidjson::Document *document) override;
    Enum &setTitle(std::string title);
    std::vector<Item> items;
private:
    int currentItem;
//    void *dataPoint;
//    int size;
};
}
