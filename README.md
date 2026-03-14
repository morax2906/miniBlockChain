BlockChain made from C++
# miniBlockChain

[![Ngôn ngữ C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![Kích thước Repo](https://img.shields.io/github/repo-size/morax2906/miniBlockChain?style=for-the-badge)](https://github.com/morax2906/miniBlockChain)
[![Commit mới nhất](https://img.shields.io/github/last-commit/morax2906/miniBlockChain?style=for-the-badge)](https://github.com/morax2906/miniBlockChain/commits/main)

Một dự án mô phỏng mạng lưới Blockchain thu nhỏ được phát triển bằng C++. Mục tiêu của dự án là để minh họa và làm rõ các cơ chế cốt lõi đằng sau công nghệ blockchain, từ việc cấu trúc dữ liệu cơ bản cho đến các thuật toán đồng thuận.

## 🚀 Tính năng cốt lõi

* **Cấu trúc Block:** Khởi tạo và liên kết các khối dữ liệu, bao gồm các thành phần cơ bản như index, timestamp, dữ liệu giao dịch và mã băm của khối trước đó (previous hash).
* **Mã hóa Hashing:** Đảm bảo tính toàn vẹn và bất biến của chuỗi thông qua thuật toán băm mật mã.
* **Cơ chế Đào (Mining):** Mô phỏng quá trình Proof-of-Work (PoW) với độ khó (difficulty) có thể tinh chỉnh để kiểm soát thời gian tạo khối mới.
* **Mô hình Peer-to-Peer (P2P):** Xây dựng nền tảng cơ bản cho việc giao tiếp và đồng bộ sổ cái giữa các node trong mạng.

## 🛠 Yêu cầu hệ thống

Trước khi bắt đầu, hãy đảm bảo hệ thống của bạn đã cài đặt sẵn:
* Trình biên dịch C++ (Hỗ trợ chuẩn C++17 trở lên, ví dụ: GCC, Clang)
* [CMake](https://cmake.org/download/) (Phiên bản 3.10 trở lên)
* (Tùy chọn) Thư viện hỗ trợ mã hóa nếu bạn sử dụng thư viện ngoài cho hàm băm.

## 💻 Hướng dẫn Cài đặt & Sử dụng

**Bước 1: Install OpenSSL**
```bash
choco install openssl
```
**Bước 2: Clone Project**
```bash
git clone https://github.com/morax2906/miniBlockChain.git
cd miniBlockChain
```
**Bước 3: Biên dịch trên CMD** 
```bash
g++ *.cpp -o blockchain_app -lssl -lcrypto
```
**Chạy chương trình **
```bash
blockchain_app.exe
```


## 📁 Cấu trúc thư mục
 ->main.cpp: Điểm khởi đầu của chương trình.

 ->block.cpp/h: Định nghĩa cấu trúc của một khối đơn lẻ.

 ->blockchain.cpp/h: Logic quản lý chuỗi và đào khối.

 ->transaction.cpp/h: Quản lý dữ liệu giao dịch.

 ->wallet.cpp/h: Hệ thống ví và khóa bảo mật.

 ->p2p.cpp/h: Xử lý kết nối mạng giữa các máy (Peer-to-Peer).
