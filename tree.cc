#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;

struct Node {
	vector<int> adj;
	bool isVisited;
	int level;
};

int getGraph(int* A, int N, vector<int>& v) {
	v.assign(N - 1, 0);

	vector<unique_ptr<Node> > graph(N);

	generate(graph.begin(), graph.end(), []() {return unique_ptr<Node>(new Node());});

	int root = -1;
	for(int i = 0; i < N; i++) {
		graph[i]->adj.push_back(A[i]);
		graph[A[i]]->adj.push_back(i);
		if (A[i] == i) {
			root = i;
		}
	}
	if (root == -1) {
		return -1;
	}

	list<int> queue;
	int level = 0;
	graph[root]->level = 0;
	queue.push_back(root);
	int distance = 0;

	while(queue.size() > 0) {
		int curIdx = queue.front();	
		queue.pop_front();

		Node* curNode = graph[curIdx].get(); 
		curNode->isVisited = true;
		if (level != curNode->level) {
			v[level] = distance;		
			distance = 0;
			level = curNode->level;
		}
		for (int i = 0; i < curNode->adj.size(); i++) {
			int adjIdx = curNode->adj[i];
			Node* curAdj = graph[adjIdx].get();
			if (curAdj->isVisited) {
				continue;
			} else {
				distance += 1;
				curAdj->level = level + 1;
				queue.push_back(adjIdx);
			}
		}
	}
	return 0;
}

int main() {
	int A[] = {9, 1, 4, 9, 0, 4, 8, 9, 0, 1};
	vector<int> v;
	getGraph(A, sizeof(A)/sizeof(int), v);
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;

	return 0;
}
