class DisjointSetUnion:
    def __init__(self, size):
        self._parent = list(range(size))
        self._rank = [0] * size

    def find(self, x):
        # if x isn't a root
        if self._parent[x] != x:
            # find a root of its parent recursively
            self._parent[x] = self.find(self._parent[x])  
        return self._parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            if self._rank[rootX] > self._rank[rootY]:
                self._parent[rootY] = rootX
            elif self._rank[rootX] < self._rank[rootY]:
                self._parent[rootX] = rootY
            else:
                self._parent[rootX] = rootY
                self._rank[rootX] += 1

    def areConnected(self, x, y):
        return self.find(x) == self.find(y)
