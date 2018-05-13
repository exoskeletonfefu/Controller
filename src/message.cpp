#include <string>
#include <iostream>

#include "message.h"

using namespace std;
using namespace rapidjson;

Message::Message::Message() :
    document(new Document(kObjectType)) {
    document->SetObject();
    Document::AllocatorType& alloc = document->GetAllocator();
    Value arr(kArrayType);
//    document->AddMember("command", command, alloc);
    document->AddMember("fields", arr, alloc);
}

Message::Message& Message::Message::add(const Number &number) {
    Document::AllocatorType& alloc = document->GetAllocator();
    Value numb(kObjectType);
    Value str(kStringType);
    numb.AddMember("type", Type::NUMBER, alloc);
    str.SetString(number.getTitle().data(), alloc);
    numb.AddMember("title", str, alloc);
    numb.AddMember("value", number.getValue(), alloc);
    document->GetObject()["fields"].PushBack(numb, alloc);
//    document->AddMember("id", numb, alloc);
    return *this;
}

string Message::Message::getData() {
    Document::AllocatorType& alloc = document->GetAllocator();
    Value str(kStringType);
    str.SetString(title.data(), alloc);
    document->AddMember("title", str, alloc);

    StringBuffer buffer;
    buffer.Clear();
    Writer<StringBuffer> writer(buffer);
    document->Accept(writer);
    string result(2, 0);
    result[0] = (char)((buffer.GetSize() >> 8) & 0xFF);
    result[1] = (char)(buffer.GetSize() & 0xFF);
    result.append(buffer.GetString());
    return result;
}

std::string Message::Message::getTitle() const {
    return title;
}

Message::Message &Message::Message::setTitle(std::string title) {
    this->title = title;
    return *this;
}

Message::Number::Number(int value) {
    this->value = value;
}

int Message::Number::getValue() const {
    return value;
}

std::string Message::Number::getTitle() const {
    return title;
}

Message::Number &Message::Number::setTitle(std::string title) {
    this->title = title;
    return *this;
}
