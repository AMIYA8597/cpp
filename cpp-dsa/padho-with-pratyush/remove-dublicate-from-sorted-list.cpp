83. Remove Duplicates from Sorted List
 
Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

 

Example 1:


Input: head = [1,1,2]
Output: [1,2]
Example 2:


Input: head = [1,1,2,3,3]
Output: [1,2,3]
 

Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.


















/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }

        return head;
    }
    
};





























/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == nullptr) return head;
        ListNode* dummy  = new ListNode(-1);
        ListNode* curr = dummy;
        int nd = head->val;
        curr->next = new ListNode(nd);
        curr = curr->next;
        while(head != nullptr){
            int num = head->val;
            if (nd != num){
                curr->next = new ListNode(num);
                nd = num;
                curr = curr->next;
            }
            head = head->next;
        }
        return dummy->next;
    }
};





























/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution 
{
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        if(head == NULL) 
        {
            return NULL;
        }

//in this way both prev and curr will adjacent to eachother
        ListNode* prev = head;
        ListNode* curr = head -> next;

        while (curr != NULL)
        {
            if(prev -> val == curr -> val)
            {
                prev -> next = curr -> next;
                curr -> next = NULL;
                delete curr;
                curr = prev -> next;
            }
            else
            {
                prev = curr;
                curr = curr -> next;
            }
        }
        return head;
    }
};

























/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* h = head;
        while(h){
            if(h->next and h->val==h->next->val){
                h->next = h->next->next;
            }else{
                h = h->next;
            }
        }
        return head;
    }
};















/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        set<int> st;
        ListNode* temp = head;
        while(temp){
            st.insert(temp->val);
            temp = temp->next;
        }
ListNode* newHead = nullptr;
ListNode* tail = nullptr;

for (auto it : st) {
    ListNode* newNode = new ListNode(it);
    if (!newHead) newHead = tail = newNode;
    else {
        tail->next = newNode;
        tail = tail->next;
    }
}
return newHead;

    }
};









