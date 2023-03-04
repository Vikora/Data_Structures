"""
Fenwick Tree or Binary Indexed Tree

Usage:
https://leetcode.com/problems/best-team-with-no-conflicts/
"""

class BinaryIndexedTree:
    def __init__(self, size, op=operator.add, init=0):
        self._init = init
        self._op = op
        self._tree = [init] * (size + 1)


    def _parent(self, node):
        return node - (node & -node)


    def running_total(self, hi):
        # log(n)
        # total of [0, hi]
        total = self._init
        while hi > 0:
            total = self._op(total, self._tree[hi])
            hi = self._parent(hi)
        return total


    def update(self, node, value):
        # log(n)
        while node < len(self._tree):
            self._tree[node] = self._op(self._tree[node], value)
            node += node & -node
