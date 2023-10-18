#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(const string& str, char sep)
{
    vector<string> tokens;

    if (str.empty()) {
        return tokens;
    }

    size_t start = 0;
    size_t end = 0;

    while ((end = str.find(sep, start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(str.substr(start));
    return tokens;
}

int main()
{
    string str = "1,2,3,4,57";
    char sep = ',';

    vector<string> tokens = split(str, sep);
    for (auto& i : tokens) {
        cout << i << ' ';
    }

    return 0;
}
