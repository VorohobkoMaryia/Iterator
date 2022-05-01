#include "List.h"
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

unsigned counting(ListIterator* li) {
    unsigned cnt = 0;
    if (li->first()) {
        do {
            cnt++;
            cout << li->currentItem() << " ";
        } while (li->next());
    }
    cout << endl;
    return cnt;
}

bool IsEven(int a) {
    return a % 2 == 0;
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand((unsigned)time(0));
    try
    {
        unsigned capacity, count;
        cout << "������� ����� �����: ";
        cin >> capacity;
        List list(capacity);
        cout << "������� ����������� ��������� ��� ���������� �����: ";
        cin >> count;
        if ((int)count <= 0)
            throw exception("Wrong data");
        for (auto i = 0; i < count; i++) {
            int x = rand() % 5;
            if (list.append(x))
                cout << x << " ";
        }
        cout << endl;

        ListIterator* litS3 = list.createIterator(Iterators::STEP, 3);
        ListIterator* litV4 = list.createIterator(Iterators::VALUE, 4);
        ListIterator* litPred = list.createIterator(Iterators::PREDICATE, 0, IsEven);

        cout << "�������� ����� � �������� �������� 3 � ���������� �����:" << endl;
        cout << counting(litS3) << endl;
        cout << "�������� �����, ������ 4, � ���������� �����:" << endl;
        cout << counting(litV4) << endl;
        cout << "׸���� �������� ����� � ���������� �����:" << endl;
        cout << counting(litPred) << endl;

        delete litS3;
        delete litV4;
        delete litPred;
    }
    catch (exception& e)
    {
        cout << "� ������ ����������: " << e.what() << endl;
    }
}