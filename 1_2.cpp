#include <iostream>
#include <stdio.h>

using namespace std;

template <typename DataType> // шаблон типа данных
class Stack // базовый класс - стек
{   
    private:
        <DataType>;
    /*
    int top; // количество элементов в стеке
    DataType * data; // указатель на верхний элемент стека
    int maxLength; // максимальное количесто элементов стека
    */

    public:
        /*StackVector(); // конструктор с параметорм, устанавливающий максимальное количество элементов стека
        ~StackVector(); // destructor */
        virtual int Empty() const = 0; // проверка на пустоту
        virtual int Full() const = 0; // проверка на полноту
        virtual DataType Top () const = 0; // неразрушающее чтение
        virtual DataType Pop () = 0; // извлечь из стека
        virtual int Push () = 0; // поместить в стек 
}; 

class StackVector : public Stack
{
    private:
        int top; // количество элементов в стеке
        <DataType> * array; // указатель на массив
        int maxLength; // максимальное количесто элементов стека
    public:
        StackVector() // конструктор
        {
            array = (<DataType> *) malloc(<DataType>); // выделяем память под массив-стек
            if(array == NULL)
            {
                perror("Ошибка выделения память");
                /* уничтожение объекта класса */
            }
        }

        int Empty() const override // проверка на пустоту
        {
            if(top == 0) // если значение вершины равно 0
                return 1; // стек пустой
            else
                return 0;
        }

        int Full() const override // проверка полноты стека
        {
            if(top != maxLength) // если значение вершины не равно значению максимальной длины
                return 1;
            else
                return 0;
        }

        DataType Top() const override // неразрушающее чтение
        {
            if(!Empty()) // если стек не пуст
                return array[top]; // возвращаем верхний элемент
            /* возврат при пустом стеке???? */
        }

        DataType Pop() override //извлечение из стека
        {
            if(!Empty())
            {
                DataType ;
                data = 
            }
        }

};

class Sell // запись о продаже
{
    private:
        int amount;
    public:
        Sell()
        {
            amount = 0;
        }

};
class Purchase // запись о закупке
{
    private:
        int amount; // количество товара
        int price; // цена за 1шт
    public:
        Purchase()
        {
            amount = 0;
            price = 0;
        }
}