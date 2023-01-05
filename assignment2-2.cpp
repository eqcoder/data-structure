#include <iostream>

using namespace std;

struct Node {
	char elem;
	Node* prev;
	Node* next;
};

class NodeList {
private:
	int n;
	Node* header;
	Node* trailer;
public:
	NodeList() {
		n = 0;
		header = new Node;
		trailer = new Node;
		header->next = trailer;
		trailer->prev = header;
	}
	int size() const {
		return n;
	}
	bool empty() const {
		return (n == 0);
	}
	void insert(Node* node, const char& e) {
		Node* w = node->next;
		Node* u = w->prev;
		Node* v = new Node;
		v->elem = e;
		v->next = w;
		w->prev = v;
		v->prev = u;
		u->next = v;
		n++;
	}
	void insertBack(const char& e) {
		insert(trailer->prev, e);
	}
	void PrintList() {
		Node *w = header->next;
		while (w!=trailer) {
			cout << w->elem;
			w = w->next;
		}
		cout << endl;
	}
	friend class TextEditor;
};

class TextEditor {
private:
	Node* cursor;
	NodeList* list;
public:
	TextEditor(const char *str){
		list = new NodeList;
		cursor = list->header;
		for (int i = 0; str[i] != '\0'; i++) list->insertBack(str[i]);
	}
	void PrintText() {
		list->PrintList();
		cout << "Current Cursor : ";
		if (cursor == list->header) cout << "before the first character" << endl;
		else cout << cursor->elem << endl;
	}
	void left() {
		if (cursor!=list->header) cursor = cursor->prev;
		PrintText();
	}
	void right() {
		if (cursor!=list->trailer) cursor = cursor->next;
		PrintText();
	}
	void Delete() {
		if (cursor->next != nullptr) {
			Node* w = cursor->next;
			w->prev->next = w->next;
			w->next->prev = w->prev;
			delete w;
		}
		PrintText();
	}
	void insert(const char c) {
		list->insert(cursor, c);
		PrintText();
	}
};

int main() {
	char* str=new char;
	cout << "처음 문자열을 입력하세요 : ";
	cin >> str;
	TextEditor t(str);
	char* ope = new char;
	while (true) {
		cout << "연산을 입력하세요(left, right, delete, insertc(띄어쓰기없이), 종료 q)"<<endl;
		cin >> ope;
		if (ope[0] == 'l') {
			t.left();
		}
		else if (ope[0] == 'r') {
			t.right();
		}
		else if (ope[0] == 'i') {
			t.insert(ope[6]);
		}
		else if (ope[0] == 'd') {
			t.Delete();
		}
		else if (ope[0] == 'q') {
			break;
		}
		else {
			cout << "다시 입력해주세요!" << endl;
			continue;
		}
	}
	return 0;
}