#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

enum KitchenTypes {
	russian, 
	asian, 
	eastern, 
	ukrain
};

class NameException {
public:
	const char* GetError() {
		return "Name error";
	}
};
class CaloriesException {
public:
	const char* GetError() {
		return "Calories error";
	}
};
class CookingTimeException {
public:
	const char* GetError() {
		return "Cooking time error";
	}
};

class Food {
	char* name;
	int calories;
	KitchenTypes kitchenType;
	double cookingTime;
public:
	Food() {
		name = new char[50];
		calories = 0;
		kitchenType = russian;
		cookingTime = 0;
	}
	Food(char* name, int calories, KitchenTypes kitchenType, double cookingTime) {
		try {
			this->name = new char[strlen(name)];
			for (int i = 0; i < strlen(name); i++) {
				this->name[i] = name[i];
			}
			this->calories = calories;
			this->kitchenType = kitchenType;
			this->cookingTime = cookingTime;


			if (this->name[0] == ' ' || strlen(this->name) == 0) {
				throw NameException();
			}
			if (calories == 0) {
				throw CaloriesException();
			}
			if (cookingTime == 0) {
				throw CookingTimeException();
			}
		}
		catch (CaloriesException e) {
			cout << e.GetError();
		}
		catch (NameException e) {
			cout << e.GetError();
		}
		catch (CookingTimeException e) {
			cout << e.GetError();
		}
	}
	Food(const Food& food) {
		try {
			name = new char[strlen(food.name)];
			for (int i = 0; i < strlen(name); i++) {
				this->name[i] = food.name[i];
			}
			calories = food.calories;
			kitchenType = food.kitchenType;
			cookingTime = food.cookingTime;

			if (this->name[0] == ' ' || strlen(this->name) == 0) {
				throw NameException();
			}
			if (calories == 0) {
				throw CaloriesException();
			}
			if (cookingTime == 0) {
				throw CookingTimeException();
			}
		}
		catch (CaloriesException e) {
			cout << e.GetError();
		}
		catch (NameException e) {
			cout << e.GetError();
		}
		catch (CookingTimeException e) {
			cout << e.GetError();
		}
	}
	~Food()
	{
		name = nullptr;
	}
	Food* operator++() {
		calories++;
		return this;
	}
	Food* operator--() {
		calories++;
		return this;
	}

	bool operator==(const Food& food) {
		return calories == food.calories;
	}

	bool operator>= (const Food& food) {
		return calories >= food.calories;
	}
	bool operator<= (const Food& food) {
		return calories <= food.calories;
	}
	
	bool operator> (const Food& food) {
		return calories > food.calories;
	}
	bool operator< (const Food& food) {
		return calories < food.calories;
	}

	friend istream& operator>> (istream& in, Food& food);
	friend ostream& operator<< (ostream& out, const Food& food);
};

istream & operator>>(istream & in, Food & food)
{
	int x;
	in >> food.name;
	in >> food.calories;
	in >> x;
	if (x == 0) {
		food.kitchenType = russian;
	}
	else if (x == 1) {
		food.kitchenType = asian;
	}
	else if (x == 2) {
		food.kitchenType = eastern;
	}
	else {
		food.kitchenType = ukrain;
	}

	in >> food.cookingTime;
	return in;
}

ostream & operator<<(ostream & out, const Food & food)
{
	char* kitchen;
	if (food.kitchenType == 0) {
		kitchen = new char[8] {"russian"};
	}
	else if (food.kitchenType == 0) {
		kitchen = new char[6] {"asian"};
	}
	else if (food.kitchenType == 0) {
		kitchen = new char[8] {"eastern"};
	}
	else {
		kitchen = new char[7] {"ukrain"};
	}

	out << food.name << "       " << food.calories << "        " << kitchen << "     " << food.cookingTime;
	return out;
}

void Sort(Food* food, int size);

template <class T>
struct Node
{
	T data;
	Node* next;
};

template <class T>
class List {
	Node<T> *head;
public:
	List() {
		head = NULL;
	}
	void Add(T& val) {
		Node<T> *nd = new Node<T>;
		nd->data = val;
		nd->next = NULL;
		if (head == NULL) {
			head = nd;
		}
		else {
		Node<T> *curr = head;
		while (curr->next != NULL) {
			if (nd->data <= curr->data) {
				nd->next = curr;
				Node<T> *before = head;
				while (true) {
					if (before->next->next == nd->next) {
						before->next = nd;
						break;
					}
				}
			}
			curr = curr->next;
		}
		curr->next = nd;
		}
	}
	void LoadToFile() {
		ofstream os("list.txt");
		os << "Name         " << "Calories     " << "Kitchen    " << "Hours\n";
		os << "-----------------------------------------------------------\n";
		Node<T> *current = head;
		while (current != NULL)
		{
			os << current->data << endl;
			current = current->next;
		}
	}
};

int main()
{
	Food* food = new Food[6];

	ifstream is("data.txt");
	if (is.is_open()) {
		for (int i = 0; i < 6; i++) {
			is >> food[i];
		}
	}
	is.close();
	for (int i = 0; i < 6; i++) {
		cout << food[i] << endl << endl;
	}
	Sort(food, 6);
	ofstream os("sorted.txt");
	os << "Name            " << "Calories        " << "Kitchen          " << "Hours\n";
	os << "-----------------------------------------------------------\n";
	for (int i = 0; i < 6; i++) {
		os << food[i] << endl << endl;
	}

	List<Food> list;
	list.Add(food[0]);
	list.Add(food[2]);
	list.Add(food[5]);
	list.LoadToFile();
	
	cin.get();
}

void Sort(Food* food, int size) {
	for (int i = 0; i < size - 1; i++) {
		int smallestIndex = i;
		for (int j = i + 1; j < size; j++) {
			if (food[j] < food[smallestIndex]) {
				smallestIndex = j;
			}
		}
		swap(food[i], food[smallestIndex]);
	}
}