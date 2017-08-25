
// PTZControl.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PTZControl.h"
#include "PTZControlDlg.h"
#include "HCNetSDK.h"
#include "plaympeg4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern long g_lUserID;
CPTZControlDlg* g_pMainDlg;
// CPTZControlApp

BEGIN_MESSAGE_MAP(CPTZControlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPTZControlApp ����

CPTZControlApp::CPTZControlApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


void CALLBACK g_ExceptionCallBack( DWORD dwType, LONG lUserID, LONG lHandle, void *pUser )
{
	char tempbuf[256] = { 0 };
	switch (dwType)
	{
	case EXCEPTION_RECONNECT:    //Ԥ��ʱ����
		printf( "----------reconnect--------%d\n", time( NULL ) );
		break;
	default:
		break;
	}
}


// Ψһ��һ�� CPTZControlApp ����

CPTZControlApp theApp;

// CPTZControlApp ��ʼ��

BOOL CPTZControlApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//�豸��ʼ��
	if (!NET_DVR_Init())
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		char szErrLan[128] = { 0 };
		sprintf_s( szErrLan, "ErrCode:%d", dwErrCode );
		::MessageBox( NULL, (LPCWSTR)szErrLan, NULL, NULL );
		return -1;
	}

	NET_DVR_SDKLOCAL_CFG struSdkLocalCfg = { 0 };
	struSdkLocalCfg.byEnableAbilityParse = 1; //
	struSdkLocalCfg.byVoiceComMode = 0;   //0 use windows Api , 1 Use liabrary
	struSdkLocalCfg.byLoginWithSimXml = 1;
	NET_DVR_SetSDKLocalConfig( &struSdkLocalCfg );

	//���ó�ʱʱ��
	NET_DVR_SetConnectTime( 4000 );
	NET_DVR_SetReconnect( 1000 );

	//�����쳣��Ϣ���յĻص�����
	NET_DVR_SetExceptionCallBack_V30( NULL, NULL, g_ExceptionCallBack, NULL );

	//�û���¼
	long lUserID = -1;

	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };
	struLoginInfo.bUseAsynLogin = true;
	struLoginInfo.bUseAsynLogin = true;
	memcpy( struLoginInfo.sDeviceAddress, "192.168.2.129", NET_DVR_DEV_ADDRESS_MAX_LEN );
	memcpy( struLoginInfo.sUserName, "admin", NAME_LEN );
	memcpy( struLoginInfo.sPassword, "qq123456", PASSWD_LEN );
	struLoginInfo.wPort = 8000;
	//struLoginInfo.byProxyType = 2;
	//struLoginInfo.byUseTransport = 1;
	lUserID = NET_DVR_Login_V40( &struLoginInfo, &struDeviceInfoV40 );

	NET_DVR_SetShowMode( NORMALMODE, RGB( 255, 255, 255 ) );
	PlayM4_InitDDrawDevice();

	if (lUserID >= 0)
	{
		//MessageBox( NULL, _T( "��¼�ɹ�" ) );
		g_lUserID = lUserID;
	}

	CPTZControlDlg dlg;
	m_pMainWnd = &dlg;
	g_pMainDlg = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

