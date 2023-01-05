#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
	T elem;
	Node<T>* next;
};

template <typename T>
class aStack {
private:
	int t;
	Node<T> *head;
public:
	aStack() :head(NULL), t(0) {}
	~aStack() {
		while (!empty()) pop();
	}
	int size() const {
		return t;
	}
	bool empty() const {
		return t == 0;
	}
	const T& top() const {
		return head->elem;
	}
	void push(const T & e) {
		Node<T>* v = new Node<T>;
		v->elem = e;
		v->next = head;
		head = v;
		t++;
	}
	void pop() {
		Node<T> *old = head;
		head = old->next;
		delete old;
	}
};

int main() {
	aStack<int> A; // A = [ ], size = 0
	A.push(7); // A = [7*], size = 1
	A.push(13); // A = [7, 13*], size = 2
	cout << A.top() << endl; A.pop(); // A = [7*], outputs: 13
	A.push(9); // A = [7, 9*], size = 2
	cout << A.top() << endl; // A = [7, 9*], outputs: 9
	cout << A.top() << endl; A.pop(); // A = [7*], outputs: 9
	aStack<string> B; // B = [ ], size = 0
	B.push("Bob"); // B = [Bob*], size = 1
	B.push("Alice"); // B = [Bob, Alice*], size = 2
	cout << B.top() << endl; B.pop(); // B = [Bob*], outputs: Alice
	B.push("Eve");
	return 0;
}