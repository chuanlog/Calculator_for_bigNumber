#include <iostream>
#include <string>
using namespace std;

// 定义链表节点
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 将字符串表示的数字转换为链表
ListNode* stringToListNode(string num) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    for (int i = num.size() - 1; i >= 0; --i) {
        int digit = num[i] - '0';
        current->next = new ListNode(digit);
        current = current->next;
    }
    return dummy->next;
}

// 将链表表示的数字转换为字符串
string listNodeToString(ListNode* l) {
    string result;
    while (l) {
        result.insert(result.begin(), l->val + '0');
        l = l->next;
    }
    return result;
}

// 大整数相加
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
        carry = sum / 10;
        current->next = new ListNode(sum % 10);
        current = current->next;
        l1 = l1 ? l1->next : NULL;
        l2 = l2 ? l2->next : NULL;
    }
    return dummy->next;
}

int main() {
    string num1 = "123456789";
    string num2 = "987654321";

    ListNode* l1 = stringToListNode(num1);
    ListNode* l2 = stringToListNode(num2);

    ListNode* result = addTwoNumbers(l1, l2);

    cout << "Result: " << listNodeToString(result) << endl;

    return 0;
}
