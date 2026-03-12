#pragma once
#include "lib.h"

class Wallet {
public:
    Wallet();
    int money_in_wallet;
    string getAddress();
    string getPublicKeyPEM();
    string getPrivateKeyPEM();
    string sign(const string& message);

private:
    string address;
    string publicKeyPEM;
    string privateKeyPEM;
};