/*!
 *    \file  HLD.cpp
 *   \brief  Perform a HLD
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
 * Heavy Light Decompositiion 
 *
 * https://blog.anudeep2011.com/heavy-light-decomposition/
 *
 * Best Time:   00:08:38
 * Latest Time: 00:08:38 -- May 17, 2017
 */
class HLD {
    vvi tree;
    vi sz;

    vi p, d, hc, rn; // parent, depth, heavy-child, root-node-of-chain

    int calSize_(int V=1, int P=-1) {
        for(auto &c: tree[V]) {
            if(c!=P) sz[V] += calSize_(c, V);
        }
        return sz[V];
    }

    void decompose_(int V=1, int P=-1, int rootNode=1) {
        p[V] = P;
        rn[V] = rootNode;
        if(P!=-1) {d[V] = d[P] + 1; }

        int sc=-1, scSize = INT_MIN;
        for(auto &c: tree[V]) {
            if(c!=P && sz[c] > scSize) { sc = c; scSize = sz[c]; }
        }
        if(sc==-1) return;

        hc[V] = sc;
        decompose_(sc, V, rootNode);

        for(auto &c: tree[V]) {
            if(c!=P && c!=sc) decompose_(c, V, c);
        }
    }

public:
    explicit HLD(vvi &input):tree(input), sz(input.size(), 1), p(input.size(), -1), d(input.size(), 1), hc(input.size(), -1), rn(input.size(), -1) {
        calSize_(); decompose_();
    }

    int lca(int u, int v) {
        for( ; rn[u]!=rn[v]; v = p[rn[v]]) { if(d[rn[u]]>d[rn[v]]) swap(u, v); }
        return d[u]<d[v]?u:v;
    }
    
    void findPath(int u, int v, vi &path) {
        int l = lca(u, v);
        int distance = (d[u]-d[l]) + (d[v]-d[l]) + 1;
        path.resize(distance, 0);
        int index = 0;
        while(u!=l) { path[index++] = u; u = p[u]; }
        index = distance-1;
        while(v!=l) { path[index--] = v; v = p[v]; }
        path[index] = l;
    }
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
    vector<string> sampleTrees = { "../sampleTrees/tree-1.txt", "../sampleTrees/tree-2.txt",  "../sampleTrees/tree-3.txt",  "../sampleTrees/tree-4.txt" };
    vector<pair<int, int>> lcaSearch = { {1, 5}, {3, 5}, {1, 10}, {6, 10}};
    int i=1;
    for(auto &s: sampleTrees) {
        cout << "Tree: " << i++ << endl;
        vvi inputTree;
        generateTree(inputTree, s);

        HLD *instance = new HLD(inputTree);
        for(auto &e: lcaSearch) {
            vi path;
            cout << "LCA of " << e.first << " and " << e.second << ": " << instance->lca(e.first, e.second) << " ----- ";
            instance->findPath(e.first, e.second, path);
            cout << "Path: "; for_each(path.begin(), path.end(), [](const int &n) { cout << n << " ";}); cout << endl;
        }
    }
    return 0;
}