// 3093. Longest Common Suffix Queries

struct TrieNode {
    vector<shared_ptr<TrieNode>> children;

    TrieNode() : children(26, nullptr) {}

    int length = INT_MAX;
    int index = -1;
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        vector<int> ans;

        int minIndex = 0;

        for (int i = 0; i < wordsContainer.size(); ++i) {

            if (wordsContainer[i].length() <
                wordsContainer[minIndex].length()) {
                minIndex = i;
            }

            insert(wordsContainer[i], i);
        }

        root->index = minIndex;

        for (const string& q : wordsQuery) {
            ans.push_back(search(q));
        }

        return ans;
    }

private:
    shared_ptr<TrieNode> root = make_shared<TrieNode>();

    void insert(const string& word, int wordIndex) {

        shared_ptr<TrieNode> node = root;

        for (int i = word.length() - 1; i >= 0; --i) {

            int charIndex = word[i] - 'a';

            if (node->children[charIndex] == nullptr) {
                node->children[charIndex] =
                    make_shared<TrieNode>();
            }

            node = node->children[charIndex];

            if (node->length > word.length()) {
                node->length = word.length();
                node->index = wordIndex;
            }
        }
    }

    int search(const string& word) {

        shared_ptr<TrieNode> node = root;

        for (int i = word.length() - 1; i >= 0; --i) {

            int charIndex = word[i] - 'a';

            if (node->children[charIndex] == nullptr) {
                return node->index;
            }

            node = node->children[charIndex];
        }

        return node->index;
    }
};
