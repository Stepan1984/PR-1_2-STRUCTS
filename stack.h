#include "struct.h"
#include <iostream>
#include <cstdio>
using namespace std;

typedef Record DataType;

class Stack
{
    public:
        Stack(){};
        ~Stack(){};
        virtual int push(DataType) = 0; // добавить элемент в стек
        virtual DataType * pop() = 0; // достать элемент из стека
        virtual int isEmpty() = 0; // проверка пустоты стека
        virtual int isFull() = 0; // проверка заполненности 
        virtual DataType *  getTop() = 0; // неразрушающее чтение с вершины стека
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
                data = new DataType * [length]; // выделяем память под массив указателей на данные
            }
            catch(const exception& e)
                {
                    cerr << e.what() << endl;
            }
            top = -1;
            max_length = length;
        }

        ~VectorStack() // деструктор
        {
            top++;
            for(int i = 0; i < top; i++)
                delete data[i]; // удаляем данные по указетелю из ячейки стека
            delete[] data;
        }

        VectorStack(const VectorStack& other) // конструктор копирования
        {
            this->max_length = other.max_length;
            this->top = -1;
            try
                {
                    this->data = new DataType * [this->max_length];
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                }
            if(other.top != -1) // если в копируемом объекте есть данные
            {   
                this->top = 0;
                this->push(*other.data[this->top]);
                while(this->top != other.top) // пока всё не скопировали
                    this->push(*other.data[this->top]); // копируем данные и кладём в новый стек
            }
        }

        VectorStack& operator = (const VectorStack& other) // перегрузка оператора присваивания(=)
        {
            if(this == &other) // если объект присваивается сам себе
                return *this; // возвращаем его же
            if(this->max_length != other.max_length) // если размер копируемого массива отличается от размера массива этого объекта  
            {
                for(int i = 0; i < this->max_length; i++)
                    delete data[i]; // удаляем все данные из нынешнего массива
                delete[] data; // удаляем массив
                this->max_length = other.max_length; // копируем длину массива
                try
                {
                    this->data = new DataType * [this->max_length]; // выделяем память под новый массив
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                }
            }
            this->top = -1; // устанавливаем индекс в -1 (массив пуст)
            if(other.top != -1) // если есть копируемый массив не пустой
            {   
                this->top = 0;
                this->push(*other.data[this->top]);
                while(this->top != other.top) // пока всё не скопировали
                    this->push(*other.data[this->top]); // копируем данные и кладём в новый стек
            }
            
        }

        int push (DataType new_record) override // положить элемент в стек
        {
            if(isFull()) // если массив полон
                return 0;
            else
                data[++top] = &new_record; //добавляем ссылку на данные в массив и увеличиваем индекс вершины на 1
            return 1;
        }
        

        DataType * pop() override // достать элемент
        {
            if(isEmpty()) // если стек пуст
                return NULL;
            else
                return data[top--]; // вытаскиваем элемент и уменьшая индекс врешины
        }

        int isFull() override // проверка на заполненность
        {
            if(data == NULL)
                return 1;
            return top == max_length - 1; // если индекс вершины стека равен максималной глубине стека, то стек полон
        }

        int isEmpty() override // проверка пустоты стека
        {
            if(data == NULL)
                return 1;
            return top < 0; // если значение вершины < 0, то стек пуст
        }

        DataType * getTop() override // неразрушающее чтение
        {
            if(isEmpty())
                return NULL;
            return data[top]; // возвращаем элемент с вершины стека
        }
};


class ListStack: public Stack
{
    private:
        struct Node
        {
            DataType * data; // указатель на данные
            Node * next; // указатель на следующий элемент
        } * p_stack; // указатель на вершину стека
    
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

        ListStack(const ListStack &other) // конструктор копирования
        {
            if(other.p_stack != NULL) // если копируем список не пуст
            {
                Node * other_node = other.p_stack; // указатель на узел копируемго списка
                try
                {
                     this->p_stack = new Node; // создаём новый узел
                    p_stack->data = new DataType; // создаём новую запись
                    p_stack->next = NULL; //NULL в указатель на следующий элемент
                    p_stack->data->amount = other_node->data->amount; // копируем data 
                    p_stack->data->cost = other_node->data->cost; // ...
                    other_node = other_node->next; // переходим к следующему узлу копируемого списка
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                    abort();
                }

                Node * new_node = this->p_stack; // указатель на узел объекта в который копируем
                while(other_node) // пока не дошли до конца копируемого списка
                {   
                    try
                    {
                        new_node->next = new Node; // создаём новый узел
                        new_node = new_node->next; // переходим к этому узлу
                        new_node->next = NULL; // NULL в указатель на слудующий узел
                        new_node->data = new Record; // создаём новую запись
                        new_node->data->amount = other_node->data->amount; // копируем data
                        new_node->data->cost = other_node->data->cost; // ...
                        other_node = other_node->next; // переходим к следующему элементу копируемого списка 
                    }
                    catch(const exception& e)
                    {
                        cerr << e.what() << endl;
                        abort();
                    }   
                }
            }
        }

        ListStack& operator = (const ListStack &other) // оператор присваивания
        {
            if(this == &other) // если присваиваем этот же объект
                return *this;
            
            Node * other_node = other.p_stack; // указатель на узел копируемого списка
            Node * this_node = this->p_stack; // указатель на узел списка в который копируют

            if(other_node != NULL && this_node == NULL) // если есть то копировать но наш список пустой
            {
                try
                {
                    this_node = new Node; // создаём узел
                    this_node->data = new Record; // создаём запись
                    this_node->next = NULL; // NULL в указатель на следующий элемент
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    abort();
                }
            }

            while(other_node != NULL) // пока есть что копировать
            {
                // копирование данных
                this_node->data->amount = other_node->data->amount;
                this_node->data->cost = other_node->data->cost;
                
                if(other_node->next != NULL && this_node->next == NULL) // если ещё есть что копировать, но в нашем списке закончились узлы
                {
                    try
                    {
                        this_node->next = new Node; // создаём новый узел
                        this_node->next->data = new Record; // создаём новую запись
                        this_node->next->next = NULL; // NULL в указатель на элемент после последнего
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        abort();
                    }
                }
                // переходим к следующим узлам
                this_node = this_node->next; 
                other_node = other_node->next;
            }

            if(this_node != NULL) // если остались неиспользованные узлы
            {
                // удаляем их
                Node * tmp;
                while (this_node)
                {
                    tmp = this_node;
                    this_node = this_node->next;
                    delete tmp->data;
                    delete tmp;
                }
            }
        
        }
        
        int push(DataType new_record) override
        {
            if(isFull())
                return 0;
            try
            {
                Node * temp = new Node; // создаём новый узел 
                temp->data = &new_record; // кладём данные в узел списка
                temp->next = p_stack; // направляем указатель на верхний элемент стека
                p_stack = temp; // делаем этот узел вершиной стека
            }
            catch(const exception& e)
            {
                cerr << e.what() << endl;
                abort();
            }
            return 1;
        }

        DataType * pop() override
        {   
            Node * p_temp_Node = p_stack; // указтель на вершину стека
            DataType * p_temp_Datatype = p_stack->data; // указатель на данные в узле
            p_stack = p_stack->next; // т.к. достаём элемент, то вершиной становится предыдущий
            delete p_temp_Node; // удаляем узел бывшей вершины
            return p_temp_Datatype; // возвращаем данные бывшей вершины
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
            return p_stack->data; // возвращаем вершину 
        }
};
 