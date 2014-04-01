
/************************ Copyright (c) 2006 ************************

程序作者:

    张鲁夺(zhangluduo) : 为所有爱我的人和我爱的人努力!

联系方式:

    zhangluduo@msn.com
	[oopfans]群:34064264

修改时间:

    2007-02-24

功能描述:

    thunk技术实现.利用这个类可以把回调函数完全封装成类成员函数.

版权声明:

    许可任何单位,个人随意使用,拷贝,修改,散布及出售这份代码,但是必须保
    留此版权信息,以慰藉作者辛勤的劳动,及表明此代码的来源,如若此份代码
    有任何BUG,请通知作者,以便弥补作者由于水平所限而导致的一些错误和不
    足,谢谢!

    此份代码是作者跟据一位网友[JERKII.SHANG (JERKII@HOTMAIL.COM)]的一
    篇文章[一种实现Win32窗口过程函数(Window Procedure)的新方法--
    基于Thunk实现的类成员消息处理函数]修改而成,在此对原作者开源的精神
    致敬!

调用示例:

	//导入头文件及库文件
	#include "ZThunk.h"

	class CTimer
	{
	private:

		// 此对像必须声时为类的数据成员或者全局对像,以保证它的生命周期
		ZThunk m_thunk; 

	public:
		
		//安装定时器
		void Set()
		{
			//计算回调函数地址
			void* pAddr=m_thunk.Callback(this,&CTimer::TimerProc,ZThunk::THISCALL);

			// 此为安装定器函数的原形
			// UINT_PTR SetTimer(
			// HWND hWnd,              // 窗口句柄
			// UINT_PTR nIDEvent,      // 定时器ID
			// UINT uElapse,           // 时间间隔
			// TIMERPROC lpTimerFunc   // 定时器回调函数
			
			//安装计时器
			SetTimer(NULL,1,1000,(TIMERPROC)pAddr);	
		}

		//定时器回调函数,完全被封装成类成员函数!
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
