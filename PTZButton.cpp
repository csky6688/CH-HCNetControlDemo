/**********************************************************
FileName:    PTZButton.cpp
Description: PTZ button      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "PTZButton.h"
#include "HCNetSDK.h"
#include "PTZControl.h"
#include "PTZControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPTZControlDlg* g_pMainDlg;
extern bool g_bPreviewBlock;
int g_iPtzBtnIndex = 0;

BOOL PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand,DWORD dwStop, char *szCmdString)
{
	BOOL bRet = FALSE;
	LONG lLoginID = -1;
	long lChanNum = -1;
	int iSpeed = g_pMainDlg->m_PTZSpeedCombo.GetCurSel() + 1;
	lLoginID = g_pMainDlg->GetlUserID();
	//lChanNum = iChanIndex + g_struDeviceInfo[iDevIndex].iStartChan;
	lChanNum = g_pMainDlg->GetChannelNum();
	if (lRealHandle >= 0 /*&& g_bInSide*/)
	{
		if (iSpeed >= 1)
		{
			bRet = NET_DVR_PTZControlWithSpeed(lRealHandle, dwPTZCommand, dwStop, iSpeed);
		}
		else
		{
			if (g_pMainDlg->GetbPreviewBlock())
			{
				bRet = NET_DVR_PTZControl_EX(lRealHandle, dwPTZCommand, dwStop);//on the preview socket
			}
			else
			{
				bRet = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStop);//not on the preview socket
			}	
		}	
		/*if (bRet)
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_SUCC_T, "NET_DVR_PTZControl[%d] %s[%d]stop[%d] speed[%d]", g_struLocalParam.bPreviewBlock, szCmdString, dwPTZCommand, dwStop, iSpeed);
		}
		else
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_FAIL_T, "NET_DVR_PTZControl[%d] %s[%d]stop[%d] speed[%d]", g_struLocalParam.bPreviewBlock, szCmdString, dwPTZCommand, dwStop, iSpeed);
		}*/
	}
	else if (lLoginID >= 0 )
	{
		if (iSpeed >= 1)
		{
			bRet = NET_DVR_PTZControlWithSpeed_Other(lLoginID, lChanNum, dwPTZCommand, dwStop, iSpeed);
		}
		else
		{
			bRet = NET_DVR_PTZControl_Other(lLoginID, lChanNum, dwPTZCommand, dwStop);
		}
	/*	if (bRet)
		{
			g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_PTZControl_Other \
				%s[%d]stop[%d] speed[%d] %s", szCmdString, dwPTZCommand, dwStop,\
				iSpeed, g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName);
		}
		else
		{
			g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_PTZControl_Other \
				%s[%d]stop[%d] speed[%d] %s", szCmdString, dwPTZCommand, dwStop, iSpeed,\
				g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName);
		}*/
	}
	return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CPTZButton
/*********************************************************
  Function:	CPTZButton
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CPTZButton::CPTZButton()
: m_lPlayHandle(-1)
{
	m_iSubBtnIndex = g_iPtzBtnIndex++;
}

/*********************************************************
  Function:	~CPTZButton
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CPTZButton::~CPTZButton()
{
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CPTZButton, CButton)
	//{{AFX_MSG_MAP(CPTZButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZButton message handlers
/*********************************************************
  Function:	OnLButtonDown
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CPTZButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	BOOL bRet = FALSE;
	m_lPlayHandle = g_pMainDlg->GetPlayHandle();

	switch (m_iSubBtnIndex)
	{
	case 0:        
		bRet = PTZControlAll(m_lPlayHandle, TILT_UP, 0, "TILT_UP");
		break;
	case 1:			
		bRet = PTZControlAll(m_lPlayHandle, TILT_DOWN, 0, "TILT_DOWN");
		break;
	case 2:		
		bRet = PTZControlAll(m_lPlayHandle, PAN_LEFT, 0, "PAN_LEFT");
		break;
	case 3:			
		bRet = PTZControlAll(m_lPlayHandle, PAN_RIGHT, 0, "PAN_RIGHT");
		break;
	case 4:
		bRet = PTZControlAll( m_lPlayHandle, UP_LEFT, 0, "UP_LEFT" );
		break;
	case 5:
		bRet = PTZControlAll( m_lPlayHandle, UP_RIGHT, 0, "UP_RIGHT" );
		break;
	case 6:
		bRet = PTZControlAll( m_lPlayHandle, DOWN_LEFT, 0, "DOWN_LEFT" );
		break;
	case 7:
		bRet = PTZControlAll( m_lPlayHandle, DOWN_RIGHT, 0, "DOWN_RIGHT" );
		break;
	case 8:         
		bRet = PTZControlAll(m_lPlayHandle, ZOOM_IN, 0, "ZOOM_IN");
		break;
	case 9:			
		bRet = PTZControlAll(m_lPlayHandle, ZOOM_OUT, 0, "ZOOM_OUT");
		break;
	case 10:			
		bRet = PTZControlAll(m_lPlayHandle, FOCUS_NEAR, 0, "FOCUS_NEAR");
		break;
	case 11:		
		bRet = PTZControlAll(m_lPlayHandle, FOCUS_FAR, 0, "FOCUS_FAR");
		break;
	case 12:		
		bRet = PTZControlAll(m_lPlayHandle, IRIS_OPEN, 0, "IRIS_OPEN");
		break;
	case 13:			
		bRet = PTZControlAll(m_lPlayHandle, IRIS_CLOSE, 0, "IRIS_CLOSE");
		break;
	default:
		break;
	}

	CButton::OnLButtonDown(nFlags, point);
}

/*********************************************************
  Function:	OnLButtonUp
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CPTZButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	BOOL bRet = FALSE;
 
	m_lPlayHandle = g_pMainDlg->GetPlayHandle();
	switch (m_iSubBtnIndex)
	{
	case 0:        
		bRet = PTZControlAll(m_lPlayHandle, TILT_UP, 1, "TILT_UP");
		break;
	case 1:			
		bRet = PTZControlAll(m_lPlayHandle, TILT_DOWN, 1, "TILT_DOWN");
		break;
	case 2:			
		bRet = PTZControlAll(m_lPlayHandle, PAN_LEFT, 1, "PAN_LEFT");
		break;
	case 3:			
		bRet = PTZControlAll(m_lPlayHandle, PAN_RIGHT, 1, "PAN_RIGHT");
		break;
	case 4:
		bRet = PTZControlAll( m_lPlayHandle, UP_LEFT, 1, "UP_LEFT" );
		break;
	case 5:
		bRet = PTZControlAll( m_lPlayHandle, UP_RIGHT, 1, "UP_RIGHT" );
		break;
	case 6:
		bRet = PTZControlAll( m_lPlayHandle, DOWN_LEFT, 1, "DOWN_LEFT" );
		break;
	case 7:
		bRet = PTZControlAll( m_lPlayHandle, DOWN_RIGHT, 1, "DOWN_RIGHT" );
		break;
	case 8:
		bRet = PTZControlAll( m_lPlayHandle, ZOOM_IN, 1, "ZOOM_IN" );
		break;
	case 9:
		bRet = PTZControlAll( m_lPlayHandle, ZOOM_OUT, 1, "ZOOM_OUT" );
		break;
	case 10:
		bRet = PTZControlAll( m_lPlayHandle, FOCUS_NEAR, 1, "FOCUS_NEAR" );
		break;
	case 11:
		bRet = PTZControlAll( m_lPlayHandle, FOCUS_FAR, 1, "FOCUS_FAR" );
		break;
	case 12:		
		bRet = PTZControlAll(m_lPlayHandle, IRIS_OPEN, 1, "IRIS_OPEN");
		break;
	case 13:		
		bRet = PTZControlAll(m_lPlayHandle, IRIS_CLOSE, 1, "IRIS_CLOSE");
		break;
	default:
		break;
	}
	if (!bRet)
	{
		/*char szLan[32] = {0};
		g_StringLanType(szLan, "ÔÆÌ¨¿ØÖÆÊ§°Ü", "ptz control failed!");
		AfxMessageBox(szLan);*/

		MessageBox( _T("ÔÆÌ¨¿ØÖÆÊ§°Ü"), _T("ptz control failed!"),NULL );
	}

	CButton::OnLButtonUp(nFlags, point);
}
