#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size; // amount of elements
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size)
        : size(size), max_table_size(0), sets(size)
    {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
        DisjointSetsElement &node = sets[table];
        if(node.parent != table)
            node.parent = getParent(node.parent);
        return node.parent;
	}

	void merge(int destination, int source) {
        // go through symlinks
		int realDestination = getParent(destination);
        // go through symlinks
		int realSource = getParent(source);

        DisjointSetsElement &realDstNode = sets[realDestination];
        DisjointSetsElement &realSrcNode = sets[realSource];
		if (realDestination != realSource) {
            if(realDstNode.rank > realSrcNode.rank) {
                // attach source node to destination
                realSrcNode.parent = realDestination;
                realDstNode.size += realSrcNode.size;
                realSrcNode.size = 0;
                max_table_size = max(max_table_size, realDstNode.size);
            }
            else {
                // attach destinatione node to source
                realDstNode.parent = realSource;
                realSrcNode.size += realDstNode.size;
                realDstNode.size = 0;
                max_table_size = max(max_table_size, realSrcNode.size);
                if(realSrcNode.rank == realDstNode.rank)
                    realSrcNode.rank += 1;
            }
		}		
	}
};

int main() {
	int n, m;
    // number of tables, number of merge queries to perform
	cin >> n >> m;

    // make n set
	DisjointSets tables(n);
    // for every set 
    for (auto &table : tables.sets) {
		cin >> table.size; // define table size
        // may be update max size of all tables
		tables.max_table_size = max(tables.max_table_size, table.size);
	}
    
	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;

		tables.merge(destination-1, source-1);
	    //for(DisjointSetsElement &table : tables.sets)
        //    cout << table.size << "->" << table.parent << " ";
        //cout << endl;
	    cout << tables.max_table_size << endl;
	}

	return 0;
}
