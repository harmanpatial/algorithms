/*!
 *    \file  maxFlow.cpp
 *   \brief  
 *  
 *  Implementing MaxFlow Algorithms.
 *
 *  1. Augmenting flow.
 *  2. Dinic's shortest path flow.
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
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

typedef long long ll;

typedef struct edge {
    int to; // Neighbouring Vertex
    int reIndex; // Reverse Edge Index
    //int f; // Current Flow
    int residual; // Residual
    int w; // Capacity
    int c; // cost -- unit cost
    
    edge(int vv, int rr, int ww, int cc):to(vv), reIndex(rr), w(ww), c(cc) { residual = w; }
} edgeT;

void addEdge(unordered_map<int, vector<edgeT>> &adjList, int u, int v, int f, int w, int c=0) {
    edgeT edge(v, (adjList.find(v)==adjList.end())?0:adjList[v].size(), w, c);
    edgeT reverseEdge(u, (adjList.find(u)==adjList.end())?0:adjList[u].size(), 0, c);

    adjList[u].push_back(edge);
    adjList[v].push_back(reverseEdge);
}

class Flow {
	vector<vector<edgeT>> &edgeList;
    int s_, t_;    

    ll augmentFlow_(int u, int f) {
	    if(u==t_) return f;
        for(auto &e: edgeList[u]) {
            if(e.residual) {
                int realFlow = augmentFlow_(e.to, min(f, e.residual));
                if(realFlow > 0) { e.residual += realFlow; edgeList[e.to][e.reIndex].residual -= realFlow; return realFlow; }
            }   }
        return 0;
    }

public:
    explicit Flow(vector<vector<edgeT>> &input, int s, int t): edgeList(input), s_(s), t_(t) { }

    int calculate() {
        ll maxFlowValue = 0; ll f;
        while((f=augmentFlow_(s_, 0))) { maxFlowValue += f; }
        return maxFlowValue;
    }
    
    void printGraph() {
        cout << "Edge List : " << endl;
        for(int i=0; i < edgeList.size()+1; i++) {
            for(int j=0; j < edgeList[i].size(); j++)
                cout << "Edge(" << i << ", " << edgeList[i][j].to << " ): " << edgeList[i][j].residual << endl;
        }
    }
};


/*
 * Dinic's Algorithgm
 *
 * Best Time:   00:11:53
 * Latest Time: 00:12:21 -- May 29, 2017
 */
class MaxFlowDinic {
	unordered_map<int, vector<edgeT>> &edgeList;
	vector<vector<edgeT>::iterator> path;
    int s, t;
	vector<int> d;
	
    bool bfs_() {
        fill(d.begin(), d.end(), -1); d[s] = 0;
        queue<int> q; q.push(s);
        while(!q.empty()) {
            int node = q.front(); q.pop();
            for(auto &e: edgeList[node])
                if(d[e.to] < 0 && e.residual) { d[e.to] = d[node]+1;  q.push(e.to); }
        }
        return (d[t]==-1)?false:true;
    }

    ll augmentFlow_(int u, int f=INT_MAX) {
	    if(u==t) return f;
        for(auto &iter = path[u]; iter != edgeList[u].end(); ++iter) {
		    edgeT &e = *iter;
            if(d[e.to] > d[u] && e.residual) {
                int realFlow = augmentFlow_(e.to, min(f, e.residual));
                if(realFlow > 0) { e.residual -= realFlow; edgeList[e.to][e.reIndex].residual += realFlow; return realFlow; }
            }
	    }
        return 0;
    }
	
public:
	explicit MaxFlowDinic(unordered_map<int, vector<edgeT>> &input, int source, int terminal):edgeList(input),s(source),t(terminal),d(input.size()+1),path(input.size()) { }

    ll calculate() {
	    ll maxFlow = 0;
        ll f = 0;
        while(bfs_()) {
            for(int i=0; i < path.size(); i++) path[i] = edgeList[i].begin();
            while((f=augmentFlow_(s))) maxFlow += f;
        }
        return maxFlow;
    }
};

int main(int argc, const char *argv[])
{
    freopen("../sampleGraphs/maxFlow-graph1.txt", "r", stdin);

    if(1) {
        int n,m; cin>>n>>m;

        unordered_map<int, vector<edgeT>> adjList(n);
        
        for(int i=0; i < m; i++) {
            int u, v, w, cost; cin>>u>>v>>w>>cost;
            addEdge(adjList, u, v, 0, w, cost);
        }

        auto_ptr<MaxFlowDinic> instance(new MaxFlowDinic(adjList, 1, n));
        cout << "Max Flow: " << instance->calculate() << endl;
    }
        
	return 0;
}
