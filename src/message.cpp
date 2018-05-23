#include <string>
#include <iostream>

#include "message.h"

using namespace std;
using namespace rapidjson;

Message::Message::Message(Command::Type command, std::map<int, std::pair<void*, int>> *fields) :
    document(new Document(kObjectType)) {
    this->fields = fields;
    fieldId = 0;

    document->SetObject();
    Document::AllocatorType& alloc = document->GetAllocator();
    Value arr(kArrayType);
    document->AddMember("command", command, alloc);
    document->AddMember("id", -1, alloc);
    document->AddMember("fields", arr, alloc);
}

Message::Message& Message::Message::add(Field &item) {
    fieldId++;
    if (fields->find(fieldId) == fields->end())
        fields->emplace(fieldId, std::make_pair(item.getDataPoint(), item.getSize()));
    Document::AllocatorType& alloc = document->GetAllocator();
    Value val(kObjectType);
    val = item.toJson(document);
    val.AddMember("id", fieldId, alloc);
    document->GetObject()["fields"].PushBack(val, alloc);
    return *this;
}

Message::Message& Message::Message::setId(int id) {
    document->GetObject()["id"] = id;
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

