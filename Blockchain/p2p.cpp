#include "p2p.h"

P2PNode::P2PNode(Blockchain* chain, int listenPort) {
    this->myChain = chain;
    this->port = listenPort;
    this->isRunning = false;
    this->serverSocket = INVALID_SOCKET; // Biến báo lỗi của Windows

    // THỦ TỤC BẮT BUỘC TRÊN WINDOWS: Khởi động thư viện mạng Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[LỖI] Khởi động Winsock thất bại!\n";
    }
}

P2PNode::~P2PNode() {
    isRunning = false;
    // Đổi close() thành closesocket()
    if (serverSocket != INVALID_SOCKET) closesocket(serverSocket);
    for (SOCKET sock : peerSockets) closesocket(sock);

    // Tắt thư viện mạng
    WSACleanup();
}

void P2PNode::startServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) return;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "[LỖI] Không thể bind port " << port << "!\n";
        closesocket(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        closesocket(serverSocket);
        return;
    }

    isRunning = true;
    std::cout << "[P2P] Node đang lắng nghe trên port " << port << "...\n";

    std::thread acceptThread(&P2PNode::acceptConnections, this);
    acceptThread.detach();
}

void P2PNode::acceptConnections() {
    while (isRunning) {
        sockaddr_in clientAddr;
        int clientLen = sizeof(clientAddr); // Windows dùng int thay vì socklen_t

        SOCKET newSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);

        if (newSocket != INVALID_SOCKET) {
            std::cout << "\n[P2P] Có Node mới kết nối tới!\n";
            peerSockets.push_back(newSocket);

            std::thread peerThread(&P2PNode::handlePeer, this, newSocket);
            peerThread.detach();
        }
    }
}

void P2PNode::handlePeer(SOCKET peerSocket) {
    char buffer[4096];
    while (isRunning) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(peerSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived <= 0) {
            std::cout << "\n[P2P] Một Node đã ngắt kết nối.\n";
            closesocket(peerSocket);
            break;
        }

        std::string message(buffer);
        std::cout << "\n[P2P NHẬN ĐƯỢC]: " << message << "\n";
    }
}

bool P2PNode::connectToPeer(std::string ip, int port) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "[P2P] Kết nối thất bại tới " << ip << ":" << port << ".\n";
        closesocket(sock);
        return false;
    }

    std::cout << "[P2P] Đã kết nối thành công tới Node " << ip << ":" << port << "\n";
    peerSockets.push_back(sock);

    std::thread peerThread(&P2PNode::handlePeer, this, sock);
    peerThread.detach();
    return true;
}

void P2PNode::broadcast(std::string message) {
    for (SOCKET sock : peerSockets) {
        send(sock, message.c_str(), message.length(), 0);
    }
    std::cout << "[P2P] Đã phát sóng dữ liệu cho " << peerSockets.size() << " nodes.\n";
}