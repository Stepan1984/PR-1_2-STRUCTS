#include <iostream>

//#define debug 1

using namespace std;

struct Record
{
    unsigned amount; // ���������� ������
    double cost; // ���� �� �����

    Record(int a = 0, double c = 0) // ����������� �� ���������
    {
        #ifdef debug
            cout << "����������� Record" << endl;
        #endif
        amount = a;
        cost = c;
    }

    Record(const Record &other) // ����������� �����������
    {
        #ifdef debug
            cout << "����������� ����������� Record" << endl;
        #endif
        this->amount = other.amount;
        this->cost = other.cost;
    }


    Record& operator= (const Record &other) // ���������� ��������� ����������
    {
        #ifdef debug
            cout << "�������� = Record" << endl;
        #endif
        if(this == &other)
            return *this;
        this->amount = other.amount;
        this->cost = other.cost;
        return *this;
    }
    
};
