// Phan01Dlg.h: archivo de encabezado
//

#pragma once
#include "afxwin.h"

// CLASE Cuadro de diálogo de CPhan01Dlg

class CPhan01Dlg : public CDialog
{
// Construcción
public:
	CPhan01Dlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
	enum { IDD = IDD_PHAN01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInicia();
	afx_msg void OnBnClickedCalibra();
	CEdit m_statusTextBox;
	afx_msg void OnBnClickedDetener();
	CEdit Enc_m1;
	CEdit Enc_m2;
	CEdit Enc_m3;
	CEdit Enc_s1;
	CEdit Enc_s2;
	CEdit Enc_s3;
	afx_msg void OnBnClickedLeerencoders();
	static void CALLBACK HHH(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK CGG(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	afx_msg void OnBnClickedHome();
	afx_msg void OnBnClickedUnicon();
	CEdit Tiempo;
	afx_msg void OnBnClickedControlObserver();
	static void CALLBACK CCB(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
};
