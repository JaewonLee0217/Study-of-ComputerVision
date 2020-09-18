// CRawInfoDlg2.cpp: 구현 파일
//

#include "pch.h"
#include "Viewer.h"
#include "CRawInfoDlg2.h"
#include "afxdialogex.h"


// CRawInfoDlg2 대화 상자

IMPLEMENT_DYNAMIC(CRawInfoDlg2, CDialogEx)

CRawInfoDlg2::CRawInfoDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RAWINFODIALOG, pParent)
	, m_radio_rawFileInfo(0)
	, m_EditHeight(0)
	, m_EditWidth(0)
{
	nFormat = 3;
}

CRawInfoDlg2::~CRawInfoDlg2()
{
}

void CRawInfoDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_GRAYFORMAT, m_radio_rawFileInfo);
	//구현추가
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_EditHeight);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_EditWidth);


	DDX_Text(pDX, IDC_EDIT_WIDTH, m_EditHeight);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_EditHeight);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_EditWidth);
}


BEGIN_MESSAGE_MAP(CRawInfoDlg2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRawInfoDlg2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRawInfoDlg2::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_GRAYFORMAT, IDC_RADIO_YUV420FORMAT, OnClickRadio)
END_MESSAGE_MAP()


// CRawInfoDlg2 메시지 처리기


void CRawInfoDlg2::OnBnClickedOk()
{
	CString cTemp1, cTemp2;

	m_EditHeight.GetWindowTextA(cTemp1);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CRawInfoDlg2::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
void CRawInfoDlg2::OnClickRadio(UINT msg)
{
	UpdateData(TRUE);
	switch (m_radio_rawFileInfo)
	{
	case 0:
		nFormat = 3;
		break;
	case 1:
		nFormat = 1;
		break;
	case 2:
		nFormat = 2;
		break;
	}
}

