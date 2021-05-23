# Data_Structures
EDU. Set of small programs implementing common data structures

## Phone book
An imitation of simple phone book manager. Use custom crude hash table.

Hash table maps integers to strings.

    h(x) = a*x + b mod p mod m
    p = 100 000 007 prime number

Supports the following types of user’s queries:

* `add number name`
* `del number`
* `find number`
