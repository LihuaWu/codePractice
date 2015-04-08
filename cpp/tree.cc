#include <stdio.h>

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <queue>
#include <memory>
#include <utility>

using namespace std;

struct Node {
	Node* left;
	Node* right;
	int value;
	Node(int x, Node* l = nullptr, Node* r = nullptr) 
		: value(x), left(l), right(r) {} 
};

int main() {

	function<Node*(int*, int, int*)> ConstructTree = [&ConstructTree](int* preOrder, int m, int* inOrder) -> Node* {
		if (m < 1) return nullptr;
		 int root= preOrder[0];
		int * p =  find(inOrder, inOrder + m, root);
		Node*  cur = new Node(root);
		//distance should be greater or equal to zero, or the tree failed
		int distance = p - inOrder;

		cur->left = ConstructTree(preOrder + 1, distance,  inOrder);
		cur->right = ConstructTree(preOrder + distance + 1, m - distance - 1, inOrder + distance + 1);
		return cur;
	};

	function<void(Node*, string&, bool)> InnerPrintTreePreorder = [&InnerPrintTreePreorder](Node* root, string& padding, bool isLeft) {

		if(isLeft) {
			printf("%s|-- %d\n", padding.c_str(), root->value);
		} else {
			printf("%s`-- %d\n", padding.c_str(), root->value);
		}

		string tmp = padding;

		if(root->left != nullptr) {
			if(isLeft) {
				padding.append("|   ");
			} else {
				padding.append("    ");

			}
			InnerPrintTreePreorder(root->left, padding, true);
			padding = tmp;
		}
		if(root->right != nullptr) {
			if(isLeft) {
				padding.append("|   ");
			} else {
				padding.append("    ");
			}
			InnerPrintTreePreorder(root->right, padding, false);
			padding = tmp;
		}
		
	};

	auto PrintTreePreorder = [&InnerPrintTreePreorder](Node* root) {
		printf("%d\n", root->value);
		string padding("");
		if(root->left != nullptr) {
			InnerPrintTreePreorder(root->left, padding, true);
		}
		if(root->right != nullptr) {
			InnerPrintTreePreorder(root->right, padding, false);
		}
		printf("-------------------------\n");
	};

	function<void(Node*, string&, bool)> InnerPrintTreeInorder = [&InnerPrintTreeInorder](Node* root, string& padding, bool isLeft) {
		string tmp(padding);

		if(root->left != nullptr) {
			if(isLeft){
				padding.append("    ");
				//padding = "    " + padding;
			}else {
				padding.append("|   ");
				//padding = "|   " + padding;
			}
			InnerPrintTreeInorder(root->left, padding, true);
			padding = tmp;
		}


		if(isLeft) {
			printf("%s|-- %d\n", padding.c_str(), root->value);
		} else {
			printf("%s`-- %d\n", padding.c_str(), root->value);
		}

		if(root->right != nullptr) {
			if(isLeft) {
				padding.append("|   ");
				//padding = "|   " + padding;
			} else {
				padding.append("    ");
				//padding = "    " + padding;
			}

			InnerPrintTreeInorder(root->right, padding, false);
			padding = tmp;
		}
	};

	auto PrintTreeInOrder = [&InnerPrintTreeInorder] (Node* root) {
		string padding("");
		if(root->left != nullptr) {
			InnerPrintTreeInorder(root->left, padding, true);
		}
		printf("%d\n", root->value);
		if(root->right != nullptr) {
			InnerPrintTreeInorder(root->right, padding, false);
		}
		printf("-------------------------\n");

	};

	function<void(Node*, string&, bool)> InnerPrintTreePostOrder = [&InnerPrintTreePostOrder] (Node* root, string& padding, bool isLeft) {
		string tmp(padding);
		if(root->left != nullptr) {
			if(isLeft) {
				padding.append("    ");
			} else {
				padding.append("|   ");
			}
			InnerPrintTreePostOrder(root->left, padding, true);
			padding = tmp;
		}

		if (root->right != nullptr) {
			if(isLeft) {
				padding.append("    ");
			} else {
				padding.append("|   ");
			}
			InnerPrintTreePostOrder(root->right, padding, false);
			padding = tmp;
		}

		printf("%s|-- %d\n", padding.c_str(), root->value);
	};

	auto PrintTreePostOrder = [&InnerPrintTreePostOrder] (Node* root) {
		string padding("");
		if(root->left != nullptr) {
			InnerPrintTreePostOrder(root->left, padding, true);
		}
		if(root->right != nullptr) {
			InnerPrintTreePostOrder(root->right, padding, false);
		}
		printf("%d\n", root->value);
		printf("-------------------------\n");
	};


	auto RandomTree = [](int num) ->Node* {
		Node* root = new Node(0);
		queue<Node*> q;
		q.push(root);
		for(int i = 1; i < num; ) {
			Node* cur = q.front();
			q.pop();
			cur->left = new Node(i++);
			cur->right = new Node(i++);
			q.push(cur->left);
			q.push(cur->right);
		}
		return root;
	};


	//int preOrder[] = {1,2,4,5,3,6,7};
	//int inOrder[] = {4,2,5,1,6,3,7};
	//PrintTreePreorder(ConstructTree(preOrder, sizeof(preOrder)/sizeof(int), inOrder));
	//PrintTreeInOrder(ConstructTree(preOrder, sizeof(preOrder)/sizeof(int), inOrder));

	Node* root = RandomTree(50);
	PrintTreePreorder(root);
	PrintTreeInOrder(root);
	PrintTreePostOrder(root);


	return 0;
}
