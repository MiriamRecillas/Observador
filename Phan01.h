// Phan01.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// S�mbolos principales


// CPhan01App:
// Consulte la secci�n Phan01.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CPhan01App : public CWinApp
{
public:
	CPhan01App();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CPhan01App theApp;