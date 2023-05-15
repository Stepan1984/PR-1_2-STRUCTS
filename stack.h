#include "struct.h"
#include <cstdio> // ��� ����������� NULL
using namespace std;

typedef Record DataType;

class Stack
{
    public:
        Stack(){};
        ~Stack(){};
        virtual int push(int amount, double cost) = 0; // ����������
        virtual DataType * pop() = 0; // ����������
        virtual int isEmpty() = 0; // �������� �� �������
        virtual int isFull() = 0; // �������� �� �������������
        virtual DataType *  getTop() = 0; // �������� �������� ��������
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
                data = new DataType * [length]; // ������ ������ ��� ���������� �� ������
                top = -1;
                max_length = length;
            }
            catch(const exception& e)
            {
                cerr << e.what() << endl;
            }
            
        }

        ~VectorStack() // ����������
        {
            top++;
            for(int i = 0; i < top; i++)
                delete data[i]; // ������� ������ �� ������ �� ������� ���������
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
            if(other.top != -1) // ���� ������ �� ������
            {   
                while(this->top != other.top) // ���� �� ����������� ��� ������ � �������
                    this->push(other.data[this->top]->amount, other.data[this->top]->cost); // ����� � ����� ���� ������ �� ����������� �����
            }
        }

        VectorStack& operator = (const VectorStack& other) 
        {
            if(this == &other) // ���� ������ ������������� ��� ����
                return *this;
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
            if(other.top != -1) // ���� ������ �� ������
            {   
                while(this->top != other.top) // ���� �� ����������� ��� ������ � �������
                    this->push(other.data[this->top]->amount, other.data[this->top]->cost); // ����� � ����� ���� ������ �� ����������� �����
            }
            
        }

        int push(int amount, double cost) override
        {
            if(isFull()) // ���� ���� �����
                return 0;
            else
            {
                Record * new_record;
                try
                { 
                    new_record = new Record;
                    new_record->amount = amount;
                    new_record->cost = cost;
                    data[++top] = new_record; //����������� ������ ������� �� 1 � ��������� ������� � ������
                }
                catch(const exception& e)
                {
                    cerr << e.what() << endl;
                }
                return 1;
            }
        }

        DataType * pop() override
        {
            if(isEmpty()) // ���� ���� ����
                return NULL;
            else
                return data[top--]; // ���������� ������� ������� � ��������� ������ �������
        }

        int isFull() override
        {
            if(data == NULL)
                return 1;
            return top == max_length - 1; // 1 - ���� ������ ������� ����� ������������ ������� �����
        }

        int isEmpty() override
        {
            if(data == NULL)
                return 1;
            return top < 0; // 1 - ���� ������ ������� ������ ����
        }

        DataType * getTop() override
        {
            if(isEmpty())
                return NULL;
            return data[top];
        }
};


class ListStack: public Stack
{
    private:
        struct Node
        {
            DataType * data; // ��������� �� ������
            Node * next; // ��������� �� ��������� ������� ������
        } * p_stack; // ��������� �� 1 ������� ������
    
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
            if(other.p_stack != NULL) // ���� ���������� ���� �� ����
            {
                Node * node = other.p_stack; // ��������� �� ������� ����������� �����
                this->p_stack = new Node; // ��������� �� ������� ������ �����
                Node * new_node = p_stack;
                new_node->data = new Record;
                new_node->next = NULL;
                new_node->data->amount = node->data->amount;
                new_node->data->cost = node->data->cost;
                node = node->next; 
                while(node) // ���� �� ����� ������
                {
                    
                    (node->data->amount, node->data->cost);
                    node = node->next;
                }
            }
        }

        int push(int amount, double cost) override
        {
            if(isFull())
                return 0;
            try
            {
                Node * temp = new Node; // ������ ����� ����
                Record * new_record = new Record; // ������ ����� ������
                new_record->amount = amount; // ��������� ������ �������
                new_record->cost = cost; //...
                temp->data = new_record; // ����������� ������ � ������ ����
                temp->next = p_stack; // ���������� ��������� ������ ���� �� ������ ������� ������(��� �� NULL, ���� ������ ������)
                p_stack = temp; // ��������� �� ������ ����������� ����� ������ ����
            }
            catch(const exception& e)
            {
                cerr << e.what() << endl;
            }
            return 1;
        }

        DataType * pop() override
        {   
            Node * p_temp_Node = p_stack; //��������� ��������� �� ����
            DataType * p_temp_Datatype = p_stack->data; //��������� ��������� �� ������
            p_stack = p_stack->next; // ������ ������ ������������� �� 2 �������
            delete p_temp_Node; // ������� ������ �� ����
            return p_temp_Datatype; // ���������� ��������� �� ������
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
            return p_stack->data; // ���������� ��������� �� ������
        }
};
 // ����������� ����������� � �������� ������������