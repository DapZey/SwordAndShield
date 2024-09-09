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
        if (currentPlayer.portDest == 0){
            currentPlayer.portDest = ntohs(currentPlayer.address.sin_port);
        }
        std::cout<<currentPlayer.portDest<<" port num\n";
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
        memset(currentPlayer->buffer, 0, sizeof(currentPlayer->buffer));
        std::string data = network.ReceiveMessageFrom(*currentPlayer);
        protocolTime = std::chrono::steady_clock::now();
        if (currentPlayer->correctionFlag && currentPlayer->init){
            currentPlayer->playerCorrectionTime = protocolTime;
            std::string correctionCurrent = ACTIVE_PLAYER_CORRECTION + std::to_string(currentPlayer->x)+","+std::to_string(currentPlayer->y)+ACTIVE_PLAYER_CORRECTION
                                            + OTHER_PLAYER_POSITION + std::to_string(otherPlayer->x) + "," + std::to_string(otherPlayer->y)+ OTHER_PLAYER_POSITION;
            currentPlayer->messageToSend += correctionCurrent;
            currentPlayer->correctionFlag = false;
        }
        std::string direction = ParsingUtils::extractSubstringBetweenDelimiters(data, PLAYER_DIR);
        if (!direction.empty()){
            Vector2 dirVec = {0,0};
            std::vector<std::string> dirSplit = ParsingUtils::splitstringbychar(direction, ",");
            dirVec.x = std::stof(dirSplit[0]);
            dirVec.y = std::stof(dirSplit[1]);
            currentPlayer->direction = dirVec;
            currentPlayer->direction = MathUtils::normalize(currentPlayer->direction);
            currentPlayer->inputs = dirVec;
            currentPlayer->correctionFlag = true;
            otherPlayer->directionFlag = true;
        }
        if (currentPlayer->directionFlag && currentPlayer->init){
            std::string dir = OTHER_PLAYER_DIRECTION + std::to_string(otherPlayer->inputs.x) + "," + std::to_string(otherPlayer->inputs.y)+ OTHER_PLAYER_DIRECTION;
            currentPlayer->messageToSend += dir;
            currentPlayer->directionFlag = false;
        }
        std::string level = ParsingUtils::extractSubstringBetweenDelimiters(data, LEVEL_SWITCH);
        if (!level.empty()){
            std::cout<<level<<"\n";
            int x = std::stoi(level);
            currentPlayer->levelID = x;
            currentPlayer->spawnPointMapper();
            currentPlayer->switchFlag = true;
        }
        if (otherPlayer->switchFlag){
            currentPlayer->messageToSend += LEVEL_SWITCH + std::to_string(otherPlayer->levelID) + LEVEL_SWITCH;
            otherPlayer->switchFlag = false;
        }
        tryConnection(data,*currentPlayer,currentPlayer->messageToSend);
        if (!currentPlayer->messageToSend.empty()){
            network.SendMessageTo(currentPlayer->messageToSend,*currentPlayer, *otherPlayer);
            currentPlayer->messageToSend="";
        }
    }
    world.run();
}
