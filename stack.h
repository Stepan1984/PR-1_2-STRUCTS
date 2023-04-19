#include <stdio.h>
#include "struct.h"
using namespace std;

typedef Record DataType;

class Stack
{
    private:
        //��������� _ � ����� ��������������
    public:
        Stack(){};
        ~Stack(){};
        virtual int push(DataType * x) = 0; // ����������
        virtual DataType * pop() = 0; // ����������
        virtual int isEmpty() = 0; // �������� �� �������
        virtual DataType *  getTop() = 0; // �������� �������� ��������
};
//���������� ����� ����������� ����������� ����������� � �������� ������������

class VectorStack: public Stack
{
    private:
        int top;  // ������ ������� �����
        int max_length;   // ������������ ������� �����  
        DataType ** data;  // ��������� �� ������ ���������� �� ������
    public:
        VectorStack(int length = 100) // �����������
        {
            data = new DataType *[length]; // ������ ����������� ������ ��� ���������� �� ������
            top = -1;
            max_length = length;
        }

        ~VectorStack() // ����������
        {
            top++;
            for(int i = 0; i < top; i++)
                delete data[i]; // ������� ������ �� ������ �� ������� ���������
            delete[] data;
        }

        int push(DataType * x) override
        {
            if(isFull()) // ���� ���� �����
                return 0;
            else
            {
                data[++top] = x; //����������� ������ ������� �� 1 � ��������� ������� � ������
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

        int isFull()
        {
            return top == max_length - 1; // 1 - ���� ������ ������� ����� ������������ ������� �����
        }

        int isEmpty() override
        {
            return top < 0; // 1 - ���� ������ ������� ������ ����
        }

        DataType * getTop() override
        {
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

        int push(DataType * x) override
        {
            Node * temp = new Node; // ������ ����� ����
            if(temp == NULL) // ���� �� ������� ������� ���� 
                return 0;
            temp->data = x; // ����������� ������ � ������ ����
            temp->next = p_stack; // ���������� ��������� ������ ���� �� ������ ������� ������(��� �� NULL, ���� ������ ������)
            p_stack = temp; // ��������� �� ������ ����������� ����� ������ ����
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

        int isEmpty() override
        {
            return p_stack == NULL;
        }

        DataType * getTop()
        {
            return p_stack->data; // ���������� ��������� �� ������
        }
};
//���������� ����� ����������� ����������� ����������� � �������� ������������