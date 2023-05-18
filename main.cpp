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
    Stack * stack; // создаём указатель на базовый класс
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
                    cout << "Ошибка выделения памяти" << endl;
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
                    cout << "Ошибка выделения памяти" << endl;
                }
                    
        }
    }while(menu != 1 && menu != 2 && menu != 3);
    
    if(menu == 3) // если выбрали "выход"
    {
        system("cls");
        return 0;
    }
    
    do
    {
        system("cls");
        cout << "Меню" << endl;
        cout << "1. Ввод записи" << endl;
        cout << "2. Выход" << endl;
        cin >> menu;
        cin.get();
        if(menu == 1)
        {
            system("cls");
            int result = enterRecord(stack);
            if(result == 0)
            {
                cout << "Операция отклонена" << endl;
            }
            else{
                if(result == -1) // если добавили запись о закупке
                {
                    cout << "Закупили товара на " << stack->getTop()->amount * stack->getTop()->cost << "$" << endl; // выводим общую стоимость закупленной партии
                }
                else // если добавили запись о продаже
                {
                    Record * tmp_record;
                    while(result > 0 && !stack->isEmpty()) // пока в стеке есть записи и не проданы весь требуемый товар
                    {
                        tmp_record = stack->pop(); // достаём из стека запись о товаре
                        if(tmp_record->amount > result) // если товара больше, чем нужно продать
                        {
                            cout << result << " штук по " << tmp_record->cost * 1.2 << " $ каждый на сумму " << tmp_record->cost * result * 1.2 << " $" << endl;
                            tmp_record->amount -= result; // уменьшаем количество товара на складе
                            stack->push(*tmp_record); // отправляем данные обратно в стек
                            result = 0; // обнуляем количество 
                        }
                        else // если количество продаваемой продукции >= количеству товара в данной записи стека о наличии
                        {
                            cout << tmp_record->amount << " штук по " << tmp_record->cost * 1.2 << " $ каждый на сумму " << tmp_record->amount * tmp_record->cost * 1.2 << " $" << endl;
                            result -= tmp_record->amount;
                            delete tmp_record; // удаляем запись, т.к. все товары по этой цене проданы
                        }
                    }

                    if(stack->isEmpty() && result > 0) // если не хватило товара
                        cout << "на складе не хватает " << result << " позиций товара" << endl;
                }   
            }
            cout << "ENTER - для возврата в меню" << endl;
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
    bool operation_type; // тип операции 1 - продажа 0 - закупка
    char ctmp;
    int end , i, amount;
    double cost;
    string input;
    do
    {
        system("cls");
        cout << "Введите запись о тороговой оперции" << endl;
        cout << "(S - префикс операции продажи)" << endl;
        cout << "(R - префикс операции покупки)" << endl;
        getline(cin, input, '\n'); // считываем строку до переноса строки
        end = input.length();
        i = 0;
        while(input[i] != 's' && input[i] != 'S' && input[i] != 'r' && input[i] != 'R' && i < end) // ищем тип записи
            i++;
        if(i == end) // если не нашли
            continue; // повторяем запрос на запись
        if(input[i] == 's' || input[i] == 'S')
            operation_type = 1;
        else
            operation_type = 0;

        while(i != end && !isdigit(input[i])) // ищем цифру
            i++;

        if(i == end) // если не нашли
            continue; // повторяем запрос на запись

        stream.clear();
        while(isdigit(input[i])) // пока цифры
            stream << input[i++];
        stream >> amount;
        

        if(operation_type == 0)
        {
            bool dot = false;
            while(i != end && !isdigit(input[i]) && input[i] != '.') // ищем цифру
                i++;
            if(i == end) // если не нашли
                continue; // повторяем запрос на запись

            int start_index = i; // индекс первого элемента числа

            stream.clear();
            while(isdigit(input[i]) || (input[i] == '.' && !dot)) // если цифра или не перва я точка
            {
                stream << input[i];
                if(input[i] == '.')
                {
                    if(i == start_index) // если точка первый элемент числа
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

    if(operation_type) // если операция продажи
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

