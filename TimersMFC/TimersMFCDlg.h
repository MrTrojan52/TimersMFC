
// TimersMFCDlg.h: файл заголовка
//

#pragma once

// Диалоговое окно CTimersMFCDlg
class CTimersMFCDlg : public CDialogEx
{
// Создание
public:
	CTimersMFCDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMERSMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEtimeinterval();
	int m_timeInterval;
	int m_count;
};
