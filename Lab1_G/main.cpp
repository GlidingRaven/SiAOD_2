#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>
#include <queue>
#include <string>
#define basesize 4000


Node* p1, p2;
static bool rost;
int x;

struct record
{
	char a[30];
	unsigned short int b;
	char c[10];
	char d[22];
};

struct Node {
	record value;
	int balance;
	struct Node* left;
	struct Node* right;
};


void printlist(std::queue<record> myqueue)
{
	int count = 0;
	std::queue<record> temp;
	temp = myqueue;
	while (!temp.empty())
	{
		count++;
		std::cout << temp.front().a << " " << temp.front().b << " " << temp.front().c << " " << temp.front().d << std::endl;
		while (count % 20 == 0)
		{
			std::cout << "Continue? (y/n)" << std::endl;
			char choice;
			std::cin >> choice;
			if (choice == 'y')
			{
				break;
			}
			else
				if (choice == 'n')
				{
					return;
				}
		}
		temp.pop();
	}
}

int getdigit(int n, int x) //returns specific digit, counting from end and 0
{
	for (int i = 0; i < x; i++)
	{
		n = n / 10;
	}

	return (n % 10);
}


int countdigit(int x)
{
	int n = 0;
	while (x > 0)
	{
		x = x / 10;
		n++;
	}
	return n;
}

int maxdigitb(std::queue <record> myqueue)
{
	int max = 0;
	std::queue<record> temp;
	temp = myqueue;
	while (!temp.empty())
	{
		if (countdigit(temp.front().b) > max)
		{
			max = countdigit(temp.front().b);
		}
		temp.pop();
	}
	return max;
}

std::string getcapitals(char* a)
{
	std::string out = "";
	for (int i = 29; i >= 0; i--) //идем справа налево в фио
	{
		char d = a[i]; //
		if (d >= -128 && d <= -97) //если большая буква
		{
			out += d;
		}
	}
	//std::cout << out << std::endl;
	return out;
}

std::string getcapitalsreverse(char* a)
{
	std::string out = "";
	for (int i = 0; i < 30; i++) //идем слева направо в фио
	{
		char d = a[i]; //
		if (d >= -128 && d <= -97) //если большая буква
		{
			out += d;
		}
	}
	//std::cout << out << std::endl;
	return out;
}

std::queue<record>* radixb(std::queue<record>* l, int t) // сортировка по b
{
	int d, m = 1;
	std::queue<record>* out;
	std::queue<record> list[10];
	out = l;

	for (int j = 0; j < t; j++) // разряды
	{
		for (int i = 0; i <= 9; i++) // обнуляем листы
			list[i] = {};

		while (!out->empty())
		{
			d = getdigit(out->front().b, j);
			list[d].push(out->front());
			out->pop();
		}
		for (int i = 0; i <= 9; i++)
		{
			while (!list[i].empty())
			{
				out->push(list[i].front());
				list[i].pop();
			}
		}

	}
	return (out);
}


std::queue<record> radixa(std::queue<record> l) // сортировка по a
{
	int d, m = 1;
	std::queue<record> out;
	std::queue<record> list[33];
	out = l;
	int counter = 0;
	for (int j = 2; j >= 0; j--) // разряды
	{
		for (int i = 0; i <= 32; i++) // обнуляем листы
			list[i] = {};
		while (!out.empty())
		{
			counter = 2;
			for (int i = 29; i >= 0; i--) //идем справа налево в фио
			{
				d = (int)out.front().a[i]; //
				if (d >= -128 && d <= -97) //если большая буква
				{
					if (counter == j) // смотрим какая букву ищем на данный момент
					{
						//std::cout << "BREAK " << d+128 << " " ; //для профессионального дебага
						break;
					}
					else
					{
						counter--; // если изменился разряд
					}
				}
			}

			d += 128; //смещение
			//std::cout << out.front().a << " " << j << " " << (int)out.front().a[j] << std::endl; // профессиональный дебаг
			list[d].push(out.front());
			out.pop();
		}
		for (int i = 0; i <= 32; i++)
		{
			while (!list[i].empty())
			{
				//std::cout << list[i].front().a << counter << std::endl; // еще дебаг
				out.push(list[i].front());
				list[i].pop();
			}
		}

	}

	return (out);
}

std::queue<record> radixab(std::queue<record> l)
{
	std::queue<record> newqueue; // массив для вывода
	std::queue<record> tempqueue; // массив для сохранения подсписков
	while (!l.empty())
	{
		record temp = l.front();
		record tempnext;
		l.pop();
		if (!l.empty())
		{
			tempnext = l.front();
		}

		if (getcapitals(temp.a) == getcapitals(tempnext.a))
		{
			tempqueue.push(temp);
		}
		else
		{
			tempqueue.push(temp);
			tempqueue = *radixb(&tempqueue, maxdigitb(tempqueue));
			while (!tempqueue.empty())
			{
				newqueue.push(tempqueue.front());
				tempqueue.pop();
			}
		}
	}
	return newqueue;
}


std::queue<record> binarysearch(std::queue<record> l, char* query1)
{
	char* query = new char[50];
	CharToOemA(query1, query);
	record* A = new record[4000];
	for (int i = 0; i < 3999; i++)
	{
		A[i] = l.front();
		l.pop();
		//std::cout << getcapitalsreverse(A[i].a) << std::endl;
	}

	int L = 0;
	int R = 3999;
	int m;
	while (L < R)
	{
		m = (L + R) / 2;
		if (getcapitalsreverse(A[m].a) < query)
		{
			L = m + 1;
		}
		else
		{
			R = m;
		}
	}
	if ((getcapitalsreverse(A[R].a).compare(query) == 0))
	{
		std::queue<record> newqueue;
		while (true)
		{
			if (R + 1 < 4000) // R = 3998
			{
				if (getcapitalsreverse(A[R].a) == getcapitalsreverse(A[R + 1].a))
				{
					newqueue.push(A[R]);
					R++;
				}
				else
				{
					newqueue.push(A[R]);
					break;
				}
			}
			else
			{
				newqueue.push(A[R]);
				break;
			}

		}
		return newqueue;
	}
	else
	{
		std::queue<record> newqueue;
		return newqueue;
	}


}




static Node* LLTurn(Node* p)
{
	Node* q;
	q = p->left;
	q->balance = 0;
	p->balance = 0;
	p->left = q->right;
	q->right = p;
	return q;
}

static Node* LRTurn(Node* p)
{
	Node* q;
	Node* r;
	q = p->left;
	r = q->right;
	if (r->balance < 0)
	{
		p->balance = 1;
	}
	else
	{
		p->balance = 0;
	}
	if (r->balance > 0)
	{
		q->balance = -1;
	}
	else
	{
		q->balance = 0;
	}
	r->balance = 0;
	p->left = r->right;
	q->right = r->left;
	r->left = q;
	r->right = p;
	return p;
}


static Node* RRTurn(Node* p)
{
	Node* q;
	q = p->right;
	q->balance = 0;
	p->balance = 0;
	p->right = q->left;
	q->left = p;
	return q;
}

static Node* RLTurn(Node* p)
{
	Node* q;
	Node* r;
	q = p->right;
	r = q->left;
	if (r->balance > 0)
	{
		p->balance = -1;
	}
	else
	{
		p->balance = 0;
	}
	if (r->balance < 0)
	{
		q->balance = 1;
	}
	else
	{
		q->balance = 0;
	}
	r->balance = 0;
	p->right = r->left;
	q->left = r->right;
	r->left = p;
	r->right = q;
	return r;
}




static Node* AddToAVL(Node* p, record x)
{
	Node* p1;
	if (p == nullptr)
	{
		p = new Node;
		p->value = x;
		p->left = nullptr;
		p->right = nullptr;
		p->balance = 0;
		rost = true;
		return p;
	}
	else
	{
		if (p->value.b > x.b)
		{
			p->left = AddToAVL(p->left, x);
			if (rost)
			{
				if (p->balance > 0)
				{
					p->balance = 0;
					rost = false;
				}
				else
				{
					if (p->balance == 0)
					{
						p->balance = -1;
					}
					else
					{
						if (p->left->balance < 0)
						{
							p1 = p->left;
							if (p1->balance == -1)
							{
								p = LLTurn(p);
							}
							else
							{
								p = LRTurn(p);
							}

							rost = false;
						}
					}
				}
			}
		}
		else
		{
			p->right = AddToAVL(p->right, x);
			if (rost)
			{
				if (p->balance < 0)
				{
					p->balance = 0;
					rost = false;
				}
				else
				{
					if (p->balance == 0)
					{
						p->balance = 1;
					}
					else
					{
						if (p->right->balance > 0)
						{
							p1 = p->right;
							if (p1->balance == 1)
							{
								p = RRTurn(p);
							}
							else
							{
								p = RLTurn(p);
							}

							rost = false;
						}
					}
				}
			}
		}
	}
	return p;
}

Node* BuildAVL(std::queue<record> l)
{
	int i;
	Node* Root = new Node;
	Root->value = l.front();
	Root->left = nullptr;
	Root->right = nullptr;
	Root->balance = 0;
	l.pop();
	for (i = 1; i < basesize; i++)
	{
		rost = false;
		Root = AddToAVL(Root, l.front());
		l.pop();
	}
	return Root;
}

void GoFromLeftToRight(Node* p)
{
	if (p != nullptr)
	{
		GoFromLeftToRight(p->left);
		std::cout << p->value.a << " " << p->value.b << " " << p->value.c << " " << p->value.d << std::endl;
		GoFromLeftToRight(p->right);
	}
}

bool SearchInTree(Node* p, int x)
{
	while (p != nullptr)
	{
		if (p->value < x)
		{
			p = p->right;

		}
		else
			if (p->value > x)
			{
				p = p->left;

			}
			else break;
	}
	if (p != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsSearchTree(Node* p)
{
	if (p != nullptr and (((p->left != nullptr) and ((p->value <= p->left->value) or (!IsSearchTree(p->left)))) or ((p->right != nullptr) and \
		((p->value >= p->right->value) or (!IsSearchTree(p->right)))))) return false;
	else
		return true;
}

int main()
{

	FILE* fp;
	fp = fopen("testBase3.dat", "rb");
	std::queue <record> myqueue;
	record* temp = new record;
	int n = 0;
	for (int i = 0; i < basesize; i++)
	{
		int x = fread(temp, sizeof(record), 1, fp);
		myqueue.push(*temp);
		n++;
	}






	while (true)
	{
		std::cout << "1: Print BD" << std::endl;
		std::cout << "2: Sort for FIO and summ" << std::endl;
		std::cout << "3: Execute fast search" << std::endl;
		std::cout << "4: Build AVL tree" << std::endl;
		std::cout << "5: print tree" << std::endl;
		std::cout << "6: search in tree" << std::endl;
		std::cout << "0: Exit" << std::endl;
		std::cout << "Your change:";
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			printlist(myqueue);
			break;
		case 2:
			printlist(radixab(radixa(myqueue)));
			break;
		case 3: {
			SetConsoleCP(1251);
			char query1[5];
			std::cout << "Put value for search (first 3 char FIO)" << std::endl;
			std::cin >> query1;
			printlist(binarysearch(radixab(radixa(myqueue)), query1));
			break;
		}
		case 4:
			p1 = BuildAVL(myqueue);
			break;
		case 5:
			GoFromLeftToRight(p1);
			std::cout << std::endl;
			system("pause");
			break;
		case 6:
			std::cout << "Enter search query: ";
			std::cin >> x;

			if (SearchInTree(p1, x))
			{
				std::cout << "Search successfull: " << x << std::endl;
			}
			else
			{
				std::cout << "Search failed " << std::endl;
			}
			system("pause");
			break;
		case 0:
			return 0;
			break;
		default:
			break;
		}

	}

	//printlist(myqueue); //работает
	//printlist(*radixb(&myqueue, maxdigitb(myqueue))); работает
	//printlist(radixa(myqueue));
	//printlist(myqueue);





	system("pause");
	return 0;
}