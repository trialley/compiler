/*******************Lexer***********************
���ܣ�������ɵ�һ������������ַ�����ǳ������ʵĴ���
��ں���:Lexer����
���룺Դ�����ַ���
��������Ա��
���������ݣ�
�����ĺ�����
*************************************************/
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <regex>//������ʽ
using namespace std;
enum L_STAGE { OPRATER, NUM, SPACE, LETTER,COMMENT};
/*����һ�����ʽ��*/
struct L_pair{
	enum L_STAGE L_type;//���浥�ʵ�����
	int num;//���浥�ʵ�λ��
	string content;//���浥�ʵ�����
};
/*�ڴʷ�����ʱ�ڱ�������ʷ���������Ǵʷ���������������﷨������������*/
typedef vector<L_pair> L_table;

/*************************************************
��������:Lexer
����:�ʷ������Ŀ��Žӿڣ��������ַ��������ؽ��
����:NoComment
����: string source
����:L_table=vector<L_pair>
*************************************************/
L_table Lexer(string source);

/*************************************************
��������:NoComment
����:�ʷ������ĵ�һ����ȥ������ע��
����:
����:string Դ����
����:string ȥ��ע�͵�Դ���� 
*************************************************/
string NoComment(string source);

