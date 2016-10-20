// Phan01.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// CPhan01App:
// Consulte la sección Phan01.cpp para obtener información sobre la implementación de esta clase
//

class CPhan01App : public CWinApp
{
public:
	CPhan01App();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CPhan01App theApp;