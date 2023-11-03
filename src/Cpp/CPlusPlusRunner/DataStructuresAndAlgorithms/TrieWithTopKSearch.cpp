#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

/* ************************************************************************ 
* Simple implementation of a trie
* 
* The SimpleTrie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

class SimpleTrie {
public:
    class TrieNode {
    public:
        int son[26];  // by convention -1 means no son
        bool end{ false };        // ends a word;

        TrieNode() {
            for (int i{ 0 }; i < 26; ++i) son[i] = -1;
            

        }
    };
    static const int notFound{ -1 };
    vector<TrieNode> nodesCollection{vector<TrieNode>(1)}; // nodes kept in a vector by convention nodesCollection[0] is the root

    SimpleTrie() {
    }

    void insert(string word) {
        int current{ 0 };
        bool nodeToCreate{ false };
        for (auto c : word) {
            if (!nodeToCreate && nodesCollection[current].son[c - 'a'] != -1)
                current = nodesCollection[current].son[c - 'a'];    // go to next node
            else {                                                  // there is no corresponding node we have to create it
                nodesCollection.emplace_back();
                nodesCollection[current].son[c - 'a'] = nodesCollection.size() - 1;
                current = nodesCollection[current].son[c - 'a'];
                nodeToCreate = true;
            }
        }
        nodesCollection[current].end = true;
    }

    bool search(string word) {
        int current{ 0 };
        for (auto c : word) {
            if ((current = nodesCollection[current].son[c - 'a']) == notFound) return false;
        }
        if (nodesCollection[current].end) return true;
        else return false;
    }

    bool startsWith(string prefix) {
        int current{ 0 };
        for (auto c : prefix) {
            if ((current = nodesCollection[current].son[c - 'a']) == notFound) return false;
        }
        return true;
    }
};



/* ************************************************************************
* 
*/

class AutoCompleteTrie {
public:
    class TrieNode {
    public:
        int son[26];  // by convention -1 means no son
        bool end{ false };        // ends a word;

        map<int, string, greater<int>> sentences;

        TrieNode() {
            for (int i{ 0 }; i < 26; ++i) son[i] = -1;


        }
    };
    static const int notFound{ -1 };
    vector<TrieNode> nodesCollection{vector<TrieNode>(1)}; // nodes kept in a vector by convention nodesCollection[0] is the root
    int mapper[256];    // mapping char to vector
    int currentNode{ 0 };
    string buffer;
    unordered_map<string, int> allSentences;


    AutoCompleteTrie(vector<string>& sentences, vector<int>& times){
        // 1 -- Initialize mapper
        for (int i{ 0 }; i < 256; ++i) {
            if (i >= 'a' && i <= 'z') mapper[i] = i - 'a';
            else if (i == ' ') {
                mapper[i] = 27;
            }
            else
                mapper[i] = -1;
        }

        // 2- Insert sentences on trie
        for (int i{ 0 }; i < sentences.size(); ++i) {
            insert(sentences[i], times[i]);
            allSentences[sentences[i]] = times[i];
        }



    }

    // Inserts a sentence to the trie
    void insert(string sentence, int times) {
        int current{ 0 };    // start from the root node
        bool nodeToCreate{ false };
        for (auto c : sentence) {
            if (!nodeToCreate && nodesCollection[current].son[mapper[c]] != notFound)
                current = nodesCollection[current].son[mapper[c]];    // go to next node
            else {                                                  // there is no corresponding node we have to create it
                nodesCollection.emplace_back();
                nodesCollection[current].son[mapper[c]] = nodesCollection.size() - 1;
                current = nodesCollection[current].son[mapper[c]];
                nodeToCreate = true;
            }
            nodesCollection[current].sentences[times] = sentence;
        }
        nodesCollection[current].end = true;
    }

    // Update a sentence to the trie
    void update(string sentence, int times) {
        int current{ 0 };    // start from the root node
        bool nodeToCreate{ false };
        for (auto c : sentence) {
            if (!nodeToCreate && nodesCollection[current].son[mapper[c]] != notFound)
                current = nodesCollection[current].son[mapper[c]];    // go to next node
            else {                                                  // there is no corresponding node we have to create it
                nodesCollection.emplace_back();
                nodesCollection[current].son[mapper[c]] = nodesCollection.size() - 1;
                current = nodesCollection[current].son[mapper[c]];
                nodeToCreate = true;
            }
            nodesCollection[current].sentences[times] = sentence;
        }
        nodesCollection[current].end = true;
    }

    vector<string> startsWith(char currentChar) {
        vector<string> result;
        int current{ 0 };
        
        if (currentChar == '#') {
            if (allSentences.find(buffer) != end(allSentences)) {
                allSentences[buffer]++;
                update(buffer, allSentences[buffer]);
            }
            else {
                allSentences[buffer] = 1;
                update(buffer, allSentences[buffer]);
            }
            currentNode = 0;
            buffer.clear();
            return result;
        }
        buffer.push_back(currentChar);
        if ((current = nodesCollection[currentNode].son[mapper[currentChar]]) == notFound) return result;
        currentNode = current;
        int i{ 0 };
        for (map<int, string>::iterator it {begin(nodesCollection[currentNode].sentences)};
            it != end(nodesCollection[currentNode].sentences) &&
            i < 3;
            ++it, ++i)
            result.push_back(it->second);
        return result;
       ;
    }

    vector<string> input(char c) {
        return startsWith(c);

    }
};



int main()
{
    cout << "Heap" << endl;

    vector<int> vec { 25, 7, 1, 2, 3, 4, 5, 14, 32};

    int mapper[256];


    vector<string> sentences {"aba aba", "ababa baba", "abcaba lasaba"};
    vector<int> times {2, 3, 4};

    AutoCompleteTrie atc (sentences, times);
    vector<string> res = atc.startsWith('a');
    res = atc.startsWith('b');
    res = atc.startsWith('c');
    res = atc.startsWith('d');
    res = atc.startsWith('#');
    res = atc.startsWith('a');



    return 0;
}