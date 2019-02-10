#include "Lexer.h"
/*用于保存保留字*/
string L_RESERVE_WORDS[] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};
/*用于保存操作符*/
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
	for (int i = 0;i < l; i++) {//将字符串扫描一遍
		if (source[i] == '/'&&source[i + 1] == '/') {//若为单行注释“//”,则去除注释后面的东西，直至遇到回车换行
			while (source[i] != '\n') {
				i++;//向后扫描
			}
		}else if(source[i] == '/'&&source[i + 1] == '*') {//如果遇到多行注释
			i =i+2;
			if (i >= l) {
				cout << "直到文件结束都没有遇到注释结束标志*/" << "错误发生在第" << i << "个字符";
				exit(0);
			}
			else {
				while ((source[i] != '*')&&(source[i+1] != '/')) {
					i++;//向后扫描
					if (i >= l) {
						cout<< "直到文件结束都没有遇到注释结束标志*/"<<"错误发生在第"<<i<<"个字符";
						exit(0);
					}else {}
				}
				i++;
			}
		}
		else  {//如果不是注释，则将字符添加到temp尾部
			temp = temp + source[i];
		}
	}
	return temp;
}
L_table Lexer(string source) {
	source = NoComment(source);//去除注释
	/*有限自动机开始*/
	L_table pairs;
	L_pair pair;
	string current_word ="";
	int i = 0;
	stage = SPACE ;
	while(1){
		char ch = source[i];
		switch (stage) {//处于什么状态
		case OPRATER://处于op状态
			switch (isWhat(ch)) {
			case OPRATER://下一子母为op
				pair.content = current_word;
				pair.L_type = OPRATER;
				pair.num = i;
				pairs.push_back(pair);

				stage = isWhat(ch);
				current_word = ch;
				break;
			case NUM://下一子母为num等，则op、结束并写入，开始新的stage
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
	/*有限自动机结束*/
	return pairs;
}