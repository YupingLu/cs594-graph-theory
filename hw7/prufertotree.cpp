// hw7. this program is to convert the prufer sequence into a tree
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

// split string into vectors
vector<int> split(string str, const char *delim) {
    vector<int> res;
    char* dup = strdup(str.c_str());
    char* pch;
    pch = strtok(dup, delim);
    while(pch != NULL) {
        res.push_back(atoi(pch));
        pch = strtok(NULL, delim);
    }
    free(dup);
    return res;
}

// The algorithm is from wikipedia
vector<pair<int, int> > pruferToTree(vector<int> &code) {
    vector<pair<int, int> > res;
    int n = code.size();
    // check if the code is valid
    for(int i = 0; i < n; i++) {
        if(code[i] < 1 || code[i] > n+2)
            return res;
    }

    vector<int> degree(n+2, 1);
    for(int i = 0; i < n; i++) {
        degree[code[i]-1] += 1;
    }
    // add edges to tree
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n+2; j++) {
            if(degree[j] == 1) {
                res.push_back(make_pair(code[i], j+1));
                degree[code[i]-1] -= 1;
                degree[j] -= 1;
                break;
            }
        }
    }
    // handle the two nodes left with degree 1
    int u = -1, v = -1;
    for(int i = 0; i < n+2; i++) {
        if(degree[i] == 1) {
            if(u == -1) u = i;
            else {
                v = i;
                res.push_back(make_pair(u+1, v+1));
                degree[u] -= 1;
                degree[v] -= 1;
                break;
            }
        }
    }
    return res;
}


int main ()
{
    string userinput;
    getline(cin, userinput);
    const char *delim = " ";
    vector<int> code = split(userinput, delim);

    vector<pair<int, int> > tree = pruferToTree(code);
    if(tree.empty()) {
        cout << "invalid prufer sequence" << endl;
        return 0;
    }

    cout << code.size() + 2 << '\t' << tree.size() << endl;
    for(int i = 0; i < tree.size(); i++) {
        cout << tree[i].first << '\t' << tree[i].second << endl;
    }

    return 0;
}
