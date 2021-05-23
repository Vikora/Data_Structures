#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::pair;
using std::cin;
using std::cout;


struct Query {
    string type, name;
    int number;
};


class HashFunction {
    // h(x) = a*x + b mod p mod m
    int prime, size, a, b;

public:
    explicit HashFunction(int m, int p=1000000007)
        :prime(p), size(m), a(3), b(1)
    {}

    int get(long long x) {
        return (a*x + b) % prime % size;
    }
};



class HashTable {
    vector<vector< pair<int, string> >> hash_tab;
    HashFunction h;     

    int get_index(vector<pair<int, string>>& c, int n) {
        // return index on element n in chain c
        // -1 if element is not in c
        int res = -1;
        for(int j = 0; j < c.size(); ++j)
            if(c[j].first == n) {
                res = j;
                break;
            }
        return res;
    }

public:
    HashTable(int size):
        hash_tab(size), h(size)
    {}

    void add(int id, string s) {
        int key, pos;
        key = h.get(id);

        // try to find id in hash table
        vector<pair<int, string>>& chain = hash_tab[key];
        pos = get_index(chain, id);
        if (pos == -1)
            chain.push_back(std::make_pair(id, s));
        else
            chain[pos].second = s;
    }

    string find(int id) {
        int key, pos;
        key = h.get(id);
        
        // try to find id in hash table
        vector<pair<int, string>>& chain = hash_tab[key];
        pos = get_index(chain, id);

        if (pos == -1)
            return "not found";
        else
            return chain[pos].second;
    }

    void del(int id) {
        int key, pos;
        key = h.get(id);
        
        // try to find id in hash table
        vector<pair<int, string>>& chain = hash_tab[key];
        pos = get_index(chain, id);

        if (pos >= 0)
            chain.erase(chain.begin() + pos);
    }
};



void process_queries() {
    int i, j, n, number, hashvalue;
    string type, name;

    // read amount of queries 
    cin >> n;

    // create hash table
    HashTable phone_dict(n);

    // read input - n queries
    for(i = 0; i < n; ++i) {
        cin >> type >> number;
        //cout << type << " " << number << "\n";
        if(type == "add") {
            cin >> name;
            phone_dict.add(number, name);
        }
        else if(type == "find") {
            name = phone_dict.find(number);
            cout << name << "\n";
        }
        else if(j >= 0) // type == "del"
            phone_dict.del(number);
    }
    return;
}

int main() {
    process_queries();
    return 0;
}
