
// ViewerDlg.h: 헤더 파일
//
#include "opencv2/opencv.hpp"
#pragma once

using namespace cv;
// CViewerDlg 대화 상자
class CViewerDlg : public CDialogEx
{
// 생성입니다.
public:
	CViewerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	Mat InpImg, OutImg, TempImg;
	unsigned char** GrayImg;
	unsigned char** U;
	unsigned char** V;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWER_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenBtnClickR();
	afx_msg void OnConvertgrayBtnClick();
	afx_msg void OnConvertyuvBtnClick();
};
