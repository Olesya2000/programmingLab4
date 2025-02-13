#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
struct List
{
	int x;
	List *Next, *Head;
};

void Add(int x, List *&MyList)
{
	List *temp = new List;
	temp->x = x;
	temp->Next = MyList->Head;
	MyList->Head = temp;
}

void Show(List *MyList) {
	List *temp = MyList->Head;
	while (temp != NULL)
	{
		cout << temp->x << " ";
		temp = temp->Next;
	}
}

void ClearList(List *MyList)
{
	while (MyList->Head != NULL)
	{
		List *temp = MyList->Head->Next;
		delete MyList->Head;
		MyList->Head = temp;
	}
	delete MyList->Head;
	delete MyList;
}

int Pop(List *MyList) {
	List *temp = MyList->Head->Next;
	int n = MyList->Head->x;
	delete MyList->Head;
	MyList->Head = temp;
	return n;
}

unsigned opPreced(int ch)
{
	switch (ch)
	{
	case '^':
		return 3;
	case '*'://множення
	case '/'://ділення
		return 2;
	case '+'://додавання
	case '-'://віднімання
		return 1;
	}
	return 0;
}

bool isOperator(char i) {
	return (i == '+' || i == '-' || i == '/' || i == '*' || i == '^');
}



void forBracket(List* firstStack, List * secondStack, bool flag) {
	if (firstStack->Head->x != ')')
		if ((firstStack->Head->Next->x != ')') && (opPreced(firstStack->Head->x) < opPreced(firstStack->Head->Next->x)))
		{
			int x = Pop(secondStack);
			int y = Pop(firstStack);
			forBracket(firstStack, secondStack, false);
			Add(x, secondStack);
			Add(y, firstStack);
			forBracket(firstStack, secondStack, true);
		}
		else
		{
			int x = 0, y = 0;

			switch (firstStack->Head->x)
			{

			case '^':
				y = Pop(secondStack);
				x = pow(y, Pop(secondStack));
				break;
			case '/':
				y = Pop(secondStack);
				x = y / Pop(secondStack);
				break;
			case '*':
				x = Pop(secondStack) * Pop(secondStack);
				break;
			case '-':
				y = Pop(secondStack);
				x = y - Pop(secondStack);
				break;
			case '+':
				x = Pop(secondStack) + Pop(secondStack);
				break;
			}
			Add(x, secondStack);
			Pop(firstStack);
			if (flag == true)
				forBracket(firstStack, secondStack, true);
		}
}

void FillStacks(string inp, List* operations, List * operands) {
	for (int i = inp.length() - 1; i >= 0; i--) {
		if (inp[i] == '-' && (i == 0 || inp[i - 1] == '(')) {
			Add(0, operands);
			Add(inp[i], operations);
		}
		else if (inp[i] == ' ') {
			continue;
		}
		else if (isOperator(inp[i]) || inp[i] == ')') {
			Add(inp[i], operations);
		}
		else if (inp[i] == '(') {
			forBracket(operations, operands, true);
			Pop(operations);
		}
		else {
			Add(inp[i] - '0', operands);
		}
	}
}

int main() {
	List *firstStack = new List;
	List *secondStack = new List;
	firstStack->Head = NULL;
	secondStack->Head = NULL;
	Add(')', firstStack);
	string input;
	cout << "Input arithmetic expression: ";
	getline(cin, input);
	FillStacks(input, firstStack, secondStack);
	forBracket(firstStack, secondStack, true);
	Pop(firstStack);
	cout << "Result: " << secondStack->Head->x << endl;
	ClearList(firstStack);
	ClearList(secondStack);
	system("pause");
}