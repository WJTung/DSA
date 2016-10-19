#include<iostream>
#include<cstring>
#include<cstdlib>
#include"biginteger_for_binary.h" 
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

const BigInteger BigInteger::operator-(const BigInteger& n) const
{
	int i;
	BigInteger result;
	for(i = 0; i < 1000; i++)
		result.array[i] = 0;
	for(i = 0; i < this->digit; i++)
	{
		result.array[i] += (this->array[i] - n.array[i]);
		if(result.array[i] < 0)
		{
			result.array[i] += 10;
			result.array[i+1]--;
		}
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

const BigInteger BigInteger::operator*(const BigInteger& n) const
{	
	int i, j;
	BigInteger result;
	for(i = 0; i < 1000; i++)
		result.array[i] = 0;
	for(i = 0; i < this->digit; i++)
	{
		for(j = 0; j < n.digit; j++)
			result.array[i+j] += (this->array[i] * n.array[j]);
	}
	for(i = 0; i < 1000; i++)
	{
		result.array[i+1] += (result.array[i] / 10);
		result.array[i] %= 10;
	}
	for(i = 999; i >=0; i--)
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

BigInteger& BigInteger::operator*=(int n)
{
	int i;
	for(i = 0; i < this->digit; i++)
		this->array[i] *= n;
	for(i = 0; i < 999; i++)
	{
		this->array[i+1] += (this->array[i] / 10);
		this->array[i] %= 10;
	}
	for(i = 999; i >=0; i--)
	{
		if(this->array[i] != 0)
		{
			this->digit = i + 1;
			return *this;
		}
	}
	this->digit = 0;
	return *this;
}

BigInteger& BigInteger::operator/=(int n)
{
	int r = 0, i;
	for(i = this->digit - 1; i >= 0; i--)
	{
		r *= 10;
		r += this->array[i];
		this->array[i] = r / n;
		r %= n;
	}
	for(i = 999; i >=0; i--)
	{
		if(this->array[i] != 0)
		{
			this->digit = i + 1;
			return *this;
		}
	}
	this->digit = 0;
	return *this;
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

bool BigInteger::iseven()
{
	if(this->array[0] % 2 == 0)
		return 1;
	return 0;
}

bool BigInteger::iszero()
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
		
	
		
		
		