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
void Protocol::run(bool connectTryFlag) {
    std::string messageToSend ="";
    std::string data = network->receive();
    if (!data.empty()){
        std::cout<<data<<"\n";
    }
    if (connectTryFlag && disconnected){
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