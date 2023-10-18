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
    size_t end = str.size();
    size_t endToken{ 0 };

    while (endToken < end)
    {
        while (endToken != end && str[endToken] != sep) endToken++;
        tokens.push_back(str.substr(start, endToken - start));
        start = endToken =endToken + 1;
       
    }

    return tokens;
}

int main()
{
    string str = "1,2,3,4,57,478";
    char sep = ',';

    vector<string> tokens = split(str, sep);
    for (auto& i : tokens) {
        cout << i << ' ';
    }

    return 0;
}