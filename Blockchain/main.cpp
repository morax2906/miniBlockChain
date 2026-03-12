#include "blockchain.h"
#include "wallet.h"
#include "p2p.h"
#include <iostream>

int main(int argc, char* argv[]) {
    int myPort = 8080;
    if (argc > 1) {
        myPort = std::atoi(argv[1]);
    }

    std::cout << "--- HỆ THỐNG BLOCKCHAIN P2P ---\n";

    Blockchain myCoin;
    P2PNode node(&myCoin, myPort);
    node.startServer();

    int choice;
    while (true) {
        std::cout << "\n=== MENU (Port " << myPort << ") ===\n";
        std::cout << "1. Xem sổ cái (Số block hiện tại)\n";
        std::cout << "2. Kết nối tới Node khác\n";
        std::cout << "3. Test gửi tin nhắn Broadcast\n";
        std::cout << "0. Thoát\n";
        std::cout << "Chọn: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Số block đang có: "  <<endl;
        }
        else if (choice == 2) {
            std::string ip; int port;
            std::cout << "Nhập IP: "; std::cin >> ip;
            std::cout << "Nhập Port: "; std::cin >> port;
            node.connectToPeer(ip, port);
        }
        else if (choice == 3) {
            std::string msg;
            std::cout << "Nhập tin nhắn: ";
            std::cin.ignore();
            std::getline(std::cin, msg);
            node.broadcast(msg); 
        }
        else if (choice == 0) {
            break;
        }
    }

    return 0;
}