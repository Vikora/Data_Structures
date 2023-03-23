class DisjointSet:
    def __init__(self, size):
        self._root = list(range(size))
        self._rank = [0] * size

    def find(self, x):
        # if x isn't a root
        if self._root[x] != x:
            # find a root of its parent recursively
            self._root[x] = self.find(self._root[x])  
        return self._root[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            if self._rank[rootX] > self._rank[rootY]:
                self._root[rootY] = rootX
            elif self._rank[rootX] < self._rank[rootY]:
                self._root[rootX] = rootY
            else:
                self._root[rootX] = rootY
                self._rank[rootX] += 1

    def isConnected(self, x, y):
        return self.find(x) == self.find(y)
