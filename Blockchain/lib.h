#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <openssl/evp.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <vector>

#include <thread>
#include <mutex>

// Thư viện Socket chuẩn của Linux
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
string time_now();
string sha256_string(const std::string& data);
