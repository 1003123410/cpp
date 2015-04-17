#include "calc_class.h"
#include <iostream>
#include <vector>
#include <string>

bool SC_CALC::is_cmd()
{
	if (calc_expression == "hst")
	{
		calc_history();
		return true;
	}
	else if (calc_expression == "exit")
	{
		exit(0);
	}
	else if (calc_expression == "hlp")
	{
		calc_help();
		return true;
	}
	else if (calc_expression == "cls")
	{
		system("cls");
		return true;
	}
	else if (calc_expression == "set")
	{
		calc_set();
		return true;
	}
	else
	{
		return false;
	}
}

void SC_CALC::calc_history()
{
	vector<string>::size_type num = calc_history_equ.size();
	cout << "history:" << endl;
	for (vector<string>::size_type i = 0; i < num; ++i)
	{
		cout << calc_history_equ[i] << endl << "\t\t\t\t" <<"=" << calc_history_res[i] << endl;
	}
}

void SC_CALC::calc_help()
{
	cout << "SC Calculator ʹ��˵����" << endl << endl
		<< "SC_Calclator ��ֱ��������ʽ�������м��㣬���⻹�в鿴��ʷ������." << endl << endl
		<< "һ������֧�ֵ�����������£�" << endl << endl
		<< "1.���" << endl
		<< "cls\t\t\t����" << endl
		<< "hst\t\t\t�鿴��ʷ" << endl
		<< "hlp\t\t\t��ʾ�˰���" << endl
		<< "exit\t\t\t�˳�����" << endl
		<< "set\t\t\tset����" << endl << endl
		<< "set���ܽ��ܣ�" << endl<<endl
		<< "set���ܵ������Ϊ�˽�ʡ�û�����Ƶ��ʹ�õ���ʽ�Ĺ��������������á�const1��Ϊ��1,2,9,36,7,15�����ڼ���ʱ���롰avg[cosnt1]�����൱�����롰avg[1,2,9,36,7,15]��" << endl<<endl
		<< "ע�⣺set���ܲ����ִ�Сд����Con��cON����һ������" << endl<<endl
		<< "��һ��set������һ��set������ǰ׺�������ֻᱻ���Σ���ͬʱ���ڡ�con���͡�conc������conc������ʧЧ" << endl<<endl
		<< "��Ҫ���Ե���set������Ҫ����con=ca��  ca=1+2����ᵼ������Ƿ�"
		<< endl << endl;
	system("pause");
		cout<< "2.�������" << endl
		<< "+\t\t\t˫Ŀ��������ӡ�   ��Ŀ�����������" << endl
		<< "-\t\t\t˫Ŀ�����������   ��Ŀ�����������" << endl
		<< "*\t\t\t˫Ŀ��������ˡ�" << endl
		<< "/\t\t\t˫Ŀ�����������" << endl
		<< "mod\t\t\t˫Ŀ�������ȡģ��" << endl
		<< "^\t\t\t˫Ŀ��������η���" << endl
		<< "e\t\t\t��ѧ������" << endl << endl;
	system("pause");
	cout << "3.������" << endl
		<< "arcsin(x)\t\t\t�����Ǻ�������ͬ��" << endl
		<< "arcos(x)" << endl
		<< "arctan(x)" << endl
		<< "sin(x)\t\t\t���Ǻ�������ͬ��" << endl
		<< "cos(x)" << endl
		<< "tan(x)" << endl
		<< "sinh(x)\t\t\t˫����������ͬ��" << endl
		<< "cosh(x)" << endl
		<< "tanh(x)" << endl
		<< "log(x,nBase)\t\t\t��nBaseΪ�ף�x�Ķ���" << endl
		<< "log10(x)\t\t\t��10Ϊ�ף�x�Ķ���" << endl
		<< "ln(x)\t\t\t����Ȼ����Ϊ�ף�x�Ķ���" << endl
		<< "pow(x,nPower)\t\t\tx��nPower�η�" << endl
		<< "exp(x)\t\t\te��x�η�" << endl
		<< "fact(x)\t\t\tx�Ľ׳ˣ�x�ᱻǿ��תΪ������" << endl
		<< "sqrt(x)\t\t\tx������ƽ������xΪ�Ǹ�����" << endl
		<< "cuberoot(x)\t\t\tx�����η���" << endl
		<< "yroot(x)\t\t\tx��y�η���" << endl << endl;
	system("pause");
	cout << "4.ͳ��" << endl
		<< "avg[����]\t\t\t���ϵ�����ƽ��ֵ��Ԫ����,�ָ�����ͬ��\t\t������1��������" << endl
		<< "sum[����]\t\t\t���ϵ�ͳ��\t\t������1��������" << endl
		<< "var[����]\t\t\t���ϵĹ��Ʒ���\t\t������2��������" << endl
		<< "varp[����]\t\t\t���ϵ����巽��\t\t������1��������" << endl
		<< "stdev[����]\t\t\t���ϵĹ��Ʊ�׼��\t\t������2��������" << endl
		<< "stdevp[����]\t\t\t���ϵ������׼��\t\t������1��������" << endl << endl;
	system("pause");
	cout << "����������Ϣ" << endl << endl
		<< "����Ƿ�\t\t\tԭ��" << endl
		<< "\t\t\t\t���뺯������������ƥ��\tsin(2,3)   var[2.3]" << endl
		<< "\t\t\t\t�����֮��Ĺ�ϵ�Ƿ�\t2+*6   5/+7" << endl
		<< "\t\t\t\t����������\tsim(5)   poe(9)" << endl
		<< "�������\t\t\tԭ��" << endl
		<<"\t\t\t\t�����˷Ƿ�����\t5/0    sqrt(-3)" << endl << endl;
}

void SC_CALC::calc_set()
{
	cout << "set����" << endl
		<< "������һ�����е�set�������Ḳ�Ǵ�ֵ" << endl;
	cout << "set��:" << flush;
	string name, value;
	getline(cin, name);
	cout << "setֵ��" << flush;
	getline(cin, value);
	string::size_type len = name.size();
	int c = 'a' - 'A';
	//����д��ĸתΪСд
	for (string::size_type i = 0; i < len; ++i)
	{
		if (name[i] >= 'A'&&name[i] <= 'Z')
		{
			name[i] += c;
		}
	}
	//�����ո�
	for (string::iterator p = name.begin(); p !=name.end(); ++p)
	{
		if (*p == ' ' || *p == '\t')
		{
			p = --name.erase(p);
		}
	}
	len = value.size();
	for (string::size_type i = 0; i < len; ++i)
	{
		if (value[i] >= 'A'&&value[i] <= 'Z')
		{
			value[i] += c;
		}
	}
	//�����ո�
	for (string::iterator p = value.begin(); p != value.end(); ++p)
	{
		if (*p == ' ' || *p == '\t')
		{
			p = --value.erase(p);
		}
	}
	calc_const[name] = value;
	cout << "����/�޸ĳɹ���" <<endl<< endl;
}