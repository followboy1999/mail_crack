
/************************ Copyright (c) 2006 ************************

��������:

    ��³��(zhangluduo) : Ϊ���а��ҵ��˺��Ұ�����Ŭ��!

��ϵ��ʽ:

    zhangluduo@msn.com
	[oopfans]Ⱥ:34064264

�޸�ʱ��:

    2007-02-24

��������:

    thunk����ʵ��.�����������԰ѻص�������ȫ��װ�����Ա����.

��Ȩ����:

    ����κε�λ,��������ʹ��,����,�޸�,ɢ����������ݴ���,���Ǳ��뱣
    ���˰�Ȩ��Ϣ,��ο���������ڵ��Ͷ�,�������˴������Դ,�����˷ݴ���
    ���κ�BUG,��֪ͨ����,�Ա��ֲ���������ˮƽ���޶����µ�һЩ����Ͳ�
    ��,лл!

    �˷ݴ��������߸���һλ����[JERKII.SHANG (JERKII@HOTMAIL.COM)]��һ
    ƪ����[һ��ʵ��Win32���ڹ��̺���(Window Procedure)���·���--
    ����Thunkʵ�ֵ����Ա��Ϣ������]�޸Ķ���,�ڴ˶�ԭ���߿�Դ�ľ���
    �¾�!

����ʾ��:

	//����ͷ�ļ������ļ�
	#include "ZThunk.h"

	class CTimer
	{
	private:

		// �˶��������ʱΪ������ݳ�Ա����ȫ�ֶ���,�Ա�֤������������
		ZThunk m_thunk; 

	public:
		
		//��װ��ʱ��
		void Set()
		{
			//����ص�������ַ
			void* pAddr=m_thunk.Callback(this,&CTimer::TimerProc,ZThunk::THISCALL);

			// ��Ϊ��װ����������ԭ��
			// UINT_PTR SetTimer(
			// HWND hWnd,              // ���ھ��
			// UINT_PTR nIDEvent,      // ��ʱ��ID
			// UINT uElapse,           // ʱ����
			// TIMERPROC lpTimerFunc   // ��ʱ���ص�����
			
			//��װ��ʱ��
			SetTimer(NULL,1,1000,(TIMERPROC)pAddr);	
		}

		//��ʱ���ص�����,��ȫ����װ�����Ա����!
		void TimerProc(HWND hWnd, DWORD dwMsg , WPARAM wPa, LPARAM lPa)
		{
			// to do something
		}
	};

************************ Copyright (c) 2006 ************************/

#ifndef _ZTHUNK
#define _ZTHUNK

class ZThunk  
{
private:
	unsigned char m_ThiscallCode[10];
	unsigned char m_StdcallCode[16];
public:
	enum CALLINGCONVENTIONS
	{
		STDCALL = 1,
		THISCALL= 2
	};
public:
	template <class T>
	void* Callback(void* pThis,T MemberOffset,CALLINGCONVENTIONS CallingConvention = STDCALL)
	{
		// these codes only use in stdcall
		if(CallingConvention == STDCALL)
		{
			// Encoded machine instruction   Equivalent assembly languate notation
			// ---------------------------   -------------------------------------
			// FF 34 24                      push  dword ptr [esp]          ; Save (or duplicate)                                                                    ; the Return Addr into stack
			// C7 44 24 04 ?? ?? ?? ??       mov   dword ptr [esp+4], pThis ; Overwite the old                                                                    ; Return Addr with 'this pointer'
			// E9 ?? ?? ?? ??                jmp   target addr              ; Jump to target message handler

			char Buf[33]={0};
			sprintf(Buf,"%d",MemberOffset);
			unsigned long JmpAddr = (unsigned long) atol(Buf) - (unsigned long) &m_StdcallCode[0] - 16;

			m_StdcallCode[11] = 0xE9; 
			*((unsigned long *)  &m_StdcallCode[ 0]) = 0x002434FF;
			*((unsigned long *)  &m_StdcallCode[ 3]) = 0x042444C7;
			*((unsigned long *)  &m_StdcallCode[ 7]) = (unsigned long) pThis;
			*((unsigned long *)  &m_StdcallCode[12]) = JmpAddr;

			return (void*)m_StdcallCode;
		}
		// these codes only use in thiscall
		else if(CallingConvention == THISCALL)
		{
			// Encoded machine instruction   Equivalent assembly languate notation
			// ---------------------------   -------------------------------------
			// B9 ?? ?? ?? ??                mov    ecx, pThis  ; Load ecx with this pointer
			// E9 ?? ?? ?? ??                jmp    target addr ; Jump to target message handler

			char Buf[33]={0};
			sprintf(Buf,"%d",MemberOffset);
			unsigned long JmpAddr = (unsigned long) atol(Buf) - (unsigned long) &m_ThiscallCode[0] - 10;

			m_ThiscallCode[0] = 0xB9;
			m_ThiscallCode[5] = 0xE9;
			*((unsigned long *) &m_ThiscallCode[1]) = (unsigned long) pThis;
			*((unsigned long *) &m_ThiscallCode[6]) = JmpAddr;

			return (void*)m_ThiscallCode;
		}return 0;
	}
};

#endif
