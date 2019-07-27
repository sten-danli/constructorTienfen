#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class String;
ostream& operator<<(ostream& out, const String& s);

class String_rep
{
	friend class String;

	friend ostream& operator<<(ostream& out, const String& s);

public:
	String_rep(const char* str) :use_counter(0)
	{
		if (str == NULL)
		{
			data = new char[1];
			data[0] = '\0';
		}
		else
		{
			data = new char[strlen(str) + 1];
			strcpy(data, str);
		}
	}
public:
	String_rep(String_rep& s) :use_counter(0)
	{
		data = new char[strlen(s.data) + 1];
		strcpy(data, s.data);
	}
public:
	String_rep& operator=(String_rep& s)
	{
		if (this != &s)
		{
			delete[]this->data;
			data = new char[strlen(s.data) + 1];
			strcpy(data, s.data);
		}
		return *this;
	}
public:
	void increment()
	{
		++use_counter;
	}
	void decrement()
	{
		if (--use_counter == 0)
			delete this;
	}
	~String_rep()
	{
		delete[]data;
		data = NULL;
	}
private:
	char* data;
	int use_counter;
};

class String

{
	friend ostream& operator<<(ostream& out, const String& s);
public:

	String(const char* str = "")
	{
		rep = new String_rep(str);
		rep->increment();
	}
public:
	String(const String& s)
	{
		rep = s.rep;
		rep->increment();
	}
	~String()
	{
		rep->decrement();
	}
public:
	String& operator=(String& s)
	{
		if (this != &s)
		{
			rep->decrement();
			rep = s.rep;
			rep->increment();
		}
		return *this;
	}
public:
	void to_upper()
	{
		if (rep->use_counter > 1)
		{
			String_rep* new_rep = new String_rep(rep->data);
			rep->decrement();
			rep = new_rep;
			rep->decrement();

		}
		char* ch = rep->data;
		while (*ch != '\0')
		{
			*ch -= 32;
			++ch;
		}
	}

private:
	String_rep* rep;

};

ostream& operator<<(ostream& out, const String& s)
{
	out << s.rep->data;
	return out;
}
void main()
{
	String s1("hello");
	String s2 = s1;
	String s3;
	s3 = s2;
	s3.to_upper();
	cout << "s3 = " << s3 << endl;
	cout << "s1 = " << s1;


}