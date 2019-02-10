#include "Lexer.h"
/*���ڱ��汣����*/
string L_RESERVE_WORDS[] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};
/*���ڱ��������*/
string L_OPRATOR[] = { 
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==","!=","^", 
	"\"", "\'", "#", "&","&&", "|", "||", "%", "~", "<<", ">>", 
	"\\", ".", "\?", ":", "!"
};
char L_DIVIDER[] = { ';', ',', '{', '}', '[', ']', '(', ')' };

enum L_STAGE stage,ch_type;
enum L_STAGE isWhat(char ch) {
	if ((47 < ch)&&(ch < 59)) {
		ch_type = NUM;
	}
	else if ((64 < ch)&&(ch < 19)||((96< ch)&&(ch < 123))||(ch> 127)) {
		ch_type = LETTER;
	}
	else if ((ch == ' ') || (ch == '\n') || (ch == '\t') || (ch == '\r')) {
		ch_type = SPACE;
	}
	else {
		ch_type = OPRATER;
	}
	return ch_type;
}
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
					}else {}
				}
				i++;
			}
		}
		else  {//�������ע�ͣ����ַ���ӵ�tempβ��
			temp = temp + source[i];
		}
	}
	return temp;
}
L_table Lexer(string source) {
	source = NoComment(source);//ȥ��ע��
	/*�����Զ�����ʼ*/
	L_table pairs;
	L_pair pair;
	string current_word ="";
	int i = 0;
	stage = SPACE ;
	while(1){
		char ch = source[i];
		switch (stage) {//����ʲô״̬
		case OPRATER://����op״̬
			switch (isWhat(ch)) {
			case OPRATER://��һ��ĸΪop
				pair.content = current_word;
				pair.L_type = OPRATER;
				pair.num = i;
				pairs.push_back(pair);

				stage = isWhat(ch);
				current_word = ch;
				break;
			case NUM://��һ��ĸΪnum�ȣ���op��������д�룬��ʼ�µ�stage
			case LETTER:
			case SPACE:
				pair.content = current_word;
				pair.L_type = OPRATER;
				pair.num = i;
				pairs.push_back(pair);

				stage = isWhat(ch);
				current_word = ch;
				break;
			}
			break;
		case NUM:
			switch (isWhat(ch)) {
			case NUM:
				current_word += ch;
				break;
			case OPRATER:
			case SPACE:
			case LETTER:
				pair.content = current_word;
				pair.L_type = NUM;
				pair.num = i;
				pairs.push_back(pair);

				stage = isWhat(ch);
				current_word = ch;
				break;
			}
			break;
		case LETTER:
			switch (isWhat(ch)) {
			case LETTER:
				current_word += ch;
				break;
			case OPRATER:
			case SPACE:
			case NUM:
				pair.content = current_word;
				pair.L_type = LETTER;
				pair.num = i;
				pairs.push_back(pair);

				stage = isWhat(ch);
				current_word = ch;
				break;
			}
			break;
		case SPACE:
			switch (isWhat(ch)) {
			case SPACE:
				break;
			case OPRATER:
			case LETTER:
			case NUM:
				stage = isWhat(ch);
				current_word = ch;
				break;
			}
			break;
		}
		i++;
		if (source[i - 1] == '\0') {
			break;
		}
	}
	/*�����Զ�������*/
	return pairs;
}