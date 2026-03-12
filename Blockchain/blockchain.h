#pragma once

#include "lib.h"
#include "block.h"
#include "transaction.h"
class Blockchain {
private:
    vector<Block> chain;
    int difficulty;
    long long miningReward;
    int maxTxPerBlock;
public:
    vector<Transaction> pendingTransactions;

    Blockchain();

    void addTransaction(Transaction tx);

    void minePendingTransactions(string minerAddress);

    Block getLastBlock();

    void addBlock(Block newBlock);
    long long getBalance(string address);
    int getChainSize() { return chain.size(); }
};
