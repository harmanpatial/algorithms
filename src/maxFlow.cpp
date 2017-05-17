/*!
 *    \file  factoryClass.cpp
 *   \brief  
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
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
#define all(x) x.begin(), x.end()

typedef struct edge {
    int to; // Neighbouring Vertex
    int reIndex; // Reverse Edge Index
    //int f; // Current Flow
    int residual; // Residual
    int w; // Capacity
    int c; // cost -- unit cost
    
    edge(int vv, int rr, int ww, int cc):v(vv), r(rr), w(ww), c(cc) { residual = w; }
} edgeT;


#define MAX_V 10001

class Flow {
    vector<edgeT> adjList[MAX_V];
    int nVertices;
    int maxFlowValue;
    int currentFlow;

    bool findPath_(int s, int t, vi &visited, vector<vector<edgeT>::iterator> &path) {
        if(s == t) return true;
        for(vector<edgeT>::iterator iter = adjList[s].begin(); iter != adjList[s].end(); i++) {
            auto &e = *iter;
            if(e.residual) { // Has Residual Left
                if(visited[e.to]) continue;
                visited[e.to] = 1;
                path.push_back(iter);
                currentFlow = 
                if(findPath(neighbor, t, visited, path)) return true;
                path.pop_back();
            }
        }
        return false;
    }

    void augmentFlow(int s, vector<vector<edgeT>::iterator> &path) {
        int minResidual = INT_MAX;

        for(int i=0; i < path.size(); i++)
            minResidual = min(minResidual, path[i]->residual);
    
        cout << "Residual: " << minResidual << " :: Path: " << s << " ";
        for_each(all(path), [](edgeT *n) { cout << n->v << " "; });
        cout << endl;

        maxFlowValue += minResidual;
    
        for(int i=0; i < path.size(); i++) {
            edgeT *currEdge = path[i];
            currEdge->residual -= minResidual;
            adjList[currEdge->v][currEdge->r].residual += minResidual;

        }
    }

public:

    explicit Flow(int vertices): nVertices(vertices), flowValue(0) {}

    void addEdge(int u, int v, int f, int w, int c=0) {
        edgeT edge(v, adjList[v].size(), w, c);
        edgeT reverseEdge(u, adjList[u].size(), 0, c);

        adjList[u].push_back(edge);
        adjList[v].push_back(reverseEdge);
    }
    
    int genericAugmentPathFlow(int s, int t) {
        maxFlowValue = 0;
        vector<edge *> path;
        cout << "calculation Flow." << endl;
        vi visited(nVertices+1, 0); visited[s] = 1;
        while(findPath_(s, t, visited, path)) {
            augmentFlow(s, path);
            fill(all(visited), 0);
            path.clear();
            visited[s] = 1;
        }
        return maxFlowValue;
    }
    
    void printGraph() {
        cout << "Edge List : " << endl;
        for(int i=0; i < nVertices+1; i++) {
            for(int j=0; j < adjList[i].size(); j++)
                cout << "Edge(" << i << ", " << adjList[i][j].v << " ): " << adjList[i][j].residual << endl;
        }
    }
};

class MaxFlowDinic {
	vector<vector<EdgeT>> &edgeList;
	vector<vector<EdgeT>::iterator> path;
	int currFlowValue;
	int n;
	vi d;
	
    void bfs_(int s) {
        fill(d.begin(), d.end(), -1); d[s] = 0;
        queue<int> temp; temp.push(s);
        while(!temp.empty()) {
            int node = temp.top(); temp.pop();
            for(auto &e: edgeList[node])
                if(d[e.to] < 0 && e.ca > e.f) { d[e.to] = d[node]+1;  temp.push(e.to); }
        }
    }

    void augmentFlow_() {
	    for(auto &ei: path) {
		    EdgeT &e = *ei;
            e.f += currFlowValue; edgeList[e.v][e.reIndex].f -= currFlowValue;
	    }
    }

    bool findPath_(int s, int t) {
	    if(s==t) { augment_(s, t); return true; }
        for(vector<EdgeT>::iterator iter = edgeList[node].begin(); iter != edgeList[node].end(); ++iter) {
		    auto &e = *iter;
            if(d[e.to] > s && e.ca > e.f) {
                path.push_back(iter); currFlowValue = min(currFlowValue, e.ca-e.f);
                if(findPath_(e.to, t)) return true;
            }
	    }
        return false;
    }
	
public:
	explicit MaxFlowPreFlow(vector<vector<EdgeT>> &input):edgeList(input),d(input.size(), -1), currFlowValue(INT_MIN) { path.reserve(V); }

    int calculate(int s, int t) {
	    int totalFlow = 0;
        while(1) {
            bfs_(s);
            if(d[t] < 0) return;
            currFlowValue = INT_MAX; path.resize(0);
            while(findPath_(s, t)) {
                totalFlow += currFlowValue;
                augmentFlow_();
                currFlowValue = INT_MAX; path.resize(0);
	        }
        }
        return totalFlow;
    }
};

int main(int argc, const char *argv[])
{
    
    if(1) {
        int n,m; cin>>n>>m;
        auto_ptr<Flow> instance(new Flow(n));
        
        for(int i=0; i < m; i++) {
            int u, v, w, cost; cin>>u>>v>>w>>cost;
            instance->addEdge(u, v, 0, w, cost);
        }

        cout << "Max Flow: " << instance->genericAugmentPathFlow(1, n) << endl;
        instance->printGraph();
    }
        
	return 0;
}
