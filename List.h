#pragma once
#include <stdexcept>
#include <vector>
#include <exception>
using namespace std;

enum class Iterators {
    STEP,
    VALUE,
    PREDICATE
};

class ListIterator;
class List
{
public:
    vector <int> vec;
    size_t top = 0;
public:
    friend class ListIterator;

    explicit List(size_t aSize) {
        if ((int)aSize <= 0)
            throw exception("Wrong data");
        vec.resize(aSize);
    }

    virtual ~List() = default;

    bool append(int a) {
        if (top == vec.size())
            return false;
        vec[top++] = a;
        return true;
    }

    bool remove() {
        if (top == 0)
            return false;
        --top;
        return true;
    }

    ListIterator* createIterator(Iterators its, const int aStep,
        bool (*predicate) (int) = nullptr) const;
};

class ListIterator {
protected:
    friend class List;
    const List* pList;
    size_t current;
public:
    explicit ListIterator(const List* aPList)
        : pList(aPList), current(aPList->top - 1) {}
    virtual bool first() = 0;
    virtual bool next() = 0;

    virtual int currentItem() {
        if (current == -1)
            throw runtime_error("Can't obtain currentItem!");
        return pList->vec[current];
    };

    virtual ~ListIterator() = default;
};

class ListIteratorStep : public ListIterator
{
private:
    int step;
public:
    friend class List;
    ListIteratorStep(const List* aPList, int aStep = 1)
        : ListIterator(aPList), step(aStep) {}

    bool first() override {
        current = pList->top - 1;
        return current >= 0;
    }

    bool next() override
    {
        if (current < step) {
            current = -1;
            return false;
        }
        current = current - step;
        return true;
    }
};

class ListIteratorPredicate : public ListIterator
{
private:
    // ”казатель на функцию, принимающую int и возвращающую bool.( предикат).
    bool (*predicate) (int);
public:
    ListIteratorPredicate(const List* aPList, bool (*aPredicate) (int))
        : ListIterator(aPList), predicate(aPredicate) {}

    bool first() override {
        current = pList->top;
        return next();
    }

    bool next() override {
        current = current - 1;
        while (current != -1 && !predicate(pList->vec[current]))
            current = current - 1;
        return current != -1;
    }
};

class ListIteratorValue : public ListIterator
{
private:
    int value;
public:
    friend class List;
    ListIteratorValue(const List* aPList, int aValue)
        : ListIterator(aPList), value(aValue) {}

    bool first() override {
        current = pList->top;
        return next();
    }
    bool next() override
    {
        current = current - 1;
        while (current != -1 && pList->vec[current] != value) {
            current = current - 1;
        }
        return current != -1;
    }
};

ListIterator* List::createIterator(Iterators its, const int aStep,
    bool (*predicate) (int)) const {
    if (its == Iterators::STEP)
        return new ListIteratorStep(this, aStep);
    if (its == Iterators::VALUE)
        return new ListIteratorValue(this, aStep);
    if (its == Iterators::PREDICATE)
        return new ListIteratorPredicate(this, predicate);
    return nullptr;
}

