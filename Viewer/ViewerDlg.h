
// ViewerDlg.h: 헤더 파일
//
#include "opencv2/opencv.hpp"
#include "CFilterDlg.h"
#pragma once

using namespace cv;
// CViewerDlg 대화 상자

enum FilterType
{
	FILTER_AVERAGE,
	FILTER_SMOOTH,
	FILTER_SHARPEN,
	FILTER_GAUSSIAN
};
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
	
	enum ImageFormat
	{
		FORMAT_RGB,
		FORMAT_YUV444,
		FORMAT_YUV420,
		FORMAT_GRAY
	};


// 구현입니다.

private:
	int nFormat;
	bool isImageOpened;
	unsigned char** ch_in_gray;

	int nHeight_in, nWidth_in;
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_PicOri;
	CStatic m_PicProc;
	//Display용 멤버 변수 및 메서드
	Mat Ori_Img, Proc_Img;
	CRect rect;
	CDC* m_pDC;
	afx_msg void OnFileOpenBtnClickR();
	afx_msg void OnConvertgrayBtnClick();
	afx_msg void OnConvertyuvBtnClick();
	afx_msg void OnEditFilterClicked();
};
unsigned char** Padding(unsigned char** In, int nHeight, int nWidth, int nFilterSize);
void AverageFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void SmoothFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth);
void SharpenFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth);
void GaussianFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth);