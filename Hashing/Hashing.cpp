// C++ translation of the provided Python open-addressing hash table.
// Features:
// - HashTable class with dynamic resizing (rehash to next prime)
// - put, get, Update, remove (delete) operations
// - collision path tracing via a passed vector<vector<int>> &collision_path
// - simple demo in main()

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>    

using namespace std;

static bool is_prime(int n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0) return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0) return false;

	return true;
}

static int find_next_prime(int size) {
	if (size < 2) return 2;

	for (int i = size + 1; i < 2 * max(2, size); ++i) {
		if (is_prime(i)) return i;
	}

	// Fallback: search further if nothing found in range
	int i = max(size + 1, 2);
	while (!is_prime(i)) ++i;

	return i;
}

class HashTable {
public:
	vector<string> keys; // "" => empty, "#" => tombstone (deleted)
	vector<unordered_map<string, string>> values;
	int size;

	explicit HashTable(int initial_size = 7) {
		int s = max(7, initial_size);
		size = find_next_prime(s);
		keys.assign(size, "");
		values.assign(size, unordered_map<string, string>());
	}

	double loadFactor() const {
		int count = 0;
		for (const auto &k : keys)
			if (k != "" && k != "#") ++count;
			
		return (double)count / (double)size;
	}

	int hash_function(const string &key) const {
		long long val = 0;
		for (unsigned char c : key) val += c;
		val = val >> 4; // match python's behavior
		int idx = (int)(val % size);
		if (idx < 0) idx = -idx;
		
		return idx;
	}

	int collision_resolver(const string &key, int oldAddress) const {
		long long offset = 0;
		for (unsigned char c : key) offset += c;
		if (size != 0) offset = offset / size;
		int address = (oldAddress + (int)(offset % size)) % size;
		return address;

        // Linear probing
        // return (oldAddress + 1) % size;

        // quadratic probing
        // static int i = 1;
        // int address = (oldAddress + i * i) % size;
        // i++;
        // return address;


	}

	void resize_hashtable(bool increase) {
		int newSize = increase ? size * 2 : max(1, size / 2);
		newSize = find_next_prime(newSize);
		if (!increase && newSize < 7) newSize = 7;

		vector<string> oldKeys = keys;
		vector<unordered_map<string, string>> oldValues = values;

		keys.assign(newSize, "");
		values.assign(newSize, unordered_map<string, string>());
		int oldSize = size;
		size = newSize;

		for (int i = 0; i < (int)oldKeys.size(); ++i) {
			if (oldKeys[i] != "" && oldKeys[i] != "#") {
				const string key = oldKeys[i];
				const auto val = oldValues[i];
				int index = hash_function(key);
				if (keys[index] == "" || keys[index] == "#") {
					keys[index] = key;
					values[index] = val;
				} else {
					while (!(keys[index] == "" || keys[index] == "#")) {
						index = collision_resolver(key, index);
					}

					keys[index] = key;
					values[index] = val;
				}
			}
		}
	}

	void put(const string &key, const unordered_map<string, string> &data) {
		if (loadFactor() > 0.75) resize_hashtable(true);
		int index = hash_function(key);
		if (keys[index] == "" || keys[index] == "#") {
			keys[index] = key;
			values[index] = data;
			return;
		}

		while (!(keys[index] == "" || keys[index] == "#")) {
			index = collision_resolver(key, index);
		}

		keys[index] = key;
		values[index] = data;
	}

	// returns pointer to stored map or nullptr if not found
	unordered_map<string, string> *get(const string &key, vector<vector<int>> &collision_path, int opNumber) {
		if (opNumber >= (int)collision_path.size()) collision_path.resize(opNumber + 1);
		collision_path[opNumber].clear();

		int index = hash_function(key);
		collision_path[opNumber].push_back(index);
		if (keys[index] == key) return &values[index];

		index = collision_resolver(key, index);
		collision_path[opNumber].push_back(index);

		while (keys[index] != "" && keys[index] != "#") {
			if (keys[index] == key) return &values[index];
			index = collision_resolver(key, index);
			collision_path[opNumber].push_back(index);
		}

		return nullptr;
	}

	void Update(const string &key, const string &columnName, const string &data, vector<vector<int>> &collision_path, int opNumber) {
		if (opNumber >= (int)collision_path.size()) collision_path.resize(opNumber + 1);
		collision_path[opNumber].clear();

		int index = hash_function(key);
		collision_path[opNumber].push_back(index);
		if (keys[index] == key) {
			values[index][columnName] = data;
			cout << "record Updated" << endl;
			return;
		}

		while (keys[index] != "" && keys[index] != "#") {
			index = collision_resolver(key, index);
			collision_path[opNumber].push_back(index);
			if (keys[index] == key) {
				values[index][columnName] = data;
				cout << "record Updated" << endl;
				return;
			}
		}
		
		cout << "record not found" << endl;
	}

	void remove(const string &key, vector<vector<int>> &collision_path, int opNumber) {
		double val = loadFactor();
		if (val < 0.3 && size > 7) resize_hashtable(false);

		if (opNumber >= (int)collision_path.size()) collision_path.resize(opNumber + 1);
		collision_path[opNumber].clear();

		int index = hash_function(key);
		collision_path[opNumber].push_back(index);
		if (keys[index] == key) {
			keys[index] = "#";
			values[index].clear();
			cout << "Item Deleted" << endl;
			return;
		}
		while (keys[index] != "" && keys[index] != "#") {
			index = collision_resolver(key, index);
			collision_path[opNumber].push_back(index);
			if (keys[index] == key) {
				keys[index] = "#";
				values[index].clear();
				cout << "Item Deleted" << endl;
				return;
			}
		}
		cout << "Item not found" << endl;
	}
};

// Small demonstration
int main() {
	// Create a hash table with initial size 7
	HashTable ht(7);
	vector<vector<int>> collision_path;

	unordered_map<string, string> alice;
	alice["name"] = "Alice";
	alice["age"] = "30";

	unordered_map<string, string> bob;
	bob["name"] = "Bob";
	bob["age"] = "25";

	ht.put("alice_key", alice);
	ht.put("bob_key", bob);

	// Get Alice
	auto *res = ht.get("alice_key", collision_path, 0);
	if (res) {
		cout << "Found alice: name=" << (*res)["name"] << ", age=" << (*res)["age"] << endl;
	} else {
		cout << "Item not found" << endl;
	}

	// Update Bob's age
	ht.Update("bob_key", "age", "26", collision_path, 1);
	auto *r2 = ht.get("bob_key", collision_path, 2);
	if (r2) cout << "Bob after update: age=" << (*r2)["age"] << endl;

	// Delete Alice
	ht.remove("alice_key", collision_path, 3);
	auto *r3 = ht.get("alice_key", collision_path, 4);
	if (!r3) cout << "alice_key not found after deletion" << endl;

	// Print collision paths recorded
	for (int i = 0; i < (int)collision_path.size(); ++i) {
		cout << "op " << i << " path: ";
		for (int idx : collision_path[i]) cout << idx << " ";
		cout << endl;
	}

	return 0;
}
