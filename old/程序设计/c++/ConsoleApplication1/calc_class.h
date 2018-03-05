#ifndef _CALC_DATASTRUCT_H_
#define _CALC_DATASTRUCT_H_ 1
#include <vector>
#include <string>
#include <map>
using namespace std;
class SC_CALC
{
public:
	//���캯��
	SC_CALC();
	//����
	void calc_input();
	void calc_input(string);
	//�ж�����Ϸ���
	bool calc_judge();
	//���
	void calc_output();
	//��������
	bool is_cmd();
	//��ʷ��ʽ
	vector<string> calc_history_equ;
	//��ʷ���
	vector<string> calc_history_res;
private:
	//��Ŀ������б�
	vector<string> calc_sg_op_list;
	//˫Ŀ������б�
	vector<char> calc_db_op_list;
	//��Ŀ��������ȼ��б�
	map<pair<char,char>, char> calc_db_op_table;
	//���ʽ�ַ���
	string calc_expression;
	//��ʽ�����ʽ�ַ�������
	void calc_format();
	//����ƥ���жϺ���
	bool bracket_match(string);
	//��������жϺ���
	bool excess_sym(string);
	//�������ϵ�Ϸ��жϺ���
	bool op_pass(string);
	//��������������Ϸ��ж�
	bool argu_num(string);
	//�������㷨
	string calc_calc(string);
	//ֻ����˫Ŀ������ļ���
	string easy_calc(string);
	//���е�Ŀ������ļ���
	string mult_calc(string,string);
	//��������
	map<string, int> min_argu;
	//��ʾ��ʷ
	void calc_history();
	//��ʾ����
	void calc_help();
	//�Ľ��ĳ˷�����
	double calc_pow(double,double);
	//С��ת����
	void dectosc(double, int&, int&);
	//�滻
	void calc_replace();
	//����ʽ
	map<string, string> calc_const;
	//set����
	void calc_set();
};
#endif