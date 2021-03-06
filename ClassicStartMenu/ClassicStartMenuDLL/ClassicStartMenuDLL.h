// Classic Shell (c) 2009-2013, Ivo Beltchev
// The sources for Classic Shell are distributed under the MIT open source license

#pragma once

#ifdef CLASSICSTARTMENUDLL_EXPORTS
#define STARTMENUAPI __declspec(dllexport)
#else
#define STARTMENUAPI __declspec(dllimport)
#endif

// Find the taskbar window for the given process
STARTMENUAPI bool FindTaskBar( DWORD process );

// WH_GETMESSAGE hook for the explorer's GUI thread. The start menu exe uses this hook to inject code into the explorer process
STARTMENUAPI LRESULT CALLBACK HookInject( int code, WPARAM wParam, LPARAM lParam );

// Toggle the start menu. bKeyboard - set to true to show the keyboard cues
STARTMENUAPI HWND ToggleStartMenu( int taskbarId, bool bKeyboard );

// Enable or disable the tooltip for the start button
void EnableStartTooltip( bool bEnable );

// Restore the original drop target
void UnhookDropTarget( void );

struct TaskbarInfo
{
	TaskbarInfo( void ) { taskBar=startButton=oldButton=rebar=NULL; rebarOffset.cx=rebarOffset.cy=0; bTimer=false; }
	int taskbarId;
	HWND taskBar;
	HWND startButton;
	HWND oldButton;
	HWND rebar;
	SIZE rebarOffset;
	bool bTimer;
};

TaskbarInfo *GetTaskbarInfo( int taskbarId );
UINT GetTaskbarPosition( HWND taskBar, MONITORINFO *pInfo, HMONITOR *pMonitor, RECT *pRc );

extern HWND STARTMENUAPI g_TaskBar, g_OwnerWindow;
extern HWND g_TopMenu, g_AllPrograms, g_ProgramsButton, g_UserPic; // from the Windows menu

enum TMenuMsgParam // wParam for the ClassicStartMenu.StartMenuMsg message
{
	MSG_TOGGLE, // toggles the classic start menu
	MSG_OPEN, // opens the classic start menu
	MSG_SETTINGS, // show Settings
	MSG_SHIFTWIN, // Shift+Win was pressed
	MSG_DRAG, // an item is dragged on the start button
	MSG_SHIFTDRAG, // an item is dragged on the start button (Shift is pressed)
	MSG_FINDMENU, // find Windows menu
	MSG_EXIT, // unhook everything and exit
	MSG_HOTKEYS, // updates the hotkeys
	MSG_NEWTASKBAR, // new taskbar is created, lParam is the HWND
};

STARTMENUAPI extern enum _MINIDUMP_TYPE MiniDumpType;
STARTMENUAPI LONG _stdcall TopLevelFilter( _EXCEPTION_POINTERS *pExceptionInfo );

enum THotkeys
{
	HOTKEYS_NORMAL,
	HOTKEYS_SETTINGS,
	HOTKEYS_CLEAR,
};

// Set the hotkeys and controls for the start menu
void EnableHotkeys( THotkeys enable );

void RecreateStartButton( int taskbarId );
bool PointAroundStartButton( int taskbarId );
void ResetHotCorners( void );
void RedrawTaskbars( void );
