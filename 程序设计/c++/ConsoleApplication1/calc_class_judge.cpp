#include "calc_class.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//���캯��
SC_CALC::SC_CALC()
{
	calc_db_op_list.push_back('+');
	calc_db_op_list.push_back('-');
	calc_db_op_list.push_back('*');
	calc_db_op_list.push_back('/');
	calc_db_op_list.push_back('^');
	calc_db_op_list.push_back('r');
	calc_db_op_list.push_back('%');
	calc_db_op_list.push_back('(');
	calc_db_op_list.push_back(')');
	calc_db_op_list.push_back('#');
	//��ʼ��˫Ŀ��������ȼ�
	calc_db_op_table.insert(make_pair(make_pair('+', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '%'), '<'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('-', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '%'), '<'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('*', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('*', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('*', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('*', '%'), '>'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('/', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('/', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('/', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('/', '%'), '>'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('(', '+'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '-'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', ')'), '='));
//	calc_db_op_table.insert(make_pair(make_pair('(', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('(', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '%'), '<'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair(')', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '/'), '>'));
//	calc_db_op_table.insert(make_pair(make_pair(')', '('), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', 'r'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '^'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '%'), '>'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('r', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('r', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', 'r'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '^'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '%'), '>'));
	/////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('^', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('^', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', 'r'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '^'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '%'), '>'));
	/////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('#', '+'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '-'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '('), '<'));
//	calc_db_op_table.insert(make_pair(make_pair('#', ')'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '#'), '='));
	calc_db_op_table.insert(make_pair(make_pair('#', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '%'), '<'));
	///////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('%', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '%'), '>'));
	//��ʼ����Ŀ������б�ͳ�������Ϊ��Ŀ���㣬���������Ϊ˫Ŀ���㣩��˳���������������
	calc_sg_op_list.push_back("arcsin(");
	calc_sg_op_list.push_back("arctan(");
	calc_sg_op_list.push_back("stdevp[");
	calc_sg_op_list.push_back("arcos(");
	calc_sg_op_list.push_back("log10(");
	calc_sg_op_list.push_back("stdev[");
	calc_sg_op_list.push_back("varp[");
	calc_sg_op_list.push_back("sinh(");
	calc_sg_op_list.push_back("cosh(");
	calc_sg_op_list.push_back("tanh(");
	calc_sg_op_list.push_back("fact(");
	calc_sg_op_list.push_back("sin(");
	calc_sg_op_list.push_back("cos(");
	calc_sg_op_list.push_back("tan(");
	calc_sg_op_list.push_back("log(");
	calc_sg_op_list.push_back("pow(");
	calc_sg_op_list.push_back("exp(");
	calc_sg_op_list.push_back("avg[");
	calc_sg_op_list.push_back("sum[");
	calc_sg_op_list.push_back("var[");
	calc_sg_op_list.push_back("ln(");
	//��ʼ����Ŀ�������������,����a��ʾ����Ӧ�У�-a��������
	min_argu.insert(make_pair("cuberoot(", 1));
	min_argu.insert(make_pair("arcsin(", 1));
	min_argu.insert(make_pair("arctan(", 1));
	min_argu.insert(make_pair("stdevp[", -1));
	min_argu.insert(make_pair("arcos(", 1));
	min_argu.insert(make_pair("log10(", 1));
	min_argu.insert(make_pair("stdev[", -2));
	min_argu.insert(make_pair("varp[", -1));
	min_argu.insert(make_pair("sinh(", 1));
	min_argu.insert(make_pair("cosh(", 1));
	min_argu.insert(make_pair("tanh(", 1));
	min_argu.insert(make_pair("fact(", 1));
	min_argu.insert(make_pair("sqrt(", 1));
	min_argu.insert(make_pair("sin(", 1));
	min_argu.insert(make_pair("cos(", 1));
	min_argu.insert(make_pair("tan(", 1));
	min_argu.insert(make_pair("log(", 2));
	min_argu.insert(make_pair("pow(", 2));
	min_argu.insert(make_pair("exp(", 1));
	min_argu.insert(make_pair("arg[", -1));
	min_argu.insert(make_pair("sum[", -1));
	min_argu.insert(make_pair("var[", -2));
	min_argu.insert(make_pair("ln(", 1));
}


//���뺯��
void SC_CALC::calc_input()
{
	cout << ">>" << flush;
	getline(cin, calc_expression);
}
void SC_CALC::calc_input(string str)
{
	calc_expression = str;
}

void SC_CALC::calc_replace()
{
	string::size_type start_loc;
	while ((start_loc = calc_expression.find("ans")) != string::npos)
	{
		if (calc_history_res.empty() || calc_history_res.back() == "���д���")
		{
			calc_expression.replace(start_loc, ((string)"ans").size(), "(0)");
		}
		else
		{

			calc_expression.replace(start_loc, ((string)"ans").size(), "(" + calc_history_res.back() + ")");
		}
	}

	for (map<string, string>::iterator p = calc_const.begin(); p != calc_const.end();++p)
	{
		while ((start_loc = calc_expression.find(p->first)) != string::npos)
		{
			calc_expression.replace(start_loc, (p->first).size(), p->second);
		}
	}
}

//�������
void SC_CALC::calc_output()
{
	string ops = calc_calc(calc_expression);
	for (string::iterator p = ops.begin(); p != ops.end(); ++p)
	{
		//������
		if ((*p<'0' || *p>'9') &&*p != '-'&&*p != 'e'&&*p!='.'&&*p!='('&&*p!=')')
		{
			ops= "�������";
			break;
		}
	}
	//ȥ��ͷβ����
	if (ops.back() == ')')
	{
		ops.erase(ops.begin());
		ops.pop_back();
		//תΪϰ���Ķ��ĸ�ʽ����β��0��
		if (ops.front() == '.')
		{
			ops = "0" + ops;
		}
		if (ops.back() == '.')
		{
			ops += "0";
		}
	}
	//����ʽ���Ľ��������ʷ���
	calc_history_res.push_back(ops);
	cout <<"=" <<ops << endl<<endl;
}


void SC_CALC::calc_format()
{
	string::size_type len = calc_expression.size();
	int c = 'a' - 'A';
	//����д��ĸתΪСд
	for (string::size_type i = 0; i < len;++i)
	{
		if (calc_expression[i]>='A'&&calc_expression[i]<='Z')
		{
			calc_expression[i] += c;
		}
	}
	//�����ո�
	for (string::iterator p = calc_expression.begin(); p != calc_expression.end();++p)
	{
		if (*p==' '||*p=='\t')
		{
			p=--calc_expression.erase(p);
		}
	}
	calc_replace();
	//����ʽ������ʽ������ʷ��¼
	calc_history_equ.push_back(calc_expression);
	//���������㼰ģ����תΪ��Ԫ����
	string::size_type start_loc;
	while ((start_loc = calc_expression.find("cuberoot")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"cuberoot").size(), "3r");
	}
	while ((start_loc = calc_expression.find("sqrt")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"sqrt").size(), "2r");
	}
	while ((start_loc = calc_expression.find("root")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"root").size(), "r");
	}
	while ((start_loc = calc_expression.find("mod")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"mod").size(), "%");
	}
#ifndef NDEBUG
	cout << "mult_format----calc_expression:" << calc_expression << endl;
#endif
}

//�ж������Ƿ�Ϸ�
bool SC_CALC::calc_judge()
{
	//��ʽ��
	calc_format();
	//���Ų�ƥ��
	if (!bracket_match(calc_expression))return false;
	//��������������������ַ�
	if (!excess_sym(calc_expression))return false;
	//�������Ĺ�ϵ���Ϸ�
	if (!op_pass(calc_expression))return false;
	//����������������Ϸ�
	if (!argu_num(calc_expression))return false;
	return true;
}

//����ƥ���жϺ���
bool SC_CALC::bracket_match(string str)
{
	vector<char> inn;
	for (string::iterator p = str.begin(); p != str.end(); ++p)
	{
		//���������ţ�ѹ��ջ��
		if (*p=='['||*p=='(')
		{
			inn.push_back(*p);
		}
		else
		{
			switch (*p)
			{
				//���������ţ���ջ���Ƚϣ�ƥ������ջ�����򷵻�false
			case ']':
				if (!inn.empty()&& inn.back() == '[')inn.pop_back();
				else return false;
				break;
			case ')':
				if (!inn.empty() && inn.back() == '(')inn.pop_back();
				else return false;
				break;
			default:break;
			}
		}
	}
	//ջ����ƥ��
	return inn.empty();
}

//������ż�⺯��
bool SC_CALC::excess_sym(string str)
{
	string::size_type start_loc;
	//ɾ������
	for (vector<string>::iterator p = calc_sg_op_list.begin(); p != calc_sg_op_list.end();++p)
	{
		while ((start_loc = str.find(*p)) != string::npos)
		{
			str.erase(start_loc,(*p).size());
		}
	}
	//ɾ�������
	for (vector<char>::iterator p = calc_db_op_list.begin(); p != calc_db_op_list.end();++p)
	{
		while ((start_loc = str.find(*p)) != string::npos)
		{
			str.erase(start_loc,  1);
		}
	}
	//ɾ�����ţ�
	while ((start_loc = str.find(",")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
	//ɾ��]
	while ((start_loc = str.find("]")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
	//ɾ��)
	while ((start_loc=str.find(")"))!=string::npos)
	{
		str.erase(start_loc, 1);
	}
	//ɾ��e
	while ((start_loc = str.find("e")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
	//ɾ��.
	while ((start_loc = str.find(".")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
#ifndef NDEBUG
	cout << "excess_sym----str:" << str << endl;
#endif
	for (string::iterator p = str.begin(); p != str.end();++p)
	{
		//�������⻹�������ַ��򲻺Ϸ�
		if (*p<'0' || *p>'9')return false;
	}
	return true;
}

//�������ϵ�ж�
bool SC_CALC::op_pass(string str)
{
	//ǰ��ӿ�ʼ���������
	str += "#";
	str = "#" + str;
	map<int, string> loc_sym;
	string::size_type start_loc;
	//��¼����λ��
	//�Ӻ���ǰ������ȷ�������������ᱻ�ض�
	long sg_num = calc_sg_op_list.size();
	for (long i = sg_num - 1; i >= 0;--i)
	{
		start_loc = -1;
		while ((start_loc = str.find(calc_sg_op_list[i],start_loc+1)) != string::npos)
		{
			loc_sym[start_loc] = calc_sg_op_list[i];
		}
	}
	vector<int> func;
	string last_sym("num");
	string::size_type sym_num=str.size();
	/*************************************************************************/
	/*num:����	#��# db�������  sg������ ������  ������ ]��]					 */
	/*************************************************************************/
	for (string::size_type i = 0; i < sym_num;++i)
	{
		if (str[i] >= '0'&&str[i] <= '9')
		{
			//����ǰ������������
			if (last_sym == ")" || last_sym == "]")
			{
				return false;
			}
			//��״̬Ϊ����
			else
			{
				last_sym = "num";
			}
		}
		else
		{
			switch (str[i])
			{
			case '+':
			case '-':
				//��+������-��ǰ�����������
				if (last_sym == "db" || last_sym == ".")
				{
					return false;
				}
				else
				{
					last_sym = "db";
				}
				break;
			case '*':
			case '/':
			case 'r':
			case '%':
			case '^':
				//�����ǰ�����С�#�������������.����������������
				if (last_sym == "#" || last_sym == "db" || last_sym == "." || last_sym == "sg" || last_sym == ",")
				{
					return false;
				}
				else
				{
					last_sym = "db";
				}
				break;
			case '#':
				if (last_sym == "#" || last_sym == "db" || last_sym == "." || last_sym == "sg" || last_sym == ",")
				{
					return false;
				}
				else
				{
					last_sym = "#";
				}
				break;
			case '(':
				if (last_sym == "num" || last_sym == "." || last_sym == ")"||last_sym=="]")
				{
					return false;
				}
				else
				{
					last_sym = "(";
					if (!func.empty())
					{
						func.push_back(0);
					}
				}
				break;
			case ')':
				if (last_sym == "db" || last_sym == "#" || last_sym == "sg" || last_sym == "." || last_sym == ",")
				{
					return false;
				}
				else
				{
					if (!func.empty()&&func.back()!=2)
					{
						func.pop_back();
					}
					else
					{
						if (!func.empty())
						{
							return false;
						}
					}
					last_sym = ")";
				}
				break;
			case '.':
				if (last_sym==")"||last_sym=="."||last_sym=="]")
				{
					return false;
				}
				else
				{
					last_sym = ".";
				}
				break;
			case ',':
				if (last_sym == "db" || last_sym == "sg" || last_sym == "." || last_sym == "#" || last_sym == ",")
				{
					return false;
				}
				else
				{
					if (func.empty()||func.back()==0)
					{
						return false;
					}
					else
					{
						last_sym = ",";
					}
				}
				break;
			case ']':
				if (last_sym == "(" || last_sym == "db" || last_sym == "sg" || last_sym == "." || last_sym == "#" || last_sym == ",")
				{
					return false;
				}
				else
				{
					if (func.empty()||func.back()!=2)
					{
						return false;
					}
					else
					{
						last_sym = "]";
						func.pop_back();
					}
				}
				break;
				//��e���⴦��
			case 'e':
				if (loc_sym[i]=="")
				{
					loc_sym.erase(i);
					if (last_sym == ")" || last_sym == "]"||last_sym=="#"||last_sym=="db"||last_sym=="sg"||last_sym==",")
					{
						return false;
					}
					else
					{
						last_sym = "num";
					}
					break;
				}
			default:
				if (last_sym == "." || last_sym == ")" || last_sym == "]")
				{
					return false;
				}
				else
				{
					if (loc_sym[i][loc_sym[i].size() - 1] == '(')
					{
						func.push_back(1);
					}
					else
					{
						func.push_back(2);
					}
					i += loc_sym[i].size()-1;
					last_sym = "sg";
				}
				break;
			}
		}
	}
#ifndef NDEBUG
	cout << "op_pass----str:" << str << endl;
#endif
	return func.empty();
}

//���������ж�
bool SC_CALC::argu_num(string str)
{
	map<int, string> loc_sym;
	string::size_type start_loc;
	//�Ӻ���ǰ������ȷ�������Ų��ᱻ�ض�
	long sg_num = calc_sg_op_list.size();
	for (long i = sg_num - 1; i >= 0; --i)
	{
		start_loc = -1;
		while ((start_loc = str.find(calc_sg_op_list[i], start_loc + 1)) != string::npos)
		{
			loc_sym[start_loc] = calc_sg_op_list[i];
		}
	}
	int bracket_num;
	int argu;
	for (map<int, string>::iterator p = loc_sym.begin(); p != loc_sym.end(); ++p)
	{
		bracket_num = 1;
		argu = 0;
		for (int j = p->first+p->second.size() + 1; j < str.size(); ++j)
		{
			switch (str[j])
			{
			case '[':
			case '(':
				++bracket_num;
				break;
			case ']':
			case ')':
				--bracket_num;
				break;
			case ',':
				if (bracket_num==1)
				{
					++argu;
				}
				break;
			}
			if (bracket_num == 0)
			{
				++argu;
				if (min_argu[p->second]>0)
				{
					if (min_argu[p->second]!=argu)
					{
						return false;
					}
					break;
				}
				else
				{
					if (0-min_argu[p->second]>argu)
					{
						return false;
					}
					break;
				}
			}
		}
	}
	return true;
}