// CFilterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Viewer.h"
#include "CFilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(CFilterDlgR, CDialogEx)

CFilterDlgR::CFilterDlgR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERDIALOG, pParent)
{

}

CFilterDlgR::~CFilterDlgR()
{
}

void CFilterDlgR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_AVER_Filter, m_radio_Filtertype);
	DDX_Control(pDX, IDC_EDIT1, m_EditFilterSize);
}


BEGIN_MESSAGE_MAP(CFilterDlgR, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFilterDlgR::OnOkbuttonClicked)
	ON_BN_CLICKED(IDCANCEL, &CFilterDlgR::OnCancelbuttonClicked)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_AVER_Filter,IDC_GAUS_Filter,OnClickedRadio)

//	ON_COMMAND(ID_EDIT_FIND, &CFilterDlgR::OnEditFind)
//	ON_EN_CHANGE(IDC_EDIT1, &CFilterDlgR::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CFilterDlg 메시지 처리기
void CFilterDlgR::OnOkbuttonClicked()
{
	CString cstrTemp;
	m_EditFilterSize.GetWindowTextA(cstrTemp);
	nFilterSize = atoi(cstrTemp);
	CDialog::OnOK();
}
void CFilterDlgR::OnCancelbuttonClicked()
{
	CDialog::OnCancel();
}
void CFilterDlgR::OnClickedRadio(UINT msg)
{
	UpdateData(TRUE);
	switch (m_radio_Filtertype)
	{
	case 0:
		nFilterType = 0;
		break;
	case 1:
		nFilterType = 1;
		break;
	case 2:
		nFilterType = 2;
		break;
	case 3:
		nFilterType = 3;
		break;
	}
}
int CFilterDlgR::getFilterSize()
{
	return nFilterSize;
}
int CFilterDlgR::getFilterType()
{
	return nFilterType;
}



