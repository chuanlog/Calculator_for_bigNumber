#include<iostream>
#include<string>
using namespace std;

struct node
{
    int data;
    node* prev;
    node* next;
    node()
    {
        data = 0;
        prev = nullptr;
        next = nullptr;
    }
};
//定义双向链表节点及初始化函数

//在表头插入节点
void insert(node*& head, char num)
{
    if (head == nullptr)
    {
        node* p = new node;
        head = p;
        head->data = (int)num - 48;
        return;
    }//若链表为空，则创建头节点并将头指针指向头节点
    else
    {
        node* p = new node;
        head->prev = p;
        p->data = (int)num - 48;
        p->next = head;
        head = p;
    }//若链表非空，则将传入的数字存到一个新节点里并将该节点插入表头
}
void insert2(node*& head, int num)
{
    if (head == nullptr)
    {
        node* p = new node;
        head = p;
        head->data = num;
        return;
    }//若链表为空，则创建头节点并将头指针指向头节点
    else
    {
        node* p = new node;
        head->prev = p;
        p->data = num;
        p->next = head;
        head = p;
    }//若链表非空，则将传入的数字存到一个新节点里并将该节点插入表头
}

//通过头尾补节点让两个链表一样长
void make_them_the_same_length(node*& head1, node*& head2, node*& end1, node*& end2, int int_len1, int int_len2, int fra_len1, int fra_len2)
{
    if (int_len1 > int_len2)
    {
        int dif = int_len1 - int_len2;
        int i;
        for (i = 0; i < dif; i++)
        {
            node* p = new node;
            p->prev = end2;
            end2->next = p;
            end2 = p;
        }
    }
    else
    {
        int dif = int_len2 - int_len1;
        int i;
        for (i = 0; i < dif; i++)
        {
            node* p = new node;
            p->prev = end1;
            end1->next = p;
            end1 = p;
        }
    }
    if (fra_len1 > fra_len2)
    {
        int dat = fra_len1 - fra_len2;
        int i;
        for (i = 0; i < dat; i++)
        {
            node* p = new node;
            p->next = head2;
            head2->prev = p;
            head2 = p;
        }
    }
    else
    {
        int dat = fra_len2 - fra_len1;
        int i;
        for (i = 0; i < dat; i++)
        {
            node* p = new node;
            p->next = head1;
            head1->prev = p;
            head1 = p;
        }
    }
}

//比较大小
bool find_the_bigger_number(node*& end1, node*& end2)//返回false则num1>num2,否则num1<=num2
{
    node* p = end1;
    node* q = end2;
    bool bigger = false;
    do
    {
        if (p->data > q->data)
        {
            bigger = false; break;
        }
        else if (p->data < q->data)
        {
            bigger = true; break;
        }
        else if (p->data == q->data)
        {
            p = p->prev;
            q = q->prev;
        }
    } while (p);
    return bigger;
}

//逐位进行加法
void addition(node*& head1, node*& head2, node*& result_head, node*& result_end, node*& result_point)
{
    int count = 0;
    int carry = 0;//进位
    int num = 0;
    node* p = head1;
    node* q = head2;
    do
    {
        if (p->data == -2 && q->data == -2)
        {
            insert(result_head, '.');
            result_point = result_head; count++;
            if (count == 1)result_end = result_head;
            p = p->next;
            q = q->next;
        }
        else
        {
            num = p->data + q->data + carry;
            if (num > 10)
            {
                carry = (num - num % 10) / 10;
                num = num % 10;
            }
            else if (num == 10)
            {
                num = 0;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            insert2(result_head, num); count++;
            if (count == 1)result_end = result_head;
            p = p->next;
            q = q->next;
        }
    } while (p);
    if (carry)insert2(result_head, carry);
}

//逐位进行减法
void subtraction(node*& head1, node*& head2, node*& end1, node*& end2, node*& res_head, node*& res_end, node*& res_point, bool& res_sign)
{
    bool bigger = find_the_bigger_number(end1, end2);
    int borrow = 0;//借位
    int num = 0;//结果位
    int count = 0;//计数器
    node* p = head1; node* q = head2;
    if (!bigger)//num1>num2
    {
        do
        {
            if (p->data == -2)
            {
                p = p->next;
                q = q->next;
                insert(res_head, '.'); count++;
                res_point = res_head;
                if (count == 1)res_end = res_head;
            }
            else
            {
                num = p->data - q->data - borrow;
                if (num < 0)
                {
                    borrow = 1;
                    num += 10;
                }
                else
                {
                    borrow = 0;
                }//判断进位
                insert2(res_head, num); count++;
                if (count == 1)res_end = res_head;
                p = p->next;
                q = q->next;
            }
        } while (p);
    }
    else//num2>num1
    {
        res_sign = true;
        do
        {
            if (p->data == -2)
            {
                p = p->next;
                q = q->next;
                insert(res_head, '.'); count++;
                res_point = res_head;
                if (count == 1)res_end = res_head;

            }
            else
            {
                num = q->data - p->data - borrow;
                if (num < 0)
                {
                    borrow = 1;
                    num += 10;
                }
                else
                {
                    borrow = 0;
                }//判断借位
                insert2(res_head, num); count++;
                if (count == 1)res_end = res_head;
                p = p->next;
                q = q->next;
            }
        } while (p);
    }
}

//输出链表
void showList_forTest(node*& end, bool sign)
{
    node* p = end;
    if (sign)cout << '-';
    while (p)
    {
        if (p->data == -2)
        {
            cout << '.';
        }
        else
        {
            cout << p->data;
        }
        p = p->prev;
    }
    cout << endl;
}
void showList_forTest2(node*& head, bool sign)
{
    if (sign)cout << '-';
    node* p = head;
    while (p)
    {
        if (p->data == -2)
        {
            cout << '.';
        }
        else
        {
            cout << p->data;
        }
        p = p->next;
    }
    cout << endl;
}
void show_list_int(node*& head, node*& point, int len)
{
    node* p = head;
    int n = len % 3;
    int count = 0;
    while (count < n)
    {
        cout << p->data;
        count++;
        p = p->next;
    }
    if (len > 3 && n != 0)cout << ',';
    count = 0;
    while (p != point)
    {
        cout << p->data; count++;
        if (count % 3 == 0 && count != len - n)cout << ',';
        p = p->next;
    }
}
void show_list_fra(node*& point)
{
    cout << '.';
    node* p = point->next;
    while (p)
    {
        cout << p->data;
        p = p->next;
    }
}
void show_list_result(node*& head, node*& point, node*& end, bool sign)
{
    if (sign)cout << '-';
    /*先删去链表前后的零*/
    node* p = head;
    node* q = end;
    while (p->data == 0)
    {
        head = p->next;
        head->prev = nullptr;
        delete p;
        p = head;
    }
    while (q->data == 0)
    {
        end = q->prev;
        end->next = nullptr;
        delete q;
        q = end;
    }
    /*结果为零的情况*/
    if (head == end && head == point)cout << 0;
    /*统计整数位数*/
    int len = 0;
    p = head;
    while (p != point)
    {
        len++;
        p = p->next;
    }
    show_list_int(head, point, len);
    if (point->next != nullptr)
    {
        show_list_fra(point);
    }
}


//删除链表释放空间
void delete_list(node*& head)
{
    node* p = head;
    node* q = head;
    head = nullptr;
    while (q->next)
    {
        q = p->next;
        q->prev = nullptr;
        delete p;
        p = q;
    }
    delete q;
}

/*本程序中以bool值表示数的符号，false为正，true为负*/
int main()
{
    int sampleNumber;
    cin >> sampleNumber;
    for (; sampleNumber; sampleNumber--)
    {
        char operation = 0;
        bool op = false;
        cin >> operation;
        char ignore = getchar();
        if (operation == '-')
        {
            op = true;
        }//判断运算符，operating为假则为加，反之为减
        /*下面读入第一个数并存储于链表中*/
        node* number1_head = nullptr;
        node* number1_end = nullptr;
        node* number1_point = nullptr;//指向小数点节点的指针
        int number1_int_len = 0;
        int number1_fra_len = 0;
        bool number1_sign = false;
        string number1;
        cin >> number1;
        const char* num1 = &number1[0];
        int len1 = strlen(num1);
        int i = 0;
        char temp_num;
        for (i = 0; i < len1; i++)
        {
            temp_num = number1[i];
            if (temp_num == '-')
            {
                number1_sign = true;
            }
            else if (temp_num == ',' || temp_num == '\12')
            {
                //什么都不用做
            }
            else if (temp_num == '.')
            {
                insert(number1_head, temp_num);
                number1_point = number1_head;
            }
            else
            {
                insert(number1_head, temp_num);
                if (number1_point == nullptr)
                {
                    number1_int_len++;
                }
                else
                {
                    number1_fra_len++;
                }
                if (number1_head->next == nullptr)
                {
                    number1_end = number1_head;
                }//创建尾节点。
            }
        }
        if (number1_fra_len == 0)
        {
            insert(number1_head, '.');
            number1_point = number1_head;
        }
        /************第一个数存储完成*************/
        node* number2_head = nullptr;
        node* number2_end = nullptr;
        node* number2_point = nullptr;//指向小数点节点的指针
        int number2_int_len = 0;
        int number2_fra_len = 0;
        bool number2_sign = false;
        string number2;
        cin >> number2;
        const char* num2 = &number2[0];
        int len2 = strlen(num2);
        for (i = 0; i < len2; i++)
        {
            temp_num = number2[i];
            if (temp_num == '-')
            {
                number2_sign = true;
            }
            else if (temp_num == ',' || temp_num == '\12')
            {
                //什么都不用做
            }
            else if (temp_num == '.')
            {
                insert(number2_head, temp_num);
                number2_point = number2_head;
            }
            else
            {
                insert(number2_head, temp_num);
                if (number2_point == nullptr)
                {
                    number2_int_len++;
                }
                else
                {
                    number2_fra_len++;
                }
                if (number2_head->next == nullptr)
                {
                    number2_end = number2_head;
                }//创建尾节点。
            }
        }
        if (number2_fra_len == 0)
        {
            insert(number2_head, '.');
            number2_point = number2_head;
        }
        /*第二个数存储完成*/
        make_them_the_same_length(number1_head, number2_head, number1_end, number2_end, number1_int_len, number2_int_len, number1_fra_len, number2_fra_len);
        node* result_head = nullptr; node* result_end = nullptr; node* result_point = nullptr; bool result_sign = false;
        if (!op)//计算加法
        {
            if ((!number1_sign) && (!number2_sign))
            {
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//两正数加法
            else if (number1_sign && number2_sign)
            {
                result_sign = true;
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//两负数加法
            else if ((!number1_sign) && (number2_sign))//正数加负数
            {
                subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, result_point, result_sign);
            }
            else//负数加正数
            {
                subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, result_point, result_sign);
            }
        }
        else//计算减法
        {
            if ((!number1_sign) && (!number2_sign))
            {
                subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, result_point, result_sign);
            }//两正数减法
            else if (number1_sign && number2_sign)
            {
                subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, result_point, result_sign);
            }//两负数减法
            else if ((!number1_sign) && (number2_sign))
            {
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//正数减负数
            else
            {
                result_sign = true;
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//负数减正数
        }
        show_list_result(result_head, result_point, result_end, result_sign);
        if (sampleNumber != 1)cout << endl;
        delete_list(number1_head);
        delete_list(number2_head);
        delete_list(result_head);//删除链表，释放内存
    }
}