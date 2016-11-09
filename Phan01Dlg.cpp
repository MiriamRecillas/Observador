// Phan01Dlg.cpp: archivo de implementación
// Maestria en Ingeniería Electrica Campo Control - Robotica
// Laura Miriam Lòpez Recillas
// Otoño 2016
// Colaboración del código Alejandro Giles, Pablo Sánchez y Marisol Maldonado
//=====================================================================================
#include "stdafx.h"
#include "Phan01.h"
#include "Phan01Dlg.h"

#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>
//*************************************************************************************
// User includes
//*************************************************************************************
#include <math.h> // Math operations
//#include "mmsystem.h" // Multimedia timer
//#include "analysis.h" // Matrix operations, etc. agragar al Link analysis.lib y agregar
//el archivo existente en la carpeta Phan01 analysis.h .....XD
// Librería Multimedia de sistema Win32 ...............................................
#include "Mmsystem.h" // Multimedia timer
// Se manda a llamar la libreria winmm para poder usar Mmsystem.h .....................
#pragma comment(lib, "winmm.lib") 
//=====================================================================================
// User definitions
//=====================================================================================
#define pi 3.1415926535
#define ROWS 150000
HHD Master;
//***Banderas**************************************************************************
// User flags
	bool inicio = false, schedulerStarted = false; 
// Input arrays
	double tau[3] = {0.0,0.0,0.0};
// Position arrays
	double qm[3] = {0.0};
// Sample time
	double T = 0.001;
	double Tr = 0.7;
	double Trm = 0.7;
	double Trs = 0.5;
// Variable para la trayectoria polinomica
	double t0 = 0.0; 
	double t = 0.0;
	const double g0 = 9.78;
// Number of joints
	const int n = 3, p = 5; 

HDSchedulerHandle servoLoopHandle;

//***Banderas**************************************************************************
bool iCHome = true, homeCF = true, iCControl = true, controlCF = true; // User flags
bool iCBi = true, biCF = true, biG = true, iCObs = true, ObsCF = true;// User flags

MMRESULT MITIMER;
MMRESULT GTIMER;
MMRESULT BTIMER;
MMRESULT CBTIMER;

double grafi[ROWS][41] = {0.0};
const int grafSkip = 0; // Number of time intervals to discard for the output file
int indx = 0, indy = 0, aux = 0, auy = 0;

double qemAUX[ROWS][n] = {0.0}, qesAUX[ROWS][n] = {0.0}, qepmAUX[ROWS][n] = {0.0}, qepsAUX[ROWS][n] = {0.0};

const double angFE = 15.0*pi/180.0;   //Where FE is Final Effector
const double a2 = 0.145, a3 = sqrt(.135*.135 + .04*.04 - 2.0*0.135*.04*cos(pi-angFE));
const double gammaFE = asin(0.04*sin(pi-angFE)/a3);
//=====================================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//=====================================================================================
// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de
//=====================================================================================
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
//=====================================================================================
// Cuadro de diálogo de CPhan01Dlg
//=====================================================================================
CPhan01Dlg::CPhan01Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhan01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhan01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITA, m_statusTextBox);
	DDX_Control(pDX, IDC_En1, Enc_m1);
	DDX_Control(pDX, IDC_En2, Enc_m2);
	DDX_Control(pDX, IDC_En3, Enc_m3);
	DDX_Control(pDX, IDC_Tem, Tiempo);
}

BEGIN_MESSAGE_MAP(CPhan01Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Inicia, &CPhan01Dlg::OnBnClickedInicia)
	ON_BN_CLICKED(IDC_Calibra, &CPhan01Dlg::OnBnClickedCalibra)
	ON_BN_CLICKED(IDC_Detener, &CPhan01Dlg::OnBnClickedDetener)
	ON_BN_CLICKED(IDC_LeerEncoders, &CPhan01Dlg::OnBnClickedLeerencoders)
	ON_BN_CLICKED(IDC_HOME, &CPhan01Dlg::OnBnClickedHome)
	ON_BN_CLICKED(IDC_UNICON, &CPhan01Dlg::OnBnClickedUnicon)
	ON_BN_CLICKED(IDC_Control_Observer, &CPhan01Dlg::OnBnClickedControlObserver)

END_MESSAGE_MAP()
//=====================================================================================
// Controladores de mensaje de CPhan01Dlg
//=====================================================================================
BOOL CPhan01Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Agregar el elemento de menú "Acerca de..." al menú del sistema.
	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//*************************************************************************************
	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño
	//*************************************************************************************
	// TODO: agregar aquí inicialización adicional
	//*************************************************************************************
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CPhan01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
//*************************************************************************************
// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.
//*************************************************************************************
void CPhan01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
//*************************************************************************************
// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
//*************************************************************************************
HCURSOR CPhan01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//=====================================================================================
//PRIMER CALLBACK para la calibracion de los robots, se guarda el Status en HDenum
//=====================================================================================
HDCallbackCode HDCALLBACK CalibraStatusCallback(void * pUserData)
{
	HDenum *pStatus = (HDenum *) pUserData;

    hdBeginFrame(Master);
	hdUpdateCalibration(HD_CALIBRATION_INKWELL);
    *pStatus = hdCheckCalibration();
    hdEndFrame(Master);


    return HD_CALLBACK_DONE;
}
//=====================================================================================
//SEGUNDO CALLBACK para la inicializacion de los robot, pregunta y envia posicion y par
//=====================================================================================
typedef struct 
{
     hduVector3Dd position;
} 
DeviceStateStruct;
DeviceStateStruct state;
HDCallbackCode HDCALLBACK ServoLoopCallback(void *pUserData)
{
	
	DeviceStateStruct *pos = static_cast<DeviceStateStruct *>(pUserData);
	HDdouble torque[3];			//Declara una variable auxiliar
	hdBeginFrame(Master);

	hdGetDoublev(HD_CURRENT_JOINT_ANGLES,pos->position);
	
	torque[0] = -1000.0*tau[0]; // nNm
	torque[1] = 1000.0*tau[1];
	torque[2] = 1000.0*tau[2];

	qm[0] = -state.position[0];
	qm[1] = state.position[1];
	qm[2] = state.position[2]-0.5*pi-qm[1]-gammaFE;

	hdSetDoublev(HD_CURRENT_JOINT_TORQUE, torque);
	
//*************************************************************************************
	hdEndFrame(Master);

return HD_CALLBACK_CONTINUE;
}
//=====================================================================================
//Inicialización del los robots
//=====================================================================================
void CPhan01Dlg::OnBnClickedInicia()
{
	// TODO: Add your control notification handler code here
	HDErrorInfo error;
	HDstring MasterRobot = "Default Device"; //Default Device
	Master = hdInitDevice(MasterRobot);
	if (HD_DEVICE_ERROR(error = hdGetError())) 
	{
        MessageBox(_T("Master Device not Found!"));
		return;
	}
	servoLoopHandle = hdScheduleAsynchronous(ServoLoopCallback, &state, HD_MAX_SCHEDULER_PRIORITY);

	hdMakeCurrentDevice(Master);
	if (!hdIsEnabled(HD_FORCE_OUTPUT))
		hdEnable(HD_FORCE_OUTPUT);

	if (HD_DEVICE_ERROR(error = hdGetError()))
		MessageBox(_T("Force output enable error!"));

	
	if(!schedulerStarted)
		{
			hdStartScheduler();
			schedulerStarted = true;
			Sleep(1500);
		}
	

    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
		MessageBox(_T("Servo loop initialization error"));

        hdDisableDevice(Master);
        exit(-1);        
    }
	
	else
	{
		inicio = true;
		m_statusTextBox.SetWindowTextW(_T("*** Phantom Robot initialized ***"));
	}
}
//=====================================================================================
//Calibración del Robot, donde las variables creadas son supportedCalibraStules y calibreStyle
//La llamada al CALLBACK esta dado por CalibraEstatusCallback
//=====================================================================================

void CPhan01Dlg::OnBnClickedCalibra() // Clase que hereda la función de calibrar
{
	// TODO: Add your control notification handler code here

	// El robot debe estar en "home"

	if(inicio)
	{
		int supportedCalibraStyles;
	    int calibraStyle;
		HDErrorInfo error;

		hdGetIntegerv(HD_CALIBRATION_STYLE, &supportedCalibraStyles); // función que calibra

		if (supportedCalibraStyles & HD_CALIBRATION_INKWELL) // supervisa si la pluma del robot están en INKWELL
		    calibraStyle = HD_CALIBRATION_INKWELL; // Ejes de rotación adecuados 
		else
		{
			MessageBox(_T(" Sorry, no ink-well calibration available ")); // mensaje de error (el robot no esta en INKWELL)
			return;
		}
			
		if (HD_DEVICE_ERROR(error = hdGetError()))
			m_statusTextBox.SetWindowTextW(_T("*** Failed to start the scheduler ***"));           

			HDenum status;
			hdScheduleSynchronous(CalibraStatusCallback, &status, HD_DEFAULT_SCHEDULER_PRIORITY);

		if (status == HD_CALIBRATION_NEEDS_MANUAL_INPUT)
			MessageBox(_T(" Please put the device into the ink-well "));
		else
		{
			m_statusTextBox.SetWindowTextW(_T("*** Calibration done ***"));  // calibración exitosa
		}
	
		return;
	}
	else
	{
		MessageBox(_T(" Please initialize first the Phantom device "));
	}
	timeBeginPeriod(1);
}
//=====================================================================================
//Detener los Robots, se debe precionar este botón antes de salir del programa para no
//dañar los robot y deshabilitarlos
//=====================================================================================
void CPhan01Dlg::OnBnClickedDetener()
{
	timeKillEvent(MITIMER);
	timeKillEvent(GTIMER);
	timeKillEvent(BTIMER);
	timeKillEvent(CBTIMER);
	timeEndPeriod(1);	
	homeCF = iCHome = true;
	controlCF = iCControl = true;
	biCF = iCBi = true;
	ObsCF = iCObs = true;
	if (inicio&&hdIsEnabled(HD_FORCE_OUTPUT))
		hdDisable(HD_FORCE_OUTPUT);
		hdUnschedule(servoLoopHandle);
	if(schedulerStarted)
		hdStopScheduler();
	if(inicio)
	{
		hdDisableDevice(Master);
	}
	FILE *outFile;
	if(fopen_s(&outFile, "prueba4.m","w")!=0){
		MessageBox(_T("No se pudo crear el archivo para graficar"));
	}
	else{
		for(int i=0; i<indx; i++){
			fprintf(outFile, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f \n",
			grafi[i][0], grafi[i][1], grafi[i][2], grafi[i][3], grafi[i][4], grafi[i][5], grafi[i][6], grafi[i][7], grafi[i][8], 
			grafi[i][9], grafi[i][10], grafi[i][11], grafi[i][12], grafi[i][13], grafi[i][14], grafi[i][15], grafi[i][16],
			grafi[i][17], grafi[i][18], grafi[i][19], grafi[i][20], grafi[i][21], grafi[i][22], grafi[i][23], grafi[i][24],
			grafi[i][25],grafi[i][26],grafi[i][27],grafi[i][28],grafi[i][29],grafi[i][30],grafi[i][31],grafi[i][32], grafi[i][33], 
			grafi[i][34],grafi[i][35], grafi[i][36], grafi[i][37], grafi[i][38], grafi[i][39], grafi[i][40]);
		}
		fclose(outFile);
	}
	exit(0);	
}
//=====================================================================================
//Leer Encoders del Maestro y del Esclavo al mismo Click en un solo instante de tiempo
//=====================================================================================

void CPhan01Dlg::OnBnClickedLeerencoders()
{
	CString text[6];
	// posición angular
	text[0].Format(L"%.3f",qm[0]*180.0/pi); 
	text[1].Format(L"%.3f",qm[1]*180.0/pi);
	text[2].Format(L"%.3f",qm[2]*180.0/pi);
	
	Enc_m1.SetWindowTextW(text[0]);
	Enc_m2.SetWindowTextW(text[1]);
	Enc_m3.SetWindowTextW(text[2]);

	return;
}
//=====================================================================================
//Llevar a la posición de Home a los dos Robots M/S
//=====================================================================================
void CPhan01Dlg::OnBnClickedHome()
{
	t0 = timeGetTime(); // Obtiene el tiempo inicial, variable auxiliar
	if(!iCHome) // si iCHome = false
	{
		timeKillEvent(MITIMER); // mata el timer inicial
		homeCF = iCHome = true; // activa las banderas
	}
	if(!iCControl) // si iCControl = false
	{
		timeKillEvent(GTIMER);
	}
 	MITIMER = timeSetEvent(T*1000, 0, HHH, 0, TIME_PERIODIC);
}
//=====================================================================================
//* PRIMER Timer y Subrutina para llevar a Home a los Robots, usando las Banderas
//* HomeCF; iCHome;
//* timeBeginPeriod(1)    Al principio de la rutina de Home
//* timeKillEvent(x)      Cuando las banderas son falsas se usa en Home, Control y en Detener
//						para evitar que se este ejecutando esa acción en dichas rutinas
//* timeEndPeriod(1)      Al principio de la rutina Detener
//* Donde "x" son las rutinas de Timer -HHH- y -CGG-
//=====================================================================================
void CALLBACK CPhan01Dlg::HHH(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//DECLARACIÓN DE VARIABLES Y CONSTANTES

	//Coeficientes para el polinomio del maestro y del esclavo
	static double bm0[n]={0.0}, bm3[n]={0.0}, bm4[n]={0.0}, bm5[n]={0.0};
	
	//Posición deseada final del M/S
	const double qmdf[n]={0.0*pi/180.0, 90.0*pi/180.0, -90.0*pi/180.0};
	
	//Tiempo de duración del experimento
	const double tf=1.0;
	
	//Declaración de las Ganacias para el M/S
	const double Kpm[n] = {3.0,2.0,2.0};	//Ganancia Proporcinal
	const double Kim[n] = {1.0,1.0,1.0};		//Ganancia Integral
	const double Kdm[n] = {0.02,0.02,0.02};	//Ganancia Derivativa
	
	//Variables para las derivadas y las integrales
	static double emi[n]={0.0}, em_1[n]={0.0};
	double qmd[n]={0.0}, em[n]={0.0}, emp[n]={0.0};

	CPhan01Dlg *pMainWnd = (CPhan01Dlg *) AfxGetApp()->m_pMainWnd;
	
	//POLINOMIO DE QUINTO ORDEN PARA EL MAESTRO Y EL ESCLAVO, bm1=bm2=bs1=bs2=0.0
	if(iCHome)
	{
		for(int i=0; i<n; i++)
		{
			//Maestro
			bm0[i] = qm[i];
			bm3[i] = 10*(qmdf[i]-bm0[i])/(tf*tf*tf);
			bm4[i] = -15*(qmdf[i]-bm0[i])/(tf*tf*tf*tf);
			bm5[i] = 6*(qmdf[i]-bm0[i])/(tf*tf*tf*tf*tf);
			
		}
	pMainWnd->m_statusTextBox.SetWindowTextW(_T("*** Reaching home position ***"));
	}
	t = (timeGetTime() - t0)/1000.0;
	for(int i=0; i<n; i++)
	{
	//La suma de los elementos del polinomio-------------------------------------------
		if(t<=tf)
		{
			qmd[i] = bm0[i] + bm3[i]*t*t*t + bm4[i]*t*t*t*t + bm5[i]*t*t*t*t*t;
		}
		else
		{
			qmd[i] = qmdf[i];
		}
	}
	
	// ----------------------  Error de Posición ----------------------------
	for(int i=0; i<n; i++)
	{
		em[i] = qm[i] - qmd[i];  
	
		if(iCHome)
		{
			 // valor anterior
			em_1[i] = em[i];
		}

		// ---------------- Derivada del Error --------------------------------------
		
		emp[i] = (em[i] - em_1[i])/T;
		
		// --------------   Control PID ----------------------------------------------

		tau[i] = -Kpm[i]*em[i] - Kim[i]*emi[i] - Kdm[i]*emp[i];
		
	}

	//------------------------------ Integral del Error   ----------------------------
	

	for(int i=0; i<n; i++)
	{
		emi[i] += em[i]*T;
		em_1[i] = em[i];
	}

	if(t>tf&&homeCF)
	{
		pMainWnd->m_statusTextBox.SetWindowTextW(_T("*** Home position ***")); // imprime el mensaje
		homeCF = false; // Desactiva Bandera
	}

	if(iCHome) // si la bandera icHome = true
		iCHome = false;
	return;
}
//=====================================================================================
//Boton para iniciar el Control unilateral de Giles
//=====================================================================================
void CPhan01Dlg::OnBnClickedUnicon()
{
	if(!iCHome) // Si es falsa la bandera
	{
		timeKillEvent(MITIMER); // Apaga el timer
	}
	if(!iCControl)
	{
		timeKillEvent(GTIMER);
		controlCF = iCControl = true;
	}
	GTIMER = timeSetEvent( T*1000, 0, CGG, 0, TIME_PERIODIC);
}
//=====================================================================================
//CALLBACK que se llama cuando es activado el Control de Giles
//=====================================================================================
void CALLBACK CPhan01Dlg::CGG(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//DECLARACIÓN DE VARIABLES Y CONSTANTES
	static int GrafF =0;
	
	//Tiempo de duración del experimento
	const double tf=1.0;
	
	//Para los senos y cosenos
	double c1 = 0.0, c2 = 0.0, c3 = 0.0, c23 = 0.0, s1 = 0.0, s2 = 0.0, s3 = 0.0, s23 = 0.0;
	
	// th
	static double th[p] = {0.000012, 0.0, 0.000015, 0.0085*g0, 0.01*g0};
	const double  lamf  = 20.0;
	
	//Ganancias
	const double Kps[n] = {2,2,2}, Kis[n] = {0.2500,0.2500,0.2500}, Kds[n]={0.020,0.020,0.020};
	
	// Para las derivadas y las integrales
	double  qmp[n] = {0.0}, qpfp[n] = {0.0}, qppfp[n] = {0.0};
	static double qm_1[n] = {0.0}, qpf[n] = {0.0}, qppf[n] ={0.0}; 
	double Y[n][p] = {0.0}, Yth[n] = {0.0};
	
	//Comienza el control, con la asignación de senos y cosenos------------------------
	CPhan01Dlg *pMainWnd = (CPhan01Dlg *) AfxGetApp()->m_pMainWnd;
	c1 = cos(qm[0]);
	c2 = cos(qm[1]);
	c3 = cos(qm[2]);
	c23 = cos(qm[1]+qm[2]);

	s1 = sin(qm[0]);
	s2 = sin(qm[1]);
	s3 = sin(qm[2]);
	s23 = sin(qm[2]+qm[3]);
	
	// Se pregunta por la bandera y se envia un mensaje a la ventana
	if(iCControl)
	{
		t0 = timeGetTime();
		pMainWnd->m_statusTextBox.SetWindowTextW(_T("*** Control in progress ***"));
	}
	t = (timeGetTime() -t0)/1000.0;

	for(int i=0; i<n; i++)
	{
		qmp[i]    = (qm[i] - qm_1[i])/T;
		qpfp[i]   = lamf*(qmp[i]-qpf[i]);
		qppfp[i]  = lamf*(qpfp[i]-qppf[i]);
	}
	
	//Para el Regresor se tiene que
	
	Y[0][0] = -2*c2*s2*qpf[0]*qpf[1];
	Y[1][0] = c2*s2*qpf[0]*qpf[0];
	Y[2][0] = 0.0;
	Y[0][1] = -(c2*s23*(qpf[1]+qpf[2])+s2*c23*qpf[1])*qpf[0];
	Y[1][1] = 0.5*(s2*c23+c2*s23)*qpf[0]*qpf[0] - 2*s3*qpf[1]*qpf[2] - s3*qpf[2]*qpf[2];
	Y[2][1] = 0.5*c2*s23*qpf[0]*qpf[0] + s3*qpf[1]*qpf[1];
	Y[0][2] = c23*(qpf[1]+qpf[2])*qpf[0] + s23*c23*(qpf[1]+qpf[2])*qpf[0];
	Y[1][2] = -s23*c23*qpf[0]*qpf[0];
	Y[2][2] = -s23*c23*qpf[0]*qpf[0];
	Y[0][3] = 0.0;
	Y[1][3] = c2;
	Y[2][3] = 0.0;
	Y[0][4] = 0.0;
	Y[1][4] = c23;
	Y[2][4] = c23;
	
	for(int i=0; i<p; i++)
	{
		Yth[0] += Y[0][i]*th[i];
		Yth[1] += Y[1][i]*th[i];
		Yth[2] += Y[2][i]*th[i];
	}
	
	for(int i=0; i<n; i++)
	{
		tau[i] = Yth[i];
	}
	
	if(t>tf&&controlCF)
	{
		pMainWnd->m_statusTextBox.SetWindowTextW(_T("*** Control completed ***"));
		controlCF = false;
	}

	for(int i=0; i<n; i++)
	{
		qm_1[i]  = qm[i];
		qpf[i]  += qpfp[i]*T;
		qppf[i] += qppfp[i]*T;
	}
	if(iCControl)
		iCControl = false;
	return;
}
//=====================================================================================
//  Boton para iniciar el contol - observador
//=====================================================================================
void CPhan01Dlg::OnBnClickedControlObserver()
{	/* Esto es para saber que no se está realizando ningun actividad */
	if(!iCHome) 
	{
		timeKillEvent(MITIMER);
	}
	if(!iCControl)
	{
		timeKillEvent(GTIMER);
		controlCF = iCControl = true;
	}
	if(!iCObs)
	{
		timeKillEvent(CBTIMER);
		ObsCF = iCObs = true;
	}
	CBTIMER = timeSetEvent( T*1000, 0, CCB, 0, TIME_PERIODIC);
}
//=====================================================================================
//CALLBACK que se llama cuando es activado el Observador - Control
//=====================================================================================

void CALLBACK CPhan01Dlg::CCB(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//DECLARACIÓN DE VARIABLES Y CONSTANTES
	static int GrafF = 0; // gráficas

	// Tiempo final
	double tf = 1.0;

	//Para los senos y cosenos
	double c2 = 0.0, c23 = 0.0, g[n] = {0.0};
	
	static double bm0[n]={0.0}, bm3[n]={0.0}, bm4[n]={0.0}, bm5[n]={0.0};
	
	//Posición deseada final del M/S
	const double qmdf[n]={pi/4, pi/4, -110.0*pi/180.0};

		
	//************* Parámetros del Observador   *********************************
	const double Kd[n] = {150,145,140}, LambdaZ[n] = {3,2,1};
    
	//************  Parámetros del control - observador *************************
	const double Kbeta[n] = {0.000001, 0.000001, 0.000001}, Kgama[n] = {3, 5, 3};
	const double Kp[n] = {0.085,0.085,0.065}, LambdaQ[n] = {15,25,25};
	const double ks = 0.4;

	//************ Frecuencias ****************************

	const  double omegaQ1 = (2*pi)/10, omegaQ2 = (2*pi)/15, omegaQ3 = (2*pi)/20;
	double qd[n]={0.0}, ePos[n] = {0.0};

	//VARIABLES PARA EL OBSERVADOR Y EL CONTROL
	
	static double hatQ[n] = {0.0,pi/2,-pi/2}, sigma[n] = {0.0}, dotHatQ0[n] = {0.0};
	double dotQd[n] = {0.0}, ddotQd[n] = {0.0}, dotQ0[n] = {0.0}, dotQr[n] = {0.0};
	double z[n] = {0.0}, s[n] = {0.0}, s0[n] = {0.0}, Signo[n] = {0.0};
	double dotHatQ[n] = {0.0}, dotSigma[n] = {0.0}, ddotHatQ0[n] = {0.0};
	

	//Comienza el Control - Observador+++++++++++++++++++++++++++++++++++++++++++++++++
	CPhan01Dlg *pMainWnd = (CPhan01Dlg *) AfxGetApp()->m_pMainWnd;
	// Se pregunta por la bandera y se envia un mensaje a la ventana
	
	c2 = cos(qm[1]);
	c23= cos(qm[1]+qm[2]);
	g[0] = 0.0;
	g[1] = c2*0.0085*g0+c23*0.01*g0;
	g[2] = c23*0.01*g0;

	if(iCObs)
	{
		t0 = timeGetTime();
		/*
		for(int i=0; i<n; i++)
		{
			//Maestro
			bm0[i] = qm[i];
			bm3[i] = 10*(qmdf[i]-bm0[i])/(tf*tf*tf);
			bm4[i] = -15*(qmdf[i]-bm0[i])/(tf*tf*tf*tf);
			bm5[i] = 6*(qmdf[i]-bm0[i])/(tf*tf*tf*tf*tf);
			
		}*/
		pMainWnd->m_statusTextBox.SetWindowTextW(_T("*** Observador en proceso ***"));
	}

	t  = (timeGetTime()-t0)/1000.0;

	CString te;
	te.Format(L"%.3f",t);
	pMainWnd->Tiempo.SetWindowTextW(te);

	/*
	for(int i=0; i<n; i++)
	{
	//La suma de los elementos del polinomio-------------------------------------------
		if(t<=tf)
		{
			qd[i] = bm0[i] + bm3[i]*t*t*t + bm4[i]*t*t*t*t + bm5[i]*t*t*t*t*t;
			dotQd[i] = 3*bm3[i]*t*t + 4*bm4[i]*t*t*t + 5*bm5[i]*t*t*t*t;
			ddotQd[i] = 6*bm3[i]*t + 12*bm4[i]*t*t + 20*bm5[i]*t*t*t;
		}
		else
		{
			qd[i] = qmdf[i];
			dotQd[i] = 0;
			ddotQd[i] = 0;
    	}
	}*/

	
	
	//****************** Trayectoria Deseada ****************************

	qd[0] = 0.785*sin(omegaQ1*t);
	qd[1] = pi/4 + ((44*pi)/180)*sin(omegaQ2*t + pi/2); 
	qd[2] = -pi/2 + (pi/9)*sin(omegaQ3*t); 
	dotQd[0] = (omegaQ1)*0.785*cos(omegaQ1*t);
	dotQd[1] = (omegaQ2)*((44*pi)/180)*cos(omegaQ2*t + pi/2);
	dotQd[2] = (omegaQ3)*(pi/9)*cos(omegaQ3*t);
	ddotQd[0] = -(omegaQ1)*(omegaQ1)*0.785*sin(omegaQ1*t);
    ddotQd[1] = -(omegaQ2)*(omegaQ2)*((44*pi)/180)*sin(omegaQ2*t + pi/2);
	ddotQd[2] = -(omegaQ3)*(omegaQ3)*(pi/9)*sin(omegaQ3*t);


	//=====================   OBSERVADOR ===============================================
	
	for(int i=0; i<n; i++)
	{
		z[i] = qm[i] - hatQ[i];
		dotHatQ[i] = dotHatQ0[i] + LambdaZ[i]*z[i] + Kd[i]*z[i];  //Velocidad Estimada de Q
        hatQ[i] = hatQ[i] + dotHatQ[i]*T; // integral sucia de dotHatQ
		ddotHatQ0[i] = ddotQd[i] - LambdaQ[i]*(dotHatQ[i] - dotQd[i])  + Kd[i]*LambdaZ[i]*z[i] ; // Variable auxiliar - ks*sd[i]
		dotHatQ0[i] = dotHatQ0[i] + ddotHatQ0[i]*T; // integral sucia de ddotHatQ0    
	
	/*}
		
	//================CONTROLADOR======================================================
    

	for(int i=0; i<n; i++)
	{*/

		dotQ0[i] = dotHatQ[i] - LambdaZ[i]*z[i]; // Velocidad Estimada de Q0      
		dotQr[i] = dotQd[i] - LambdaQ[i]*(hatQ[i] - qd[i]) - Kgama[i]*sigma[i];  //Control de trayectoria sd[i]
        s[i] = dotHatQ[i] - dotQd[i] +  LambdaQ[i]*(hatQ[i] - qd[i]);
        		
		if(s[i] < 0)
			Signo[i] = -1;
		else if(s[i] > 0)
			Signo[i] = 1;
		else
			Signo[i] = 0;

    	dotSigma[i] = Kbeta[i]*s[i] + Signo[i];
		sigma[i] =  sigma[i] + dotSigma[i]*T; // integral sucia de dotSigma
        s0[i] = dotQ0[i] - dotQr[i];
		ePos[i] = qm[i] - qd[i];


	}
	//================PARES============================================================
	for(int i=0; i<n; i++)
	{
		tau[i] = - Kp[i]*s0[i] + g[i];
	}

	if(t>tf&&ObsCF)
	{
		pMainWnd->m_statusTextBox.SetWindowTextW(_T("*** Observador  ***"));
		ObsCF = false;
	}
	//+++++++++++ Receteamos los contadores ++++++++++++++++++++++++++++++++++++++++++++
	if(iCObs)
	{
		indx = 0; // guarda datos en una matriz 
		indy = 0;
	}

	//======================GRAFICAR====================================================
	if(GrafF==0)
	{
		grafi[indx][0] = t;
		grafi[indx][1] = qm[0];
		grafi[indx][2] = qm[1];
		grafi[indx][3] = qm[2];
		grafi[indx][4] = hatQ[0];
		grafi[indx][5] = hatQ[1];
		grafi[indx][6] = hatQ[2];
		grafi[indx][7] = z[0];
		grafi[indx][8] = z[1];
		grafi[indx][9] = z[2];
		grafi[indx][10] = tau[0];
		grafi[indx][11] = tau[1];
		grafi[indx][12] = tau[2];
		grafi[indx][13] = qd[0];
		grafi[indx][14] = qd[1];
		grafi[indx][15] = qd[2];
		grafi[indx][16] = dotHatQ[0];
		grafi[indx][17] = dotHatQ[1];
		grafi[indx][18] = dotHatQ[2];
		grafi[indx][19] = ePos[0];
		grafi[indx][20] = ePos[1];
		grafi[indx][21] = ePos[2];
		grafi[indx][22] = sigma[0];
		grafi[indx][23] = sigma[1];
		grafi[indx][24] = sigma[2];
		grafi[indx][25] = s[0];
		grafi[indx][26] = s[1];
		grafi[indx][27] = s[2];
		grafi[indx][28] = Signo[0];
		grafi[indx][29] = Signo[1];
		grafi[indx][30] = Signo[2];
		grafi[indx][31] = dotSigma[0];
		grafi[indx][32] = dotSigma[1];
		grafi[indx][33] = dotSigma[2];

		indx++;
		
		GrafF = grafSkip+1;
	}
	GrafF--;
	// %%%%%% Integral Sucia %%%% //

	/*
	for(int i=0; i<n; i++)
	{
		hatQ[i] += dotHatQ[i]*T; // integral sucia de dotHatQ
		dotHatQ0[i] += ddotHatQ0[i]*T; // integral sucia de ddotHatQ0   
		sigma[i] += dotSigma[i]*T; // integral sucia de dotSigma
		
	}*/
	if(iCObs)
		iCObs = false;
	return;
}
