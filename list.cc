#include <stdio.h>

#include <vector>


using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

int main() {
	auto ConstructList = [] (const vector<int>& v) -> ListNode* {
		ListNode dummy(-1);
		ListNode* prev = &dummy;
		for(auto i : v) {
			prev->next = new ListNode(i);
			prev = prev->next;
		}
		return dummy.next;
	};

	auto PrintList = [](ListNode* head) {
		ListNode* cur = head;
		while(cur != nullptr) {
			printf("%d -> ", cur->val);
			cur = cur->next;
		}
		printf("NULL\n");
	};


	auto ReverseBetween = [](ListNode* head, int m, int n) -> ListNode* {
		ListNode dummy(-1);
		ListNode* prev = &dummy;
		dummy.next = head;

		for (int i = 0; i < m - 1; ++i) {
			prev = prev->next;
		}

		ListNode* head2 = prev;
		prev = prev->next;
		ListNode* cur = prev->next;

		for (int i = m; i < n; ++i) {
			prev->next = cur->next;
			cur->next = head2->next;
			head2->next = cur;
			cur = prev->next;
		}
		return dummy.next;

	};

	auto ListAdd = [](ListNode* lhs, ListNode* rhs) ->ListNode* {
		ListNode dummy(-1);
		ListNode *prev = &dummy;
		int carry = 0;

		for (ListNode *pa = lhs, *pb = rhs;
				pa != nullptr || pb != nullptr;
				prev = prev->next, pa = pa->next, pb = pb->next) {
			const int ai = pa == nullptr ? 0 : pa->val;
			const int bi = pb == nullptr ? 0 : pb->val;
			const int sum = ai + bi + carry;
			carry = sum / 10;
			prev->next = new ListNode(sum % 10);
		}

		if (carry > 0) {
			prev->next = new ListNode(carry);
		}
		return dummy.next;

	};

	auto ListPartition = [](ListNode* head, int num) ->ListNode* {
		ListNode lhead(-1), rhead(-1);
		ListNode *lhs = &lhead, *rhs = &rhead, *cur = head;
		for(; cur != nullptr; cur = cur->next) {
			if(cur->val < num) {
				lhs->next = cur;
				lhs = lhs->next;
			} else {
				rhs->next = cur;
				rhs = rhs->next;
			}
		}
		lhs->next = rhead.next;
		rhs->next = nullptr;
		return lhead.next;
	};

	auto ListRemoveDup = [](ListNode* head) -> ListNode* {
		if (head == nullptr) return head;
		for (ListNode *tail = head, *cur = head->next; cur != nullptr; ) {
			if (tail->val == cur->val) {
				tail->next = cur->next;
				ListNode* toBeDeleted = cur;
				cur = cur->next;
				delete toBeDeleted;
			} else {
				tail = cur;
				cur = cur->next;
			}
		}
		return head;
	};

	auto ListRemoveDup2 = [](ListNode* head) -> ListNode* {
		if (head == nullptr) return head;
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *prev = &dummy;
		for (ListNode *cur = head->next; cur != nullptr;) {
			if (prev->next->val == cur->val) {
				int val = prev->next->val;
				delete prev->next;
				while(cur != nullptr && cur->val == val) {
					ListNode* toBeDeleted = cur;
					cur = cur->next;
					delete toBeDeleted;
				}
				if(cur == nullptr)  {
					prev->next = nullptr;
					break;
				}
				else {
					prev->next = cur;
					cur = cur->next;
				}
			} else {
				prev = prev->next;
				cur = cur->next;
			}
		}
		return dummy.next;
	};

	auto ListRotate = [](ListNode* head, int k) ->ListNode* {
		if (head == nullptr) {return head;}
		int len = 0; 
		ListNode *prev, *cur;
		for (cur = head; cur != nullptr; cur = cur->next) {
			++len;
			prev = cur;
		}
		k %= len;
		prev->next = head;
		cur = head;

		for (int i = 0; i < len - k; ++i) {
			prev = cur;
			cur = cur->next;
		}
		prev->next = nullptr;
		return cur;
	};

	auto ListDeleteNthElementR = [](ListNode* head, int num) -> ListNode* {
		ListNode *slow = head, *fast = head;
		for (int i = 0; i < num ; ++i) {
			if (fast == nullptr) {
				return head;
			}
			fast = fast->next;
		}
		ListNode* prev;
		for(; fast != nullptr; ) {
			prev = slow;
			slow = slow->next;
			fast = fast->next;
		} 
		prev->next = slow->next;
		delete slow;
		return head;
	};


//	vector<int> v = {1,2,3,4,5};
//	ListNode* vl = ConstructList(v);
//	PrintList(vl);
//
//	ListNode* v2 = ReverseBetween(vl, 2, 4);
//	PrintList(v2);
//
//	ListNode* v3 = ReverseBetween(ConstructList(v), 3, 5);
//	PrintList(v3);

//	vector<int> a = {2,3,4};
//	vector<int> b = {3,4,6};
//
//	ListNode* la = ConstructList(a);
//	ListNode* lb = ConstructList(b);
//	PrintList(la);
//	PrintList(lb);
//
//	PrintList(ListAdd(la, lb));

//	ListNode* la = ConstructList({1,4,3,2,5,2});
//	PrintList(la);
//	ListNode* pa = ListPartition(la, 3);
//	PrintList(la);

	//PrintList(ListRemoveDup(ConstructList({1,2,2,3,3,4,5,6,6,7,7,8})));
//	PrintList(ConstructList({1,2,2}));
//	PrintList(ListRemoveDup2(ConstructList({1,2,2})));

//	PrintList(ConstructList({1,2,3,4,5}));
//	PrintList(ListRotate(ConstructList({1,2,3,4,5}), 2));

	PrintList(ConstructList({}));
	PrintList(ListDeleteNthElementR(ConstructList({}), 100));

	return 0;
}
