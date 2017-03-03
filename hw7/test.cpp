#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

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


int main ()
{
    string str;
    getline(cin, str);
    const char *delim = " ";
    vector<int> res = split(str, delim);
    for(int i = 0; i < res.size(); i++)
        cout << res[i] << endl;

    return 0;
}
