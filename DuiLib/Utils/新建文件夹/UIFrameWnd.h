#pragma once
#include <list>
//namespace DuiLib{
using namespace DuiLib;

typedef MenuCmd MENUCOMMAND;

class CUIForm;
class UILIB_API CUIFrameWnd : public WindowImplBase
{
public:
	CUIFrameWnd(void);
	virtual ~CUIFrameWnd(void);
	virtual void OnFinalMessage( HWND hWnd );

	BOOL IsControl(TNotifyUI& msg, LPCTSTR name) { return _tcsicmp(msg.pSender->GetName(), name) == 0; }
	BOOL IsClass(TNotifyUI& msg, LPCTSTR classname) { return _tcsicmp(msg.pSender->GetClass(), classname) == 0; }
	BOOL IsInterface(TNotifyUI &msg, LPCTSTR pstrName) { return msg.pSender->GetInterface(pstrName) != NULL; }
	CControlUI *FindControl(LPCTSTR pstrName){ return m_pm.FindControl(pstrName); }
	BOOL IsMenuCommand(const MenuCmd *cmd, LPCTSTR name) { return _tcsicmp(cmd->szName, name) == 0; }	
	CPaintManagerUI *GetManager() { return &m_pm; }

	CMenuWnd *CreateMenu(STRINGorID xml);

	void AttachForm(CUIForm *pForm);
	void DetachForm(CUIForm *pForm);

	void ShowFullScreen(); //全屏显示
public:
	virtual LPCTSTR GetWindowClassName() const =0;
	virtual CDuiString GetSkinFile() =0;

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleMenuCommandMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual void Notify(TNotifyUI& msg);


	//消息处理
	virtual void OnNotifyClick(TNotifyUI& msg){}
	virtual void OnNotifyRClick(TNotifyUI& msg){}
	virtual void OnNotifyDbClick(TNotifyUI& msg){}
	virtual void OnNotifyMenu(TNotifyUI& msg) {}
	virtual void OnNotifyLink(TNotifyUI& msg) {}
	virtual void OnNotifyTimer(TNotifyUI& msg) {}
	virtual void OnNotifyReturn(TNotifyUI& msg) {}
	virtual void OnNotifyScroll(TNotifyUI& msg) {}
	virtual void OnNotifyDropDown(TNotifyUI& msg) {}
	virtual void OnNotifySetFocus(TNotifyUI& msg) {}
	virtual void OnNotifyKillFocus(TNotifyUI& msg) {}
	virtual void OnNotifyItemClick(TNotifyUI& msg) {}
	virtual void OnNotifyItemRClick(TNotifyUI& msg) {}
	virtual void OnNotifyTabSelect(TNotifyUI& msg) {}
	virtual void OnNotifyItemSelect(TNotifyUI& msg) {}
	virtual void OnNotifyItemExpand(TNotifyUI& msg) {}
	virtual void OnNotifyWindowPrepare(TNotifyUI& msg) {}
	virtual void OnNotifyButtonDown(TNotifyUI& msg) {}
	virtual void OnNotifyMouseEnter(TNotifyUI& msg) {}
	virtual void OnNotifyMouseLeave(TNotifyUI& msg) {}
	virtual void OnNotifyTextChanged(TNotifyUI& msg) {}
	virtual void OnNotifyHeaderClick(TNotifyUI& msg) {}
	virtual void OnNotifyItemDBClick(TNotifyUI& msg) {}
	virtual void OnNotifyShowActivex(TNotifyUI& msg) {}
	virtual void OnNotifyItemCollapse(TNotifyUI& msg) {}
	virtual void OnNotifyItemActivate(TNotifyUI& msg) {}
	virtual void OnNotifyValueChanged(TNotifyUI& msg) {}
	virtual void OnNotifySelectChanged(TNotifyUI& msg) {}

	virtual void OnNotityGridStartEdit(TNotifyUI &msg) {}
	virtual void OnNotityGridEndEdit(TNotifyUI &msg) {}
	virtual void OnNotityGridStartSelChange(TNotifyUI &msg) {}
	virtual void OnNotityGridEndSelChange(TNotifyUI &msg) {}
	virtual void OnNotityGridDropDownList(TNotifyUI &msg) {}
	virtual void OnNotityGridGetDispInfo(TNotifyUI &msg) {}

	//接收菜单消息，返回true，不继续往下发送消息
	virtual bool OnMenuCommand(const MenuCmd *cmd) { return false; }

	//自定义消息处理, 返回TRUE, 表示已经处理, 底层不会继续处理此消息, 
	virtual bool OnCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return FALSE; }

	virtual LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	std::list<CUIForm *>	m_listForm;

	DUI_DECLARE_MESSAGE_MAP()
};

inline CMenuWnd *DuiCreateMenu(LPCTSTR xmlFile, CPaintManagerUI *pManager)
{
	CDuiPoint pt;
	::GetCursorPos(&pt);
	CMenuWnd *pMenuWnd = CMenuWnd::CreateMenu(NULL, xmlFile, pt, pManager);
	if(pMenuWnd)
	{
		pMenuWnd->ResizeMenu();
	}
	return pMenuWnd;
}

//}