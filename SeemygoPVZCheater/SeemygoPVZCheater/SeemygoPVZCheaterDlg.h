
// SeemygoPVZCheaterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSeemygoPVZCheaterDlg �Ի���
class CSeemygoPVZCheaterDlg : public CDialogEx
{
// ����
public:
	CSeemygoPVZCheaterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEEMYGOPVZCHEATER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	HCURSOR  m_copyrightCursor;
	RECT  m_copyrightRect;
public:
	afx_msg void OnBnClickedCoin();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedUnbreakable();
	afx_msg void OnBnClickedKill();
	afx_msg void OnBnClickedBackground();
	afx_msg void OnBnClickedCd();
	afx_msg void OnBnClickedZoombieUnbreakable();
	CButton m_sunshine;
	CButton m_unbreakable;
	CButton m_coin;
	CButton m_cancel;
	CButton m_kill;
	CButton m_background;
	CButton m_zoombieUnbreakable;
	CButton m_cd;
	afx_msg void OnClose();
	CStatic m_copyright;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCourse();
};
