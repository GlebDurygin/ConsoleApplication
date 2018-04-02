// ConsoleApplicationDuryginGleb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>  
#include <string> 
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;
static const char characters[] = { '*','+','/','-','(',')' };
static const char symbols[] = { '0','1','2','3','4','5','6','7','8','9','(','.','-','*','/','+',')' };

bool read_str(string str) {
	int count_brackets = 0;
	bool flag = true;
	regex rx_1("([\\d\-\(]*)");
	regex rx_2("([\\d\)]*)");
	if (!(regex_match(str.substr(0, 1), rx_1))) {
		cerr << "ERORR: Invalid first symbol" << endl << "Please, try again!" << endl;
		return false;
	}
	if (!(regex_match(str.substr(str.length() - 1, 1), rx_2))) {
		cerr << "ERORR: Invalid last symbol" << endl << "Please, try again!" << endl;
		return false;
	}
	for (int i = 0; i != str.length(); ++i) {
		if (str[i] == '(') ++count_brackets;
		if (str[i] == ')') --count_brackets;
		bool flag_1 = false;
		for (int j = 0; j < 17; j++) {
			if (str[i] == symbols[j])
			{
				bool flag_2 = false;
				if (str[i] == '.') {
					for (int k = 0; k < 6; k++)
						if (str[i + 1] == characters[k]) flag_2 = true;
					if (flag_2) {
						cerr << "ERORR: Invalid number" << endl << "Please, try again!" << endl;
						return false;
					}
					else {
						int k = i + 1;
						while (k < str.length() && (str[k] != '(' && str[k] != ')' && str[k] != '-' && str[k] != '+' && str[k] != '*' && str[k] != '/' && str[k] != '.'))
							k++;
						if (k < str.length() && str[k] == '.') {
							cerr << "ERORR: Invalid number" << endl << "Please, try again!" << endl;
							return false;
						}
					}
				}
				if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-') {
					for (int k = 0; k < 11; k++)
						if (str[i + 1] == symbols[k]) flag_2 = true;
					if (!flag_2) {
						cerr << "ERORR: Input error" << endl << "Please, try again!" << endl;
						return false;
					}
				}
				flag_1 = true;
			}
		}
		if (!flag_1) {
			cerr << "ERORR: Input error" << endl << "Please, try again!" << endl;
			return false;
		}
	}
	if (count_brackets != 0) {
		cerr << "ERORR: Error of bracket's balanse" << endl << "Please, try again!" << endl;
		return false;
	}
	return flag;
}

double addition(double a, double b)
{
	return (a + b);
}
double difference(double a, double b)
{
	return (a - b);
}
double multiplication(double a, double b)
{
	return (a * b);
}
double division(double a, double b)
{
	return (a / b);
}
bool checkForCharacter(string str)
{
	for (auto i = str.begin(); i != str.end(); ++i) {
		if (*i == '-' || *i == '+' || *i == '*' || *i == '/') return false;
	}
	return true;
}

double StrToDouble(string str) {
	double value = 0;
	for (int j = 0; j < str.length(); j++)
	{
		if (str[j] != '-') {
			value *= 10;
			value += str[j] - '0';
		}
	}
	if (str[0] == '-') return (-1)*value;
	else return value;
}

string DeleteBrackets(string str)
{
	int j = 0;
	bool flag = true;
	while ((j + 1) < str.length() && str[j] != ')')
		j++;
	if (j + 1 == str.length() && str.find(')') == -1) return str;
	else {
		int i = 0;
		while (str[j - i] != '(') {
			for (int k = 0; k < 4; k++) {
				if (str[j - i] == characters[k])
					if (k == 3 && (j - i == 0 || str[j - i - 1] == '(')) flag = true;
					else flag = false;
					if (!flag) return str;
			}
			i++;
		}
		return (str.substr(0, j - i) + str.substr(j - i + 1, i - 1) + str.substr(j + 1, str.length() - j - 1));
	}
}

string CalculateOneExpression(string str, char character, int pos)
{
	int i = 0;
	double value_1 = 0;
	double value_2 = 0;
	bool flag = true;
	int k = 0;
	string str_value_1 = str.substr(0, pos);
	if (str_value_1.find('.') != -1)
		if (str_value_1[0] == '-') value_1 = StrToDouble(str_value_1.substr(0, str_value_1.find('.'))) - StrToDouble(str_value_1.substr((str_value_1.find('.') + 1), str_value_1.length()))*pow(0.1, (str_value_1.length() - str_value_1.find('.') - 1));
		else value_1 = StrToDouble(str_value_1.substr(0, str_value_1.find('.'))) + StrToDouble(str_value_1.substr((str_value_1.find('.') + 1), str_value_1.length()))*pow(0.1, (str_value_1.length() - str_value_1.find('.') - 1));
	else value_1 = StrToDouble(str_value_1);
	string str_value_2 = str.substr(pos + 1, str.length());
	if (str_value_2.find('.') != -1) value_2 = StrToDouble(str_value_2.substr(0, str_value_2.find('.'))) + StrToDouble(str_value_2.substr((str_value_2.find('.') + 1), str_value_2.length()))*pow(0.1, (str_value_2.length() - str_value_2.find('.') - 1));
	else value_2 = StrToDouble(str_value_2);
	switch (character)
	{
	case '*':
		str = to_string(multiplication(value_1, value_2));
		break;
	case '/':
		str = to_string(division(value_1, value_2));
		break;
	case '-':
		str = to_string(difference(value_1, value_2));
		break;
	case '+':
		str = to_string(addition(value_1, value_2));
		break;
	}
	return str;
}

string SelectionOneExpression(string str, int pos, char character) {
	bool flag = true;
	int j = 1, k = 1;
	while (flag && pos + 1 >j) {
		for (int i = 0; i < 6; i++) {
			if (str[pos - j] == characters[i]) {
				if (str[pos - j] == '-' && (pos - j == 0 || str[pos - j - 1] == '(' || str[pos - j - 1] == ')')) flag = true;
				else flag = false;
			}
			if (!flag) {
				j--;
				break;
			}
		}
		j++;
	}
	flag = true;
	while (flag && pos + k - 1 < str.length()) {
		for (int i = 0; i < 6; i++) {
			if (str[pos + k] == characters[i])
			{
				if (str[pos + k] == '-' && k == 1) flag = true;
				else flag = false;
			}
			if (!flag) {
				k--;
				break;
			}
		}
		k++;
	}
	string substr = str.substr(pos - j + 1, k + j - 1);
	if ((pos + k) > str.length()) substr = str.substr(0, pos - j + 1) + CalculateOneExpression(substr, character, substr.find(character));
	else substr = str.substr(0, pos - j + 1) + CalculateOneExpression(substr, character, substr.find(character)) + str.substr(pos + k, str.length() - pos - k);
	return substr;
}

string CalculateOneBracket(string str) {
	bool flag = true;
	string substr = "";
	while (flag) {
		while (substr != str) {
			substr = str;
			str = DeleteBrackets(str);
		}
		if (str.find('*') != -1 || str.find('/') != -1)
		{
			int i = str.find('*');
			int j = str.find('/');
			if ((i > -1 && i < j) || (i > -1 && j == -1)) str = SelectionOneExpression(str, i, '*');
			if ((j > -1 && j < i) || (j > -1 && i == -1)) str = SelectionOneExpression(str, j, '/');
		}
		else {
			flag = false;
			if (str.find('+') != -1 || str.find('-') != -1)
			{
				int i = str.find('+');
				int j = str.find('-');
				if (j == 0 || (j == 1 && str[0] == '(')) {
					string substr = str.substr(1, str.length() - 1);
					if (substr.find('+') != -1 || substr.find('-') != -1) {
						i = substr.find('+');
						j = substr.find('-');
						if ((i > -1 && i < j) || (i > -1 && j == -1)) str = SelectionOneExpression(str, i + 1, '+');
						if ((j > -1 && j < i) || (j > -1 && i == -1)) str = SelectionOneExpression(str, j + 1, '-');
						flag = true;
					}
					else break;
				}
				else {
					if ((i > -1 && i < j) || (i > -1 && j == -1)) str = SelectionOneExpression(str, i, '+');
					if ((j > -1 && j < i) || (j > -1 && i == -1)) str = SelectionOneExpression(str, j, '-');
					flag = true;
				}
			}
		}
	}
	return str;
}

double Calculate(string substr) {
	string str = substr;
	while (1) {
		int j = 0;
		while ((j + 1) < str.length() && str[j] != ')')
			j++;
		if (j + 1 == str.length() && (str[0] == '(' || str.find('(') == -1)) {
			str = CalculateOneBracket(str);
			double value_1;
			if (str.find('.') != -1)
				if (str[0] == '-') value_1 = StrToDouble(str.substr(0, str.find('.'))) - StrToDouble(str.substr((str.find('.') + 1), str.length()))*pow(0.1, (str.length() - str.find('.') - 1));
				else value_1 = StrToDouble(str.substr(0, str.find('.'))) + StrToDouble(str.substr((str.find('.') + 1), str.length()))*pow(0.1, (str.length() - str.find('.') - 1));
			else value_1 = StrToDouble(str);
			return value_1;
		}
		else
		{
			int i = 0;
			while (str[j - i] != '(') i++;
			str = str.substr(0, j - i) + CalculateOneBracket(str.substr(j - i, i + 1)) + str.substr(j + 1, str.length() - j - 1);
		}
	}
}

int main()
{
	string str;
	cout << "	Enter the expression (allowed characters '(',')',+,-,*,/):" << endl;
	cin >> str;
	while (read_str(str) == false) cin >> str;
	if (read_str(str) != false) cout << round(Calculate(str) * 1000) / 1000 << endl;
	system("pause");
	return 0;
}


