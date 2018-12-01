
// JsonHelperTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JsonHelperTest.h"
#include "JsonHelperTestDlg.h"
#include "afxdialogex.h"
#include "JsonHelper.h"
#include "Shape.h"
#include "TestModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CJsonHelperTestDlg dialog




CJsonHelperTestDlg::CJsonHelperTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJsonHelperTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJsonHelperTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJsonHelperTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_SELECT_FILE, &CJsonHelperTestDlg::OnBnClickedSelectFile)
	ON_BN_CLICKED(ID_SINGLE_FRAME_MODEL, &CJsonHelperTestDlg::OnBnClickedSingleFrameModel)
	ON_BN_CLICKED(ID_TEST_MODEL, &CJsonHelperTestDlg::OnBnClickedTestModel)
END_MESSAGE_MAP()


// CJsonHelperTestDlg message handlers

BOOL CJsonHelperTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJsonHelperTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJsonHelperTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJsonHelperTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJsonHelperTestDlg::OnBnClickedSelectFile()
{
	CFileDialog FileDialog(TRUE, _T(".json"), NULL, NULL, _T("Json File (*.json)|*.json||"));
	if(FileDialog.DoModal() != IDOK)
	{
		return;
	}
	SetDlgItemText(IDC_EDIT_FILE_NAME, FileDialog.GetPathName());
}


void CJsonHelperTestDlg::OnBnClickedSingleFrameModel()
{
	CString strFileName;
	GetDlgItemText(IDC_EDIT_FILE_NAME, strFileName);

	JsonHelper jsonHelperRead(true);
	jsonHelperRead.ReadFile(strFileName);

	Shape shape;
	shape.Json(jsonHelperRead);

	JsonHelper jsonHelperWrite(false);
	shape.Json(jsonHelperWrite);
	int pos = strFileName.ReverseFind('.');
	CString strFileNameOutput = strFileName.Left(pos) + "_output" + strFileName.Right(strFileName.GetLength() - pos);
	jsonHelperWrite.WriteFile(strFileNameOutput, true);

	AfxMessageBox( "\"" + strFileNameOutput + "\" generated!");
}


void CJsonHelperTestDlg::OnBnClickedTestModel()
{
	CString strFileName;
	GetDlgItemText(IDC_EDIT_FILE_NAME, strFileName);

	JsonHelper jsonHelperRead(true);
	jsonHelperRead.ReadFile(strFileName);

	TestModel testModel;
	testModel.Json(jsonHelperRead);

	JsonHelper jsonHelperWrite(false);
	testModel.Json(jsonHelperWrite);
	int pos = strFileName.ReverseFind('.');
	CString strFileNameOutput = strFileName.Left(pos) + "_output" + strFileName.Right(strFileName.GetLength() - pos);
	jsonHelperWrite.WriteFile(strFileNameOutput, true);

	AfxMessageBox( "\"" + strFileNameOutput + "\" generated!");
}
