#pragma once
#include "afxwin.h"
#include <gl/gl.h>
#include <gl/glu.h>

class COpenGLControl :
	public CDialogEx
{
public:
	/******************/
	/* PUBLIC MEMBERS */
	/******************/
	// Timer
	UINT_PTR m_unpTimer;

private:
	/*******************/
	/* PRIVATE MEMBERS */
	/*******************/
	// Window information
	CWnd    *hWnd;
	HDC     hdc;
	HGLRC   hrc;
	int     m_nPixelFormat;
	CRect   m_rect;
	CRect   m_oldWindow;
	CRect   m_originalRect;

public:
	COpenGLControl();
	COpenGLControl(UINT nIDTemplate, CWnd* pParent);
	virtual ~COpenGLControl();
	void oglCreate(CRect rect, CWnd *parent);
	void oglInitialize(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

