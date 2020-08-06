#include <bits/stdc++.h>
using namespace std;

int op_type(char);
bool is_operator(char);
int apply_op(int, int, char);
int evaluate(string);

bool is_operator(char op)
{
	int val = op_type(op);
	return (val == 1 || val == 2);
}

int op_type(char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '/' || op == '*')
		return 2;
	else
		return 0;
}

int apply_op(int a, int b, char op)
{
	switch (op)
	{
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '*':
		return (a * b);
	case '/':
		return (b / a);
	}
}

int evaluate(string elements)
{
	size_t i;

	// operators
	stack<char> ops;
	// operands
	stack<int> vals;

	for (i = 0; i < elements.length(); i++)
	{

		if (elements[i] == '(')
		{
			ops.push(elements[i]);
		}

		else if (isdigit(elements[i]))
		{
			int value = 0;
			while (i < elements.length() && isdigit(elements[i]))
			{

				value = (value * 10) + (elements[i] - '0');
				i++;
			}
			vals.push(value);
		}

		else if (elements[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{

				int value1 = vals.top();
				vals.pop();
				int value2 = vals.top();
				vals.pop();
				char op = ops.top();
				ops.pop();

				int result = apply_op(value1, value2, op);
				vals.push(result);
			}

			if (!ops.empty())
			{
				ops.pop();
			}
		}

		else if (is_operator(elements[i]))
		{
			while (!ops.empty() && op_type(ops.top()) >= op_type(elements[i]))
			{

				int value1 = vals.top();
				vals.pop();
				int value2 = vals.top();
				vals.pop();
				char op = ops.top();
				ops.pop();

				int result = apply_op(value1, value2, op);
				vals.push(result);
			}

			ops.push(elements[i]);
		}
	}

	while (!ops.empty())
	{
		int value1 = vals.top();
		vals.pop();
		int value2 = vals.top();
		vals.pop();
		char op = ops.top();
		ops.pop();

		int result = apply_op(value1, value2, op);
		vals.push(result);
	}
	return vals.top();
}

int main(void)
{
	string expr;

	// cout << "enter expr : ";
	// getline(cin, expr);
	// cout << expr <<endl;

	cout << evaluate("10 + 3 - 6 * 2 + ( 10 - 4 )") << endl;

	return 0;
}