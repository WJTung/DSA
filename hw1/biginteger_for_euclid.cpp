#include<iostream>
#include<cstring>
#include<cstdlib>
#include"biginteger_for_euclid.h"
int largerequal(int a[1000], int b[1000], int starta, int digit) // a >= b
{
	int i;
	for(i = 0; i < digit; i++)
	{
		if(a[starta-i] > b[digit-1-i])
			return 1;
		if(a[starta-i] < b[digit-1-i])
			return 0;
	}
	return 1;
}
void minus(int a[1000], int b[1000], int starta, int digit)// a -= b
{
	int i;
	for(i = digit - 1; i >= 0; i--)
	{
		a[starta-i] -= b[digit-1-i];
		if(a[starta-i] < 0)
		{
			a[starta-i] += 10;
			a[starta-i+1]--;
		}			
	}
}
BigInteger::BigInteger()
{
	int i;
	for(i = 0; i < 1000; i++)
		array[i] = 0;
	digit = 0;
}
BigInteger::BigInteger(const int& n)
{
	int i, num = n;
	for(i = 0; i < 1000; i++)
		array[i] = 0;
	i = 0;
	digit = 0;
	while(num > 0)
	{
		array[i] = num % 10;
		num /= 10;
		i++;
		digit++;
	}
}

BigInteger::BigInteger(const std::string& t)
{
	std::string str;
	str = t;
	int i, l = str.length();
	for(i = 0; i < 1000; i++)
		array[i] = 0;
	for(i = 0; i < l; i++)
		array[i] = (str[l-i-1] - '0');
	digit = l;
}

BigInteger::BigInteger(const BigInteger& n)
{
	int i;
	for(i = 0; i < 1000; i++)
		array[i] = 0;
	for(i = 0; i < n.digit; i++)
		array[i] = n.array[i];
	digit = n.digit;
}
BigInteger::~BigInteger()
{
}
bool BigInteger::operator<(const BigInteger& n) const
{
	int i;
	if(this->digit < n.digit)
		return 1;
	if(this->digit > n.digit)
		return 0;
	for(i = (this->digit - 1); i >= 0; i--)
	{
		if(this->array[i] < n.array[i])
			return 1;
		if(this->array[i] > n.array[i])
			return 0;
	}
	return 0;
}
const BigInteger BigInteger::operator%(const BigInteger& n) const
{
	int i;
	BigInteger result(*this);
	BigInteger t(n);
	for(i = (result.digit - 1); i >= (t.digit - 1); i--)
	{
		result.array[i] += (result.array[i+1] * 10);
		result.array[i+1] = 0;
		while(largerequal(result.array, t.array, i, t.digit))
			minus(result.array, t.array, i, t.digit);
	}
	for(i = 999; i >= 0; i--)
	{
		if(result.array[i] != 0)
		{
			result.digit = i + 1;
			return result;
		}
	}
	result.digit = 0;
	return result;
}
BigInteger& BigInteger::operator=(const BigInteger& n)
{
	int i;
	for(i = 0; i < 1000; i++)
		this->array[i] = 0;
	for(i = 0; i < n.digit; i++)
		this->array[i] = n.array[i];
	this->digit = n.digit;
	return *this;
}
bool BigInteger::iszero() const 
{
	if(this->digit == 0) 
		return 1;
	return 0;
}
std::ostream& operator<<(std::ostream& s, const BigInteger& n)
{
	int i;
	for(i = n.digit - 1; i >= 0; i--)
		s<<n.array[i];
	return s;
}