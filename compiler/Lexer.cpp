#include "Lexer.h"
/*���ڱ��汣����*/
vector<string> L_RESERVE_WORDS = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};
/*���ڱ��������*/
vector<string> L_OPRATOR_WORDS = { 
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
"}", "\\", ".", "\?", ":", "!"
};

string NoComment(string source) {
	int l = source.length();
	string temp = "";
	for (int i = 0;i < l; i++) {//���ַ���ɨ��һ��
		if (source[i] == '/'&&source[i + 1] == '/') {//��Ϊ����ע�͡�//��,��ȥ��ע�ͺ���Ķ�����ֱ�������س�����
			while (source[i] != '\n') {
				i++;//���ɨ��
			}
		}else if(source[i] == '/'&&source[i + 1] == '*') {//�����������ע��
			i =i+2;
			if (i >= l) {
				cout << "ֱ���ļ�������û������ע�ͽ�����־*/" << "�������ڵ�" << i << "���ַ�";
				exit(0);
			}
			else {
				while ((source[i] != '*')&&(source[i+1] != '/')) {
					i++;//���ɨ��
					if (i >= l) {
						cout<< "ֱ���ļ�������û������ע�ͽ�����־*/"<<"�������ڵ�"<<i<<"���ַ�";
						exit(0);
					}else {

					}
				}
				i++;
			}

		}else {//�������ע�ͣ����ַ���ӵ�tempβ��
			temp = temp + source[i];
		}
	}
	cout << temp;
	return temp;
}
L_table Lexer(string source) {
	L_table pairs;
	L_pair pair;
	source = NoComment(source);
	/*�����Զ�����ʼ*/
		
	/*�����Զ�������*/
	return pairs;
}