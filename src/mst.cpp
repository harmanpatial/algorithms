/*!
 *    \file  mst.cpp
 *   \brief  Implementing Min. Spanning Tree
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
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef long long ll;
#define all(x) x.begin(), x.end()

struct Edge { int to; int weight; };
struct PQ { int from; Edge e; };

bool operator>(const PQ &lhs, const PQ &rhs) { return lhs.e.weight > rhs.e.weight; }

class Prim {
    vector<vector<Edge>> &adjList;
    vi processed;
public:
    Prim(vector<vector<Edge>> &input):adjList(input), processed(input.size(), 0) { }
    
    ll run(vector<pair<int, int>> &tree) {
        priority_queue<PQ, vector<PQ>, greater<PQ>> temp;
        for(auto c: adjList[1]) { PQ q; q.from = 1; q.e = c; temp.push(q); }
        processed[1] = 1;
        ll tc = 0; int i=0; int n = adjList.size();
        

        while(i < n-1 && !temp.empty()) {
            PQ q = temp.top(); temp.pop();
            int from = q.from; int to = q.e.to; int weight = q.e.weight;
            if(processed[to]) continue;
            processed[to] = 1; ++i;
            
            tc += weight; tree.push_back(make_pair(from, to));
            for(auto c: adjList[to]) { if(!processed[c.to]) { PQ q; q.from = to; q.e = c; temp.push(q); } }
        }
        return tc;
    }
};

void splitString(std::string input, char delim, std::vector<string> &elems) {
    elems.clear();
    std::istringstream iss(input);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(elems));
}

void generateGraph(vector<vector<Edge>> &input, string fileName) {
    string line;
    ifstream myfile (fileName);
    vector<string> token;
    
    if (myfile.is_open()) {
        getline(myfile, line); splitString(line, ' ', token);
        int n = stoi(token[0]); input.resize(n+1);
        int nEdges = stoi(token[1]);
        token.clear();

        int from, to;                    
        for(int i=0; i < nEdges; i++) {
            getline(myfile, line); splitString(line, ' ', token);
            from = stoi(token[0]); to = stoi(token[1]); int weight = stoi(token[2]);;
            token.clear();
            struct Edge e; e.to = to; e.weight = weight; struct Edge re; re.to = from; re.weight = weight;
            input[from].push_back(e); input[to].push_back(re);
        }
    }
}


int main(int argc, const char *argv[])
{
    vector<string> sampleTrees = { "../sampleGraphs/graph-1.txt" };
            
    for(auto c: sampleTrees) {
        vector<vector<Edge>> graph;
        vector<pair<int, int>> tree;
        generateGraph(graph, c);
        
        Prim *instance = new Prim(graph);
        instance->run(tree);
        cout << "MST: " << endl;
        for(auto e: tree) cout << e.first << " -- " << e.second << endl;
    }    
}