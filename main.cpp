#include "stack.h"
#include <iostream>
#include <locale.h>
#include <sstream>

using namespace std;

int chooseStack();
int enterRecord(Stack * );
int isInt(string &);
int isDouble(string &);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    Stack * stack; // ������ ��������� �� ������� �����
    int stack_type = chooseStack();
    if(stack_type == 3) // ���� ������� "�����"
    {
        system("cls");
        return 0;
    }
    else
    {
        if(stack_type == 1) // ���� ������� ������
            stack = new VectorStack;
        else // ���� ������� ������
            stack = new ListStack;
    }
    
    
    int menu;
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
            if(!enterRecord(stack))
            {
                system("cls");
                cout << "������������ ������" << endl;
                cout << "ENTER - ��� �������� � ����" << endl;
                while(cin.get() != '\n');
                continue;
            }

            system("cls");

            if(stack->getTop()->type == 0) // ���� �������� ������ � ������� 
            {
                cout << "�������� ������ �� " << stack->getTop()->amount * stack->getTop()->cost << "$" << endl; // ������� ����� ��������� ����������� ������
            }
            else // ���� �������� ������ � �������
            {
                Record * sell_record = stack->pop(); // ����������� ������ � ������� �� �����
                Record * tmp_record;
                while(sell_record->amount > 0 && !stack->isEmpty()) // ���� � ����� ���� ������ � �� ������� ��� ����������� �����
                {
                    tmp_record = stack->pop(); // ������ �� ����� ������ � ������
                    if(tmp_record->amount > sell_record->amount) // ���� ������ ������, ��� ����� �������
                    {
                        cout << sell_record->amount << " ���� �� " << tmp_record->cost * 1.2 << " $ ������ �� ����� " << tmp_record->cost * sell_record->amount * 1.2 << " $" << endl;
                        tmp_record->amount -= sell_record->amount; // ��������� ���������� ������ �� ������
                        stack->push(tmp_record); // ���������� ������ ������� � ����
                        sell_record->amount = 0; // �������� ���������� 
                    }
                    else // ���� ���������� ����������� ��������� >= ���������� ������ � ������ ������ ����� � �������
                    {
                        cout << tmp_record->amount << " ���� �� " << tmp_record->cost * 1.2 << " $ ������ �� ����� " << tmp_record->amount * tmp_record->cost * 1.2 << " $" << endl;
                        sell_record->amount -= tmp_record->amount;
                        delete tmp_record; // ������� ������, �.�. ��� ������ �� ���� ���� �������
                    }
                }

                if(stack->isEmpty() && sell_record->amount > 0) // ���� �� ������� ������
                    cout << "�� ������ �� ������� " << sell_record->amount << " ������� ������" << endl;
            }
            cout << "ENTER - ��� �������� � ����" << endl;
            while(cin.get() != '\n');
            continue;
        }

        if(menu == 4)
        {
            if(stack->isEmpty())
                cout << "�����" << endl;
            else
            {
                Record * tmp = stack->getTop();
                cout << tmp->type << " " << tmp->amount << " " << (!tmp->type? tmp->cost : 0) << endl; 
                
            }
            while(cin.get() != '\n');
        }
    }while(menu != 2);


    delete stack;
    return 0;
}

int chooseStack() // ������� ������ ���������� �����
{
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
    }while(menu != 1 && menu != 2 && menu != 3);
    return menu;
}


int enterRecord(Stack * stack)
{
    Record * new_record;
    new_record = new Record;
    if(new_record == NULL)
        return 0;
    
    stringstream stream;
    char ctmp;
    int end ,i;
    string input;
    do
    {
        system("cls");
        cout << "������� ������ � ��������� �������" << endl;
        cout << "(S - ������� �������� �������)" << endl;
        cout << "(R - ������� �������� �������)" << endl;
        getline(cin, input, '\n'); // ��������� ������ �� ��������� ������
        end = input.length();
        i = 0;
        while(input[i] != 's' && input[i] != 'S' && input[i] != 'r' && input[i] != 'R' && i < end) // ���� ��� ������
            i++;
        if(i == end) // ���� �� �����
            continue; // ��������� ������ �� ������
        if(input[i] == 's' || input[i] == 'S')
            new_record->type = 1;
        else
            new_record->type = 0;

        while(i != end && !isdigit(input[i])) // ���� �����
            i++;

        if(i == end) // ���� �� �����
            continue; // ��������� ������ �� ������

        stream.clear();
        while(isdigit(input[i])) // ���� �����
            stream << input[i++];
        stream >> new_record->amount;
        

        if(new_record->type == 0)
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
            stream >> new_record->cost;
            
        }
        break;

    }while(1);

    stack->push(new_record);
    return 1;
}

int isInt(string &str)
{
    int end = str.length();
    for(int i = 0; i < end; i++)
    {
        if(!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int isDouble(string &str)
{
    bool dot = 0; // ������� �����
    int end = str.length();
    for(int i = 0; i < end; i++)
    {
        if(!isdigit(str[i]) && str[i] == '.' && dot ) // ���� �� ����� � �� ������ �����
            return 0;
        if(str[i] == '.')
            dot = 1;
    }
    return 1;
}