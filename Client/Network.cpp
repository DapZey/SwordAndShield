#include "Network.h"

void Network::Init(std::string& ip) {
    startup();
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT_1);
    if (inet_pton(AF_INET, ip.c_str(), &address.sin_addr) != 1) {
        std::cout<<"error connecting\n";
    }
    createSocket();
}

void Network::startup() {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
        if (iResult != 0) {
            std::cerr << "WSAStartup failed: " << iResult << "\n";
        }
}
std::string Network::receive() {
    int bytesReceived = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&address, &addressLength);
    if (bytesReceived == SOCKET_ERROR) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            return "";
        }
    } else {
        return buffer;
    }
    return "";
}
void Network::send(std::string& s) {
    int message = sendto(sock, s.c_str(), static_cast<int>(s.size()) + 1, 0, (sockaddr*)&address, addressLength);
    if (message == SOCKET_ERROR) {
        std::cerr << "sendto() failed: " << WSAGetLastError() << "\n";
    }
}
void Network::createSocket() {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        }
        u_long mode = 1;
        ioctlsocket(sock, FIONBIO, &mode);
        addressLength = sizeof(address);
}
Network::~Network() {
    closesocket(sock);
    WSACleanup();
}