#include "stack.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
    char stack_type = chooseStack(); // запоминаем выбор пользователя
    if(stack_type == 3) // если пользователь выбрал "выход"
        return 0;
    if(stack_type == 1)
        typedef VectorStack StackType;
    else
        typedef ListStack StackType;
    
    

        

        
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

