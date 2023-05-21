#include <iostream>

//#define debug 1

using namespace std;

struct Record
{
    unsigned amount; // количество товара
    double cost; // цена за штуку

    Record(int a = 0, double c = 0) // конструктор по умолчанию
    {
        #ifdef debug
            cout << "конструктор Record" << endl;
        #endif
        amount = a;
        cost = c;
    }

    Record(const Record &other) // конструктор копирования
    {
        #ifdef debug
            cout << "конструктор копирования Record" << endl;
        #endif
        this->amount = other.amount;
        this->cost = other.cost;
    }


    Record& operator= (const Record &other) // перегрузка оператора присвоения
    {
        #ifdef debug
            cout << "оператор = Record" << endl;
        #endif
        if(this == &other)
            return *this;
        this->amount = other.amount;
        this->cost = other.cost;
        return *this;
    }
    
};
