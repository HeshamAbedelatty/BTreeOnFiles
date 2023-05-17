//
// Created by HESHAM on 1/2/2023.
//

#include "B-TreeFunctions.h"
#include <bits/stdc++.h>

using namespace std;

Node createNode() {
    Node node{};
    node.flag = -1;
    pair<int, int> mins;
    mins.first = -1;
    mins.second = -1;
    for (int i = 0; i < 5; ++i) {
        node.key_offset.push_back(mins);
    }
    return node;
}

int GetFreeNodeIndex(vector<Node> BTree) {
    for (int i = 1; i < BTree.size(); ++i) {
        if (BTree[i].flag == -1) {
            return i;
        }
    }
    return false;
}

int GetMaxiIdFormRecord(Node node) {
    for (int i = 0; i < node.key_offset.size(); ++i) {
        if (node.key_offset[i].first == -1) {
            return node.key_offset[i - 1].first;
        } else if (node.key_offset.size() - 1 == i)
            return node.key_offset[i].first;
    }
    return false;
}

pair<int, int> GetMaxiId(Node node) {
    for (int i = 0; i < node.key_offset.size(); ++i) {
        if (node.key_offset[i].first == -1) {
            return node.key_offset[i - 1];
        } else if (node.key_offset.size() - 1 == i)
            return node.key_offset[i];
    }
    return node.key_offset[0];
}

bool CheckDouble(const Node &node, int id) {
    for (auto &i: node.key_offset) {
        if (i.first == id) {
            return true;
        }
    }
    return false;
}

void SplitLeaf(vector<Node> &BTree, int firstLocation, int secondLocation, Node node) {

    int Max1, Max2;
    Node node1 = createNode();
    Node node2 = createNode();
    Node root = createNode();
    pair<int, int> newPair, header1, header2;
    if (firstLocation == BTree[0].key_offset[0].first) {
        secondLocation = firstLocation + 1;
    }
    node1.flag = 0;
    node2.flag = 0;
    for (int i = 0; i < node.key_offset.size(); ++i) {
        newPair.first = node.key_offset[i].first;
        newPair.second = node.key_offset[i].second;
        if (i < 3) {
            node1.key_offset[i] = newPair;
        } else {
            node2.key_offset[i - 3] = newPair;
        }
    }
    BTree[firstLocation] = node1;
    BTree[secondLocation] = node2;

    if (firstLocation == BTree[0].key_offset[0].first) {
        Max1 = GetMaxiIdFormRecord(node1);
        Max2 = GetMaxiIdFormRecord(node2);
        header1.first = Max1;
        header1.second = firstLocation;
        header2.first = Max2;
        header2.second = secondLocation;
        root.flag = 1;
        for (int i = 0; i < 2; ++i) {
            if (i == 0) {
                root.key_offset[i] = header1;
            } else
                root.key_offset[i] = header2;
        }
        BTree[1] = root;
    } /*else {
            root = BTree[1];
            root.key_offset.push_back(header1);
            root.key_offset.push_back(header2);
            sort(root.key_offset.begin(), root.key_offset.end());
        }

        if (root.key_offset.size() <= 5) {
            BTree[1] = root;
        }*/
}

void SplitNonLeaf(vector<Node> &BTree, int firstLocation, int secondLocation, Node node) {

    int Max1, Max2;
    Node node1 = createNode();
    Node node2 = createNode();
    Node root = createNode();
    pair<int, int> newPair, header1, header2;

    secondLocation = firstLocation + 1;

    node1.flag = 1;
    node2.flag = 1;
    for (int i = 0; i < node.key_offset.size(); ++i) {
        newPair.first = node.key_offset[i].first;
        newPair.second = node.key_offset[i].second;
        if (i < 3) {
            node1.key_offset[i] = newPair;
        } else {
            node2.key_offset[i - 3] = newPair;
        }
    }
    BTree[firstLocation] = node1;
    BTree[secondLocation] = node2;
    Max1 = GetMaxiIdFormRecord(node1);
    Max2 = GetMaxiIdFormRecord(node2);
    header1.first = Max1;
    header1.second = firstLocation;
    header2.first = Max2;
    header2.second = secondLocation;
    root.flag = 1;
    for (int i = 0; i < 2; ++i) {
        if (i == 0) {
            root.key_offset[i] = header1;
        } else
            root.key_offset[i] = header2;
    }
    BTree[1] = root;
}

vector<int> FindLocation(vector<Node> B_Tree, int id) {
    vector<int> roots;
    bool flag = false;
    int byte = 1, position;
    roots.push_back(byte);
    Node node = B_Tree[byte];
    for (int i = 0; i < node.key_offset.size(); ++i) {
        if (id <= node.key_offset[i].first) {
            position = node.key_offset[i].second;
            roots.push_back(position);
            node = B_Tree[position];
            flag = true ;
            i = 0;
        } else if (i == node.key_offset.size() - 1) {
            position = node.key_offset[i].second;
            roots.push_back(position);
            i = 0;
            node = B_Tree[position];
            flag = true;
        }
        if (node.flag == 0)
            break;
    }
    return roots;
}

vector<pair<int, int>> GetHeaders(vector<Node> &BTree) {
    vector<pair<int, int>> headers;
    pair<int, int> test;
    for (int i = 1; i < BTree.size(); ++i) {
        if (BTree[i].flag == 0) {
            test.first = GetMaxiIdFormRecord(BTree[i]);
            test.second = i;
            headers.push_back(test);
        }
    }
    sort(headers.begin(), headers.end());
    return headers;
}
//++++++++++++++++++++++++++For Delete+++++++++++++++++++++++++

int searchForItem(const Node &node, int id) {
    for (int i = 0; i < node.key_offset.size(); ++i) {
        if (node.key_offset[i].first == id)
            return i;
    }
    return -1;
}

int searchForReference(const Node &node, int id) {
    for (int i = 0; i < node.key_offset.size(); ++i) {
        if (node.key_offset[i].second == id)
            return i;
    }
    return -1;
}

vector<pair<int, int>> fixSort(Node node) {
    vector<pair<int, int>> headers;
    pair<int, int> test;
    for (auto &i: node.key_offset) {
        if (i.first != -1) {
            headers.push_back(i);
        }
    }
    sort(headers.begin(), headers.end());
    return headers;
}

vector<pair<int, int>> Sort(Node node) {
    vector<pair<int, int>> headers;
    pair<int, int> test;
    test.first = -1;
    test.second = -1;
    for (auto &i: node.key_offset) {
        if (i.first != -1) {
            headers.push_back(i);
        }
    }
    headers.push_back(test);
    return headers;
}

int searchItemBefore(Node &node, int ref) {
    for (int i = 0; i < node.key_offset.size(); ++i) {
        if (node.key_offset[i].second == ref) {
            return node.key_offset[i - 1].second;
        }
    }
    return -1;
}

void fixLeaf(vector<Node> &B_Tree, int rootpos) {
    vector<int> refs, Maxs;
    vector<pair<int, int>> node;
    for (auto &i: B_Tree[rootpos].key_offset) {
        refs.push_back(i.second);
    }
    for (int i = 0; i < refs.size(); ++i) {
        Maxs.push_back(GetMaxiIdFormRecord(B_Tree[refs[i]]));
    }
    for (int i = 0; i < refs.size(); ++i) {
        pair<int, int> n;
        n.first = Maxs[i];
        n.second = refs[i];
        node.push_back(n);
    }
    B_Tree[rootpos].key_offset = node;
}

void Merge(vector<Node> &B_Tree, int behindpos, int rootpos, int leafpos) {
    char Index [10];
    string string1 = "B-Tree.txt";
    strcpy(Index,string1.c_str());
    Node header = readHeader(Index,0);
    int headerValue = header.key_offset[0].first;
    pair<int, int> mergedNode;
    vector<pair<int, int>> node;
    mergedNode.first = B_Tree[leafpos].key_offset[0].first;
    mergedNode.second = B_Tree[leafpos].key_offset[0].second;
    B_Tree[leafpos].flag = -1;
    B_Tree[leafpos].key_offset[0].first = -1;
    B_Tree[leafpos].key_offset[0].second = -1;
    writeRecord(Index,leafpos,B_Tree[leafpos]);
    B_Tree[behindpos].key_offset.push_back(mergedNode);
    int test = searchForReference(B_Tree[rootpos], leafpos);
    B_Tree[rootpos].key_offset[test].first = -1;
    B_Tree[rootpos].key_offset[test].second = -1;
    writeRecord(Index,rootpos,B_Tree[rootpos]);
    node = fixSort(B_Tree[rootpos]);
    B_Tree[rootpos].key_offset = node;
    header.key_offset[0].first = leafpos;
    B_Tree[leafpos].key_offset[0].first = headerValue;
    B_Tree[0] = header;
}

void Redistribution(vector<Node> &B_Tree, int behindpos, int rootpos, int leafpos) {
    pair<int, int> mergedNode;
    vector<pair<int, int>> node;
    int Size = B_Tree[behindpos].key_offset.size();
    mergedNode.first = B_Tree[behindpos].key_offset[Size - 1].first;
    mergedNode.second = B_Tree[behindpos].key_offset[Size - 1].second;
    B_Tree[behindpos].key_offset[Size - 1].first = -1;
    B_Tree[behindpos].key_offset[Size - 1].second = -1;
    B_Tree[leafpos].key_offset.push_back(mergedNode);
    sort(B_Tree[leafpos].key_offset.begin(), B_Tree[leafpos].key_offset.end());
}