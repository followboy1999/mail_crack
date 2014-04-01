


#ifndef _ZSMTP
#define _ZSMTP

#include "ZBase64.h"
#include <string>
#include <deque>
using namespace std;

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define COPYRIGHT "Smtp Client By ZhangLuduo"	// 版权信息
#define BOUNDARY "www.oopfans.com"				// 边界字符串
#define for if(0); else for						// 变量作用域

//缓冲区大小,这个值必须是57的整数倍!
#define BUFFER_READ 11400

class ZSmtp  
{
public:

	ZSmtp();
	virtual ~ZSmtp();

private:

	SOCKET m_SOCKET;		
	WSADATA m_WSADATA;
	HOSTENT* m_HOSTENT;
	SOCKADDR_IN m_SOCKADDR_IN;

private:

	bool CreateSocket();	// 创建Socket
	void ReleaseSocket();	// 释放Socket

	/*
	功能:
		验证从服务器返回的前三位代码和传递进来的参数是否一样

	备注:
		211 帮助返回系统状态
		214 帮助信息
		220 服务准备就绪
		221 关闭连接
		235 用户验证成功
		250 请求操作就绪
		251 用户不在本地，转寄到其他路径
		334 等待用户输入验证信息
		354 开始邮件输入
		421 服务不可用
		450 操作未执行，邮箱忙
		451 操作中止，本地错误
		452 操作未执行，存储空间不足
		500 命令不可识别或语言错误
		501 参数语法错误
		502 命令不支技
		503 命令顺序错误
		504 命令参数不支持
		550 操作未执行，邮箱不可用
		551 非本地用户
		552 中止存储空间不足
		553 操作未执行，邮箱名不正确
		554 传输失败
	*/
	bool CheckResponse(const char* RecvCode);

public:

	//边接smtp服务器
	bool Connect(const string SmtpAddr,const int Port);

	//验证用户名和密码
	bool Validate(const string Username,const string Password);

	//发送数据
	bool SendData(const string SendFrom,			// 发送地址
				  const deque<string> SendToList,	// 目地地址列表
				  const string SenderName,			// 发送者姓名
				  const string ReceiverName,		// 接收者姓名
				  const string Subject,				// 邮件主题
				  const string Content,				// 邮件内容
				  const deque<string> Files,		// 附件列表
				  bool IsHtml);						// 是否以HTML格式发送
};

#endif
