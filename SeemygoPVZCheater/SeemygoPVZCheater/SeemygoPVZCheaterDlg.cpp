
// SeemygoPVZCheaterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SeemygoPVZCheater.h"
#include "SeemygoPVZCheaterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����̵߳�ˢ��ʱ��
#define MONITOR_REFRESH_TIME_INTERVAL 1000

// ֲ���ս��ʬ�Ľ��̾��
static HANDLE g_processHandle;
// �������ֲ���ս��ʬ���߳̾��
static HANDLE g_monitoringThreadHandle;
// ��������
static CSeemygoPVZCheaterDlg *g_dlg;

// ��ĳ��ֵд��ֲ���ս��ʬ�ڴ棨����Ŀɱ�����ǵ�ַ����Ҫ��-1��β��
void WriteMemory(void *value, DWORD valueSize, ...)
{
	if (value == NULL || valueSize == NULL || g_processHandle == NULL) return;

	DWORD tempValue = NULL;

	// �������еĵ�ַ
	va_list addresses;
	va_start(addresses, valueSize);
	DWORD offset = NULL;
	DWORD lastAddress = NULL;
	while ((offset = va_arg(addresses, DWORD)) != -1)
	{
		lastAddress = tempValue + offset;
		::ReadProcessMemory(g_processHandle, (LPCVOID)lastAddress, &tempValue, sizeof(DWORD), NULL);
	}
	va_end(addresses);

	// д
	::WriteProcessMemory(g_processHandle, (LPVOID)lastAddress, value, valueSize, NULL);
}

// �������ֲ���ս��ʬ���߳�
DWORD WINAPI MonitoringThreadProc(LPVOID lpParam)
{
	while (1)
	{
		// �Ҵ���
		HWND hwnd = ::FindWindow(TEXT("MainWindow"), TEXT("ֲ���ս��ʬ���İ�"));
		if (hwnd == NULL)
		{
			::CloseHandle(g_processHandle);
			g_processHandle = NULL;

			// ��ֹ���
			g_dlg->m_sunshine.SetCheck(FALSE);
			g_dlg->m_sunshine.EnableWindow(FALSE);

			g_dlg->m_unbreakable.SetCheck(FALSE);
			g_dlg->m_unbreakable.EnableWindow(FALSE);
			g_dlg->OnBnClickedUnbreakable();

			g_dlg->m_cd.SetCheck(FALSE);
			g_dlg->m_cd.EnableWindow(FALSE);
			g_dlg->OnBnClickedCd();

			g_dlg->m_background.SetCheck(FALSE);
			g_dlg->m_background.EnableWindow(FALSE);
			g_dlg->OnBnClickedBackground();

			g_dlg->m_kill.SetCheck(FALSE);
			g_dlg->m_kill.EnableWindow(FALSE);
			g_dlg->OnBnClickedKill();

			g_dlg->m_zoombieUnbreakable.SetCheck(FALSE);
			g_dlg->m_zoombieUnbreakable.EnableWindow(FALSE);
			g_dlg->OnBnClickedZoombieUnbreakable();

			g_dlg->m_cancel.EnableWindow(FALSE);
			g_dlg->m_coin.EnableWindow(FALSE);
		}
		else if (g_processHandle == NULL)
		{
			// �ҽ���ID
			DWORD pid = NULL;
			::GetWindowThreadProcessId(hwnd, &pid);

			// �ҽ��̾��
			g_processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

			// �������
			g_dlg->m_sunshine.EnableWindow(TRUE);
			g_dlg->m_unbreakable.EnableWindow(TRUE);
			g_dlg->m_cd.EnableWindow(TRUE);
			g_dlg->m_coin.EnableWindow(TRUE);
			g_dlg->m_cancel.EnableWindow(TRUE);
			g_dlg->m_background.EnableWindow(TRUE);
			g_dlg->m_kill.EnableWindow(TRUE);
			g_dlg->m_zoombieUnbreakable.EnableWindow(TRUE);
		}

		if (g_dlg->m_sunshine.GetCheck())
		{ // �����Ҫ��������
			DWORD value = 9990;
			WriteMemory(&value, sizeof(value), 0x6A9EC0, 0x320, 0x8, 0x0, 0x8, 0x144, 0x2c, 0x5560, -1);
		}

		::Sleep(MONITOR_REFRESH_TIME_INTERVAL);
	}
	return 0;
}

// ���XP��߳���ķ���Ȩ��
BOOL ImproveAccessPrivilege()
{
	HANDLE tokenHandle;
	LUID privilegeValue;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &tokenHandle)) return FALSE;

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &privilegeValue))
	{
		CloseHandle(tokenHandle);
		return FALSE;
	}

	TOKEN_PRIVILEGES privileges;
	privileges.PrivilegeCount = 1;
	privileges.Privileges[0].Luid = privilegeValue;
	privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(tokenHandle, FALSE, &privileges, sizeof(privileges), NULL, NULL))
	{
		CloseHandle(tokenHandle);
		return FALSE;
	}

	return TRUE;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSeemygoPVZCheaterDlg �Ի���
CSeemygoPVZCheaterDlg::CSeemygoPVZCheaterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEEMYGOPVZCHEATER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeemygoPVZCheaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUNSHINE, m_sunshine);
	DDX_Control(pDX, IDC_UNBREAKABLE, m_unbreakable);
	DDX_Control(pDX, IDC_COIN, m_coin);
	DDX_Control(pDX, IDC_CANCEL, m_cancel);
	DDX_Control(pDX, IDC_KILL, m_kill);
	DDX_Control(pDX, IDC_BACKGROUND, m_background);
	DDX_Control(pDX, IDC_ZOOMBIE_UNBREAKABLE, m_zoombieUnbreakable);
	DDX_Control(pDX, IDC_CD, m_cd);
	DDX_Control(pDX, IDC_COPYRIGHT, m_copyright);
}

BEGIN_MESSAGE_MAP(CSeemygoPVZCheaterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COIN, &CSeemygoPVZCheaterDlg::OnBnClickedCoin)
	ON_BN_CLICKED(IDC_CANCEL, &CSeemygoPVZCheaterDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_UNBREAKABLE, &CSeemygoPVZCheaterDlg::OnBnClickedUnbreakable)
	ON_BN_CLICKED(IDC_KILL, &CSeemygoPVZCheaterDlg::OnBnClickedKill)
	ON_BN_CLICKED(IDC_BACKGROUND, &CSeemygoPVZCheaterDlg::OnBnClickedBackground)
	ON_BN_CLICKED(IDC_CD, &CSeemygoPVZCheaterDlg::OnBnClickedCd)
	ON_BN_CLICKED(IDC_ZOOMBIE_UNBREAKABLE, &CSeemygoPVZCheaterDlg::OnBnClickedZoombieUnbreakable)
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_COURSE, &CSeemygoPVZCheaterDlg::OnBnClickedCourse)
END_MESSAGE_MAP()


// CSeemygoPVZCheaterDlg ��Ϣ�������
BOOL CSeemygoPVZCheaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ���XPϵͳ��߳����Ȩ��
	ImproveAccessPrivilege();

	// ��������
	g_dlg = this;

	// ��������߳�
	g_monitoringThreadHandle = ::CreateThread(NULL, 0, MonitoringThreadProc, NULL, 0, NULL);

	// ���ذ�Ȩ���е����
	m_copyrightCursor = ::LoadCursor(NULL, IDC_HAND);

	// ��Ȩ���еľ��ο�
	this->m_copyright.GetWindowRect(&m_copyrightRect);
	ScreenToClient(&m_copyrightRect);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSeemygoPVZCheaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSeemygoPVZCheaterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSeemygoPVZCheaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSeemygoPVZCheaterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);

	if (point.x > m_copyrightRect.left && point.x < m_copyrightRect.right &&
		point.y > m_copyrightRect.top  && point.y < m_copyrightRect.bottom)
	{
		::SetCursor(m_copyrightCursor);
	}
}

void CSeemygoPVZCheaterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);

	if (point.x > m_copyrightRect.left && point.x < m_copyrightRect.right &&
		point.y > m_copyrightRect.top  && point.y < m_copyrightRect.bottom)
	{
		::SetCursor(m_copyrightCursor);
		::ShellExecute(NULL, TEXT("open"), TEXT("http://www.520it.com/?CPP_Class_PVZ_UE"), NULL, NULL, SW_SHOWNORMAL);
	}
}

HBRUSH CSeemygoPVZCheaterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_COPYRIGHT)
	{
		// ����Ϊ��ɫ
		pDC->SetTextColor(RGB(0, 0, 255));
	}

	return hbr;
}

// �رմ���
void CSeemygoPVZCheaterDlg::OnClose()
{
	CDialogEx::OnClose();

	// ȥ�����Ч��
	this->OnBnClickedCancel();

	// ɱ���߳�
	::TerminateThread(g_monitoringThreadHandle, 0);
	::CloseHandle(g_monitoringThreadHandle);

	// �رվ��
	::CloseHandle(g_processHandle);
}

// ֲ�ﲻ��-checkbox
void CSeemygoPVZCheaterDlg::OnBnClickedUnbreakable()
{
	DWORD address1 = 0x52FCF0;
	DWORD address2 = 0x46D7A6;
	DWORD address3 = 0x45EC63;
	DWORD address4 = 0x46CFEB;
	if (this->m_unbreakable.GetCheck())
	{ // �����Ҫֲ�ﲻ��
		BYTE data1[] = { 0x90, 0x90, 0x90, 0x90 };
		WriteMemory(data1, sizeof(data1), address1, -1);

		BYTE data2[] = { 0x90, 0x90, 0x90 };
		WriteMemory(data2, sizeof(data2), address2, -1);

		BYTE data3[] = { 0x90, 0x90, 0x90, 0x90 };
		WriteMemory(data3, sizeof(data3), address3, -1);

		BYTE data4[] = { 0x90, 0x90, 0x90 };
		WriteMemory(data4, sizeof(data4), address4, -1);
	}
	else
	{ // �������Ҫֲ�ﲻ��
		BYTE data1[] = { 0x83, 0x46, 0x40, 0xFC };
		WriteMemory(data1, sizeof(data1), address1, -1);

		BYTE data2[] = { 0x29, 0x4E, 0X40 };
		WriteMemory(data2, sizeof(data2), address2, -1);

		BYTE data3[] = { 0x83, 0x46, 0x40, 0xCE };
		WriteMemory(data3, sizeof(data3), address3, -1);

		BYTE data4[] = { 0x29, 0x50, 0x40 };
		WriteMemory(data4, sizeof(data4), address4, -1);
	}
}

// ��CD-checkbox
void CSeemygoPVZCheaterDlg::OnBnClickedCd()
{
	DWORD address = 0x487296;
	if (this->m_cd.GetCheck())
	{ // �����Ҫ��CD
		BYTE data[] = { 0x90, 0x90 };
		WriteMemory(data, sizeof(data), address, -1);
	}
	else
	{ // �������Ҫ��CD
		BYTE data[] = { 0x7E, 0x14 };
		WriteMemory(data, sizeof(data), address, -1);
	}
}

// ��̨����
void CSeemygoPVZCheaterDlg::OnBnClickedBackground()
{
	DWORD address = 0x54E1C2;
	if (this->m_background.GetCheck())
	{ // �����Ҫ��̨����
		BYTE data[] = { 0x90, 0x90, 0x90 };
		WriteMemory(data, sizeof(data), address, -1);
	}
	else
	{ // �������Ҫ��̨����
		BYTE data[] = { 0x0F, 0x95, 0xC0 };
		WriteMemory(data, sizeof(data), address, -1);
	}
}

// ��ɱ��ʬ
void CSeemygoPVZCheaterDlg::OnBnClickedKill()
{
	DWORD address1 = 0x53130F;
	DWORD address2 = 0x531066;
	DWORD address3 = 0x530CB1;
	if (this->m_kill.GetCheck())
	{ // �����Ҫ��ɱ��ʬ
	  // ȥ����ʬ����
		g_dlg->m_zoombieUnbreakable.SetCheck(FALSE);
		g_dlg->OnBnClickedZoombieUnbreakable();

		BYTE data1[] = { 0x2B, 0xFF, 0x90, 0x90 };
		WriteMemory(data1, sizeof(data1), address1, -1);

		BYTE data2[] = { 0x90, 0x90 };
		WriteMemory(data2, sizeof(data2), address2, -1);

		BYTE data3[] = { 0x90, 0x90 };
		WriteMemory(data3, sizeof(data3), address3, -1);
	}
	else
	{ // �������Ҫ��ɱ��ʬ
		BYTE data1[] = { 0x2B, 0x7C, 0x24, 0x20 };
		WriteMemory(data1, sizeof(data1), address1, -1);

		BYTE data2[] = { 0x75, 0x11 };
		WriteMemory(data2, sizeof(data2), address2, -1);

		BYTE data3[] = { 0x75, 0x17 };
		WriteMemory(data3, sizeof(data3), address3, -1);
	}
}

// ��ʬ����
void CSeemygoPVZCheaterDlg::OnBnClickedZoombieUnbreakable()
{
	DWORD address1 = 0x53130F;
	DWORD address2 = 0x531042;
	DWORD address3 = 0x530C9F;
	if (this->m_zoombieUnbreakable.GetCheck())
	{ // �����Ҫ��ʬ����
	  // ȥ����ɱ��ʬ
		g_dlg->m_kill.SetCheck(FALSE);
		g_dlg->OnBnClickedKill();

		BYTE data1[] = { 0x83, 0xEF, 0x00, 0x90 };
		WriteMemory(data1, sizeof(data1), address1, -1);

		BYTE data2[] = { 0x90, 0x90, 0x90, 0x90 };
		WriteMemory(data2, sizeof(data2), address2, -1);

		BYTE data3[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		WriteMemory(data3, sizeof(data3), address3, -1);
	}
	else
	{ // �������Ҫ��ʬ����
		BYTE data1[] = { 0x2B, 0x7C, 0x24, 0x20 };
		WriteMemory(data1, sizeof(data1), address1, -1);

		BYTE data2[] = { 0x2B, 0xF0, 0x2B, 0xC8 };
		WriteMemory(data2, sizeof(data2), address2, -1);

		BYTE data3[] = { 0x2B, 0xD0, 0x29, 0x86, 0xDC, 0x00, 0x00, 0x00 };
		WriteMemory(data3, sizeof(data3), address3, -1);
	}
}

// ���޽��
void CSeemygoPVZCheaterDlg::OnBnClickedCoin()
{
	DWORD value = 99990;
	WriteMemory(&value, sizeof(value), 0x6A9EC0, 0x82C, 0x28, -1);
}

// һ��ȡ��
void CSeemygoPVZCheaterDlg::OnBnClickedCancel()
{
	this->m_sunshine.SetCheck(FALSE);

	this->m_unbreakable.SetCheck(FALSE);
	this->OnBnClickedUnbreakable();

	this->m_cd.SetCheck(FALSE);
	this->OnBnClickedCd();

	this->m_background.SetCheck(FALSE);
	this->OnBnClickedBackground();

	this->m_kill.SetCheck(FALSE);
	this->OnBnClickedKill();

	this->m_zoombieUnbreakable.SetCheck(FALSE);
	this->OnBnClickedZoombieUnbreakable();
}

// ��ȡ��ҿ����̳�
void CSeemygoPVZCheaterDlg::OnBnClickedCourse()
{
	::ShellExecute(NULL, TEXT("open"), 
		TEXT("https://ke.qq.com/course/336509"), 
		NULL, NULL, SW_SHOWNORMAL);
}
