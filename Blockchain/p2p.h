#pragma once
#include "blockchain.h"
#include "lib.h"
// Thư viện Socket chuẩn của Windows (Winsock2)
#include <winsock2.h>
#include <ws2tcpip.h>

// Ép Visual Studio tự động link thư viện mạng (Nếu dùng MinGW/GCC thì xem lưu ý bên dưới)
#pragma comment(lib, "ws2_32.lib") 

class P2PNode {
private:
    Blockchain* myChain;
    SOCKET serverSocket;             // Đổi int thành SOCKET
    std::vector<SOCKET> peerSockets; // Đổi int thành SOCKET
    int port;
    bool isRunning;

    void acceptConnections();
    void handlePeer(SOCKET peerSocket);

public:
    P2PNode(Blockchain* chain, int listenPort);
    ~P2PNode();

    void startServer();
    bool connectToPeer(std::string ip, int port);
    void broadcast(std::string message);
};