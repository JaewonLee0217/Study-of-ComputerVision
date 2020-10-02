#pragma once


// CAddNoiseTab_2 대화 상자

class CAddNoiseTab_2 : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNoiseTab_2)

public:
	CAddNoiseTab_2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddNoiseTab_2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDNOISE_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
