//
// Created by benra on 7/16/2024.
//

#include "Network.h"
void Network::SendMessageTo(const std::string& s, Player& p, Player& o) {
    if (p.init && o.init){
        p.address.sin_port = htons(p.portDest);
    }
    std::cout << "Attempting to send message to player " << p.id << std::endl;
    std::cout << "  Message: " << s << std::endl;
    std::cout << "  Destination IP: " << inet_ntoa(p.address.sin_addr) << std::endl;
    std::cout << "  Destination Port: " << ntohs(p.address.sin_port) << std::endl;
    std::cout << "  Other Port: " << ntohs(o.address.sin_port) << std::endl;
    int message = sendto(p.socket, s.c_str(), static_cast<int>(s.size()), 0, (sockaddr*)&p.address, p.addressLength);
    if (message == SOCKET_ERROR) {
        std::cerr << "sendto() failed: " << WSAGetLastError() << " for player " << p.id << std::endl;
    } else {
        std::cout << "Successfully sent " << message << " bytes to player " << p.id << std::endl;
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

std::string Network::ReceiveMessageFrom(Player &p) {
    char buffer[BUFFER_SIZE];
    int bytesReceived = recvfrom(p.socket, buffer, BUFFER_SIZE, 0, (sockaddr*)&p.address, &p.addressLength);
    if (bytesReceived == SOCKET_ERROR) {
//        std::cerr << "recvfrom() failed: " << WSAGetLastError() << " for player " << p.id << std::endl;
        return "";
    } else {
        std::string received(buffer, bytesReceived);
        std::cout << "Received " << bytesReceived << " bytes from player " << p.id
                  << " (Port: " << ntohs(p.address.sin_port) << "): " << received << std::endl;
        return received;
    }
}
