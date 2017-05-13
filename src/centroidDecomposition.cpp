/*!
 *    \file  centroidTree.cpp
 *   \brief  Doing a Centroid Decomposition
 *  
 *  <+DETAILED+>
 *  
 *  \author  Harman Patial, harman.patial@gmail.com
 *  
 *  \internal
 *      Compiler:  g++
 *     Copyright:  
 *  
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <random>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <chrono>
#include <math.h>
#include <unistd.h>
#include <iterator>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<string> vs;

/* 
 * Centroid Decomposition
 *
 * https://threads-iiith.quora.com/Centroid-Decomposition-of-a-Tree
 *
 * Theorem (Jordan, 1869) : Given a tree with N nodes,  there  exists a vertex whose
 * removal partitions the tree into components, each with at most N/2 nodes.
 * (i.e. For any given tree, the centroid always exists)
 *
 * Best Time:   00:08:04
 * Latest Time: 00:08:04 -- May 12, 2017
 */
class CentroidTree {
    vector<vector<int>> &originalTree;
    vector<int> sz;
    
    vector<vector<int>> ct;
    vector<int> parent;
    vector<int> depth;
    vector<int> processed;
    int rootIndex;
   
    int findSize(int v=1, int p=-1) {
        for(auto &c: originalTree[v]) {
            if(c!=p) { sz[v] += findSize(c, v); }
        }
        return sz[v];
    }
 
    void _decompose(int v=1, int p=-1) {
        if(processed[v]) return;

        for(auto &c: originalTree[v]) {
            if(!processed[c] && (sz[c] > sz[v]/2)) {
                    sz[v] -= sz[c]; sz[c] += sz[v];
                    return _decompose(c, p);
            }
        }

        processed[v] = 1;

        if(p==-1) { rootIndex = v; }
        else { ct[p].push_back(v); ct[v].push_back(p); depth[v] = depth[p] + 1; }
        parent[v] = p;

        for(auto &c: originalTree[v]) {
            if(!processed[c]) _decompose(c, v);
        }
    }

    void _printEdgeList(int v, int p=-1) {
        for(auto &c: ct[v]) {
            if(c != p) { cout << "Centroid Tree -- Edge: " << v << " -- " << c << endl; _printEdgeList(c, v); }
        }
    }
    
public:
    explicit CentroidTree(vector<vector<int>> &input):originalTree(input), sz(input.size(), 1), parent(input.size(), 0), processed(input.size(), 0), depth(input.size(), 1),ct(input.size()), rootIndex(-1)
    {
            findSize(); _decompose();
    }

    int lca(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);
        while(depth[u] != depth[v]) u = parent[u];
        while(u != v) { u = parent[u]; v = parent[v]; }
        return u;
    }

    int maxLevel() {
        return *max_element(depth.begin()+1, depth.end());
    }
    
    void printEdgeList() { cout << "Rootnode is: " << rootIndex << endl; _printEdgeList(rootIndex);}
};

void splitString(std::string input, char delim, std::vector<string> &elems) {
    elems.clear();
    
    std::istringstream iss(input);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(elems));
}

void generateTree(vvi &tree, string &fileName) {
    string line;
    ifstream myfile (fileName);

    vector<string> token;
    
    if (myfile.is_open())
    {
        // First Line
        getline(myfile, line);
        int n = stoi(line);
        int nEdges = n+1;
        token.clear();

        tree.resize(n+1, vector<int> ());
        int counter = 0;
        int from, to;
                    
        for(int i=0; i < nEdges; i++) {
            getline(myfile, line); splitString(line, ' ', token);
            from = stoi(token[0]); to = stoi(token[1]);
            token.clear();
            tree[from].push_back(to); tree[to].push_back(from);
        }
    }
}


int main(int argc, const char *argv[])
{
    vector<string> sampleTrees = { "../sampleTrees/tree-1.txt",  "../sampleTrees/tree-2.txt",  "../sampleTrees/tree-3.txt",  "../sampleTrees/tree-4.txt" };
    vector<pair<int, int>> lcaSearch = { {1, 5}, {3, 5}, {1, 10}, {6, 10}};
    int i=1;
    for(auto &s: sampleTrees) {
        cout << "Tree: " << i++ << endl;
        vvi inputTree;
        generateTree(inputTree, s);

        CentroidTree *instance = new CentroidTree(inputTree);        
        for(auto &e: lcaSearch)
            cout << "LCA of " << e.first << " and " << e.second << ": " << instance->lca(e.first, e.second) << endl;
    }
}