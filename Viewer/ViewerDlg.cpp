
// ViewerDlg.cpp: 구현 파일

#include "pch.h"
#include "framework.h"
#include "Viewer.h"
#include "ViewerDlg.h"
#include "afxdialogex.h"
#include "CFilterDlg.h"


#include <opencv2/opencv.hpp>

using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenBtnClick();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_FILE_FILEOPEN, &CAboutDlg::OnFileOpenBtnClick)
END_MESSAGE_MAP()


// CViewerDlg 대화 상자



CViewerDlg::CViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_FILEOPEN, &CViewerDlg::OnFileOpenBtnClickR)
	ON_COMMAND(ID_CONVERTCOLOR_CONVERTGRAY, &CViewerDlg::OnConvertgrayBtnClick)
	ON_COMMAND(ID_CONVERTCOLOR_CONVERTYUV, &CViewerDlg::OnConvertyuvBtnClick)
	ON_COMMAND(ID_EDIT_FIND, &CViewerDlg::OnEditFilterClicked)
END_MESSAGE_MAP()


// CViewerDlg 메시지 처리기

BOOL CViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAboutDlg::OnFileOpenBtnClick()
{
	
}


void CViewerDlg::OnFileOpenBtnClickR()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.GetFileExt() != "jpg" && dlg.GetFileExt() != "JPG")
		{
			MessageBox("JPG파일이 아닙니다.");
			return;
		}
		
		InpImg = imread((const char *)dlg.GetPathName());
		imshow("original_image", InpImg);
		isImageOpened = true;
		nFormat = FORMAT_GRAY;
		waitKey(0);

	}
}


void CViewerDlg::OnConvertgrayBtnClick()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		InpImg = imread((const char*)dlg.GetPathName());
		imshow("Converted_Image", InpImg);
		waitKey(0);
	}
	/*
	if (InpImg.data != NULL)
	{
		
		//2차원 메모리 할당
		GrayImg = new unsigned char*[InpImg.rows];
		for (int h = 0;h < InpImg.rows;h++) {
			GrayImg[h] = new unsigned char[InpImg.cols];
		}
		Mat OutImg(InpImg.rows, InpImg.cols, CV_8UC1);
		//그레이 이미지로 변환
		for (int h = 0;h < InpImg.rows;h++) {
			for (int w = 0; w < InpImg.cols;w++) {
				unsigned char R, G, B;//한 픽셀에 접근에서 RGB값을 받아와서 그레이지 이미지 할당영역에 넣는다
				R = InpImg.at<uchar>(h, w * 3+2);
				G = InpImg.at<uchar>(h, w * 3+1);
				B= InpImg.at<uchar>(h, w * 3);//B,G,R순서로 읽으니까
				OutImg.at<uchar>(h,w) = 0.299 * R + 0.587 * G + 0.114 * B;
			}
		}
		
		//
		//2차원 메모리 해제
		for (int n = 0;n < InpImg.rows;n++) {
			delete[] GrayImg[n];
		}
		delete[] GrayImg;

		imshow("OutImg", OutImg);

	}
	*/
}


void CViewerDlg::OnConvertyuvBtnClick()
{
	Mat OutY(InpImg.rows, InpImg.cols, CV_8UC1);
	Mat OutU(InpImg.rows, InpImg.cols, CV_8UC1);
	Mat OutV(InpImg.rows, InpImg.cols, CV_8UC1);
	if (InpImg.data != NULL)
	{
		GrayImg = new unsigned char* [InpImg.rows];
		U = new unsigned char*[InpImg.rows];
		V = new unsigned char*[InpImg.rows];
		for (int h = 0;h < InpImg.rows;h++)
		{
			GrayImg[h] = new unsigned char[InpImg.cols];
			U[h] = new unsigned char[InpImg.cols];
			V[h] = new unsigned char[InpImg.cols];
		}
		//Convert RGB for YUV444
		for (int h = 0;h < InpImg.rows;h++) {
			for (int w = 0; w < InpImg.cols;w++) {
				unsigned char R, G, B;//한 픽셀에 접근에서 RGB값을 받아와서 그레이지 이미지 할당영역에 넣는다
				R = InpImg.at<uchar>(h, w * 3 + 2);
				G = InpImg.at<uchar>(h, w * 3 + 1);
				B = InpImg.at<uchar>(h, w * 3);//B,G,R순서로 읽으니까
				GrayImg[h][w] = (0.299 * R) + (0.587 * G) + (0.114 * B);
			}
		}
		for (int h = 0;h < InpImg.rows;h++) {
			for (int w = 0; w < InpImg.cols;w++) {
				unsigned char R, G, B;//한 픽셀에 접근에서 RGB값을 받아와서 그레이지 이미지 할당영역에 넣는다
				R = InpImg.at<uchar>(h, w * 3 + 2);
				G = InpImg.at<uchar>(h, w * 3 + 1);
				B = InpImg.at<uchar>(h, w * 3);//B,G,R순서로 읽으니까
				U[h][w] = (-0.169 * R) +(-0.331 * G) + (0.499 * B);
			}
		}
		for (int h = 0;h < InpImg.rows;h++) {
			for (int w = 0; w < InpImg.cols;w++) {
				unsigned char R, G, B;//한 픽셀에 접근에서 RGB값을 받아와서 그레이지 이미지 할당영역에 넣는다
				R = InpImg.at<uchar>(h, w * 3 + 2);
				G = InpImg.at<uchar>(h, w * 3 + 1);
				B = InpImg.at<uchar>(h, w * 3);//B,G,R순서로 읽으니까
				V[h][w] = (0.499 * R) - (0.418 * G) - (0.081 * B);
			}
		}
		for (int h = 0;h < InpImg.rows;h++) {
			for (int w = 0; w < InpImg.cols;w++) {
				OutY.at<uchar>(h, w) = GrayImg[h][w];
				OutU.at<uchar>(h, w) = U[h][w];
				OutV.at<uchar>(h, w) = V[h][w];

			}
		}
		
		//write YUN444 file
		FILE* fp;
		fopen_s(&fp, "Result.yuv", "wb");
		for (int h = 0;h < InpImg.rows;h++)
		{
			fwrite(GrayImg[h], sizeof(unsigned char), InpImg.cols, fp);
		}
		for (int h = 0;h < InpImg.rows;h++)
		{
			fwrite(U[h], sizeof(unsigned char), InpImg.cols, fp);
		}
		for (int h = 0;h < InpImg.rows;h++)
		{
			fwrite(V[h], sizeof(unsigned char), InpImg.cols, fp);
		}
		imshow("ResultY.yuv", OutY);
		imshow("ResultU.yuv", OutU);
		imshow("ResultV.yuv", OutV);
		fclose(fp);
		
		//2D메모리 해제
		for (int n = 0;n < InpImg.rows;n++) {
			delete[] GrayImg[n];
			delete[] U[n];
			delete[] V[n];
		}
		delete[] GrayImg;
		delete[] U;
		delete[] V;


	}
}
unsigned char** MemAlloc2D(int nHeight, int nWidth, unsigned char nInitVal)
{
	unsigned char** rtn = new unsigned char* [nHeight];
	for (int n = 0; n < nHeight; n++)
	{
		rtn[n] = new unsigned char[nWidth];
		memset(rtn[n], nInitVal, sizeof(unsigned char) * nWidth);
	}
	return rtn;
}

void MemFree2D(unsigned char** Mem, int nHeight)
{
	for (int n = 0; n < nHeight; n++)
	{
		delete[] Mem[n];
	}
	delete[] Mem;
}

unsigned char** Padding(unsigned char** In, int nHeight, int nWidth, int nFilterSize)
{
	int nPadSize = (int)(nFilterSize / 2);
	unsigned char** Pad = MemAlloc2D(nHeight + 2 * nPadSize, nWidth + 2 * nPadSize, 0);
	for (int h = 0;h < nHeight;h++)
	{
		for (int w = 0;w < nWidth;w++) {
			Pad[h + nPadSize][w + nPadSize] = In[h][w];
		}
	}

	for (int h = 0;h < nPadSize;h++)
	{
		for (int w = 0;w < nWidth;w++)
		{
			Pad[h][w + nPadSize] = In[0][w];
			Pad[h + (nHeight - 1)][w + nPadSize] = In[nHeight - 1][w];
		}
	}
	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nPadSize; w++)
		{
			Pad[h + nPadSize][w] = In[h][0];
			Pad[h + nPadSize][w + (nWidth - 1) + nPadSize] = In[h][nWidth - 1];
		}
	}

	for (int h = 0; h < nPadSize; h++)
	{
		for (int w = 0; w < nPadSize; w++)
		{
			Pad[h][w] = In[0][0];
			Pad[h + (nHeight - 1) + nPadSize][w] = In[nHeight - 1][0];
			Pad[h][w + (nWidth - 1) + nPadSize] = In[0][nWidth - 1];
			Pad[h + (nHeight - 1) + nPadSize][w + (nWidth - 1) + nPadSize] = In[nHeight - 1][nWidth - 1];
		}
	}

	return Pad;
}

void AverageFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth, int nFilterSize)
{
	int nTemp = 0, nPadSize = (int)(nFilterSize / 2);
	In_Pad = Padding(In_Pad, nHeight, nWidth, nFilterSize);

	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			nTemp = 0;
			for (int n = 0; n < nFilterSize; n++)
			{
				for (int m = 0; m < nFilterSize; m++)
				{
					nTemp += In_Pad[h + n][w + m];
				}
			}

			Out[h][w] = static_cast<unsigned char>(nTemp / (nFilterSize * nFilterSize));
		}
	}
	Mat ResultImg(nHeight, nWidth, CV_8UC1);
	for (int h = 0; h < ResultImg.rows; h++)
	{
		for (int w = 0; w < ResultImg.cols; w++)
		{
			ResultImg.at<unsigned char>(h, w) = Out[h][w];
		}
	}
	MemFree2D(In_Pad, nHeight + 2 * nPadSize);
	imshow("S", ResultImg);
	

}
void SmoothFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth)
{
	int nTemp = 0, nPadSize = (int)(3 / 2);
	In_Pad = Padding(In_Pad, nHeight, nWidth, 3);

	double Mask[3][3] = {
		{ 1, 2, 1 },
		{ 2 , 4 , 2 },
		{ 1, 2 , 1 }
	};

	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			nTemp = 0;
			for (int n = 0; n < 3; n++)
			{
				for (int m = 0; m < 3; m++)
				{
					nTemp += In_Pad[h + n][w + m] * Mask[n][m];
				}
			}

			Out[h][w] = static_cast<unsigned char>(nTemp / 16);
		}
	}
	Mat ResultImg(nHeight, nWidth, CV_8UC1);
	for (int h = 0; h < ResultImg.rows; h++)
	{
		for (int w = 0; w < ResultImg.cols; w++)
		{
			ResultImg.at<unsigned char>(h, w) = Out[h][w];
		}
	}
	MemFree2D(In_Pad, nHeight + 2 * nPadSize);
	imshow("S", ResultImg);
	
}
void SharpenFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth)
{
	int Mask[3][3] = {
		{ 0,-1,0 },
		{ -1,5,-1 },
		{ 0,-1,0 }
	};
	int nTemp = 0, nPadSize = (int)(3 / 2);
	In_Pad = Padding(In_Pad, nHeight, nWidth, 3);

	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			nTemp = 0;
			for (int n = 0; n < 3; n++)
			{
				for (int m = 0; m < 3; m++)
				{
					nTemp += In_Pad[h + n][w + m] * Mask[n][m];
				}
			}
			if (nTemp > 255)nTemp = 255;
			else if (nTemp < 0)nTemp = 0;

			Out[h][w] = static_cast<unsigned char>(nTemp);
		}
	}
	Mat ResultImg(nHeight, nWidth, CV_8UC1);
	for (int h = 0; h < ResultImg.rows; h++)
	{
		for (int w = 0; w < ResultImg.cols; w++)
		{
			ResultImg.at<unsigned char>(h, w) = Out[h][w];
		}
	}
	MemFree2D(In_Pad, nHeight + 2 * nPadSize);
	imshow("S", ResultImg);
	
}
void GaussianFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth)
{
	int PadSize = 1;
	double gaussian[3][3];
	double result = 0;

	double stdv = 1;
	double r, s = 2.0 * stdv * stdv;
	double sum = 0.0;

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			r = (x * x + y * y);
			gaussian[x + 1][y + 1] = (exp(-(r) / s)) / sqrt(3.14 * s);
			sum += gaussian[x + 1][y + 1];
		}
	}

	for (int i = 0; i < 3; ++i) // Loop to normalize the kernel
		for (int j = 0; j < 3; ++j)
			gaussian[i][j] /= sum;

	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			result = 0;
			for (int i = -PadSize; i <= PadSize; i++)
				for (int j = -PadSize; j <= PadSize; j++)
				{
					result += In_Pad[h + i + PadSize][w + j + PadSize] * gaussian[i + PadSize][j + PadSize];
				}

			Out[h][w] = result;
		}
	}

	Mat ResultImg(nHeight, nWidth, CV_8UC1);
	for (int h = 0; h < ResultImg.rows; h++)
	{
		for (int w = 0; w < ResultImg.cols; w++)
		{
			ResultImg.at<unsigned char>(h, w) = Out[h][w];
		}
	}
	imshow("G", ResultImg);
}

void CViewerDlg::OnEditFilterClicked()
{
	
	
	if (isImageOpened && nFormat ==FORMAT_GRAY)
	{
		CFilterDlgR FilterDlg;
		
		unsigned char** Pad, ** Out;
		if (FilterDlg.DoModal() == IDOK)
		{
			int nFilterType = FilterDlg.getFilterType();
			int nFilterSize = FilterDlg.getFilterSize();
			switch (nFilterType)
			{
			case FILTER_AVERAGE:
				if (nFilterSize >= 3)
				{
					if (nFilterSize % 2 == 0)
					{
						nFilterSize++;
					}
					Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, nFilterSize);
					Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

					AverageFilter(Pad, Out, nHeight_in, nWidth_in, nFilterSize);

					MemFree2D(Pad, nHeight_in + (int)(nFilterSize / 2) * 2);
					MemFree2D(Out, nHeight_in);
				}
				else MessageBox("FilterSize가 잘못되었습니다. FilterSize는 3 이상의 정수 값을 가져야 합니다.");
				break;
			case FILTER_SMOOTH:
				Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
				Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

				SmoothFilter(Pad, Out, nHeight_in, nWidth_in);

				MemFree2D(Pad, nHeight_in + 2);
				MemFree2D(Out, nHeight_in);
				break;
			case FILTER_SHARPEN:
				Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
				Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

				SharpenFilter(Pad, Out, nHeight_in, nWidth_in);

				MemFree2D(Pad, nHeight_in + 2);
				MemFree2D(Out, nHeight_in);
				break;
			case FILTER_GAUSSIAN:
				Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
				Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

				GaussianFilter(Pad, Out, nHeight_in, nWidth_in);

				MemFree2D(Pad, nHeight_in + 2);
				MemFree2D(Out, nHeight_in);
				break;
			}
		}
	}
	else
	{
		MessageBox("불러온 영상이 없거나 영상 포맷이 회색조 영상이 아닙니다.");
		}
	

}

