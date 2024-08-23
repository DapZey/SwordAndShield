//
// Created by benra on 7/16/2024.
//

#include "Protocol.h"
#include "MathUtils.h"
#define LEVEL_SWITCH '|'
#define PLAYER_DIR '*'
#define ACTIVE_PLAYER_CORRECTION '~'
#define OTHER_PLAYER_DIRECTION '#'
#define OTHER_PLAYER_POSITION '$'
Protocol::Protocol() {
    network.CreateSocket(players[0],port_1);
    network.CreateSocket(players[1],port_2);
    world.setPlayers(players[0], players[1]);
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
void Protocol::sendCorrection(Player &p, std::string &toSend, std::string &toAdd) {
    if (p.init){
        toSend += toAdd;
    }
}
void Protocol::Run() {
    for (int i = 0; i < PLAYER_COUNT; i++){
        int otherPlayerIndex = (i == 0) ? 1 : 0;
        Player* currentPlayer;
        currentPlayer = &players[i];
        Player* otherPlayer;
        otherPlayer = &players[otherPlayerIndex];
        protocolTime = std::chrono::steady_clock::now();
        int elapsedCorrectionTime = std::chrono::duration_cast<std::chrono::milliseconds>(protocolTime - playerCorrectionTime).count();
        std::string messageToSendCurrent ="";
        std::string messageToSendOther = "";
        if (elapsedCorrectionTime > 1000){
            playerCorrectionTime = protocolTime;
            std::string correctionCurrent = ACTIVE_PLAYER_CORRECTION + std::to_string(currentPlayer->x)+","+std::to_string(currentPlayer->y)+ACTIVE_PLAYER_CORRECTION;
            std::string correctionOther = ACTIVE_PLAYER_CORRECTION + std::to_string(otherPlayer->x)+","+std::to_string(otherPlayer->y)+ACTIVE_PLAYER_CORRECTION;
            sendCorrection(*currentPlayer, messageToSendCurrent, correctionCurrent);
            sendCorrection(*otherPlayer, messageToSendOther, correctionOther);
        }
        std::string data = network.ReceiveMessageFrom(*currentPlayer);
        if (!data.empty()){
//            std::cout<<data<<"\n";
        }
        std::string direction = ParsingUtils::extractSubstringBetweenDelimiters(data, PLAYER_DIR);
        if (!direction.empty()){
            Vector2 dirVec;
            std::vector<std::string> dirSplit = ParsingUtils::splitstringbychar(direction, ",");
            dirVec.x = std::stof(dirSplit[0]);
            dirVec.y = std::stof(dirSplit[1]);
            dirVec = MathUtils::normalize(dirVec);
            currentPlayer->direction = dirVec;
            messageToSendOther+=OTHER_PLAYER_DIRECTION + std::to_string(dirVec.x) + "," + std::to_string(dirVec.y) + OTHER_PLAYER_DIRECTION;
        }
        std::string level = ParsingUtils::extractSubstringBetweenDelimiters(data, LEVEL_SWITCH);
        if (!level.empty()){
            std::cout<<level<<"\n";
            int x = std::stoi(level);
            currentPlayer->levelID = x;
            currentPlayer->spawnPointMapper();
            std::cout<<"player level updated to: "<<currentPlayer->levelID<<"\n";
            std::cout<<currentPlayer->x<<"\n";
            messageToSendOther += LEVEL_SWITCH + level + LEVEL_SWITCH;
        }
        tryConnection(data,*currentPlayer,messageToSendCurrent);
        if (!messageToSendCurrent.empty()){
            network.SendMessageTo(messageToSendCurrent,*currentPlayer);
        }
        if (!messageToSendOther.empty()){
            network.SendMessageTo(messageToSendOther, *otherPlayer);
        }
        memset(currentPlayer->buffer, 0, sizeof(currentPlayer->buffer));
    }
    world.run();
}
