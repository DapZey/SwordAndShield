#include <iostream>
#include "Network.h"
#include "Player.h"
#define PORT_1  54000
#define PORT_2 54001
int main() {
    int port = PORT_1;
    Player player;
    Network network;
    network.CreateSocket(player,port);
    std::string s;
    while (s != "quit"){
        network.ReceiveMessageFrom(player);
        std::cin>>s;
        network.SendMessageTo(s, player);
    }
    network.Kill(player);
    network.Shutdown();
    return 0;
}
