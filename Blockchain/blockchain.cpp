#include "lib.h"
#include "blockchain.h"
void Blockchain::addTransaction(Transaction tx) {
    pendingTransactions.push_back(tx);
}
void Blockchain::minePendingTransactions(string minerAddress) {

    vector<Transaction> blockTx;

    int count = min(maxTxPerBlock, (int)pendingTransactions.size());

    for (int i = 0; i < count; i++) {
        blockTx.push_back(pendingTransactions[i]);
    }

    Block block(getLastBlock().getHash(), blockTx);

    block.mineBlock(difficulty);

    chain.push_back(block);

    pendingTransactions.erase(
        pendingTransactions.begin(),
        pendingTransactions.begin() + count
    );

    pendingTransactions.push_back(
        Transaction("SYSTEM", minerAddress, miningReward)
    );
}
Block Blockchain::getLastBlock() {
    return chain.back();
}
void Blockchain::addBlock(Block newBlock) {
    chain.push_back(newBlock);
}
Blockchain::Blockchain() {
    difficulty = 3;
    miningReward = 500;
    maxTxPerBlock = 10;

    // TẠO GENESIS BLOCK NGAY LÚC KHỞI TẠO
    vector<Transaction> emptyTxs;
    Block genesis("0000000000000000000000000000000000000000000000000000000000000000", emptyTxs);
    chain.push_back(genesis);
}

long long Blockchain::getBalance(string address) {
    long long balance = 0;
    for (auto& block : chain) {
        for (auto& tx : block.getTransaction()) {
            if (tx.getFrom() == address)
                balance -= tx.getAmount(); // Đảo dấu: Gửi đi thì trừ tiền

            if (tx.getTo() == address)
                balance += tx.getAmount(); // Đảo dấu: Nhận về thì cộng tiền
        }
    }
    return balance;
}