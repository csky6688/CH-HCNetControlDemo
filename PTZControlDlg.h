
// PTZControlDlg.h : 头文件
//

#pragma once
#include "PTZButton.h"
#include "afxwin.h"

// CPTZControlDlg 对话框
class CPTZControlDlg : public CDialogEx
{
// 构造
public:
	CPTZControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PTZCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton9();
	bool StopVideo(void);
	long GetPlayHandle( void )
	{
		return m_lHandle;
	}

	bool GetbPreviewBlock( void )
	{
		return m_bPreviewBlock;
	}

	int GetChannelNum( void )
	{
		return m_iChannel;
	}

	long GetlUserID( void )
    {
        return m_lUserID;
    }

private:
	long m_lHandle;
	bool m_bPreviewBlock;
	int m_iChannel;
	long m_lUserID;

public:
	afx_msg void OnClose();

	//The order of the below icon must be same as in CPTZButton
	CPTZButton m_btnPtzUp;
	CPTZButton m_btnPtzDown;
	CPTZButton m_btnPtzLeft;
	CPTZButton m_btnPtzRight;
	CPTZButton m_btnPtzUpLeft;
	CPTZButton m_btnPtzUpRight;
	CPTZButton m_btnPtzDownLeft;
	CPTZButton m_btnPtzDownRight;
	CPTZButton m_btnZoomIn;//zoom in
	CPTZButton m_btnZoomOut;//zoom out
	CPTZButton m_btnFocusNear;//focus near
	CPTZButton m_btnFocusFar;//focus far
	CPTZButton m_btnIrisOpen;//iris open
	CPTZButton m_btnIrisClose;//iris close
	int m_iCruiseRoute;
	CComboBox m_PTZSpeedCombo;
	int m_iPTZSpeed;
};
