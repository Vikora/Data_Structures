#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;

struct Query {
    // type in ('add', 'del', 'find', 'check')
    string type, s;
    size_t ind;
};


class QueryProcessor {
    int bucket_count;
    vector<vector<string>> elems;

    size_t hash_func(const string& s) const {
        int i;
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count)
        : bucket_count(bucket_count)
    {
        elems.resize(bucket_count);
    }


    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }


    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }


    void processQuery(const Query& query) {
        int i;
        if (query.type == "check") {
            // check:
            // print elements of hash table

            vector<string>& c = elems[query.ind];
            // use reverse order, because we append strings to the end
            for (i = c.size()-1; i >= 0; --i)
                cout << c[i] << " ";
            cout << "\n";
        }
        else {
            // compute hash value of string s
            size_t ind = hash_func(query.s);

            vector<string>::iterator it;
            it = std::find(elems[ind].begin(), elems[ind].end(), query.s);
            bool was_founded = it != elems[ind].end();
            
            if (query.type == "find")
                writeSearchResult(was_founded);
            else if (query.type == "add") {
                if (!was_founded)
                    elems[ind].push_back(query.s);
            }
            else if (query.type == "del") {
                if (was_founded)
                    elems[ind].erase(it);
            }
        }
    }


    void processQueries() {
        int n;
        cin >> n; // number of queries
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};


int main() {
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

