// C++ implementation of the approach
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stack>
#include <string>
using namespace std;


//Реализуем множество на основе Бинарного деревья

struct Node {
	string data;
    Node* left;
    Node* right;
public:
	//Обход деревья
	void inorder(Node* r)
	{
		if (r == NULL) {
			return;
		}
		inorder(r->left);
		cout << r->data << " ; ";
		inorder(r->right);
	}
	//Проверка узла
    int containsNode(Node* r, string d)
	{
		if (r == NULL) {
			return 0;
		}
		int x = r->data == d ? 1 : 0;
		return x | containsNode(r->left, d) | containsNode(r->right, d);
	}
	//Вставка в бинарном деревья
	Node* insert(Node* r, string d)
	{

		if (r == NULL) {
			Node* tmp = new Node;
			tmp->data = d;
			tmp->left = tmp->right = NULL;
			return tmp;
		}

		if (d < r->data) {
			r->left = insert(r->left, d);
			return r;
		}
        else if (d > r->data) {
			r->right = insert(r->right, d);
			return r;
		}
		else
			return r;
	}
};

// На основе деревья создаем Множества
class Set {


	Node* root;//Корен деревья
	int size;//Количтество элементов

public:
	// Конструктор
	Set()
	{
		root = NULL;
		size = 0;
	}

	// Конструктор копирование
	Set(const Set& s)
	{
		root = s.root;
		size = s.size;
	}
	//Добавление элемента Если конечно это элемент нет уже там 
	void add(const string data)
	{
		if (!root->containsNode(root, data)) {
			root = root->insert(root, data);
			size++;
		}
	}
	//Объеденение множество 
	Set unionSet(Set& s)
	{
		Set res;

		if (root == NULL)
			return res;

		if (s.root == NULL)
			return *this;

		stack<Node*> nodeStack;
		nodeStack.push(root);
        while (!nodeStack.empty()) {
			Node* node;
			node = nodeStack.top();
			nodeStack.pop();

			res.add(node->data);

			if (node->right)
				nodeStack.push(node->right);
			if (node->left)
				nodeStack.push(node->left);
		}

		stack<Node*> nodeStack1;
		nodeStack1.push(s.root);

		while (!nodeStack1.empty()) {
			Node* node;
			node = nodeStack1.top();
			nodeStack1.pop();

			res.add(node->data);

			if (node->right)
				nodeStack1.push(node->right);
			if (node->left)
				nodeStack1.push(node->left);
		}

		return res;
	}
	//Пересечение множество 
	Set intersectionSet(Set& s)
	{
		Set res;
		stack<Node*> nodeStack;
		nodeStack.push(root);

		while (!nodeStack.empty()) {
			Node* node;
			node = nodeStack.top();
			nodeStack.pop();
			if (s.contains(node->data)) {
				res.add(node->data);
			}
			if (node->right)
				nodeStack.push(node->right);
			if (node->left)
				nodeStack.push(node->left);
		}
		return res;
	}
	//Разность симметричность то есть this^c=U
	Set complementSet(Set& U)
	{
		return (U - *this);
	}
     //Операция разность
	Set operator-(Set& s)
	{
		Set res;
		stack<Node*> nodeStack;
		nodeStack.push(this->root);

		while (!nodeStack.empty()) {
			Node* node;
			node = nodeStack.top();
			nodeStack.pop();
			if (!s.contains(node->data)) {
				res.add(node->data);
			}
			if (node->right)
				nodeStack.push(node->right);
			if (node->left)
				nodeStack.push(node->left);
		}
		return res;
	}
	//Проверка на равенство
	bool operator==(Set& s)
	{
		if (s.getSize() != size) {
			return false;
		}
		stack<Node*> nodeStack;
		nodeStack.push(this->root);

		while (!nodeStack.empty()) {
			Node* node;
			node = nodeStack.top();
			nodeStack.pop();
			if (!s.contains(node->data)) {
				return false;
			}
			if (node->right)
				nodeStack.push(node->right);
			if (node->left)
				nodeStack.push(node->left);
		}
		return true;
	}
	//Декартовое произведение
	 void displayProduct(Set& s)
	{
		int i, j, n2 = s.getSize();
		string* A = toArray();
		string* B = s.toArray();

		i = 0;

		cout << "{ ";
		for (i = 0; i < size; i++) {
			for (j = 0; j < n2; j++) {
				cout << "{ " << A[i] << " " << B[j] << " } ";
			}
		}
		cout << "}" << endl;
	}

	 //Степен множество
	void displayPowerSet()
	{
		int n = pow(2, size);
		string* A = toArray();
		int i;
		while (n-- > 0) {
			cout << "{ ";
			for (int i = 0; i < size; i++) {
				if ((n & (1 << i)) == 0) {
					cout << A[i] << " ";
				}
			}
			cout << "}" << endl;
		}
	}
	//Переобразовать в массив строк
	string* toArray()
	{
		string* A = new string[size];
		int i = 0;
		stack<Node*> nodeStack;
		nodeStack.push(this->root);

		while (!nodeStack.empty()) {
			Node* node;
			node = nodeStack.top();
			nodeStack.pop();

			A[i++] = node->data;

			if (node->right)
				nodeStack.push(node->right);
			if (node->left)
				nodeStack.push(node->left);
		}
		return A;
	}
    //Проверка принадлежности элемента
	bool contains(string data)
	{
		return root->containsNode(root, data) ? true : false;
	}
    //Вывод на экран
	void displaySet()
	{
		cout << "{ ";
		root->inorder(root);
		cout << "}" << endl;
	}
	//Количество -размер элементов
	int getSize()
	{
		return size;
	}
};

int main()
{
	system("chcp 1251");
	Set A;//Первый цветовод
	Set B;//Второй
	Set C;//Третый
	Set Al;//Все сорты
	Al.add("Анжелика");
	Al.add("Виктория");
	Al.add("Гагарин");
	Al.add("Ave Maria");
	Al.add("Катарина");
	Al.add("Юбилейная");
	int NA;//Количество роз который хотим добавить в первую цветовод
	int NB;//Количество роз который хотим добавить в первую цветовод
	int NC;//Количество роз который хотим добавить в первую цветовод
	cout << "Количество роз который хотите добавит к первому: ";
	cin >> NA;
	for (int i = 0; i < NA; i++)
	{
		string cur;//Сорт один из который указан в условиях
		cin >> cur;
		A.add(cur);
	}
	cout << "Количество роз который хотите добавит к второму: ";
	cin >> NB;
	for (int i = 0; i < NB; i++)
	{
		string cur;//Сорт один из который указан в условиях
		cin >> cur;
		B.add(cur);
	}
	cout << "Количество роз который хотите добавит к третуму: ";
	cin >> NC;
	for (int i = 0; i < NC; i++)
	{
		string cur;//Сорт один из который указан в условиях
		cin >> cur;
		C.add(cur);
	}
	cout << "==========================Сорты роз===================================\n\n";
	Al.displaySet();
	cout << "\n\n====================================================================\n\n";
	//Тепер найдем те сорта который имеется у каждого (Можно заметить что это пересечение)
	Set D = C.intersectionSet(B);
	D=D.intersectionSet(A);
	cout << "==================Те сорты который есть в каждом========================== \n";
	D.displaySet();
	cout << "\n======================================end================================= \n";
	//Тепер те который есть хотя бы у один из этих (Объединение )
	Set Ob = C.unionSet(B);
	Ob = Ob.unionSet(A);
	cout << "==================Те сорты который есть хотя в одном========================== \n";
	Ob.displaySet();
	cout << "\n======================================end================================= \n";
	Al = Al - Ob;
	cout << "\n\n======================Нет у цветоводах====================================\n";
	Al.displaySet();
	cout << endl;
	return 0;
}
