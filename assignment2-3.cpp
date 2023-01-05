#include <iostream>

using namespace std;

class LinkedBinaryTree {
private:
	struct Node {
		char elem;
		Node* left;
		Node* right;
		Node* par;
		Node() : par(NULL), elem(), left(NULL), right(NULL) { }
	};
	Node* ptr[10];
	Node* currentNode;
	Node* root;
	int rootNum = 1;
	char draw[100][100];
	int posx = 0, posy = -1, maxx=0, maxy=0;
public:
	LinkedBinaryTree(const char *e) {
		Node* newNode = new Node;
		currentNode = newNode;
		root = newNode;
		for (int i = 0; e[i] != '\0'; i++) {
			switch (e[i]) {
			case'x':
				ptr[e[i + 1] - '0'] = currentNode;
				setData('0');
				i ++;
				break;
			case '(':
				addLeaf();
				break;
			case ')':
				getParent();
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				if (isPar()) addRoot();
				getParent();
				if (currentNode->right != NULL) {
					addRoot();
					getParent();
				}
				setData(e[i]);
				addLeaf();
				//getRight();
				break;
			default:
				setData(e[i]);
			}
		}
	}
	void addRoot() {
		Node* newNode = new Node;
		currentNode->par = newNode;
		root = newNode;
		root->left = currentNode;
		rootNum++;
	}
	void addLeaf() {
		Node* newNode = new Node;
		if (currentNode->left == NULL) currentNode->left = newNode;
		else currentNode->right = newNode;
		newNode->par = currentNode;
		currentNode = newNode;
	}
	void setData(const char e) {
		currentNode->elem = e;
	}
	bool isPar() {
		return currentNode->par == NULL;
	}
	void getParent() {
		currentNode = currentNode->par;
	}
	void getLeft() {
		currentNode = currentNode->left;
	}
	void getRight() {
		currentNode = currentNode->right;
	}
	Node* Root() {
		return root;
	}
	void inOrder(Node* node, int posy, int posx){
		draw[posy + 1][posx - 1] = '/';
		draw[posy + 2][posx - 2] = '/';
		draw[posy + 1][posx + 1] = '\\';
		draw[posy + 2][posx + 2] = '\\';
		if (node->left->left == NULL) {
			draw[posy+3][posx-3] = node->left->elem;
			if (maxy < posy + 3) maxy = posy + 3;
		}
		else {
			inOrder(node->left, posy+3, posx-3);
		}
		draw[posy][posx]=node->elem;
		if (node->right->left == NULL) {
			draw[posy + 3][posx + 3] = node->right->elem;
			if (maxx < posx + 3) maxx = posx + 3;
		}
		else {
			inOrder(node->right, posy+3, posx+3);
		}
	}
	int co_x() {
		return rootNum * 3;
	}
	void drawTree() {
		for (int i = 0; i <= maxy; i++) {
			for (int j = 0; j <= maxx; j++) {
				if (draw[i][j] == '\0') cout << " ";
				else cout << draw[i][j];
			}
			cout << endl;
		}
	}
	void setVariable(const char* e, char num) {
		ptr[e[1] - '0']->elem = num+'0';
	}
};

int main() {
	char* str = new char;
	cin >> str;
	LinkedBinaryTree tree(str);
	//tree.setVariable("x1", 1); set variable
	tree.inOrder(tree.Root(), 0, tree.co_x());
	tree.drawTree();
	return 0;
}