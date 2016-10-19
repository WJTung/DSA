#include <cstdio>
#include <stack>
using namespace std;
int precedence(char c)
{
	if(c == '!' || c == '~' || c == 'P' || c == 'N')
		return 2;
	if(c == '*' || c == '/' || c == '%')
		return 3;
	if(c == '+' || c == '-')
		return 4;
	if(c == '<' || c == '>')
		return 5;
	if(c == '&')
		return 8;
	if(c == '^')
		return 9;
	if(c == '|')
		return 10;
	if(c == 'A')
		return 11;
	if(c == 'O')
		return 12;
	if(c == '(')
		return 13;
	if(c == 'H')
		return 14;
	return 0;
}
void character_switch(stack<char> &, stack<int> &, char, bool &, bool &, int &, bool &);
void calculate(stack<int> &number_stack, char c)
{
	int a;
	int b;
	int result;
	if(c == '!')
	{
		putchar(' ');
		putchar('!');
		a = number_stack.top();
		number_stack.pop();
		result = !a;
		number_stack.push(result);
	}
	else if(c == '~')
	{
		putchar(' ');
		putchar('~');
		a = number_stack.top();
		number_stack.pop();
		result = ~a;
		number_stack.push(result);
	}
	else if(c == 'P')
	{
		putchar(' ');
		putchar('+');
	}
	else if(c == 'N')
	{
		putchar(' ');
		putchar('-');
		a = number_stack.top();
		number_stack.pop();
		result = -1 * a;
		number_stack.push(result);
	}
	else if(c == '*')
	{
		putchar(' ');
		putchar('*');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a * b;
		number_stack.push(result);
	}
	else if(c == '/')
	{
		putchar(' ');
		putchar('/');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a / b;
		number_stack.push(result);
	}
	else if(c == '%')
	{
		putchar(' ');
		putchar('%');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a % b;
		number_stack.push(result);
	}
	else if(c == '+')
	{
		putchar(' ');
		putchar('+');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a + b;
		number_stack.push(result);
	}
	else if(c == '-')
	{
		putchar(' ');
		putchar('-');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a - b;
		number_stack.push(result);
	}
	else if(c == '>')
	{
		putchar(' ');
		putchar('>');
		putchar('>');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a >> b;
		number_stack.push(result);
	}
	else if(c == '<')
	{
		putchar(' ');
		putchar('<');
		putchar('<');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a << b;
		number_stack.push(result);
	}
	else if(c == '&')
	{
		putchar(' ');
		putchar('&');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a & b;
		number_stack.push(result);
	}
	else if(c == '^')
	{
		putchar(' ');
		putchar('^');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a ^ b;
		number_stack.push(result);
	}
	else if(c == '|')
	{
		putchar(' ');
		putchar('|');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a | b;
		number_stack.push(result);
	}
	else if(c == 'A')
	{
		putchar(' ');
		putchar('&');
		putchar('&');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a && b;
		number_stack.push(result);
	}
	else if(c == 'O')
	{
		putchar(' ');
		putchar('|');
		putchar('|');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = a || b;
		number_stack.push(result);
	}
}
void operator_push(stack<char> &operator_stack, stack<int> &number_stack, char c)
{
	char top;
	int p;
	if(c == ')')
	{
		while(operator_stack.top() != '(')
		{
			top = operator_stack.top();
			operator_stack.pop();
			calculate(number_stack, top);
		}
		operator_stack.pop();
	}
	else
	{
		p = precedence(c);
		if(c == '!' || c == '~' || c == 'P' || c == 'N')
		{			
			while(precedence(operator_stack.top()) < p)
			{
				top = operator_stack.top();
				operator_stack.pop();
				calculate(number_stack, top);
			}
			operator_stack.push(c);
		}
		else
		{
			while(precedence(operator_stack.top()) <= p)
			{
				top = operator_stack.top();
				operator_stack.pop();
				calculate(number_stack, top);
			}
			operator_stack.push(c);
		}
	}
}
void operator_clear(stack<char> &operator_stack, stack<int> &number_stack)
{
	char top;
	while(operator_stack.top() != 'H')
	{
		top = operator_stack.top();
		operator_stack.pop();
		calculate(number_stack, top);
	}
}
void number_push(stack<int> &number_stack, int num)
{
	printf(" %d",num);
	number_stack.push(num);
}
int main()
{
	stack<char> operator_stack;
	operator_stack.push('H');
	stack<int> number_stack;
	char c;
	int num = 0;
	bool nonempty = 0; 
	bool end_parenthesis = 0;
	bool start = 1;
	while((c = getchar()) != EOF)
	{
		if(c != ' ')
			character_switch(operator_stack, number_stack, c, nonempty, end_parenthesis, num, start);
	}
}
void character_switch(stack<char> &operator_stack, stack<int> &number_stack, char c, bool &nonempty, bool &end_parenthesis, int &num, bool &start)
{
	if(start)
	{
		printf("Postfix Exp:");
		start = 0;
	}
	char next;
	if(c == '\n')
	{
		if(nonempty)
			number_push(number_stack, num);
		operator_clear(operator_stack, number_stack);
		putchar('\n');
		printf("RESULT: %d\n", number_stack.top());
		number_stack.pop();
		num = 0;
		nonempty = 0;
		start = 1;
	}
	else if('0' <= c && c <= '9')
	{
		nonempty = 1;
		num *= 10;
		num += (c - '0');
	}
	else if(c == '(')
		operator_stack.push(c);
	else if(c == '+')
	{
		if(nonempty)
		{
			number_push(number_stack, num);
			nonempty = 0;
			num = 0;
			operator_push(operator_stack, number_stack, c);
		}
		else if(end_parenthesis)
			operator_push(operator_stack, number_stack, c);
		else
			operator_push(operator_stack, number_stack, 'P');
	}
	else if(c == '-')
	{
		if(nonempty)
		{
			number_push(number_stack, num);
			nonempty = 0;
			num = 0;
			operator_push(operator_stack, number_stack, c);
		}
		else if(end_parenthesis)
			operator_push(operator_stack, number_stack, c);
		else
			operator_push(operator_stack, number_stack, 'N');
	}
	else
	{
		if(nonempty)
		{
			number_push(number_stack, num);
			nonempty = 0;
			num = 0;
		}
		if(c == '>')
		{
			getchar();
			operator_push(operator_stack, number_stack, c);
		}
		else if(c == '<')
		{
			getchar();
			operator_push(operator_stack, number_stack, c);
		}
		else if(c == '&')
		{
			end_parenthesis = 0;
			next = getchar();
			if(next == '&')
				operator_push(operator_stack, number_stack, 'A'); //Use A to represent &&
			else 
			{
				operator_push(operator_stack, number_stack, c);
				character_switch(operator_stack, number_stack, next, nonempty, end_parenthesis, num, start);
			}
		}
		else if(c == '|')
		{
			end_parenthesis = 0;
			next = getchar();
			if(next == '|')
				operator_push(operator_stack, number_stack, 'O'); //Use O to represent ||
			else 
			{
				operator_push(operator_stack, number_stack, c);
				character_switch(operator_stack, number_stack, next, nonempty, end_parenthesis, num, start);
			}
		}
		else
			operator_push(operator_stack, number_stack, c);
	}
	if(c == ')')
		end_parenthesis = 1;
	else
		end_parenthesis = 0;	
}
					
			