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
//����˫������ڵ㼰��ʼ������

//�ڱ�ͷ����ڵ�
void insert(node*& head, char num)
{
    if (head == nullptr)
    {
        node* p = new node;
        head = p;
        head->data = (int)num - 48;
        return;
    }//������Ϊ�գ��򴴽�ͷ�ڵ㲢��ͷָ��ָ��ͷ�ڵ�
    else
    {
        node* p = new node;
        head->prev = p;
        p->data = (int)num - 48;
        p->next = head;
        head = p;
    }//������ǿգ��򽫴�������ִ浽һ���½ڵ��ﲢ���ýڵ�����ͷ
}
void insert2(node*& head, int num)
{
    if (head == nullptr)
    {
        node* p = new node;
        head = p;
        head->data = num;
        return;
    }//������Ϊ�գ��򴴽�ͷ�ڵ㲢��ͷָ��ָ��ͷ�ڵ�
    else
    {
        node* p = new node;
        head->prev = p;
        p->data = num;
        p->next = head;
        head = p;
    }//������ǿգ��򽫴�������ִ浽һ���½ڵ��ﲢ���ýڵ�����ͷ
}

//ͨ��ͷβ���ڵ�����������һ����
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

//�Ƚϴ�С
bool find_the_bigger_number(node*& end1, node*& end2)//����false��num1>num2,����num1<=num2
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

//��λ���мӷ�
void addition(node*& head1, node*& head2, node*& result_head, node*& result_end, node*& result_point)
{
    int count = 0;
    int carry = 0;//��λ
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

//��λ���м���
void subtraction(node*& head1, node*& head2, node*& end1, node*& end2, node*& res_head, node*& res_end, node*& res_point, bool& res_sign)
{
    bool bigger = find_the_bigger_number(end1, end2);
    int borrow = 0;//��λ
    int num = 0;//���λ
    int count = 0;//������
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
                }//�жϽ�λ
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
                }//�жϽ�λ
                insert2(res_head, num); count++;
                if (count == 1)res_end = res_head;
                p = p->next;
                q = q->next;
            }
        } while (p);
    }
}

//�������
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
    /*��ɾȥ����ǰ�����*/
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
    /*���Ϊ������*/
    if (head == end && head == point)cout << 0;
    /*ͳ������λ��*/
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


//ɾ�������ͷſռ�
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

/*����������boolֵ��ʾ���ķ��ţ�falseΪ����trueΪ��*/
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
        }//�ж��������operatingΪ����Ϊ�ӣ���֮Ϊ��
        /*��������һ�������洢��������*/
        node* number1_head = nullptr;
        node* number1_end = nullptr;
        node* number1_point = nullptr;//ָ��С����ڵ��ָ��
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
                //ʲô��������
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
                }//����β�ڵ㡣
            }
        }
        if (number1_fra_len == 0)
        {
            insert(number1_head, '.');
            number1_point = number1_head;
        }
        /************��һ�����洢���*************/
        node* number2_head = nullptr;
        node* number2_end = nullptr;
        node* number2_point = nullptr;//ָ��С����ڵ��ָ��
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
                //ʲô��������
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
                }//����β�ڵ㡣
            }
        }
        if (number2_fra_len == 0)
        {
            insert(number2_head, '.');
            number2_point = number2_head;
        }
        /*�ڶ������洢���*/
        make_them_the_same_length(number1_head, number2_head, number1_end, number2_end, number1_int_len, number2_int_len, number1_fra_len, number2_fra_len);
        node* result_head = nullptr; node* result_end = nullptr; node* result_point = nullptr; bool result_sign = false;
        if (!op)//����ӷ�
        {
            if ((!number1_sign) && (!number2_sign))
            {
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//�������ӷ�
            else if (number1_sign && number2_sign)
            {
                result_sign = true;
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//�������ӷ�
            else if ((!number1_sign) && (number2_sign))//�����Ӹ���
            {
                subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, result_point, result_sign);
            }
            else//����������
            {
                subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, result_point, result_sign);
            }
        }
        else//�������
        {
            if ((!number1_sign) && (!number2_sign))
            {
                subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, result_point, result_sign);
            }//����������
            else if (number1_sign && number2_sign)
            {
                subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, result_point, result_sign);
            }//����������
            else if ((!number1_sign) && (number2_sign))
            {
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//����������
            else
            {
                result_sign = true;
                addition(number1_head, number2_head, result_head, result_end, result_point);
            }//����������
        }
        show_list_result(result_head, result_point, result_end, result_sign);
        if (sampleNumber != 1)cout << endl;
        delete_list(number1_head);
        delete_list(number2_head);
        delete_list(result_head);//ɾ�������ͷ��ڴ�
    }
}