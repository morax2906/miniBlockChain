#include "transaction.h"
long long Transaction::get_amount() {
	return amount;
}
string Transaction::get_message() {
	return message;
}
string Transaction::getTo() { return to; }
string Transaction::getFrom() { return from; }
long long Transaction::getAmount() { return amount; }
Transaction::Transaction(string fromAddress, string toAddress, long long amount) {
	this->from = fromAddress;
	this->to = toAddress;
	this->amount = amount;
}
string Transaction::to_string_transaction() {
	string h = from + "->" + to + ":" + to_string(amount) + "|" + message;
	return h;
}
string merkleRoot(vector<Transaction> txs) {

	vector<string> hashes;

	for (auto& tx : txs)
		hashes.push_back(sha256_string(tx.to_string_transaction()));

	while (hashes.size() > 1) {

		vector<string> newHashes;

		for (int i = 0; i < hashes.size(); i += 2) {

			if (i + 1 < hashes.size())
				newHashes.push_back(
					sha256_string(hashes[i] + hashes[i + 1])
				);
			else
				newHashes.push_back(
					sha256_string(hashes[i] + hashes[i])
				);
		}

		hashes = newHashes;
	}

	return hashes[0];
}