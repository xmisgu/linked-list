#include "pch.h"
#include <iostream>

using namespace std;

template <typename T>
class List {
public:
	struct node {
		T dane;
		node* next, * prev;
		node() {
			next = nullptr;
			prev = nullptr;
		}
	};

	/*List* operator [](int n) const {
		node* ptr = head;
		int i = 0;
		while (ptr && i < n) {
			ptr = ptr->next;
			i++;
			cout << "test" << endl;
		}
		if (ptr) {
			return ptr;
		}
		else {
			cout << "Indeks poza zakresem" << endl;
		}
	}*/

	List() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	~List() {}



	void new_node_back(const T& dane) {
		node* n = new node;
		n->dane = dane;
		n->next = nullptr;
		if (tail == nullptr) {
			n->prev = nullptr;
			head = n;
			tail = n;
		}
		else {
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
		size++;
	}

	void new_node_front(const T& dane) {
		node* n = new node;
		n->dane = dane;
		n->prev = nullptr;
		if (head == nullptr) {
			n->prev = nullptr;
			head = n;
			tail = n;
		}
		else {
			n->next = head;
			head->prev = n;
			head = n;
		}
		size++;
	}

	void delete_last() {
		if (size == 0) {
			cout << "Brak elementow do usuniecia" << endl;
		}
		else if (size == 1) {
			head = tail = nullptr;
			size--;
		}
		else {
			node* temp = tail;
			tail = temp->prev;
			tail->next = nullptr;
			delete(temp);
			size--;
		}
	}

	void delete_first() {
		if (size == 0) {
			cout << "Brak elementow do usuniecia" << endl;
		}
		else if (size == 1) {
			head = tail = nullptr;
			size--;
		}
		else {
			node* temp = head;
			head = temp->next;
			head->prev = nullptr;
			delete(temp);
			size--;
		}
	}

	T find_element(int n) {
		node* ptr = head;
		int i = 0;
		while (ptr && i < n) {
			ptr = ptr->next;
			i++;
		}
		if (ptr) {
			return ptr->dane;
		}
	}
	node* find_node(const T& key) {
		node* ptr = head;
		while (ptr) {
			if ((ptr->dane == key)) {
				return ptr;
			}
			else {
				ptr = ptr->next;
			}
		}
		cout << "No such element" << endl;
	}

	bool find_and_delete(const T& key) {

		node* ptr = head;
		while (ptr) {
			if ((ptr->dane == key)) {
				if (ptr == head) {
					this->delete_first();
					return 1;
				}
				else if (ptr == tail) {
					this->delete_last();
					return 1;
				}
				else {
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;
					return 1;
				}

			}
			else {
				ptr = ptr->next;
			}
		}
		return 0;

	}

	void swap_element(int n, const T& new_data) {
		node* ptr = head;
		int i = 0;
		while (ptr && i < n) {
			ptr = ptr->next;
			i++;
		}
		if (ptr) {
			ptr->dane = new_data;
		}
	}

	void delete_all() {
		if (size == 0) {
			cout << "Lista pusta" << endl;
		}
		else if (size == 1) {
			head = tail = nullptr;
			size--;
		}
		else {
			node* tmp = head;
			while (tmp) {
				tmp = tmp->next;
				head = nullptr;
				head = tmp;
				size--;
			}
			tail = nullptr;
			delete tmp;
		}

	}

	void display_list() {
		node* ptr = head;
		while (ptr) {
			cout << ptr->dane << endl;
			ptr = ptr->next;
		}
	}


private:
	node* head, * tail;
	unsigned size;
};




struct listData {
	int d1;
	char d2;
	listData() {
		d1 = 1;
		d2 = 'a';
	}

};

ostream& operator << (ostream& out, const listData& obj) {
	out << "{d1: " << obj.d1 << endl << "d2: " << obj.d2 << "}";
	return out;
}

bool operator < (const listData& a, const listData& b) {
	return a.d1 < b.d1 || a.d1 == b.d1 && a.d2 < b.d2;
}

bool operator ==(const listData& a, const listData& b) {
	return (!(a < b) && !(b < a));
}




int main()
{
	List<listData>* lista = new List<listData>();
	listData* test = new listData();
	listData* test2 = new listData();
	/*cout << "----------------------------" << endl;*/
	//lista->delete_first();
	lista->new_node_back(*test);
	test->d1 = 2;
	test->d2 = 'b';
	lista->new_node_front(*test);
	test->d1 = 3;
	test->d2 = 'c';
	lista->new_node_back(*test);
	test->d1 = 4;
	test->d2 = 'd';
	lista->new_node_back(*test);
	cout << "----------------------------" << endl;
	test2->d1 = 4;
	test2->d2 = 'd';
	cout << lista->find_node(*test2) << endl;
	cout << "----------------------------" << endl;
	lista->display_list();
	cout << "----------------------------" << endl;
	test2->d1 = 1;
	test2->d2 = 'a';
	cout << lista->find_and_delete(*test2) << endl;
	cout << "----------------------------" << endl;
	lista->display_list();
	cout << "----------------------------" << endl;

	lista->new_node_back(*test);
	test->d1 = 2;
	test->d2 = 'b';
	lista->new_node_front(*test);
	lista->display_list();
	cout << "----------------------------" << endl;
	lista->delete_last();
	lista->display_list();
	cout << "----------------------------" << endl;
	test->d1 = 10;
	test->d2 = 'g';
	lista->swap_element(0, *test);
	lista->display_list();

	lista->delete_first();
	lista->display_list();
	cout << "----------------------------" << endl;
	cout << lista->find_element(0) << endl;
	cout << "----------------------------" << endl;
	lista->delete_all();
	lista->display_list();
	cout << "----------------------------" << endl;


	delete lista;
	delete test;
}











/*
	struct some_object{
		int field_1;
		char field_2;
		bool operator ==(const some_object& o) const {return field_1 == o.field_1 && field_2 == o.field_2;}
	};

	std::ostream & operator << (std::ostream& out, const some_object& obj){
	out << "{field_1: << obj.field_1 << ... ;
	return out;
	}

	#include<sstream>
	std::ostringstream out;

	out << head->dane

	return out.str();



	bool operator < (const some_object& a, const some_object& b){
		return a.field_1 < b.field_1 || a.field_1 == b.field1 && a.field_2 < b.field_2;
	}


	for(auto i = head; i; i = i-> nast){

	}

	auto ptr = tail;
	while(ptr){
	...
	ptr = ptr->poprz;
	}

*/
