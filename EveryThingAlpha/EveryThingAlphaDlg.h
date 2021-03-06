
// EveryThingAlphaDlg.h: 头文件
//

#pragma once


// CEveryThingAlphaDlg 对话框
class CEveryThingAlphaDlg : public CDialog
{
// 构造
public:
	CEveryThingAlphaDlg(CWnd* pParent = NULL);	// 标准构造函数
	afx_msg void MSGBOX(const char* MSG);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVERYTHINGALPHA_DIALOG };
#endif

	protected:
		BOOL is_win_toped = 0;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);  // PreTranslateMessage是消息在送给TranslateMessage函数之前被调用的
	virtual void LogFile(string ToLog);
	CFont The_Font;
	HANDLE GetProcessByName(string namex);
	BOOL IsWow64ProcessEx(HANDLE hProcess);
	void EnableDebugPriv();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOptionsExit();
	afx_msg void OnOptionsSettings();
	afx_msg void OnAboutEverythingalp();
	afx_msg void OnAboutSaurik();
	afx_msg void OnAbout32775();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnOptionsTopmost();
	afx_msg void OnClickandtransparentClicksomewhereandtransparentit();
	afx_msg ~CEveryThingAlphaDlg();
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
