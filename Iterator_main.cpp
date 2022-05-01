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
        cout << "Введите объём стека: ";
        cin >> capacity;
        List list(capacity);
        cout << "Введите кколичество элементов для заполнения стека: ";
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

        cout << "Элементы стека с разницей индексов 3 и количество таких:" << endl;
        cout << counting(litS3) << endl;
        cout << "Элементы стека, равные 4, и количество таких:" << endl;
        cout << counting(litV4) << endl;
        cout << "Чётные элементы стека и количество таких:" << endl;
        cout << counting(litPred) << endl;

        delete litS3;
        delete litV4;
        delete litPred;
    }
    catch (exception& e)
    {
        cout << "я словил исключение: " << e.what() << endl;
    }
}