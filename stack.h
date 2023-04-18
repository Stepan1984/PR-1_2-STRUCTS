#include <stdio.h>
using namespace std;

typedef int DataType;

class Stack
{
    private:
        //Добавлять _ в конце идентификатора
    public:
        Stack(){};
        ~Stack(){};
        virtual int push(DataType x) = 0; // добавление
        virtual DataType pop() = 0; // извлечение
        //virtual int isFull() = 0; // проверка на полноту
        virtual int isEmpty() = 0; // проверка на пустоту
        virtual DataType getTop() = 0; // просмотр верхнего элемента
};
//необходимо также перегрузить конструктор копирования и операцию присваивания

class VectorStack: public Stack
{
    private:
        int top;  // индекс вершины стека
        int max_length;   // максимальная глубина стека  
        DataType * data;  // указатель на массив с данными
    public:
        VectorStack(int length = 100) // конструктор
        {
            data = new DataType[length];
            top = -1;
            max_length = length;
        }

        ~VectorStack() // деструктор
        {
            delete[] data;
        }

        int push(DataType x) override
        {
            if(isFull()) // если стек полон
                return 0;
            else
            {
                top++; // увеличиваем индекс вершины на 1
                data[top] = x; // добавляем элемент в массив
                return 1;
            }
        }

        DataType pop() override
        {
            if(isEmpty()) // если стек пуст
                return 0;
            else
                return data[top--]; // возвращаем верхний элемент и уменьшаем индекс вершины
        }

        int isFull()
        {
            return top == max_length - 1; // 1 - если индекс вершины равен максимальной глубине стека
        }

        int isEmpty() override
        {
            return top < 0; // 1 - если индекс вершины меньше нуля
        }

        DataType getTop() override
        {
            return data[top];
        }
};

class ListStack: public Stack
{
    private:
        struct node
        {
            DataType data; // данные
            node * next; // указатель на следующий элемент списка
        } * p_stack; // указатель на 1 элемент списка
    
    public:
        ListStack() // конструктор
        {
            p_stack = NULL;
        }

        ~ListStack() // деструктор
        {
            node * temp;
            while(p_stack)
            {   
                temp = p_stack;
                p_stack = p_stack->next;
                delete temp;
            }
        }

        int push(DataType x) override
        {
            node * temp = new node; // создаём новый узел
            if(temp == NULL) 
                return 0;
            temp->data = x;
            temp->next = p_stack;
            p_stack = temp;
            return 1;
        }

        DataType pop() override
        {   
            node * del = p_stack;
            DataType temp = p_stack->data;
            p_stack = p_stack->next;
            delete del;
            return temp;
        }

        int isEmpty() override
        {
            return p_stack == NULL;
        }

        DataType getTop()
        {
            return p_stack->data;
        }
};
//необходимо также перегрузить конструктор копирования и операцию присваивания