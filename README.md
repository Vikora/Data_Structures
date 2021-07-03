# Data_Structures
EDU. Set of small programs implementing common data structures

## Phone book
An imitation of a simple phone book manager. Use custom crude hash table.

Hash table maps integers to strings.

    h(x) = (a*x + b) mod p mod m,
    
where `p = 100 000 007` is a prime number, `m` is a size of a hash table.

Supports the following types of user’s queries:

* `add number name`
* `del number`
* `find number`

## Hashing with chains
Given the number of buckets and the hash function. It is a polynomial hash function

    h(S) = sum from i=0 to |S|-1 { S[i]*x^i mod p mod m },

where `S[i]` is the ASCII code of the i-th symbol of S, `p = 1e9+7` and `x  = 263`.

Supports the following kinds of queries:

* `add string` — insert string into the table. If there is already such string in the hash table, then
just ignore the query.
*  `del string` — remove string from the table. If there is no such string in the hash table, then
just ignore the query.
* `find string` — output “yes" or “no".
* `check`  — output the content of the i-th list in the table.

## Find pattern in text (Rabin-Karp's algorithm)

Implementation of the Rabin–Karp’s algorithm for searching the given pattern in the given text.

Given a string S. Let's say that `H(i, p)` is a hash of a substring `S[i-p]..S[i]`.

Hence `H(i, i)` is a hash of `S[0]..S[i]` and

    H(i, i) = S[0] + S[1]*x + S[2]*x^2 + ... S[i]*x^i (mod prime)
    H(i, p) = x*H(i+1, p) - x^p * S[i+p] + S[i] (mod prime)

## Substring equality

An algorithm that is able to preprocess a given string
to answer any query of the form "are these two substrings of `s` equal?" efficiently.


