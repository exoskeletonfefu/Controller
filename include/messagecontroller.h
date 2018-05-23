#pragma once
#include <QString>
#include <string>
#include <map>

#include "message.h"
#include "scheme.h"
#include "server.h"

class MessageController {
public:
    MessageController(Server *server);
    int addScheme(Message::Scheme *scheme, Message::Command::Type command);
    void writeStates();
    void writeInits(int descriptor);
//    std::string getData(int id, Message::Command::Type command);
//    std::string getData(Message::Scheme *scheme, Message::Command::Type command);
    void updateControl(QString data);
    bool isUpdated(Message::Scheme *scheme);
private:
    void updateField(Message::Scheme* scheme, rapidjson::Value &name, rapidjson::Value &type, rapidjson::Value &field);
    int schemeId;
    std::map<int, Message::Scheme*> controls;
    std::map<int, Message::Scheme*> states;
    std::map<Message::Scheme*, int> ids;
    std::map<Message::Scheme*, bool> updated;
    Server* server;
};
