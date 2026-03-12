#pragma once        

#include "lib.h"
class Transaction; // forward declaration
class Block {
private:
    string hash;
    string prev_hash;

    vector<Transaction> transactions;

    string time_xem;
    long long timestamp;
    int nonce;

public:
    string calculateHash();
    Block(string prev_hash, vector<Transaction> nhan);
    void mineBlock(int diff);
    string getHash();
    string getPrevHash();
    string getTime();
    long long getTimeStamp();
    int getNonce();
    vector<Transaction> getTransaction();
};