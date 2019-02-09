/*******************overview***********************
Licence:MIT
Author:Trialley
Date:2019-02-09
Description:A simple compiler demo.
**************************************************/
/*******************git info***********************
master
start
word
sentence...
**************************************************/

// ！！！请先阅读预编译头pch.h ！！！
//预编译头，存放不需要经常修改的代码:公共头文件
#include "pch.h"

/* Global Title failure, as follows */      // 变量作用、含义

/* sccp interface with sccp user primitive message name */
enum SCCP_USER_PRIMITIVE
{
	N_UNITDATA_IND, // sccp notify sccp user unit data come 
	N_NOTICE_IND,   // sccp notify user the No.7 network can not  transmission this message 
	N_UNITDATA_REQ, // sccp user's unit data transmission request
};

/*************************************************
Function:       // 函数名称
Description:    // 函数功能、性能等的描述
Calls:          // 被本函数调用的函数清单

Input:
	// 输入参数说明，包括每个参数的作用、取值说明及参数间关系。
Output:         // 对打印的说明。
Return:         // 函数返回值的说明
*************************************************/

using namespace std;

//程序入口
int main()
{
	string x;
    cout << "请输入源代码文件的相对路径：\n";
	cin >> x;
	return 0;
}
