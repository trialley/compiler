// Lexical_Analysis.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "iostream"
using namespace std;
//�ʷ���������
//���ȶ����ֱ���
/*
��һ�ࣺ��ʶ��   letter(letter | digit)*  ���
�ڶ��ࣺ����    (digit)+  ���
�����ࣺ������(32)
auto       break    case     char        const      continue
default    do       double   else        enum       extern
float      for      goto     if          int        long
register   return   short    signed      sizeof     static
struct     switch   typedef  union       unsigned   void
volatile    while

�����ࣺ���  ��/*������//���� () { } [ ] " "  '
�����ࣺ����� <��<=��>��>=��=��+��-��*��/��^��

�����п������Ž��б��룺
<$,0>
<auto,1>
...
<while,32>
<+��33>
<-,34>
<*,35>
</,36>
<<,37>
<<=,38>
<>,39>
<>=,40>
<=,41>
<==,42>
<!=,43>
<;,44>
<(,45>
<),46>
<^,47>
<,,48>
<",49>
<',50>
<#,51>
<&,52>
<&&,53>
<|,54>
<||,55>
<%,56>
<~,57>
<<<,58>����
<>>,59>����
<[,60>
<],61>
<{,62>
<},63>
<\,64>
<.,65>
<?,66>
<:,67>
<!,68>
"[","]","{","}"
<����99  ,��ֵ>
<��ʶ��100 ����ʶ��ָ��>


*/

/****************************************************************************************/
//ȫ�ֱ����������ֱ�
/*
static char reserveWord[32][20] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};
//����������,������Ҫ������������
static char operatorOrDelimiter[36][10] = {
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
	"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
	"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
	"}", "\\", ".", "\?", ":", "!"
};

static  char IDentifierTbl[1000][50] = { "" };//��ʶ����
/****************************************************************************************/

/********���ұ�����*****************/
int searchReserve(char reserveWord[][20], char s[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(reserveWord[i], s) == 0)
		{//���ɹ����ң��򷵻��ֱ���
			return i + 1;//�����ֱ���
		}
	}
	return -1;//���򷵻�-1��������Ҳ��ɹ�����Ϊ��ʶ��
}
/********���ұ�����*****************/

/*********************�ж��Ƿ�Ϊ��ĸ********************/
bool IsLetter(char letter)
{//ע��C���������»���ҲΪ��ʶ����һ���ֿ��Է����ײ��������ط�
	if (letter >= 'a'&&letter <= 'z' || letter >= 'A'&&letter <= 'Z' || letter == '_')
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*********************�ж��Ƿ�Ϊ��ĸ********************/


/*****************�ж��Ƿ�Ϊ����************************/
bool IsDigit(char digit)
{
	if (digit >= '0'&&digit <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*****************�ж��Ƿ�Ϊ����************************/


/********************����Ԥ����ȡ�����õ��ַ���ע��**********************/
void filterResource(char r[], int pProject)
{
	char tempString[10000];
	int count = 0;
	for (int i = 0; i <= pProject; i++)
	{
		if (r[i] == '/'&&r[i + 1] == '/')
		{//��Ϊ����ע�͡�//��,��ȥ��ע�ͺ���Ķ�����ֱ�������س�����
			while (r[i] != '\n')
			{
				i++;//���ɨ��
			}
		}
		if (r[i] == '/'&&r[i + 1] == '*')
		{//��Ϊ����ע�͡�/* ������*/����ȥ��������
			i += 2;
			while (r[i] != '*' || r[i + 1] != '/')
			{
				i++;//����ɨ��
				if (r[i] == '$')
				{
					printf("ע�ͳ���û���ҵ� */���������������\n");
					exit(0);
				}
			}
			i += 2;//�����*/��
		}
		if (r[i] != '\n'&&r[i] != '\t'&&r[i] != '\v'&&r[i] != '\r')
		{//�����������ַ�������ˣ��������
			tempString[count++] = r[i];
		}
	}
	tempString[count] = '\0';
	strcpy(r, tempString);//��������֮���Դ����
}
/********************����Ԥ����ȡ�����õ��ַ���ע��**********************/


/****************************�����ӳ����㷨����***********************/
void Scanner(int &syn, char resourceProject[], char token[], int &pProject)
{//����DFA��״̬ת��ͼ���
	int i, count = 0;//count������token[]��ָʾ�����ռ������ַ�
	char ch;//��Ϊ�ж�ʹ��
	ch = resourceProject[pProject];
	while (ch == ' ')
	{//���˿ո񣬷�ֹ������ʶ���˿ո������
		pProject++;
		ch = resourceProject[pProject];
	}
	for (i = 0; i < 20; i++)
	{//ÿ���ռ�ǰ������
		token[i] = '\0';
	}
	if (IsLetter(resourceProject[pProject]))
	{//��ͷΪ��ĸ
		token[count++] = resourceProject[pProject];//�ռ�
		pProject++;//����
		while (IsLetter(resourceProject[pProject]) || IsDigit(resourceProject[pProject]))
		{//�����ĸ������
			token[count++] = resourceProject[pProject];//�ռ�
			pProject++;//����
		}//�����һ���ַ������´ν�Ҫ��ʼ��ָ��λ��
		token[count] = '\0';
		syn = searchReserve(reserveWord, token);//����ҵ��ֱ���
		if (syn == -1)
		{//�����Ǳ��������Ǳ�ʶ��
			syn = 100;//��ʶ���ֱ���
		}
		return;
	}
	else if (IsDigit(resourceProject[pProject]))
	{//���ַ�Ϊ����
		while (IsDigit(resourceProject[pProject]))
		{//�������
			token[count++] = resourceProject[pProject];//�ռ�
			pProject++;
		}//�����һ���ַ������´ν�Ҫ��ʼ��ָ��λ��
		token[count] = '\0';
		syn = 99;//�����ֱ���
	}
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
		|| ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
		|| ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':')
	{//��Ϊ��������߽�������õ����
		token[0] = resourceProject[pProject];
		token[1] = '\0';//�γɵ��ַ���
		for (i = 0; i < 36; i++)
		{//������������
			if (strcmp(token, operatorOrDelimiter[i]) == 0)
			{
				syn = 33 + i;//����ֱ��룬ʹ����һ�㼼�ɣ�ʹ֮������ӳ��
				break;//�鵽���Ƴ�
			}
		}
		pProject++;//ָ�����ƣ�Ϊ��һɨ����׼��
		return;
	}
	else  if (resourceProject[pProject] == '<')
	{//<,<=,<<
		pProject++;//���ƣ���ǰ����
		if (resourceProject[pProject] == '=')
		{
			syn = 38;
		}
		else if (resourceProject[pProject] == '<')
		{//����
			pProject--;
			syn = 58;
		}
		else
		{
			pProject--;
			syn = 37;
		}
		pProject++;//ָ������
		return;
	}
	else  if (resourceProject[pProject] == '>')
	{//>,>=,>>
		pProject++;
		if (resourceProject[pProject] == '=')
		{
			syn = 40;
		}
		else if (resourceProject[pProject] == '>')
		{
			syn = 59;
		}
		else
		{
			pProject--;
			syn = 39;
		}
		pProject++;
		return;
	}
	else  if (resourceProject[pProject] == '=')
	{//=.==
		pProject++;
		if (resourceProject[pProject] == '=')
		{
			syn = 42;
		}
		else
		{
			pProject--;
			syn = 41;
		}
		pProject++;
		return;
	}
	else  if (resourceProject[pProject] == '!')
	{//!,!=
		pProject++;
		if (resourceProject[pProject] == '=')
		{
			syn = 43;
		}
		else
		{
			syn = 68;
			pProject--;
		}
		pProject++;
		return;
	}
	else  if (resourceProject[pProject] == '&')
	{//&,&&
		pProject++;
		if (resourceProject[pProject] == '&')
		{
			syn = 53;
		}
		else
		{
			pProject--;
			syn = 52;
		}
		pProject++;
		return;
	}
	else  if (resourceProject[pProject] == '|')
	{//|,||
		pProject++;
		if (resourceProject[pProject] == '|')
		{
			syn = 55;
		}
		else
		{
			pProject--;
			syn = 54;
		}
		pProject++;
		return;
	}
	else  if (resourceProject[pProject] == '$')
	{//������
		syn = 0;//�ֱ���Ϊ0
	}
	else
	{//���ܱ����ϴʷ�����ʶ�������
		printf("error��there is no exist %c \n", ch);
		exit(0);
	}
}


int main()
{
	//��һ���ļ�����ȡ���е�Դ����
	char resourceProject[10000];
	char token[20] = { 0 };
	int syn = -1, i;//��ʼ��
	int pProject = 0;//Դ����ָ��
	FILE *fp, *fp1;
	if ((fp = fopen("D:\\zyr_rc.txt", "r")) == NULL)
	{//��Դ����
		cout << "can't open this file";
		exit(0);
	}
	resourceProject[pProject] = fgetc(fp);
	while (resourceProject[pProject] != '$')
	{//��Դ�������resourceProject[]����
		pProject++;
		resourceProject[pProject] = fgetc(fp);
	}
	resourceProject[++pProject] = '\0';
	fclose(fp);
	cout << endl << "Դ����Ϊ:" << endl;
	cout << resourceProject << endl;
	//��Դ������й���
	filterResource(resourceProject, pProject);
	cout << endl << "����֮��ĳ���:" << endl;
	cout << resourceProject << endl;
	pProject = 0;//��ͷ��ʼ��

	if ((fp1 = fopen("D:\\zyr_compile.txt", "w+")) == NULL)
	{//��Դ����
		cout << "can't open this file";
		exit(0);
	}
	while (syn != 0)
	{
		//����ɨ��
		Scanner(syn, resourceProject, token, pProject);
		if (syn == 100)
		{//��ʶ��
			for (i = 0; i < 1000; i++)
			{//�����ʶ������
				if (strcmp(IDentifierTbl[i], token) == 0)
				{//���ڱ���
					break;
				}
				if (strcmp(IDentifierTbl[i], "") == 0)
				{//���ҿռ�
					strcpy(IDentifierTbl[i], token);
					break;
				}
			}
			printf("(��ʶ��  ,%s)\n", token);
			fprintf(fp1, "(��ʶ��   ,%s)\n", token);
		}
		else if (syn >= 1 && syn <= 32)
		{//������
			printf("(%s   ,  --)\n", reserveWord[syn - 1]);
			fprintf(fp1, "(%s   ,  --)\n", reserveWord[syn - 1]);
		}
		else if (syn == 99)
		{//const ����
			printf("(����   ,   %s)\n", token);
			fprintf(fp1, "(����   ,   %s)\n", token);
		}
		else if (syn >= 33 && syn <= 68)
		{
			printf("(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
			fprintf(fp1, "(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
		}
	}
	for (i = 0; i < 100; i++)
	{//�����ʶ������
		printf("��%d����ʶ����  %s\n", i + 1, IDentifierTbl[i]);
		fprintf(fp1, "��%d����ʶ����  %s\n", i + 1, IDentifierTbl[i]);
	}
	fclose(fp1);
	return 0;
}