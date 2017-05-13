/*!
 *    \file  segmentTree.cpp
 *   \brief  Create a segmentTree for range searches
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

typedef struct { int mi; int ma; } nodeT;

/*
 * Segment Tree
 */
class ST {
    vi &values;
    vector<nodeT> st;

    void postProcessing(int pos) {
        st[pos].mi = min(st[2*pos+1].mi, st[2*pos+2].mi);
        st[pos].ma = max(st[2*pos+1].ma, st[2*pos+2].ma);
    }

    void create_(int cl, int cr, int pos) {
        if(cl == cr) { st[pos].mi = st[pos].ma = values[cl]; return; }
        
        create_(cl, (cl+cr)/2, 2*pos+1);
        create_(((cl+cr)/2)+1, cr, 2*pos+2);
        
        postProcessing(pos);
    }
    
    void query_(const pair<int, int> &queryInput, pair<int, int> &results, int cl, int cr, int pos) {
        if((cl>cr) || (queryInput.second < cl || queryInput.first > cr)) return;
        if(queryInput.first<=cl && queryInput.second>=cr) {
            results.first = min(results.first, st[pos].mi);
            results.second = max(results.second, st[pos].ma);
            return;
        }
        query_(queryInput, results, cl, (cl+cr)/2, 2*pos+1);
        query_(queryInput, results, ((cl+cr)/2)+1, cr, 2*pos+2);
    }
public:
    explicit ST(vi &input):values(input), st(2*input.size()+1) {
        create_(0, values.size(), 0);
    }

    void query(const pair<int, int> &queryInput, pair<int, int> &results) {
        results.first = INT_MAX; results.second = INT_MIN;
        query_(queryInput, results, 0, values.size(), 0);
    }
};

void testRangeSearchMinMax(bool debugOn=false) {
    int inputSize = 0;
	vector<int> input;
	bool testFailed = false;

	cout << "Testing Range-Search-Min-Max Begin. " << endl;
	cout << "===========================================" << endl;
    
    for(int x=0; x < 10; x++) {
        inputSize = rand()%1000;
        input.resize(inputSize, 0);
        generate(input.begin(), input.end(), rand);
        
        ST *instance = new ST(input);
        cout << "Size of the input vector: " << input.size() << endl;        
        
        for(int leftRange = 0; leftRange < input.size(); ++leftRange) {
            for(int rightRange = leftRange; rightRange < input.size(); ++rightRange) {
                pair <int, int> result;
                
                instance->query(make_pair(leftRange, rightRange), result);
                int realMin = *min_element(input.begin()+leftRange, input.begin()+rightRange+1);
                int realMax = *max_element(input.begin()+leftRange, input.begin()+rightRange+1);
                if(debugOn == true) {
                    cout << "Query(" << leftRange << ", " << rightRange << ") ==>  " << result.first << ", " << result.second << " ---- ";
                    cout << "STD Library Query  " << realMin << ", " << realMax << endl;                    
                }
                    
                if((realMin != result.first) || (realMax != result.second)) {
                    cout << "MISMATCH:: Query(" << leftRange << ", " << rightRange << ") ==>  " << result.first << ", " << result.second << " ---- ";
                    cout << "STD Library Query  " << realMin << ", " << realMax << endl;
                    
                    testFailed = true;
                    break;
		        }
            }
            if(testFailed == true)
                break;            
        }
        if(testFailed == true)
            break;
	}
    
	if(testFailed == true)
		cout << "FATAL ERROR: Range-Search-Min-Max has bug !!!!" << endl;
	else
		cout << "Range-Search-Min-Max successful !!!!" << endl;

	cout << "===========================================" << endl;
}

int main(int argc, const char *argv[])
{
    
    srand(time(NULL));
    testRangeSearchMinMax();
    return 0;
}