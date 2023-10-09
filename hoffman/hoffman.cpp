#include <bits/stdc++.h>

using namespace std;

class hoffmanLeafNode
{
private:
    char ch;
    int weight;

public:
    bool isLeaf;
    hoffmanLeafNode *left;
    hoffmanLeafNode *right;
    hoffmanLeafNode(char x, int f)
    {
        this->ch = x;
        this->weight = f;
        this->left = nullptr;
        this->right = nullptr;
        this->isLeaf = true;
    }
    hoffmanLeafNode(hoffmanLeafNode *l, hoffmanLeafNode *r, int wt)
    {
        this->left = l;
        this->right = r;
        this->weight = wt;
        this->ch = ' ';
        this->isLeaf = false;
    }

    bool isLeafNode()
    {
        return this->isLeaf;
    }
    int getWeight()
    {
        return this->weight;
    }
    char getChar()
    {
        return this->ch;
    }
};

hoffmanLeafNode *createPrefixTree(map<char, int> &mpp)
{
    priority_queue<pair<int, hoffmanLeafNode *>,
                   vector<pair<int, hoffmanLeafNode *>>,
                   greater<pair<int, hoffmanLeafNode *>>>
        minHeap; // {weight, node}

    // mpp ({char, freq})
    for (auto it : mpp)
    {
        hoffmanLeafNode *node = new hoffmanLeafNode(it.first, it.second);
        int val = it.second;
        minHeap.push({val, node});
    }

    while (minHeap.size() > 1)
    {
        auto fir = minHeap.top(); // {weight, node}
        minHeap.pop();
        auto sec = minHeap.top();
        minHeap.pop();

        hoffmanLeafNode *newNode = new hoffmanLeafNode(sec.second, fir.second, fir.first + sec.first);

        minHeap.push({fir.first + sec.first, newNode});
    }

    return minHeap.top().second;
}

// table
void createTable(hoffmanLeafNode *root, string str, map<char, string> &mpp)
{
    if (root->isLeaf == true)
    {
        mpp[root->getChar()] = str;
        return;
    }

    if (root->left)
        createTable(root->left, str + '0', mpp);
    if (root->right)
        createTable(root->right, str + '1', mpp);
    return;
}

char decodeFunc(string &word, map<char, string> &table)
{
    for (auto it : table)
    {
        if (it.second == word)
            return it.first;
    }
    return ' ';
}

void decoding(map<char, string> &table)
{
    ifstream into("txt2.txt");

    ofstream fto("txt3.txt");

    while (!into.eof())
    {

        string text;

        getline(into, text);
        string decoded = "";
        string word = "";
        for (auto it : text)
        {
            if (it == ' ')
            {
                decoded += decodeFunc(word, table);
                word = "";
            }
            else
            {
                word += it;
            }
        }

        fto << decoded << endl;
    }
    into.close();
    fto.close();
}

int main()
{

    map<char, int> mpp;

    fstream file;
    file.open("txt.txt");
    if (file.is_open())
    {
        while (file)
        {
            string ss;
            file >> ss;
            for (auto it : ss)
            {
                mpp[it]++;
            }
        }
    }
    file.close();

    // // create prefix tree
    hoffmanLeafNode *Root = createPrefixTree(mpp);

    // // create table
    map<char, string> table;
    createTable(Root, "", table);

    // encode
    ifstream in("txt.txt");
    ofstream f("txt2.txt");

    while (!in.eof())
    {

        string text;

        getline(in, text);
        string encoded = "";
        for (auto it : text)
        {
            encoded += table[it];
            encoded += " ";
        }

        f << encoded << endl;
    }
    in.close();
    f.close();

    // decode
    int val = 1;
    cout << "type 0 to decode" << endl;
    cin >> val;

    if (val == 0)
        decoding(table);

    return 0;
}