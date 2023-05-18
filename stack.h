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
        virtual int push(DataType) = 0; // �������� ������� � ����
        virtual DataType * pop() = 0; // ������� ������� �� �����
        virtual int isEmpty() = 0; // �������� ������� �����
        virtual int isFull() = 0; // �������� ������������� 
        virtual DataType *  getTop() = 0; // ������������� ������ � ������� �����
};


class VectorStack: public Stack
{
    private:
        int top;  // ������ ������� �����
        int max_length;   // ������������ ������� �����  
        DataType ** data;  // ��������� �� ������ ���������� �� ������
    public:
        VectorStack(int length = 100) // �����������
        {
            try
            {
                data = new DataType * [length]; // �������� ������ ��� ������ ���������� �� ������
            }
            catch(const exception& e)
                {
                    cerr << e.what() << endl;
            }
            top = -1;
            max_length = length;
        }

        ~VectorStack() // ����������
        {
            top++;
            for(int i = 0; i < top; i++)
                delete data[i]; // ������� ������ �� ��������� �� ������ �����
            delete[] data;
        }

        VectorStack(const VectorStack& other) // ����������� �����������
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
            if(other.top != -1) // ���� � ���������� ������� ���� ������
            {   
                this->top = 0;
                this->push(*other.data[this->top]);
                while(this->top != other.top) // ���� �� �� �����������
                    this->push(*other.data[this->top]); // �������� ������ � ����� � ����� ����
            }
        }

        VectorStack& operator = (const VectorStack& other) // ���������� ��������� ������������(=)
        {
            if(this == &other) // ���� ������ ������������� ��� ����
                return *this; // ���������� ��� ��
            if(this->max_length != other.max_length) // ���� ������ ����������� ������� ���������� �� ������� ������� ����� �������  
            {
                for(int i = 0; i < this->max_length; i++)
                    delete data[i]; // ������� ��� ������ �� ��������� �������
                delete[] data; // ������� ������
                this->max_length = other.max_length; // �������� ����� �������
                try
                {
                    this->data = new DataType * [this->max_length]; // �������� ������ ��� ����� ������
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                }
            }
            this->top = -1; // ������������� ������ � -1 (������ ����)
            if(other.top != -1) // ���� ���� ���������� ������ �� ������
            {   
                this->top = 0;
                this->push(*other.data[this->top]);
                while(this->top != other.top) // ���� �� �� �����������
                    this->push(*other.data[this->top]); // �������� ������ � ����� � ����� ����
            }
            
        }

        int push (DataType new_record) override // �������� ������� � ����
        {
            if(isFull()) // ���� ������ �����
                return 0;
            else
                data[++top] = &new_record; //��������� ������ �� ������ � ������ � ����������� ������ ������� �� 1
            return 1;
        }
        

        DataType * pop() override // ������� �������
        {
            if(isEmpty()) // ���� ���� ����
                return NULL;
            else
                return data[top--]; // ����������� ������� � �������� ������ �������
        }

        int isFull() override // �������� �� �������������
        {
            if(data == NULL)
                return 1;
            return top == max_length - 1; // ���� ������ ������� ����� ����� ����������� ������� �����, �� ���� �����
        }

        int isEmpty() override // �������� ������� �����
        {
            if(data == NULL)
                return 1;
            return top < 0; // ���� �������� ������� < 0, �� ���� ����
        }

        DataType * getTop() override // ������������� ������
        {
            if(isEmpty())
                return NULL;
            return data[top]; // ���������� ������� � ������� �����
        }
};


class ListStack: public Stack
{
    private:
        struct Node
        {
            DataType * data; // ��������� �� ������
            Node * next; // ��������� �� ��������� �������
        } * p_stack; // ��������� �� ������� �����
    
    public:
        ListStack() // �����������
        {
            p_stack = NULL;
        }

        ~ListStack() // ����������
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

        ListStack(const ListStack &other) // ����������� �����������
        {
            if(other.p_stack != NULL) // ���� �������� ������ �� ����
            {
                Node * other_node = other.p_stack; // ��������� �� ���� ���������� ������
                try
                {
                     this->p_stack = new Node; // ������ ����� ����
                    p_stack->data = new DataType; // ������ ����� ������
                    p_stack->next = NULL; //NULL � ��������� �� ��������� �������
                    p_stack->data->amount = other_node->data->amount; // �������� data 
                    p_stack->data->cost = other_node->data->cost; // ...
                    other_node = other_node->next; // ��������� � ���������� ���� ����������� ������
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                    abort();
                }

                Node * new_node = this->p_stack; // ��������� �� ���� ������� � ������� ��������
                while(other_node) // ���� �� ����� �� ����� ����������� ������
                {   
                    try
                    {
                        new_node->next = new Node; // ������ ����� ����
                        new_node = new_node->next; // ��������� � ����� ����
                        new_node->next = NULL; // NULL � ��������� �� ��������� ����
                        new_node->data = new Record; // ������ ����� ������
                        new_node->data->amount = other_node->data->amount; // �������� data
                        new_node->data->cost = other_node->data->cost; // ...
                        other_node = other_node->next; // ��������� � ���������� �������� ����������� ������ 
                    }
                    catch(const exception& e)
                    {
                        cerr << e.what() << endl;
                        abort();
                    }   
                }
            }
        }

        ListStack& operator = (const ListStack &other) // �������� ������������
        {
            if(this == &other) // ���� ����������� ���� �� ������
                return *this;
            
            Node * other_node = other.p_stack; // ��������� �� ���� ����������� ������
            Node * this_node = this->p_stack; // ��������� �� ���� ������ � ������� ��������

            if(other_node != NULL && this_node == NULL) // ���� ���� �� ���������� �� ��� ������ ������
            {
                try
                {
                    this_node = new Node; // ������ ����
                    this_node->data = new Record; // ������ ������
                    this_node->next = NULL; // NULL � ��������� �� ��������� �������
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    abort();
                }
            }

            while(other_node != NULL) // ���� ���� ��� ����������
            {
                // ����������� ������
                this_node->data->amount = other_node->data->amount;
                this_node->data->cost = other_node->data->cost;
                
                if(other_node->next != NULL && this_node->next == NULL) // ���� ��� ���� ��� ����������, �� � ����� ������ ����������� ����
                {
                    try
                    {
                        this_node->next = new Node; // ������ ����� ����
                        this_node->next->data = new Record; // ������ ����� ������
                        this_node->next->next = NULL; // NULL � ��������� �� ������� ����� ����������
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        abort();
                    }
                }
                // ��������� � ��������� �����
                this_node = this_node->next; 
                other_node = other_node->next;
            }

            if(this_node != NULL) // ���� �������� ���������������� ����
            {
                // ������� ��
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
                Node * temp = new Node; // ������ ����� ���� 
                temp->data = &new_record; // ����� ������ � ���� ������
                temp->next = p_stack; // ���������� ��������� �� ������� ������� �����
                p_stack = temp; // ������ ���� ���� �������� �����
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
            Node * p_temp_Node = p_stack; // �������� �� ������� �����
            DataType * p_temp_Datatype = p_stack->data; // ��������� �� ������ � ����
            p_stack = p_stack->next; // �.�. ������ �������, �� �������� ���������� ����������
            delete p_temp_Node; // ������� ���� ������ �������
            return p_temp_Datatype; // ���������� ������ ������ �������
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
            return p_stack->data; // ���������� ������� 
        }
};
 