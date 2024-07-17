//
// Created by benra on 7/16/2024.
//

#include "Protocol.h"
Protocol::Protocol() {
    network.CreateSocket(players[0],port_1);
    network.CreateSocket(players[1],port_2);
}
Protocol::~Protocol(){
    network.Kill(players[0]);
    network.Kill(players[1]);
    network.Shutdown();
}
void Protocol::tryConnection(std::string& data,Player& currentPlayer, std::string& messageToSendCurrent) {
    if (ParsingUtils::containsChar(data, CONNECTION_TRY)){
        if (!currentPlayer.establishConnection()){
            messageToSendCurrent+=CONNECTION_FAIL;
        }
        else {
            messageToSendCurrent+=CONNECTION_SUCCEED;
        }
    }
}
void Protocol::Run() {
    for (int i = 0; i < PLAYER_COUNT; i++){
        int otherPlayerIndex = (i == 0) ? 1 : 0;
        Player* currentPlayer;
        currentPlayer = &players[i];
        Player* otherPlayer;
        otherPlayer = &players[otherPlayerIndex];
        std::string messageToSendCurrent ="";
        std::string data = network.ReceiveMessageFrom(*currentPlayer);
        if (!data.empty()){
            std::cout<<data<<"\n";
        }
        tryConnection(data,*currentPlayer,messageToSendCurrent);
        if (!messageToSendCurrent.empty()){
            network.SendMessageTo(messageToSendCurrent,*currentPlayer);
        }
        memset(currentPlayer->buffer, 0, sizeof(currentPlayer->buffer));
    }
}