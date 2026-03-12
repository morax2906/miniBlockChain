#pragma once
#include "lib.h"
class Transaction {
private:
    string to;
    string from;
    long long amount;
    string message;
public:
    long long get_amount();
    string get_message();
    string getTo();
    string getFrom();
    long long getAmount();
    Transaction(string fromAddress, string toAddress, long long amount);
    string to_string_transaction();
};

