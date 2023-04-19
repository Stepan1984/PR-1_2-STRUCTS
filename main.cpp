#include "stack.h"
#include <iostream>
#include <stdio.h>
#include <locale.h>

using namespace std;

int chooseStack();

int main(void)
{
    setlocale(LC_ALL, "Rus");
    char stack_type = chooseStack(); // ���������� ����� ������������
    if(stack_type == 3) // ���� ������������ ������ "�����"
        return 0;
    Stack * p_stack = NULL;
    if(stack_type == 1) // ���� ���� ��������
        p_stack = new VectorStack(); // ������ ������
    else 
        p_stack = new ListStack; // ������ ������

    int menu;
    do
    {
        system("cls");
        cout << "   ����" << endl;
        cout << "1. ���� ������" << endl;
        cout << "2. �����" << endl;

        if(menu == 1)
        {
            enterRecord(p_stack);
        }

    }while(menu != 2);
    
    delete p_stack;

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
    }while(menu < 1 || menu > 3);
    return menu;
}

void enterRecord(Stack * p_stack)
{
    string input_record;
    do
    {
        system("cls");
        cout << "������� ������ � ��������� �������" << endl;
        cout << "(S - ������� �������� �������)" << endl;
        cout << "(R - ������� �������� �������)" << endl;
        getline(cin, input_record, '\n'); // ��������� ������ �� ����� ������
        //input_record.erase(remove(input_record.begin(), input_record.end())) // ������� ��� �������
        if(input_record[0] != 'R' && input_record[0] != 'r' && input_record[0] != 'S' && input_record[0] != 's') // ��������� ������ ������
        {
            if(incorrectInputMenu())
                continue;
            else
                break;
        }
        if(!isdigit(input_record[1]))
        {
            if(incorrectInputMenu())
                continue;
            else
                break;
        }
        
    }while(1);
    return;
}

int incorrectInputMenu() // ���� ��� �������� ������� �������� ������
{
    char temp;
    cout << "�������� ������ ������" << endl;
    cout << "ENTER - ��� ���������� �����" << endl;
    cout << "SPACE - ��� ������ � ����" << endl;
    do
    {cin >> temp;}
    while(temp != '\n' && temp != ' ');

    if(temp == ' ')
        return 0;
    else
        return 1;
}
