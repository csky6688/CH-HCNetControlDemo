
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#define ZOOM_IN            11    /* �������ٶ�SS���(���ʱ��) */
#define ZOOM_OUT        12    /* �������ٶ�SS��С(���ʱ�С) */
#define FOCUS_NEAR      13  /* �������ٶ�SSǰ�� */
#define FOCUS_FAR       14  /* �������ٶ�SS��� */
#define IRIS_OPEN       15  /* ��Ȧ���ٶ�SS���� */
#define IRIS_CLOSE      16  /* ��Ȧ���ٶ�SS��С */

#define TILT_UP            21    /* ��̨��SS���ٶ����� */
#define TILT_DOWN        22    /* ��̨��SS���ٶ��¸� */
#define PAN_LEFT        23    /* ��̨��SS���ٶ���ת */
#define PAN_RIGHT        24    /* ��̨��SS���ٶ���ת */
#define UP_LEFT            25    /* ��̨��SS���ٶ���������ת */
#define UP_RIGHT        26    /* ��̨��SS���ٶ���������ת */
#define DOWN_LEFT        27    /* ��̨��SS���ٶ��¸�����ת */
#define DOWN_RIGHT        28    /* ��̨��SS���ٶ��¸�����ת */
#define PAN_AUTO        29    /* ��̨��SS���ٶ������Զ�ɨ�� */

#define TILT_DOWN_ZOOM_IN    58    /* ��̨��SS���ٶ��¸�&&�������ٶ�SS���(���ʱ��) */
#define TILT_DOWN_ZOOM_OUT  59  /* ��̨��SS���ٶ��¸�&&�������ٶ�SS��С(���ʱ�С) */
#define PAN_LEFT_ZOOM_IN    60  /* ��̨��SS���ٶ���ת&&�������ٶ�SS���(���ʱ��)*/
#define PAN_LEFT_ZOOM_OUT   61  /* ��̨��SS���ٶ���ת&&�������ٶ�SS��С(���ʱ�С)*/
#define PAN_RIGHT_ZOOM_IN    62  /* ��̨��SS���ٶ���ת&&�������ٶ�SS���(���ʱ��) */
#define PAN_RIGHT_ZOOM_OUT  63  /* ��̨��SS���ٶ���ת&&�������ٶ�SS��С(���ʱ�С) */
#define UP_LEFT_ZOOM_IN     64  /* ��̨��SS���ٶ���������ת&&�������ٶ�SS���(���ʱ��)*/
#define UP_LEFT_ZOOM_OUT    65  /* ��̨��SS���ٶ���������ת&&�������ٶ�SS��С(���ʱ�С)*/
#define UP_RIGHT_ZOOM_IN    66  /* ��̨��SS���ٶ���������ת&&�������ٶ�SS���(���ʱ��)*/
#define UP_RIGHT_ZOOM_OUT   67  /* ��̨��SS���ٶ���������ת&&�������ٶ�SS��С(���ʱ�С)*/
#define DOWN_LEFT_ZOOM_IN   68  /* ��̨��SS���ٶ��¸�����ת&&�������ٶ�SS���(���ʱ��) */
#define DOWN_LEFT_ZOOM_OUT  69  /* ��̨��SS���ٶ��¸�����ת&&�������ٶ�SS��С(���ʱ�С) */
#define DOWN_RIGHT_ZOOM_IN    70  /* ��̨��SS���ٶ��¸�����ת&&�������ٶ�SS���(���ʱ��) */
#define DOWN_RIGHT_ZOOM_OUT    71  /* ��̨��SS���ٶ��¸�����ת&&�������ٶ�SS��С(���ʱ�С) */
#define TILT_UP_ZOOM_IN        72    /* ��̨��SS���ٶ�����&&�������ٶ�SS���(���ʱ��) */
#define TILT_UP_ZOOM_OUT    73    /* ��̨��SS���ٶ�����&&�������ٶ�SS��С(���ʱ�С) */