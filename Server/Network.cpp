//
// Created by benra on 7/16/2024.
//

#include "Network.h"
std::string Network::ReceiveMessageFrom(Player& p) {
    int bytes = recvfrom(p.socket, p.buffer, sizeof(p.buffer), 0, (sockaddr*)&p.address, &p.addressLength);
    if (bytes == SOCKET_ERROR) {
        std::cout<<"error receiving"<<WSAGetLastError()<<"\n";
    }
    return p.buffer;
}
void Network::SendMessageTo(const std::string& s, Player& p) {
    int message = sendto(p.socket, s.c_str(), static_cast<int>(s.size()) + 1, 0, (sockaddr*)&p.address, p.addressLength);
    if (message == SOCKET_ERROR) {
        std::cerr << "sendto() failed: " << WSAGetLastError() << "\n";
    }
}
Network::Network() {
    this->Startup();
}
void Network::Startup() {
    iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << "\n";
    }
}
void Network::Kill(Player& p) {
    closesocket(p.socket);
}
void Network::Shutdown(){
    WSACleanup();
}
void Network::CreateSocket(Player& player, const int& port) {
    player.socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (player.socket == INVALID_SOCKET) {
        std::cout<<"error creating socket\n"<<WSAGetLastError();
    }

    if (!SetNonBlocking(player.socket) || !BindSocketToPort(player, port)) {
        closesocket(player.socket);
        std::cout<<"error binding or not blocking\n";
    }
}
bool Network::SetNonBlocking(SOCKET& sock) {
    u_long mode = 1;
    if (ioctlsocket(sock, FIONBIO, &mode) == SOCKET_ERROR) {
        std::cout<<"error making socket non-blocking\n";
        return false;
    }
    return true;
}
bool Network::BindSocketToPort(Player& p, const int& port) {
    p.address.sin_family = AF_INET;
    p.address.sin_addr.s_addr = INADDR_ANY;
    p.address.sin_port = htons(port);
    if (bind(p.socket, reinterpret_cast<sockaddr*>(&p.address), sizeof(p.address)) == SOCKET_ERROR) {
        std::cout<<"bind failed\n"<<WSAGetLastError();
        return false;
    }
    return true;
}
