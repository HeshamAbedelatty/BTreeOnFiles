#include <bits/stdc++.h>
#include "B-TreeFunctions.h"
using namespace std;


int main() {
    char Index [10];
    string string1 = "B-Tree.txt";
    strcpy(Index,string1.c_str());
    CreateIndexFile(Index,10,5);
    cout << "What Would You Like To Do \n";
    int y;
    bool flag = true;
    string Id ;
    while (flag) {
        cout << "\n1. Insert Id and Reference" << endl
             << "2. Search For Id "<< endl
             << "3. Delete Id" << endl
             << "4. Display Index" << endl
             << "5. Exit" << endl
             << "Number: ";
        cin >> y;
        switch (y) {
            case 1:
                int id ,reference,in;
                cout << "Enter -1 -1 to end function:"<<endl;
                cin>> id >>reference;
                while (id != -1|| reference != -1)
                {
                    in = InsertNewRecordAtIndex(Index,id ,reference);
                    if (in == 0)
                    {
                        cout << "This id is Exist "<<endl;
                    } else
                    cout << "Successful" << endl;

                    cin >> id >>reference;
                }
                break;
            case 2:

                cout << "Enter -1 to end function:"<<endl;
                cin >> id;
                while (id != -1)
                {
                    in = SearchARecord(Index,id);
                    if (in == -1)
                    {
                        cout << "This id is Not Exist "<<endl;
                    } else
                        cout << "Successful" << endl;
                    cin >> id ;
                }
                break;
            case 3:
                cout << "Enter -1 to end function:"<<endl;
                cin >> id;
                while (id != -1)
                {
                    in = DeleteRecordFromIndex(Index,id);
                    if (in == -1)
                    {
                        cout << "This id is Not Exist "<<endl;
                    } else
                        cout << "Successful" << endl;
                    cin >> id ;
                }
                break;
            case 4:
                DisplayIndexFileContent(Index,10);
                break;
            case 5:
                flag = false;
                break;
            default:
                break;
        }
    }

    return 0;
}