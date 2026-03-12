#include "block.h"
#include "transaction.h"
    string Block::calculateHash() {
        string data;

        for (auto& tx : transactions) {
            data += tx.to_string_transaction();
        }

        string input =
            prev_hash +
            data +
            to_string(timestamp) +
            to_string(nonce);

        return sha256_string(input);
    }
    
    Block::Block(string prev_hash, vector<Transaction> nhan) {
        time_xem = time_now();
        timestamp = time(NULL);
        this->prev_hash = prev_hash;
        this->transactions = nhan;
        nonce = 0;
        hash = calculateHash();
    }
    void Block::mineBlock(int diff) {
        string target(diff, '0');
        while (hash.substr(0, diff) != target) {
            nonce++;
            hash = calculateHash();
        }
        cout << "Complete , Hash: " << hash << endl;
    }
    string Block::getHash() { return hash; }
    string Block::getPrevHash() { return prev_hash; }
    string Block::getTime() { return time_xem; }
    long long Block::getTimeStamp() { return timestamp; }
    int Block::getNonce() { return nonce; }
    vector<Transaction> Block::getTransaction() { return  transactions; }
    