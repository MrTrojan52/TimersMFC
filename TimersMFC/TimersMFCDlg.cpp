
// TimersMFCDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "TimersMFC.h"
#include "TimersMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CTimersMFCDlg



CTimersMFCDlg::CTimersMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMERSMFC_DIALOG, pParent)
	, m_timeInterval(100)
	, m_count(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimersMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETIMEINTERVAL, m_timeInterval);
	DDV_MinMaxInt(pDX, m_timeInterval, 1, 100000);
}

BEGIN_MESSAGE_MAP(CTimersMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BSTART, &CTimersMFCDlg::OnBnClickedStart)
	ON_EN_CHANGE(IDC_ETIMEINTERVAL, &CTimersMFCDlg::OnEnChangeEtimeinterval)
	ON_BN_CLICKED(IDC_BSTOP, &CTimersMFCDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// Обработчики сообщений CTimersMFCDlg

BOOL CTimersMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	SetTimer(ID_TIMER_TIME, 1000, NULL);
	CEdit * e = ((CEdit*)GetDlgItem(IDC_ETIMEINTERVAL));
	e->SetFocus();
	e->SetSel(0, -1);
	return FALSE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTimersMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTimersMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTimersMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimersMFCDlg::OnTimer(UINT timer)
{
	switch (timer)
	{
		case ID_TIMER_TIME:
		{
			CTime t = CTime::GetCurrentTime();
			SetDlgItemText(IDC_STIME, t.Format("%H:%M:%S"));
			break;
		}
		case ID_TIMER_COUNT:
		{
			CString str;
			str.Format(L"%d", ++m_count);
			SetDlgItemText(IDC_SCOUNT, str);
		}

	}
	
}

void CTimersMFCDlg::OnBnClickedStart()
{
	UpdateData(TRUE);
	m_count = 0;
	SetDlgItemText(IDC_SCOUNT, L"0");
	SetTimer(ID_TIMER_COUNT, m_timeInterval, NULL);
	GetDlgItem(IDC_BSTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_BSTOP)->EnableWindow(TRUE);
}

void CTimersMFCDlg::OnEnChangeEtimeinterval()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CTimersMFCDlg::OnBnClickedStop()
{
	KillTimer(ID_TIMER_COUNT);
	GetDlgItem(IDC_BSTART)->EnableWindow(TRUE);
	GetDlgItem(IDC_BSTOP)->EnableWindow(FALSE);
}