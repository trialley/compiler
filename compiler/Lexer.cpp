#include "Lexer.h"
/*用于保存保留字*/
vector<string> L_RESERVE_WORDS = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};
/*用于保存操作符*/
vector<string> L_OPRATOR_WORDS = { 
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
"}", "\\", ".", "\?", ":", "!"
};

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
					}else {

					}
				}
				i++;
			}

		}else {//如果不是注释，则将字符添加到temp尾部
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
	/*有限自动机开始*/
		
	/*有限自动机结束*/
	return pairs;
}