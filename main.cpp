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
    Stack * stack; // создаём указатель на базовый класс
    int stack_type = chooseStack();
    if(stack_type == 3) // если выбрали "выход"
    {
        system("cls");
        return 0;
    }
    else
    {
        if(stack_type == 1) // если выбрали массив
            stack = new VectorStack;
        else // если выбрали список
            stack = new ListStack;
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
                cout << "Закупили товара на " << stack->getTop()->amount * stack->getTop()->cost << endl; // выводим общую стоимость закупленной партии
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
                        cout << "ENTER - для выхода в меню" << endl;
                        tmp_record->amount -= sell_record->amount; // уменьшаем количество товара на складе
                        stack->push(tmp_record); // отправляем данные обратно в стек
                        sell_record->amount = 0; // обнуляем количество 
                        while(cin.get() != '\n');
                        
                    }
                    else // если количество продаваемой продукции >= количеству товара в данной записи стека о наличии
                    {
                        cout << tmp_record->amount << " штук по " << tmp_record->cost * 1.2 << " $ каждый на сумму " << tmp_record->amount * tmp_record->cost * 1.2 << " $" << endl;
                        sell_record->amount -= tmp_record->amount;
                        delete tmp_record; // удаляем запись, т.к. все товары по этой цене проданы
                    }
                }

                if(!stack->isEmpty() && sell_record->amount > 0) // если не хватило товара
                    cout << "на складе не хватает " << sell_record->amount << " позиций товара" << endl;
            }
            cout << "ENTER - для возврата в меню" << endl;
            while(cin.get() != '\n');
            continue;
        }

        if(menu == 4)
        {
            if(stack->isEmpty())
                cout << "Пусто" << endl;
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
    }while(menu != 1 && menu != 2 && menu != 3);
    return menu;
}

/* int enterRecord(Stack * stack)
{
    Record * new_record;
    new_record = new Record;
    if(new_record == NULL)
        return 0;
    
    stringstream stream;
    char ctmp;
    int itmp;
    string stmp;
    do
    {
        system("cls");
        cout << "Введите запись о тороговой оперции" << endl;
        cout << "(S - префикс операции продажи)" << endl;
        cout << "(R - префикс операции покупки)" << endl;

        cin >> ctmp;
        if(ctmp == 'S' || ctmp == 's') // если операция о продаже
            new_record->type = 1;
        else
        {
            if(ctmp == 'R' || ctmp == 'r')
                new_record->type = 0;
            else
            {
                cout << "Некорректный тип записи" << endl;
                cout << "ENTER - для повторного ввода" << endl;
                while(cin.get() != '\n');
                continue;
            }
        }

        cin >> stmp; // считываем количество товара
        cin >> ctmp;
        if(ctmp != '\n' && ctmp != ' ')
            cin.putback(ctmp);
        if(isInt(stmp)) // если встроку передали число
        {
            stream.clear();
            stream << stmp;
            stream >> new_record->amount;

        }
        else
        {
            cout << "Некорректное количество товара" << endl;
            cout << "ENTER - для повторного ввода" << endl;
            while(cin.get() != '\n');
            continue;
        }

        if(!new_record->type) // если запись о закупке
        {
            cin >> stmp; // считываем стоимость одного товара
            cin.get();
            // если входной поток пустой
            //      ничего не считываем
            // иначе
            //      считываем символ 

            if(isDouble(stmp)) // если число типа double
            {
                stream.clear();
                stream << stmp;
                stream >> new_record->cost;
            }
            else
            {
                cout << "Некорректная цена" << endl;
                cout << "ENTER - для повторного ввода" << endl;
                while(cin.get() != '\n');
                continue;
            }
        }

        break;
    }while(1);

    stack->push(new_record); 

    return 1;
} */

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

        while(!isdigit(input[++i])); // ищем цифру

        while(isdigit(input[i])) // пока цифры
            stream << input[i++];
        stream >> new_record->amount;
        stream.clear();

        if(new_record->type == 0)
        {
            bool dot = false;
            while(isdigit(input[i]) || input[i] == '.' && !dot)
            {
                stream << input[i];
                if(input[i] == '.')
                    dot = true;
            }
            stream >> new_record->cost;
        }


    }while(1);

    stack->push(new_record);
}

/* int incorrectInputMenu() // меню при неверном формате входящей записи
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
} */

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
    bool dot = 0; // счётчик точек
    int end = str.length();
    for(int i = 0; i < end; i++)
    {
        if(!isdigit(str[i]) && str[i] == '.' && dot ) // если не цифра и не первая точка
            return 0;
        if(str[i] == '.')
            dot = 1;
    }
    return 1;
}