
// JsonHelperTestDlg.h : header file
//

#pragma once


// CJsonHelperTestDlg dialog
class CJsonHelperTestDlg : public CDialogEx
{
// Construction
public:
	CJsonHelperTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_JSONHELPERTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelectFile();
	afx_msg void OnBnClickedSingleFrameModel();
	afx_msg void OnBnClickedTestModel();
};
