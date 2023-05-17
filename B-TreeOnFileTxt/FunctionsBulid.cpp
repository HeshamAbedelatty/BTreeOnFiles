//
// Created by HESHAM on 1/2/2023.
//
#include "B-TreeFunctions.h"
#include <bits/stdc++.h>

using namespace std;

void CreateIndexFile(char *filename, int numberOfRecords, int m) {
    int True = 0;
    int fl;
    ifstream readfile(filename, ios::in);
    readfile.seekg(0, ios::end);
    fl = (int) readfile.tellg();
    if (fl < 1) {
        True = 1;
    }
    readfile.close();
    if (True == 1) {
        ofstream outfile(filename, ios::out | ios::in);
        outfile.seekp(0, ios::beg);
        string flag = "-1", space = " ";
        int header;
        char flag_char[sizeof(int)];
        strcpy(flag_char, flag.c_str());

        for (int i = 0; i < numberOfRecords; i++) {
            outfile.write(flag_char, sizeof(int));
            if (i + 1 != numberOfRecords) {
                header = i + 1;
                string headerString;
                char header_char[sizeof (int)];
                headerString = to_string(header);
                strcpy(header_char, headerString.c_str());
                outfile.write(header_char, (int)headerString.length());
                char lenSpace[4-(int)headerString.length()];
                strcpy(lenSpace,space.c_str());
                for (int j = 0; j <4-(int)headerString.length() ; ++j) {
                    outfile.write(lenSpace, 1);
                }

            } else {
                string headerString;
                headerString = flag;
                char header_char[sizeof(int)];
                strcpy(header_char, headerString.c_str());
                outfile.write(header_char, sizeof(int));
            }
            outfile.write(flag_char, sizeof(int));
            for (int j = 0; j < m - 1; ++j) {
                outfile.write(flag_char, sizeof(int));
                outfile.write(flag_char, sizeof(int));

            }
        }
        outfile.close();
    }
}


Node readRecord(char *file_name, int recordNum) {
    ifstream Record(file_name, ios::in);
    Node no{};
    pair<int, int > value;
    char read_flag[sizeof(int)];
    char cell[sizeof(int)];
    string string1l;
    Record.seekg(recordNum * 44);
    Record.read(read_flag, sizeof(int));
    string1l = (string) read_flag;
    no.flag = stoi(string1l);
    for (int i = 0; i < 5; ++i) {
        Record.read(cell, sizeof(int));
        string string1 = (string) cell;
        if (string1 == "-1")
            break;
        value.first = stoi(string1);
        Record.read(cell, sizeof(int));
        string1 = (string) cell;
        value.second = stoi(string1);
        no.key_offset.push_back(value);
    }
    Record.close();
    return no;
}

void DisplayIndexFileContent(char* filename , int numOfRecords) {

    pair<int,int>value;
    value.first=-1;
    value.second=-1;
    for (int i = 0; i < numOfRecords; ++i) {
        Node node{};

        node = readRecord(filename,i);
        while (node.key_offset.size()<5) {
            node.key_offset.push_back(value);
        }
        cout << left<<setw(5)<<node.flag <<" ";
        for (auto & item : node.key_offset) {
            cout <<left<< setw(5)<<item.first << " " << setw(5)<<item.second << " ";
        }
        cout << endl;
    }


}
void writeRecord(char *file_name, int recordNum, const Node& no) {
    fstream output(file_name, ios::in | ios::out);
    output.seekg(0,ios::beg);
    output.seekg(recordNum * 44);
    string space = " ";
    int flag = no.flag;
    string FlagString = to_string(flag);
    char read_flag[sizeof(int)];
    strcpy(read_flag, FlagString.c_str());
    output.write(read_flag, 4);
    for (auto & i : no.key_offset) {
        string Cell = to_string(i.first);
        char cell[sizeof(int)];
        strcpy(cell, Cell.c_str());
        output.write(cell,4);
        Cell = to_string(i.second);
        char cell2[sizeof(int)];
        strcpy(cell2, Cell.c_str());
        output.write(cell2, 4);
    }
    output.close();
}
vector<Node> bringBTree(char* filename)
{
    vector<Node> Btree;
    Node node{};
    for (int i = 0; i < 10; ++i) {
        node = readRecord(filename,i);
        Btree.push_back(node);
    }
    return Btree;
}
void WriteBTree(char* filename,vector<Node> Btree)
{
    for (int i = 0; i < 10; ++i) {
        writeRecord(filename,i,Btree[i]);
    }
}
Node readHeader(char *file_name, int recordNum) {
    ifstream Record(file_name, ios::in);
    Node no{};
    pair<int, int > value;
    char read_flag[sizeof(int)];
    char cell[sizeof(int)];
    string string1l;
    Record.seekg(recordNum * 44);
    Record.read(read_flag, sizeof(int));
    string1l = (string) read_flag;
    no.flag = stoi(string1l);
    for (int i = 0; i < 5; ++i) {
        Record.read(cell, sizeof(int));
        string string1 = (string) cell;
        value.first = stoi(string1);
        Record.read(cell, sizeof(int));
        string1 = (string) cell;
        value.second = stoi(string1);
        no.key_offset.push_back(value);
    }
    Record.close();
    return no;
}