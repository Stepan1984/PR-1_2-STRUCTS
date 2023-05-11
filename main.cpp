#include "stack.h"
#include <iostream>
#include <locale.h>
#include <sstream>

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
                catch(const bad_alloc& e)
                {
                    cerr << e.what() << '\n';
                    cout << "Ошибка выделения памяти" << endl;
                }
                break;
            case 2:
                stack = new ListStack;
                
                    
        }
    }while(menu != 1 && menu != 2 && menu != 3);
    
    if(menu == 3) // если выбрали "выход"
    {
        system("cls");
        return 0;
    }
    
    
    int menu;
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
            if(!enterRecord(stack))
            {
                system("cls");
                cout << "Недостаточно памяти" << endl;
                cout << "ENTER - для возврата в меню" << endl;
                while(cin.get() != '\n');
                continue;
            }

            system("cls");

            if(stack->getTop()->type == 0) // если добавили запись о закупке 
            {
                cout << "Закупили товара на " << stack->getTop()->amount * stack->getTop()->cost << "$" << endl; // выводим общую стоимость закупленной партии
            }
            else // если добавили запись о продаже
            {
                Record * sell_record = stack->pop(); // вытаскиваем запись о продаже из стека
                Record * tmp_record;
                while(sell_record->amount > 0 && !stack->isEmpty()) // пока в стеке есть записи и не проданы все запрошенные грузы
                {
                    tmp_record = stack->pop(); // достаём из стека запись о товаре
                    if(tmp_record->amount > sell_record->amount) // если товара больше, чем нужно продать
                    {
                        cout << sell_record->amount << " штук по " << tmp_record->cost * 1.2 << " $ каждый на сумму " << tmp_record->cost * sell_record->amount * 1.2 << " $" << endl;
                        tmp_record->amount -= sell_record->amount; // уменьшаем количество товара на складе
                        stack->push(tmp_record); // отправляем данные обратно в стек
                        sell_record->amount = 0; // обнуляем количество 
                    }
                    else // если количество продаваемой продукции >= количеству товара в данной записи стека о наличии
                    {
                        cout << tmp_record->amount << " штук по " << tmp_record->cost * 1.2 << " $ каждый на сумму " << tmp_record->amount * tmp_record->cost * 1.2 << " $" << endl;
                        sell_record->amount -= tmp_record->amount;
                        delete tmp_record; // удаляем запись, т.к. все товары по этой цене проданы
                    }
                }

                if(stack->isEmpty() && sell_record->amount > 0) // если не хватило товара
                    cout << "на складе не хватает " << sell_record->amount << " позиций товара" << endl;
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
        cout << "Введите запись о тороговой оперции" << endl;
        cout << "(S - префикс операции продажи)" << endl;
        cout << "(R - префикс операции покупки)" << endl;
        getline(cin, input, '\n'); // считываем строку до опереноса строки
        end = input.length();
        i = 0;
        while(input[i] != 's' && input[i] != 'S' && input[i] != 'r' && input[i] != 'R' && i < end) // ищем тип записи
            i++;
        if(i == end) // если не нашли
            continue; // повторяем запрос на запись
        if(input[i] == 's' || input[i] == 'S')
            new_record->type = 1;
        else
            new_record->type = 0;

        while(i != end && !isdigit(input[i])) // ищем цифру
            i++;

        if(i == end) // если не нашли
            continue; // повторяем запрос на запись

        stream.clear();
        while(isdigit(input[i])) // пока цифры
            stream << input[i++];
        stream >> new_record->amount;
        

        if(new_record->type == 0)
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
            stream >> new_record->cost;
            
        }
        break;

    }while(1);

    stack->push(new_record);
    return 1;
}

