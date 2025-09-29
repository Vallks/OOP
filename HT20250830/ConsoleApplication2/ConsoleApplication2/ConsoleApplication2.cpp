#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <iostream>
using namespace std;
void RenameFile();
void RemoveFile();
void Dir();
void main()
{
    cout << "Please, select preffer number...\n";
    char ch;
    do {
        cout << "\n1 - Rename\n";
        cout << "2 - Remove\n";
        cout << "3 - View some folder\n";
        cout << "0 - Exit\n\n";
        cin >> ch;
        switch (ch)
        {
        case '1':
            RenameFile();
            break;
        case '2':
            RemoveFile();
            break;
        case '3':
            Dir();
            break;
        }
    } while (ch != '0');
}
void RenameFile()
{
    char oldName[50], newName[50];
    cout << "Enter old name:";
    cin >> oldName;
    cout << "Enter new name:";
    cin >> newName;
    if (rename(oldName, newName) != 0)
        cout << "Error!\n Couldn't rename file. Check old and new filename...\n\n";
    else
        cout << "Ok...\n\n";
}
void RemoveFile()
{
    char Name[50];
    cout << "Enter name:";
    cin >> Name;
    if (remove(Name) != 0)
        cout << "Error!\n Couldn't remove file. Check filename...\n";
    else
        cout << "Ok...\n";
}
void Dir()
{
    char path[200];
    cout << "\nEnter full path (for example, C:\\):";
    cin >> path;
    char mask[200];
    cout << "\nEnter mask (for example, *.* or *.txt):";
    cin >> mask;
    strcat(path, mask);
    _finddata_t fileinfo{0};
    intptr_t  done = _findfirst(path, &fileinfo);
    intptr_t  MayWeWork = 0;
    int count = 0;
    while (MayWeWork != -1 && done)
    {
        count++;
        cout << fileinfo.name << "\n\n";
        MayWeWork = _findnext(done, &fileinfo);
    }
    cout << "\nInformation: was found " << count;
    cout << " file(s) in folder..." << path << "\n\n";
    _findclose(done);
}
