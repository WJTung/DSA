#include <stdio.h>
#include <stack>
#include <math.h>
using namespace std;
int precedence(char c)
{
	if(c == 'P' || c == 'N')
		return 1;
	if(c == '*')
		return 2;
	if(c == '+' || c == '-')
		return 3;
	if(c == '(' || c == 'S' || c == 'C' || c == 'E' || c == 'L' || c == 'W' || c == 'Q' || c == 'F')
		return 4;
	if(c == 'H') //head
		return 5;
	return 0;
}
void character_switch(stack<char> &, stack<double> &, char, bool &, bool &, bool &, double &, double &, bool &);
void calculate(stack<double> &number_stack, char c)
{
	double a;
	double b;
	double result;
	if(c == 'P')
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
	else if(c == 'S') //sin
	{
		putchar(' ');
		putchar('s');
		putchar('i');
		putchar('n');
		a = number_stack.top();
		number_stack.pop();
		result = sin(a);
		number_stack.push(result);
	}
	else if(c == 'C') //cos
	{
		putchar(' ');
		putchar('c');
		putchar('o');
		putchar('s');
		a = number_stack.top();
		number_stack.pop();
		result = cos(a);
		number_stack.push(result);
	}
	else if(c == 'E') //exp
	{
		putchar(' ');
		putchar('e');
		putchar('x');
		putchar('p');
		a = number_stack.top();
		number_stack.pop();
		result = exp(a);
		number_stack.push(result);
	}
	else if(c == 'L') //log
	{
		putchar(' ');
		putchar('l');
		putchar('o');
		putchar('g');
		a = number_stack.top();
		number_stack.pop();
		result = log(a);
		number_stack.push(result);
	}
	else if(c == 'W') //pow
	{
		putchar(' ');
		putchar('p');
		putchar('o');
		putchar('w');
		b = number_stack.top();
		number_stack.pop();
		a = number_stack.top();
		number_stack.pop();
		result = pow(a, b);
		number_stack.push(result);
	}
	else if(c == 'Q') //sqrt
	{
		putchar(' ');
		putchar('s');
		putchar('q');
		putchar('r');
		putchar('t');
		a = number_stack.top();
		number_stack.pop();
		result = sqrt(a);
		number_stack.push(result);
	}
	else if(c == 'F')
	{
		putchar(' ');
		putchar('f');
		putchar('a');
		putchar('b');
		putchar('s');
		a = number_stack.top();
		number_stack.pop();
		result = fabs(a);
		number_stack.push(result);
	}
}
void operator_push(stack<char> &operator_stack, stack<double> &number_stack, char c)
{
	char top;
	int p;
	if(c == ')')
	{
		top = operator_stack.top();
		while(top != '(' && top != 'S' && top != 'C' && top != 'E' && top != 'L' && top != 'W' && top != 'Q' && top != 'F')
		{
			operator_stack.pop();
			calculate(number_stack, top);
			top = operator_stack.top();
		}
		if(top == '(')
			operator_stack.pop();
		else
		{
			operator_stack.pop();
			calculate(number_stack, top);
		}
	}
	else
	{
		p = precedence(c);
		if(c == 'P' || c == 'N')
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
void operator_clear(stack<char> &operator_stack, stack<double> &number_stack)
{
	char top;
	while(operator_stack.top() != 'H')
	{
		top = operator_stack.top();
		operator_stack.pop();
		calculate(number_stack, top);
	}
}
void number_push(stack<double> &number_stack, double num)
{
	printf(" %.6f",num);
	number_stack.push(num);
}
int main()
{
	stack<char> operator_stack;
	operator_stack.push('H');
	stack<double> number_stack;
	char c;
	double num = 0;
	double digitnow = 1;
	bool nonempty = 0; 
	bool end_parenthesis = 0;
	bool dot = 0;
	bool start = 1;
	while((c = getchar()) != EOF)
	{
		if(c != ' ')
			character_switch(operator_stack, number_stack, c, nonempty, end_parenthesis, dot, num, digitnow, start);
	}
}
void character_switch(stack<char> &operator_stack, stack<double> &number_stack, char c, bool &nonempty, bool &end_parenthesis, bool &dot, double &num, double &digitnow, bool &start)
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
		{
			number_push(number_stack, num);
			dot = 0;
		}
		operator_clear(operator_stack, number_stack);
		putchar('\n');
		printf("RESULT: %.6f\n", number_stack.top());
		number_stack.pop();
		num = 0;
		nonempty = 0;
		start = 1;
	}
	else if('0' <= c && c <= '9')
	{
		if(dot)
		{
			digitnow /= 10;
			num += digitnow * (c - '0');
		}
		else
		{
			nonempty = 1;
			num *= 10;
			num += (c - '0');
		}
	}
	else if(c == '.')
	{
		dot = 1;
		digitnow = 1;
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
			dot = 0;
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
			dot = 0;
			operator_push(operator_stack, number_stack, c);
		}
		else if(end_parenthesis)
			operator_push(operator_stack, number_stack, c);
		else
			operator_push(operator_stack, number_stack, 'N');
	}
	else if(c == ',')
	{
		if(nonempty)
		{
			number_push(number_stack, num);
			nonempty = 0;
			num = 0;
			dot = 0;
		}
	}
	else
	{
		if(nonempty)
		{
			number_push(number_stack, num);
			nonempty = 0;
			num = 0;
			dot = 0;
		}
		if(c == 's')
		{
			next = getchar();
			if(next == 'i') //sin
			{
				getchar(); // n
				next = getchar();
				while(next != '(')
					next = getchar();
				operator_stack.push('S');
			}
			else // sqrt 
			{
				getchar(); //r
				getchar(); //t
				next = getchar();
				while(next != '(')
					next = getchar();
				operator_stack.push('Q');
			}
		}
		else if(c == 'c') // cos
		{
			getchar(); //o
			getchar(); //s
			next = getchar();
			while(next != '(')
				next = getchar();
			operator_stack.push('C');
		}
		else if(c == 'e') // exp
		{
			getchar(); //x
			getchar(); //p
			next = getchar();
			while(next != '(')
				next = getchar();
			operator_stack.push('E');
		}
		else if(c == 'l') // log
		{
			getchar(); //o
			getchar(); //g
			next = getchar();
			while(next != '(')
				next = getchar();
			operator_stack.push('L');
		}
		else if(c == 'p') // pow
		{
			getchar(); //o
			getchar(); //w
			next = getchar();
			while(next != '(')
				next = getchar();
			operator_stack.push('W');
		}			
		else if(c == 'f') // fabs
		{
			getchar(); //a
			getchar(); //b
			getchar(); //s
			next = getchar();
			while(next != '(')
				next = getchar();
			operator_stack.push('F');
		}					
		else
			operator_push(operator_stack, number_stack, c);
	}
	if(c == ')')
		end_parenthesis = 1;
	else
		end_parenthesis = 0;	
}
					
			