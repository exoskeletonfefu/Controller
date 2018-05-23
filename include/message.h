#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>

#include "field.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace Message {

namespace Command {
enum Type {
    INIT    = 0,
    STATE   = 1,
    CONTROL = 2
};
}

class Field;

typedef std::shared_ptr<rapidjson::Document> PDocument;

class Message {
public:
    Message(Command::Type command, std::map<int, std::pair<void*, int>> *fields);
    Message &add(Field &item);
    std::string getData();
    std::string getTitle() const;
    Message &setTitle(std::string title);
    Message &setId(int id);
private:
    std::map<int, std::pair<void*, int>> *fields;
    int fieldId;
    std::string title;
    rapidjson::Document *document;
};
}

