#pragma once
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace Message {

namespace Type {
enum Type {
    NUMBER = 0
};
}

//namespace Command {
//enum Type {
//    INIT = 0,
//    STATE = 1
//};
//}

class Number;

typedef std::shared_ptr<rapidjson::Document> PDocument;

class Message {
public:
    Message();
    Message &add(const Number &number);
    std::string getData();
    std::string getTitle() const;
    Message &setTitle(std::string title);
private:
    std::string title;
    PDocument document;
};

class Number {
public:
    Number(int value);
    int getValue() const;
    std::string getTitle() const;
    Number &setTitle(std::string title);
private:
    std::string title;
    int value;
};

class Id {
public:
    uint8_t id;
    Message message() {
        return Message().setTitle("first").add(Number(id).setTitle("id")); }
};

class Test {
public:
    uint8_t id;
    Message message() {
        return Message().add(Number(id).setTitle("test")).add(Number(8).setTitle("another")); }
};
}
