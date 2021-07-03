#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long bigint;


struct Data {
    string pattern, text;
};


class PolyHash {
    size_t multiplier;
    size_t prime;

public:
    explicit PolyHash(size_t p, size_t m)
        : prime(p), multiplier(m)
    {}

    bigint Hash(const string &s) {
        bigint hash = 0;
        for (int i = s.size() - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash;
    }
};


Data* read_input() {
    Data *data = new Data;
    std::cin >> data->pattern >> data->text;
    return data;
}


void print_occurrences(const std::vector<int>& output) {
    for (int i = output.size() - 1; i >= 0; --i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}


bigint power(bigint x, bigint n, bigint p) {
    // return x^n mod m
    bigint res = 1;
    for (bigint i = 0; i < n; ++i)
        res = res * x % p;
    return res;
}


std::vector<int> get_occurrences(const Data *input) {
    int i;
    static const bigint x = 71; //263;
    static const bigint prime = 10'000'007;
    const string& s = input->pattern, t = input->text;
    std::vector<int> ans;
    PolyHash polyHash(prime, x);
    unsigned int lp = s.size(); // length of pattern

    // compute hash for the pattern s
    bigint pattern_hash = polyHash.Hash(s);
    // compute hash for the most right substring of length lp in t
    bigint cur_hash, fwd_hash = polyHash.Hash(t.substr(t.size() - lp, lp));

    // compare the most right substring and pattern
    if(fwd_hash == pattern_hash)
        if (t.substr(t.size() - lp, lp) == s)
            ans.push_back(t.size() - lp);

    // x^lp mod prime
    bigint x_pow_lp = power(x, lp, prime);

    // start from t.size()-1 downto 0
    for (i = t.size() - 1 - lp; i >= 0; --i) {
        // Rabin-Karp's algorithm
        // use previous hash value to compute current:
        // H[i] = x*H[i+1] + S[i] - x^lp * S[i+lp]
        cur_hash = x*fwd_hash % prime;
        cur_hash = (cur_hash + prime - x_pow_lp*t[i+lp] % prime) % prime;
        cur_hash = (cur_hash + t[i]) % prime;
        
        fwd_hash = cur_hash;
        
        //std::cout << cur_hash << ' ' << pattern_hash << '\n';
        if(cur_hash == pattern_hash)
            if (t.substr(i, lp) == s)
                ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);

    // read the pattern and the text 
    Data *d = read_input();

    print_occurrences(get_occurrences(d));
    return 0;
}

