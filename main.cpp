#include "stack.h"
#include <iostream>
#include <locale.h>
#include <sstream>
#include <math.h>
//#include <regex>
#define EPS 1e-6

using namespace std;

int enterRecord(Stack * );

int main(void)
{
    setlocale(LC_ALL, "Rus");
    Stack * stack; // ������ ��������� �� ������� �����
    int menu;

    do
    {   
        system("cls");
        cout << "�������� ��������� ���������� �����" << endl;
        cout << "1. ������" << endl;
        cout << "2. ������" << endl;
        cout << "3. �����" << endl;
        cin >> menu;
        cin.get();
        switch(menu)
        {
            case 1:
                try
                {
                    stack = new VectorStack;
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                    cout << "������ ��������� ������" << endl;
                }
                break;
            case 2:
                try
                {
                    stack = new ListStack;
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                    cout << "������ ��������� ������" << endl;
                }
                    
        }
    }while(menu != 1 && menu != 2 && menu != 3);
    
    if(menu == 3) // ���� ������� "�����"
    {
        system("cls");
        return 0;
    }
    
    do
    {
        system("cls");
        cout << "����" << endl;
        cout << "1. ���� ������" << endl;
        cout << "2. �����" << endl;
        cin >> menu;
        cin.get();
        if(menu == 1)
        {
            system("cls");
            int result = enterRecord(stack);
            if(result == 0)
            {
                cout << "�������� ���������" << endl;
            }
            else{
                if(result == -1) // ���� �������� ������ � �������
                {
                    cout << "�������� ������ �� " << stack->getTop()->amount * stack->getTop()->cost << "$" << endl; // ������� ����� ��������� ����������� ������
                }
                else // ���� �������� ������ � �������
                {
                    Record * tmp_record;
                    while(result > 0 && !stack->isEmpty()) // ���� � ����� ���� ������ � �� ������� ���� ��������� �����
                    {
                        tmp_record = stack->pop(); // ������ �� ����� ������ � ������
                        if(tmp_record->amount > result) // ���� ������ ������, ��� ����� �������
                        {
                            cout << result << " ���� �� " << tmp_record->cost * 1.2 << " $ ������ �� ����� " << tmp_record->cost * result * 1.2 << " $" << endl;
                            tmp_record->amount -= result; // ��������� ���������� ������ �� ������
                            stack->push(*tmp_record); // ���������� ������ ������� � ����
                            result = 0; // �������� ���������� 
                        }
                        else // ���� ���������� ����������� ��������� >= ���������� ������ � ������ ������ ����� � �������
                        {
                            cout << tmp_record->amount << " ���� �� " << tmp_record->cost * 1.2 << " $ ������ �� ����� " << tmp_record->amount * tmp_record->cost * 1.2 << " $" << endl;
                            result -= tmp_record->amount;
                            delete tmp_record; // ������� ������, �.�. ��� ������ �� ���� ���� �������
                        }
                    }

                    if(stack->isEmpty() && result > 0) // ���� �� ������� ������
                        cout << "�� ������ �� ������� " << result << " ������� ������" << endl;
                }   
            }
            cout << "ENTER - ��� �������� � ����" << endl;
            while(cin.get() != '\n');
            continue;
        }
    }while(menu != 2);


    delete stack;
    return 0;
}



int enterRecord(Stack * stack)
{
    stringstream stream;
    bool operation_type; // ��� �������� 1 - ������� 0 - �������
    char ctmp;
    int end , i, amount;
    double cost;
    string input;
    do
    {
        system("cls");
        cout << "������� ������ � ��������� �������" << endl;
        cout << "(S - ������� �������� �������)" << endl;
        cout << "(R - ������� �������� �������)" << endl;
        getline(cin, input, '\n'); // ��������� ������ �� �������� ������
        end = input.length();
        i = 0;
        while(input[i] != 's' && input[i] != 'S' && input[i] != 'r' && input[i] != 'R' && i < end) // ���� ��� ������
            i++;
        if(i == end) // ���� �� �����
            continue; // ��������� ������ �� ������
        if(input[i] == 's' || input[i] == 'S')
            operation_type = 1;
        else
            operation_type = 0;

        while(i != end && !isdigit(input[i])) // ���� �����
            i++;

        if(i == end) // ���� �� �����
            continue; // ��������� ������ �� ������

        stream.clear();
        while(isdigit(input[i])) // ���� �����
            stream << input[i++];
        stream >> amount;
        

        if(operation_type == 0)
        {
            bool dot = false;
            while(i != end && !isdigit(input[i]) && input[i] != '.') // ���� �����
                i++;
            if(i == end) // ���� �� �����
                continue; // ��������� ������ �� ������

            int start_index = i; // ������ ������� �������� �����

            stream.clear();
            while(isdigit(input[i]) || (input[i] == '.' && !dot)) // ���� ����� ��� �� ����� � �����
            {
                stream << input[i];
                if(input[i] == '.')
                {
                    if(i == start_index) // ���� ����� ������ ������� �����
                        break;
                    dot = true;
                } 
                    
                i++;
            }
            if(i == start_index)
                continue;
            stream >> cost; 
        }
        break;

    }while(1);

    if(fabs(cost) < EPS || amount <= 0)
    {
                return 0;
    }

    if(operation_type) // ���� �������� �������
    {
        return amount;
    }
    else
    {
        Record new_record;
        new_record.amount = amount;
        new_record.cost = cost;
        stack->push(new_record);
        return -1;
    }
}

