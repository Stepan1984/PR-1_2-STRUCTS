#include "struct.h"
#include <cstdio> // для определения NULL
using namespace std;

typedef Record DataType;

class Stack
{
    public:
        Stack(){};
        ~Stack(){};
        virtual int push(int amount, double cost) = 0; // добавление
        virtual DataType * pop() = 0; // извлечение
        virtual int isEmpty() = 0; // проверка на пустоту
        virtual int isFull() = 0; // проверка на заполненность
        virtual DataType *  getTop() = 0; // просмотр верхнего элемента
};


class VectorStack: public Stack
{
    private:
        int top;  // индекс вершины стека
        int max_length;   // максимальная глубина стека  
        DataType ** data;  // указатель на массив указателей на данные
    public:
        VectorStack(int length = 100) // конструктор
        {
            try
            {
                data = new DataType * [length]; // создаём массив для указателей на данные
                top = -1;
                max_length = length;
            }
            catch(bad_alloc)
            {
                
            }
            
        }

        ~VectorStack() // деструктор
        {
            top++;
            for(int i = 0; i < top; i++)
                delete data[i]; // очищаем память от данных по каждому указателю
            delete[] data;
        }

        int push(int amount, double cost) override
        {
            if(isFull()) // если стек полон
                return 0;
            else
            {
                Record * new_record = new Record;
                new_record->amount = amount;
                new_record->cost = cost;
                data[++top] = new_record; //увеличиваем индекс вершины на 1 и добавляем элемент в массив
                return 1;
            }
        }

        DataType * pop() override
        {
            if(isEmpty()) // если стек пуст
                return NULL;
            else
                return data[top--]; // возвращаем верхний элемент и уменьшаем индекс вершины
        }

        int isFull() override
        {
            if(data == NULL)
                return 1;
            return top == max_length - 1; // 1 - если индекс вершины равен максимальной глубине стека
        }

        int isEmpty() override
        {
            if(data == NULL)
                return 1;
            return top < 0; // 1 - если индекс вершины меньше нуля
        }

        DataType * getTop() override
        {
            if(isEmpty())
                return NULL;
            return data[top];
        }
};
// конструктор копирования и оператор присваивания

class ListStack: public Stack
{
    private:
        struct Node
        {
            DataType * data; // указатель на данные
            Node * next; // указатель на следующий элемент списка
        } * p_stack; // указатель на 1 элемент списка
    
    public:
        ListStack() // конструктор
        {
            p_stack = NULL;
        }

        ~ListStack() // деструктор
        {
            Node * temp;
            while(p_stack)
            {   
                temp = p_stack;
                p_stack = p_stack->next;
                delete temp->data;
                delete temp;
            }
        }

        int push(int amount, double cost) override
        {
            if(isFull())
                return 0;
            Node * temp = new Node; // создаём новый узел
            Record * new_record = new Record;
            new_record->amount = amount;
            new_record->cost = cost;
            temp->data = new_record; // привязываем данные к новому узлу
            temp->next = p_stack; // направляем указатель нового узла на первый элемент списка(или на NULL, если список пустой)
            p_stack = temp; // указателю на список присваиваем адрес нового узла
            return 1;
        }

        DataType * pop() override
        {   
            Node * p_temp_Node = p_stack; //временный указатель на узел
            DataType * p_temp_Datatype = p_stack->data; //временный указатель на данные
            p_stack = p_stack->next; // начало списка устанавливаем на 2 элемент
            delete p_temp_Node; // очищаем память от узла
            return p_temp_Datatype; // возвращаем указатель на данные
        }

        int isFull() override
        {
            Node * tmp;
            tmp = new Node;
            if(tmp == NULL)
            {
                return 1;
            }
            delete tmp;
            return 0;
        }

        int isEmpty() override
        {
            return p_stack == NULL;
        }

        DataType * getTop()
        {
            return p_stack->data; // возвращаем указатель на данные
        }
};
 // конструктор копирования и оператор присваивания