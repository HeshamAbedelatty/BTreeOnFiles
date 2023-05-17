//
// Created by HESHAM on 1/2/2023.
//

#ifndef B_TREEONFILETXT_B_TREEFUNCTIONS_H
#define B_TREEONFILETXT_B_TREEFUNCTIONS_H
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int flag;
    vector<pair<int, int>> key_offset;
};

void CreateIndexFile(char *, int, int);
Node readRecord(char *, int);
void writeRecord(char *, int , const Node& ) ;
void DisplayIndexFileContent(char *, int);
vector<Node> bringBTree(char* );
void WriteBTree(char* ,vector<Node>);
Node readHeader(char *, int ) ;
//++++++++++++++++++++++++++==========================++++++++++++++++++++++++++++
int InsertNewRecordAtIndex(char *, int , int );
int DeleteRecordFromIndex(char *, int ) ;
void Merge(vector<Node>& ,int , int ,int );
int SearchARecord(char *, int ) ;
//++++++++++++++++++++++++++==========================++++++++++++++++++++++++++++
void SplitLeaf(vector<Node>& , int, int , Node ) ;
void SplitNonLeaf(vector<Node> &, int , int , Node);
vector<int> FindLocation(vector<Node>, int );
int GetFreeNodeIndex(vector<Node> );
bool CheckDouble(const Node&,int );
Node createNode();
int GetMaxiIdFormRecord(Node );
pair<int,int> GetMaxiId(Node );
vector<pair<int ,int>> GetHeaders(vector<Node> &BTree);
int searchForItem(const Node &, int ) ;
int searchForReference(const Node &, int );
vector<pair<int, int>> Sort(Node ) ;
vector<pair<int, int>> fixSort(Node );
int searchItemBefore(Node& ,int );
void fixLeaf(vector<Node>& ,int );
void Redistribution(vector<Node>& ,int , int ,int );
void insertionSort(vector <pair<int ,int>>& ,pair<int, int>) ;

#endif //B_TREEONFILETXT_B_TREEFUNCTIONS_H
