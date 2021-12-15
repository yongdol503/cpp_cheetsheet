#include <iostream>

using namespace std;

/*
stack
- FILO(선입후출) 형태의 데이터 구조
- 재귀적인 반복 구현시 사용 가능

구현
1. stl에 stack 라이브러리
2. 동적할당 배열로 구현
3. 연결 리스트로 구현
*/

//동적할당 배열 스택 구현
template <typename T>
class stack_arr
{
private:
    int size;
    int length;
    T *arr_ptr;

public:
    stack_arr(int size);
    ~stack_arr();
    int get_length();
    bool is_empty();
    bool is_full();
    void push(const T &data);
    T pop();
};
template <typename T>
stack_arr<T>::stack_arr(int size)
{
    if (size < 1)
        throw out_of_range("음의 크기 존재 불가\n");
    this->size = size;
    this->length = 0;
    this->arr_ptr = new T[this->size];
}

template <typename T>
stack_arr<T>::~stack_arr()
{
    if (this->arr_ptr != NULL)
        delete[] this->arr_ptr;
}

template <typename T>
int stack_arr<T>::get_length()
{
    return this->length;
}

template <typename T>
bool stack_arr<T>::is_empty()
{
    return this->length == 0;
}

template <typename T>
bool stack_arr<T>::is_full()
{
    return this->length == this->size;
}

template <typename T>
void stack_arr<T>::push(const T &data)
{
    if (this->is_full())
        throw out_of_range("이미 가득찬 스택\n");
    else
    {
        *(this->arr_ptr + this->length) = data;
        this->length++;
    }
}

template <typename T>
T stack_arr<T>::pop()
{
    if (this->is_empty())
        throw out_of_range("비어있는 스택\n");
    else
    {
        return this->arr_ptr[--this->length];
    }
}

//연결리스트 스택 구현
template <typename T>
class node
{
public:
    T data;
    node *next;
    node(T _data);
};

template <typename T>
node<T>::node(T _data)
{
    this->data = _data;
    this->next = NULL;
}

template <typename T>
class stack_list
{
private:
    node<T> *front;
    int length;

public:
    stack_list();
    ~stack_list();
    bool is_empty();
    int get_length();
    void push(const T &data);
    T pop();
};

template <typename T>
stack_list<T>::stack_list()
{
    this->front = NULL;
    this->length = 0;
}

template <typename T>
stack_list<T>::~stack_list()
{
    while (!this->is_empty())
        this->pop();
}

template <typename T>
bool stack_list<T>::is_empty()
{
    return this->front == NULL;
}

template <typename T>
int stack_list<T>::get_length()
{
    return this->length;
}

template <typename T>
void stack_list<T>::push(const T &data)
{
    node<T> *tmp = new node<T>(data);
    tmp->next = this->front;
    this->front = tmp;
    this->length++;
}

template <typename T>
T stack_list<T>::pop()
{
    if (this->is_empty())
        throw out_of_range("비어있는 스택\n");
    T data = this->front->data;
    node<T> *next = this->front->next;
    delete this->front;
    this->front = next;
    this->length--;
    return data;
}

int main()
{
    //동적할당 배열로 구현한 스택
    stack_arr<int> stack1(10);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    while (!stack1.is_empty())
        cout << "stack1 pop : " << stack1.pop() << endl;

    stack_arr<char> stack2(10);
    stack2.push('a');
    stack2.push('b');
    stack2.push('c');
    while (!stack2.is_empty())
        cout << "stack2 pop : " << stack2.pop() << endl;

    //연결리스트로 구현한 스택
    stack_list<int> stack3;
    stack3.push(1);
    stack3.push(2);
    stack3.push(3);
    while (!stack3.is_empty())
        cout << "stack3 pop : " << stack3.pop() << endl;

    stack_list<char> stack4;
    stack4.push('a');
    stack4.push('b');
    stack4.push('c');
    while (!stack4.is_empty())
        cout << "stack4 pop : " << stack4.pop() << endl;

    return 0;
}