


#ifndef _ZSMTP
#define _ZSMTP

#include "ZBase64.h"
#include <string>
#include <deque>
using namespace std;

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define COPYRIGHT "Smtp Client By ZhangLuduo"	// ��Ȩ��Ϣ
#define BOUNDARY "www.oopfans.com"				// �߽��ַ���
#define for if(0); else for						// ����������

//��������С,���ֵ������57��������!
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

	bool CreateSocket();	// ����Socket
	void ReleaseSocket();	// �ͷ�Socket

	/*
	����:
		��֤�ӷ��������ص�ǰ��λ����ʹ��ݽ����Ĳ����Ƿ�һ��

	��ע:
		211 ��������ϵͳ״̬
		214 ������Ϣ
		220 ����׼������
		221 �ر�����
		235 �û���֤�ɹ�
		250 �����������
		251 �û����ڱ��أ�ת�ĵ�����·��
		334 �ȴ��û�������֤��Ϣ
		354 ��ʼ�ʼ�����
		421 ���񲻿���
		450 ����δִ�У�����æ
		451 ������ֹ�����ش���
		452 ����δִ�У��洢�ռ䲻��
		500 �����ʶ������Դ���
		501 �����﷨����
		502 ���֧��
		503 ����˳�����
		504 ���������֧��
		550 ����δִ�У����䲻����
		551 �Ǳ����û�
		552 ��ֹ�洢�ռ䲻��
		553 ����δִ�У�����������ȷ
		554 ����ʧ��
	*/
	bool CheckResponse(const char* RecvCode);

public:

	//�߽�smtp������
	bool Connect(const string SmtpAddr,const int Port);

	//��֤�û���������
	bool Validate(const string Username,const string Password);

	//��������
	bool SendData(const string SendFrom,			// ���͵�ַ
				  const deque<string> SendToList,	// Ŀ�ص�ַ�б�
				  const string SenderName,			// ����������
				  const string ReceiverName,		// ����������
				  const string Subject,				// �ʼ�����
				  const string Content,				// �ʼ�����
				  const deque<string> Files,		// �����б�
				  bool IsHtml);						// �Ƿ���HTML��ʽ����
};

#endif
