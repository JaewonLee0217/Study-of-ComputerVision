// CAddNoiseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Viewer.h"
#include "CAddNoiseDlg.h"
#include "afxdialogex.h"


// CAddNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CAddNoiseDlg, CDialogEx)

CAddNoiseDlg::CAddNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDNOISEDIALOG, pParent)
{

}

CAddNoiseDlg::~CAddNoiseDlg()
{
}

void CAddNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddNoiseDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddNoiseDlg 메시지 처리기
