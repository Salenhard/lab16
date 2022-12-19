#include <iostream>
#include "BinFile.h"


const long Empty = -1;

struct FileDataRecord {
    int data;
    int nextIndex;
};

void LoadRecord(BinFile<FileDataRecord>& bf, long& startindex, FileDataRecord& dr) {
    dr.nextIndex = startindex;
    startindex = bf.Size();
    bf.Append(dr);
}
void PrintList(BinFile<FileDataRecord>& bf, long& startindex) {
    long index = startindex;
    FileDataRecord rec;
    while (index != Empty)
    {
        rec = bf.Read(index);
        cout << rec.data << " ";
        index = rec.nextIndex;
    }
    cout << endl;
}

int main()
{
    setlocale(0, "ru");
    long hashTable[10];
    FileDataRecord dr;
    int i, item, request;
    BinFile<FileDataRecord> dataFile("DRfile.txt", INOUT);
    for (i = 0; i < 10; i++)
        hashTable[i] = Empty;   
    for (i = 0; i < 50; i++) {
        item = rand();
        dr.data = item;
        LoadRecord(dataFile, hashTable[item % 10], dr);
    }

    cout << "Введите номер ячейки хеш-таблицы: ";
    cin >> request;
    cout << "Печать элементво данныхб хешируемых в число " << request << endl;
    PrintList(dataFile, hashTable[request]);
    dataFile.Delete();
}

