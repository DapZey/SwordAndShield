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
void Protocol::GameRun(bool levelSwitchFlag, int level, int moveFlag, Vector2 dir) {
    std::string messageToSend ="";
    std::string data = network->receive();
    if (levelSwitchFlag){
        std::string x = LEVEL_SWITCH + std::to_string(level) + LEVEL_SWITCH;
        std::cout<<x<<"\n";
        messageToSend += x;
    }
    if (moveFlag){
        std::string x = PLAYER_DIR + std::to_string(dir.x) + "," +std::to_string(dir.y)+ PLAYER_DIR;
        messageToSend += x;
        std::cout<<dir.x<<",";
        std::cout<<dir.y<<"\n";
    }
    if (!data.empty()){
        std::cout<<data<<"\n";
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
    if (flag && disconnected){
        messageToSend += CONNECTION_TRY;
    }
    if (disconnected){
        checkTry(data);
    }
    if (!messageToSend.empty()){
        network->send(messageToSend);
    }
    memset(network->buffer, 0, sizeof(network->buffer));
}