
// PTZControlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PTZControl.h"
#include "PTZControlDlg.h"
#include "afxdialogex.h"
#include "HCNetSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long g_lUserID = -1;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPTZControlDlg �Ի���



CPTZControlDlg::CPTZControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPTZControlDlg::IDD, pParent)
	, m_iPTZSpeed( 0 )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lHandle = -1;
	m_lUserID = -1;
	m_iChannel = 0;
}

void CPTZControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_COMBO1, m_PTZSpeedCombo );
	DDX_CBIndex( pDX, IDC_COMBO1, m_iPTZSpeed );
}

BEGIN_MESSAGE_MAP(CPTZControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_BUTTON9, &CPTZControlDlg::OnBnClickedButton9 )
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPTZControlDlg ��Ϣ�������

BOOL CPTZControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_btnPtzUp.SubclassDlgItem( IDC_BTN_PTZ_UP, this );
	m_btnPtzDown.SubclassDlgItem( IDC_BTN_PTZ_DOWN, this );
	m_btnPtzLeft.SubclassDlgItem( IDC_BTN_PTZ_LEFT, this );
	m_btnPtzRight.SubclassDlgItem( IDC_BTN_PTZ_RIGHT, this );
    m_btnPtzUpLeft.SubclassDlgItem( IDC_BUTTON_UPLEFT, this);
    m_btnPtzUpRight.SubclassDlgItem( IDC_BUTTON_UPRIGHT, this);
    m_btnPtzDownLeft.SubclassDlgItem( IDC_BUTTON_DOWNLEFT, this);
    m_btnPtzDownRight.SubclassDlgItem( IDC_BUTTON_DOWNRIGHT, this);
	m_btnZoomOut.SubclassDlgItem( IDC_BTN_ZOOM_OUT, this );
	m_btnZoomIn.SubclassDlgItem( IDC_BTN_ZOOM_IN, this );
	m_btnFocusNear.SubclassDlgItem( IDC_BTN_FOCUS_NEAR, this );
	m_btnFocusFar.SubclassDlgItem( IDC_BTN_FOCUS_FAR, this );
	m_btnIrisOpen.SubclassDlgItem( IDC_BTN_IRIS_OPEN, this );
	m_btnIrisClose.SubclassDlgItem( IDC_BTN_IRIS_CLOSE, this );

	CString strComboValue;
	for (int i = 1; i < 7;i ++)
	{
		strComboValue.Format(_T("%d"),i);
		m_PTZSpeedCombo.AddString( strComboValue );
	}
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPTZControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPTZControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPTZControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CPTZControlDlg::StopVideo( void )
{
	//�ر�Ԥ��
	if (!NET_DVR_StopRealPlay( m_lHandle ))
	{
		CString strInfo;
		strInfo.Format( _T( "NET_DVR_StopRealPlay failed! Error number: %d" ), NET_DVR_GetLastError() );

		MessageBox( strInfo );
		return false;
	}

	m_lHandle = -1;
	return true;
}

void CPTZControlDlg::OnBnClickedButton9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_lHandle >= 0)
	{
		StopVideo();
		//Sleep( 100 );

		/*CStatic *pStatic = (CStatic *)GetDlgItem( IDC_VIDEO_CAMERA );
		pStatic->SetBitmap( NULL );*/
		/*GetDlgItem( IDC_VIDEO_CAMERA )->RedrawWindow();
		UpdateWindow();
		GetDlgItem( IDC_VIDEO_CAMERA )->Invalidate(true);*/

		CRect Rect;
		GetDlgItem( IDC_VIDEO_CAMERA )->GetClientRect( &Rect );
		/*Rect.left = Rect.left + 2;
		Rect.top = Rect.top + 2;
		Rect.right = Rect.right - 2;
		Rect.bottom = Rect.bottom - 2;*/
		GetDlgItem( IDC_VIDEO_CAMERA )->GetDC()->FillSolidRect( &Rect, RGB( 240, 240, 240 ) );

		/*CDC* pDC = GetDlgItem( IDC_VIDEO_CAMERA )->GetDC();
		pDC->FillSolidRect( GetDlgItem( IDC_VIDEO_CAMERA )->GetClientRect(), RGB( 240, 240, 240 ) );*/

		return;
	}
	 

	 NET_DVR_PREVIEWINFO ClientInfo = {0};
	 if (GetDlgItem( IDC_VIDEO_CAMERA )->GetSafeHwnd())
		 ClientInfo.hPlayWnd = GetDlgItem( IDC_VIDEO_CAMERA )->GetSafeHwnd();
	 ClientInfo.lChannel = 7;
	 ClientInfo.dwStreamType = 0;
	 ClientInfo.dwLinkMode = 0;
	 ClientInfo.byPreviewMode = 0;
	 ClientInfo.bBlocked = 1;
	 ClientInfo.byProtoType = 0;
	 ClientInfo.bPassbackRecord = 0;
	 ClientInfo.byVideoCodingType = 0;
	 ClientInfo.dwDisplayBufNum = 0;

	 long lRealPlayHandle = 0;
	 lRealPlayHandle = NET_DVR_RealPlay_V40( g_lUserID, &ClientInfo, NULL, NULL );
	 if (lRealPlayHandle < 0)
	 {
		 CString strInfo;
		 strInfo.Format( _T( "NET_DVR_RealPlay_V40 failed! Error number: %d" ), NET_DVR_GetLastError() );

		 //MessageBox( strInfo );
		 return;
	 }

	 if (ClientInfo.bBlocked == 1)
	 {
		 m_bPreviewBlock = true;
	 }
	 m_iChannel = ClientInfo.lChannel;
	 m_lUserID = g_lUserID;
	 m_lHandle = lRealPlayHandle;
	 //NET_DVR_StopRealPlay( lRealPlayHandle );
	 ////cvWaitKey(0);
	 //Sleep( -1 );

	 //fclose(fp);
	 //---------------------------------------
	 //�ر�Ԥ��
	 //if (!NET_DVR_StopRealPlay( lRealPlayHandle ))
	 //{
	 //	CString strInfo;
	 //	strInfo.Format( _T( "NET_DVR_StopRealPlay failed! Error number: 1" ), NET_DVR_GetLastError() );

	 //	MessageBox( strInfo );
	 //	return;
	 //}
	 //
	 ////ע���û�
	 //NET_DVR_Logout( lUserID );
	 //NET_DVR_Cleanup();

 //   NET_DVR_CLIENTINFO ClientInfoChn;
	//ClientInfoChn.lChannel = 6;        //Channel number �豸ͨ����
	//ClientInfoChn.hPlayWnd = GetDlgItem(IDC_VIDEO_CAMERA)->GetSafeHwnd();     //����Ϊ�գ��豸SDK������ֻȡ��
	//ClientInfoChn.lLinkMode = 0;       //Main Stream
	//ClientInfoChn.sMultiCastIP = "";

	//LONG lRealPlayHandleChn ;
	//lRealPlayHandleChn = NET_DVR_RealPlay_V30( g_lUserID, &ClientInfoChn, NULL, NULL, TRUE );

	//// ��ʼ��
	//NET_DVR_Init();
	////��������ʱ��������ʱ��
	//NET_DVR_SetConnectTime( 2000, 1 );
	//NET_DVR_SetReconnect( 10000, true );

	////---------------------------------------
	//// ��ȡ����̨���ھ��
	////HMODULE hKernel32 = GetModuleHandle((LPCWSTR)"kernel32");
	////GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32,"GetConsoleWindow");

	////---------------------------------------
	//// ע���豸
	//LONG lUserID;
	//NET_DVR_DEVICEINFO_V30 struDeviceInfo;
	//lUserID = NET_DVR_Login_V30( "192.168.2.129", 8000, "admin", "qq123456", &struDeviceInfo );
	//if (lUserID < 0)
	//{
	//	printf( "Login error, %d\n", NET_DVR_GetLastError() );
	//	NET_DVR_Cleanup();
	//	return;
	//}

	////---------------------------------------
	////�����쳣��Ϣ�ص�����
	//NET_DVR_SetExceptionCallBack_V30( 0, NULL, g_ExceptionCallBack, NULL );


	////cvNamedWindow("IPCamera");
	////---------------------------------------
	////����Ԥ�������ûص������� 
	//NET_DVR_PREVIEWINFO ClientInfoChn;
	//ClientInfoChn.lChannel = 1;        //Channel number �豸ͨ����
	//ClientInfoChn.hPlayWnd = GetDlgItem(IDC_VIDEO_CAMERA)->GetSafeHwnd();     //����Ϊ�գ��豸SDK������ֻȡ��
	//ClientInfoChn.lChannel = 1;
	//ClientInfoChn.dwStreamType = 0;
	//ClientInfoChn.dwLinkMode = 0;
	//ClientInfoChn.byPreviewMode = 0;
	//ClientInfoChn.bBlocked = 1;
	//ClientInfoChn.byProtoType = 0;
	//ClientInfoChn.bPassbackRecord = 0;
	//ClientInfoChn.byVideoCodingType = 0;
	//ClientInfoChn.dwDisplayBufNum = 0;

	//long lRealPlayHandleChn = 0;
	//lRealPlayHandleChn = NET_DVR_RealPlay_V40( g_lUserID, &ClientInfoChn, NULL, &ClientInfoChn.dwDisplayBufNum );

	///*LONG lRealPlayHandleChn;
	//lRealPlayHandleChn = NET_DVR_RealPlay_V30( lUserID, &ClientInfoChn, NULL, NULL, TRUE );*/
	//if (lRealPlayHandleChn<0)
	//{
	//	CString strInfo;
	//	strInfo.Format( _T("NET_DVR_RealPlay_V30 failed! Error number: %d"), NET_DVR_GetLastError() );

	//	MessageBox( strInfo );
	//	return;
	//}
	////cvWaitKey(0);
	//Sleep( -1 );

	////fclose(fp);
	////---------------------------------------
	////�ر�Ԥ��
	//if (!NET_DVR_StopRealPlay( lRealPlayHandleChn ))
	//{
	//	CString strInfo;
	//	strInfo.Format( _T( "NET_DVR_StopRealPlay failed! Error number: 1" ), NET_DVR_GetLastError() );

	//	MessageBox( strInfo );
	//	return;
	//}
	//
	////ע���û�
	//NET_DVR_Logout( lUserID );
	//NET_DVR_Cleanup();

}


void CPTZControlDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ע���û�
	NET_DVR_Logout( g_lUserID );
	NET_DVR_Cleanup();

	CDialogEx::OnClose();
}
