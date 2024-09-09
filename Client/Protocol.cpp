//
// Created by benra on 7/16/2024.
//

#include "Protocol.h"
#include "raylib.h"
Protocol::Protocol(Network& connection) {
    network = &connection;
}

void Protocol::checkTry(std::string& data) {
    if (ParsingUtils::containsChar(data, CONNECTION_FAIL)){
        std::cout<<"failed!\n";
        network->address.sin_port = htons(PORT_2);
    }
    if (ParsingUtils::containsChar(data, CONNECTION_SUCCEED)){
        std::cout<<"success!\n";
        disconnected = false;
    }
}
void Protocol::GameRun(bool levelSwitchFlag, int level, int moveFlag, Vector2 dir, Player& user, Player& other) {
    std::string messageToSend ="";
    std::string data = network->receive();
    if (levelSwitchFlag){
        std::string x = LEVEL_SWITCH + std::to_string(level) + LEVEL_SWITCH;
//        std::cout<<x<<"\n";
        messageToSend += x;
    }
    if (moveFlag){
        std::string x = PLAYER_DIR + std::to_string((int)dir.x) + "," +std::to_string((int)dir.y)+ PLAYER_DIR;
        messageToSend += x;
//        std::cout<<dir.x<<",";
//        std::cout<<dir.y<<"\n";
    }
    if (!data.empty()){
        std::cout<<data<<"\n";
    }
    if (ParsingUtils::containsChar(data,LEVEL_SWITCH)){
        std::string otherLevel = ParsingUtils::extractSubstringBetweenDelimiters(data, '|');
        other.level = std::stoi(otherLevel);
    }
    if (ParsingUtils::containsChar(data,ACTIVE_PLAYER_CORRECTION)){
        std::string coords = ParsingUtils::extractSubstringBetweenDelimiters(data, ACTIVE_PLAYER_CORRECTION);
        if (!coords.empty()){
            Vector2 coordsVec;
            std::vector<std::string> coordsSplit = ParsingUtils::splitstringbychar(coords, ",");
            coordsVec.x = std::stof(coordsSplit[0]);
            coordsVec.y = std::stof(coordsSplit[1]);
            std::cout<<coordsVec.x<<"\n";
            std::cout<<coordsVec.y<<"\n";
            user.activeWorldPosition = coordsVec;
        }
    }
    if (ParsingUtils::containsChar(data,OTHER_PLAYER_DIRECTION)){
        std::string coords = ParsingUtils::extractSubstringBetweenDelimiters(data, OTHER_PLAYER_DIRECTION);
        if (!coords.empty()){
            Vector2 coordsVec;
            std::vector<std::string> coordsSplit = ParsingUtils::splitstringbychar(coords, ",");
            coordsVec.x = std::stof(coordsSplit[0]);
            coordsVec.y = std::stof(coordsSplit[1]);
            other.activeDirection = Player::vectorMapper(coordsVec);
        }
    }
    if (ParsingUtils::containsChar(data,OTHER_PLAYER_POSITION)){
        std::string coords = ParsingUtils::extractSubstringBetweenDelimiters(data, OTHER_PLAYER_POSITION);
        if (!coords.empty()){
            Vector2 coordsVec;
            std::vector<std::string> coordsSplit = ParsingUtils::splitstringbychar(coords, ",");
            coordsVec.x = std::stof(coordsSplit[0]);
            coordsVec.y = std::stof(coordsSplit[1]);
            other.activeWorldPosition = coordsVec;
        }
    }
    if (!messageToSend.empty()){
        network->send(messageToSend);
    }
    memset(network->buffer, 0, sizeof(network->buffer));
}
void Protocol::MenuRun(bool flag) {
    std::string messageToSend ="";
    std::string data = network->receive();
    if (!data.empty()){
        std::cout<<data<<"\n";
    }
    if (flag && disconnected && connectionTries>0){
        messageToSend += CONNECTION_TRY;
        connectionTries--;
    }
    if (disconnected){
        checkTry(data);
    }
    if (!messageToSend.empty()){
        network->send(messageToSend);
    }
    memset(network->buffer, 0, sizeof(network->buffer));
}