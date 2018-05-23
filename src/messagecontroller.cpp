#include "messagecontroller.h"

using namespace rapidjson;

MessageController::MessageController(Server *server) : server(server) {
    schemeId = 0;
}

int MessageController::addScheme(Message::Scheme *scheme, Message::Command::Type command) {
    schemeId++;
    switch (command) {
    case Message::Command::CONTROL: {
        controls.emplace(schemeId, scheme);
        updated.emplace(scheme, false);
        break;
    }
    case Message::Command::STATE: {
        states.emplace(schemeId, scheme);
        break;
    }
    }
    ids.emplace(scheme, schemeId);
    return schemeId;
}

void MessageController::writeStates() {
    for (auto &scheme: states) {
        server->write(scheme.second->message(Message::Command::STATE).setId(scheme.first).getData());
    }
}

void MessageController::writeInits(int descriptor) {
    for (auto &scheme: states) {
        server->write(scheme.second->message(Message::Command::INIT).setId(scheme.first).getData(), descriptor);
    }
    for (auto &scheme: controls) {
        server->write(scheme.second->message(Message::Command::CONTROL).setId(scheme.first).getData(), descriptor);
    }
}

void MessageController::updateControl(QString data) {
    Document document;
    document.Parse(data.toStdString().data());
    document.GetObject();
    Value &fields = document["fields"];
    Value &id = document["id"];
    updated.at(controls.at(id.GetInt())) = true;
    for (auto &field: fields.GetArray()) {
        updateField(controls.at(id.GetInt()), field["id"], field["type"], field);
    }
}

bool MessageController::isUpdated(Message::Scheme *scheme) {
    bool result = updated.at(scheme);
    updated.at(scheme) = false;
    return result;
}

void MessageController::updateField(Message::Scheme* scheme, rapidjson::Value &name, rapidjson::Value &type, rapidjson::Value &field) {
    switch (type.GetInt()) {
    case Message::Type::NUMBER: {
        scheme->setFieldValue<int>(name.GetInt(), field["value"].GetInt());
        break;
    }
    case Message::Type::ENUM: {
        scheme->setFieldValue<int>(name.GetInt(), field["currentItem"].GetInt());
        break;
    }
    }
}
