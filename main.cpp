#include "stack.h"
#include <iostream>
#include <stdio.h>
#include <locale.h>

using namespace std;

int chooseStack();

int main(void)
{
    setlocale(LC_ALL, "Rus");
    char stack_type = chooseStack(); // запоминаем выбор пользователя
    if(stack_type == 3) // если пользователь выбрал "выход"
        return 0;
    Stack * p_stack = NULL;
    if(stack_type == 1) // если стек массивом
        p_stack = new VectorStack(); // создаём массив
    else 
        p_stack = new ListStack; // создаём список

    int menu;
    do
    {
        system("cls");
        cout << "   Меню" << endl;
        cout << "1. Ввод записи" << endl;
        cout << "2. Выход" << endl;

        if(menu == 1)
        {
            enterRecord(p_stack);
        }

    }while(menu != 2);
    
    delete p_stack;

    return 0;
}

int chooseStack() // функция выбора реализации стека
{
    int menu;
    do
    {   
        system("cls");
        cout << "Выберите структуру реализации стека" << endl;
        cout << "1. Массив" << endl;
        cout << "2. Список" << endl;
        cout << "3. Выход" << endl;
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
        cout << "Введите запись о тороговой оперции" << endl;
        cout << "(S - префикс операции продажи)" << endl;
        cout << "(R - префикс операции покупки)" << endl;
        getline(cin, input_record, '\n'); // считываем данные из одной строки
        //input_record.erase(remove(input_record.begin(), input_record.end())) // удаляем все пробелы
        if(input_record[0] != 'R' && input_record[0] != 'r' && input_record[0] != 'S' && input_record[0] != 's') // проверяем первый символ
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

int incorrectInputMenu() // меню при неверном формате входящей записи
{
    char temp;
    cout << "Неверный формат записи" << endl;
    cout << "ENTER - для повторного ввода" << endl;
    cout << "SPACE - для выхода в меню" << endl;
    do
    {cin >> temp;}
    while(temp != '\n' && temp != ' ');

    if(temp == ' ')
        return 0;
    else
        return 1;
}
