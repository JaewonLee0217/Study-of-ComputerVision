#pragma once


// CFilterDlg 대화 상자

class CFilterDlgR : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlgR)

public:
	CFilterDlgR(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFilterDlgR();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERDIALOG };
#endif
private:
	CStatic m_EditFilterSize;
	int nFilterSize;
	int nFilterType;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio_Filtertype;
	afx_msg void OnOkbuttonClicked();
	afx_msg void OnCancelbuttonClicked();
	afx_msg void OnClickedRadio(UINT msg);
	int getFilterSize();
	int getFilterType();


//	afx_msg void OnEditFind();
//	afx_msg void OnEnChangeEdit1();
};
