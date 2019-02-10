/*******************Lexer***********************
功能：这里完成第一步：将输入的字符串标记出各单词的词性
入口函数:Lexer（）
输入：源代码字符串
输出：词性标记
包含的数据：
包含的函数：
*************************************************/
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <regex>//正则表达式
using namespace std;
enum L_STAGE { OPRATER, NUM, SPACE, LETTER,COMMENT};
/*保存一个单词结果*/
struct L_pair{
	enum L_STAGE L_type;//保存单词的类型
	int num;//保存单词的位置
	string content;//保存单词的内容
};
/*在词法分析时期保存各单词分析结果，是词法分析器的输出，语法分析器的输入*/
typedef vector<L_pair> L_table;

/*************************************************
函数名称:Lexer
描述:词法分析的开放接口，用输入字符串并返回结果
调用:NoComment
输入: string source
返回:L_table=vector<L_pair>
*************************************************/
L_table Lexer(string source);

/*************************************************
函数名称:NoComment
描述:词法分析的第一步：去除所有注释
调用:
输入:string 源代码
返回:string 去除注释的源代码 
*************************************************/
string NoComment(string source);

