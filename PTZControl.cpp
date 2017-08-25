
// PTZControl.cpp : 定义应用程序的类行为。
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


// CPTZControlApp 构造

CPTZControlApp::CPTZControlApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


void CALLBACK g_ExceptionCallBack( DWORD dwType, LONG lUserID, LONG lHandle, void *pUser )
{
	char tempbuf[256] = { 0 };
	switch (dwType)
	{
	case EXCEPTION_RECONNECT:    //预览时重连
		printf( "----------reconnect--------%d\n", time( NULL ) );
		break;
	default:
		break;
	}
}


// 唯一的一个 CPTZControlApp 对象

CPTZControlApp theApp;

// CPTZControlApp 初始化

BOOL CPTZControlApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//设备初始化
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

	//设置超时时间
	NET_DVR_SetConnectTime( 4000 );
	NET_DVR_SetReconnect( 1000 );

	//设置异常消息接收的回调函数
	NET_DVR_SetExceptionCallBack_V30( NULL, NULL, g_ExceptionCallBack, NULL );

	//用户登录
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
		//MessageBox( NULL, _T( "登录成功" ) );
		g_lUserID = lUserID;
	}

	CPTZControlDlg dlg;
	m_pMainWnd = &dlg;
	g_pMainDlg = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

