/*******************overview***********************
Licence:MIT
Author:Trialley
Date:2019-02-09
Description:A simple compiler demo.
**************************************************/
/*******************main.cpp***********************
这里完成数据的输入与输出，不关注任何内部逻辑
**************************************************/
//负责输入输出不解释
#include <fstream>
#include <iostream>
#include <sstream>

//负责emmm输出输入之外的其他东西
#include <vector>
#include <map>
#include <string>
using namespace std;



/*对保留字进行枚举*/
enum SCCP_USER_PRIMITIVE
{
	N_UNITDATA_IND, // sccp notify sccp user unit data come 
	N_NOTICE_IND,   // sccp notify user the No.7 network can not  transmission this message 
	N_UNITDATA_REQ, // sccp user's unit data transmission request
};
//词法分析函数，Lexer()是它暴露的唯一接口
#include "Lexer.h"


/*************************************************
Function: readFileIntoString
Description:用于将文件读取为字符串
Calls:
Input:string path：用字符串表示的源文件相对地址
Return:string source：用字符串表示的源代码
*************************************************/
string readFileIntoString(string filename){
	ifstream ifile(filename);
	//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}

/*************************************************
Function: main
Description:用于输入输出以及整体调度
Calls:Lexer()
Input:主程序无参数输入，请运行后按照提示输入信息
Return:0
*************************************************/
int main(){
	/*输入相对路径并打印*/
	string path;
	path = "./test.txt";
    /*cout << "请输入源代码文件的相对路径：\n";
	cin >> path;*/
	cout << "这是您输入的地址：\n" << path << endl;

	/*通过相对路径获得内容并打印*/
	string source = readFileIntoString(path);
	cout << "这是文件的内容：\n" << source << endl;

	cout << "-------------词法分析函数输出开始------------\n";
	/*通过文件内容获取分词信息并打印*/
	
	L_table LexResult = Lexer(source);
	 
	return 0;
}
