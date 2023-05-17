//
// Created by HESHAM on 1/2/2023.
//
#include "B-TreeFunctions.h"
#include <bits/stdc++.h>

using namespace std;

int InsertNewRecordAtIndex(char *filename, int recordId, int reference) {
    int FreeNode;
    bool CheckFlag;
    Node root{};
    vector<Node> B_Tree;
    B_Tree = bringBTree(filename);
    pair<int, int> writtenNode;
    writtenNode.first = recordId;
    writtenNode.second = reference;
    int header = readHeader(filename, 0).key_offset[0].first;
    int start = B_Tree[1].flag;
    if (start == -1) {
        Node node = B_Tree[1];
        node.flag = 0;
        node.key_offset[0] = writtenNode;
        B_Tree[0].key_offset[0].first++;
        B_Tree[1] = node;
        WriteBTree(filename, B_Tree);
        return 1;
    } else if (start == 0) {
        Node node = B_Tree[1];
        CheckFlag = CheckDouble(node, recordId);
        if (CheckFlag) {
            return 0;
        }
        node.key_offset.push_back(writtenNode);
        sort(node.key_offset.begin(), node.key_offset.end());
        if (node.key_offset.size() <= 5) {
            B_Tree[1] = node;
            WriteBTree(filename, B_Tree);
            return 1;
        }
        SplitLeaf(B_Tree, header, 0, node);
        FreeNode = GetFreeNodeIndex(B_Tree);
        B_Tree[0].key_offset[0].first = FreeNode;
        WriteBTree(filename, B_Tree);
        return 1;
    } else if (start == 1) {
        vector<pair<int, int>> headers;
        vector<int> roots = FindLocation(B_Tree, recordId);
        int pos = roots[roots.size() - 1];
        Node node = B_Tree[pos];
        CheckFlag = CheckDouble(node, recordId);
        if (CheckFlag) {
            return 0;
        }
        node.key_offset.push_back(writtenNode);
        sort(node.key_offset.begin(), node.key_offset.end());
        B_Tree[pos] = node;
        if (node.key_offset.size() <= 5) {
            for (int i= roots.size()-1;i >=1; --i) {
                fixLeaf(B_Tree,roots[i-1]);
            }
            WriteBTree(filename, B_Tree);
            return 1;

        }
        if (node.key_offset.size() > 5 && header != -1) {
            SplitLeaf(B_Tree, pos, header, node);
            FreeNode = GetFreeNodeIndex(B_Tree);
            B_Tree[0].key_offset[0].first = FreeNode;
            headers = GetHeaders(B_Tree);
            if (headers.size() <= 5) {
                FreeNode = GetFreeNodeIndex(B_Tree);
                B_Tree[0].key_offset[0].first = FreeNode;
                B_Tree[1].key_offset = headers;
                WriteBTree(filename, B_Tree);
                return 1;
            } else {
                Node r{};
                r.flag = 1;
                r.key_offset = headers;
                SplitNonLeaf(B_Tree, B_Tree[0].key_offset[0].first, 0, r);
                FreeNode = GetFreeNodeIndex(B_Tree);
                if (FreeNode == 0) {
                    B_Tree[0].key_offset[0].first = -1;
                }
                WriteBTree(filename, B_Tree);
                return 1;
            }
        } else {
            return 2;
        }
    }
    return 0;
}

int DeleteRecordFromIndex(char *filename, int RecordID) {
    int isExist;
    Node leaf{};
    vector<Node> B_Tree;
    vector<int> roots;
    B_Tree = bringBTree(filename);
    roots = FindLocation(B_Tree, RecordID);//1,8,5
    int leafPosition = roots[roots.size() - 1],//5
    rootPosition = roots[roots.size() - 2],//8
    rootRootPosition = roots[roots.size() - 3];//1
    isExist = searchForItem(B_Tree[leafPosition], RecordID);
    if (isExist == -1) {
        return -1;
    }
    leaf = B_Tree[leafPosition];
    leaf.key_offset[isExist].first = -1;
    leaf.key_offset[isExist].second = -1;
    leaf.key_offset = Sort(leaf);
    writeRecord(filename, leafPosition, leaf);
    leaf.key_offset = fixSort(leaf);
    B_Tree[leafPosition] = leaf;
    int SizeOfRecord = leaf.key_offset.size();
    if (SizeOfRecord < 2) {
        int behindPositon = searchItemBefore(B_Tree[rootPosition], leafPosition);
        if (B_Tree[behindPositon].key_offset.size() > 2) {
            Redistribution(B_Tree, behindPositon, rootPosition, leafPosition);
            fixLeaf(B_Tree, rootPosition);
            fixLeaf(B_Tree, rootRootPosition);
            WriteBTree(filename, B_Tree);
            return 1;
        } else {
            Merge(B_Tree, behindPositon, rootPosition, leafPosition);
            fixLeaf(B_Tree, rootPosition);
            fixLeaf(B_Tree, rootRootPosition);
            WriteBTree(filename, B_Tree);
            return 1;
        }
    }
    fixLeaf(B_Tree, rootPosition);
    fixLeaf(B_Tree, rootRootPosition);
    WriteBTree(filename, B_Tree);
    return 1;

}

int SearchARecord(char *filename, int RecordID) {
    vector<Node> B_Tree;
    vector<int> roots;
    B_Tree = bringBTree(filename);
    roots = FindLocation(B_Tree, RecordID);
    int ay_7aga = roots[roots.size() - 1];
    for (auto &i: B_Tree[ay_7aga].key_offset) {
        if (i.first == RecordID)
            return RecordID;
    }
    return -1;
}