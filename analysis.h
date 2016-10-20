/*============================================================================*/
/*                        L a b W i n d o w s / C V I                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 1987-1998.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       analysis.h                                                    */
/* Purpose:     Include file for LabWindows CVI Advanced Analysis Library     */
/*                                                                            */
/*============================================================================*/


#ifndef _ANALYSIS_H
#define _ANALYSIS_H

#ifdef _CVI_
#pragma EnableLibraryRuntimeChecking
#endif

#include "cvidef.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Error Codes */
typedef enum {
    NoAnlysErr              =      0,
    OutOfMemAnlysErr        = -20001,
    EqSamplesAnlysErr       = -20002,
    SamplesGTZeroAnlysErr   = -20003,
    SamplesGEZeroAnlysErr   = -20004,
    SamplesGEOneAnlysErr    = -20005,
    SamplesGETwoAnlysErr    = -20006,
    SamplesGEThreeAnlysErr  = -20007,
    ArraySizeAnlysErr       = -20008,
    PowerOfTwoAnlysErr      = -20009,
    MaxXformSizeAnlysErr    = -20010,
    DutyCycleAnlysErr       = -20011,
    CyclesAnlysErr          = -20012,
    WidthLTSamplesAnlysErr  = -20013,
    DelayWidthAnlysErr      = -20014,
    DtGEZeroAnlysErr        = -20015,
    DtGTZeroAnlysErr        = -20016,
    IndexLTSamplesAnlysErr  = -20017,
    IndexLengthAnlysErr     = -20018,
    UpperGELowerAnlysErr    = -20019,
    NyquistAnlysErr         = -20020,
    OrderGTZeroAnlysErr     = -20021,
    DecFactAnlysErr         = -20022,
    BandSpecAnlysErr        = -20023,
    RippleGTZeroAnlysErr    = -20024,
    AttenGTZeroAnlysErr     = -20025,
    WidthGTZeroAnlysErr     = -20026,
    FinalGTZeroAnlysErr     = -20027,
    AttenGTRippleAnlysErr   = -20028,
    StepSizeAnlysErr        = -20029,
    LeakAnlysErr            = -20030,
    EqRplDesignAnlysErr     = -20031,
    RankAnlysErr            = -20032,
    EvenSizeAnlysErr        = -20033,
    OddSizeAnlysErr         = -20034,
    StdDevAnlysErr          = -20035,
    MixedSignAnlysErr       = -20036,
    SizeGTOrderAnlysErr     = -20037,
    IntervalsAnlysErr       = -20038,
    MatrixMulAnlysErr       = -20039,
    SquareMatrixAnlysErr    = -20040,
    SingularMatrixAnlysErr  = -20041,
    LevelsAnlysErr          = -20042,
    FactorAnlysErr          = -20043,
    ObservationsAnlysErr    = -20044,
    DataAnlysErr            = -20045,
    OverflowAnlysErr        = -20046,
    BalanceAnlysErr         = -20047,
    ModelAnlysErr           = -20048,
    DistinctAnlysErr        = -20049,
    PoleAnlysErr            = -20050,
    ColumnAnlysErr          = -20051,
    FreedomAnlysErr         = -20052,
    ProbabilityAnlysErr     = -20053,
    InvProbAnlysErr         = -20054,
    CategoryAnlysErr        = -20055,
    TableAnlysErr           = -20056,
    BetaFuncAnlysErr        = -20057,
    DimensionAnlysErr       = -20058,
    NegNumAnlysErr          = -20059,
    DivByZeroAnlysErr       = -20060,
    InvSelectionAnlysErr    = -20061,
    MaxIterAnlysErr         = -20062,
    PolyAnlysErr            = -20063,
    InitStateAnlysErr       = -20064,
    ZeroVectorAnlysErr      = -20065,
    IIRFilterInfoAnlysErr   = -20066,
    FFSRInvalidAnlysErr     = -20067,
    BaseGETopAnlysErr       = -20101,
    ShiftRangeAnlysErr      = -20102,
    OrderGEZeroAnlysErr     = -20103,
    InternalAnlysErr        = -20999,
    RankDeficient           =  20001,   /*The matrix is rank deficient*/ 
    _unusedAnlysErr     = 0x7fffffff
} AnalysisLibErrType;


/* Filter types */
enum {
    LOWPASS = 0,
    HIGHPASS = 1,
    BANDPASS = 2,
    BANDSTOP = 3
};

/*- Typedefs -----------------------------------------------------------------*/

/* Window constants used by measurement functions */
typedef struct {
    double enbw;
    double coherentgain;
} WindowConst;

/* Model function used by NonLinearFit() */
typedef double CVICALLBACK ModelFun(double x, double *coef, int ncoef);

/* Filter information used by IIR filter functions */
typedef struct {
    int type;       /* filter type (LOWPASS, etc.) */
    int order;      /* filter order */
    int reset;
    int na;
    double *a;      /* a coefficients */
    int nb;
    double *b;      /* b coefficients */
    int ns;
    double *s;      /* internal state */

} *IIRFilterPtr;


/* Define datatype ComplexNum */
typedef struct {
    double real;
    double imaginary;
} ComplexNum;

/*- Signal Generation --------------------------------------------------------*/

AnalysisLibErrType CVIFUNC Impulse      (int n, double amp, int index, double x[]);
AnalysisLibErrType CVIFUNC Pulse        (int n, double amp, int delay,
                                         int width, double pulsePattern[]);
AnalysisLibErrType CVIFUNC Ramp         (int n, double first, double last,
                                         double rampvals[]);
AnalysisLibErrType CVIFUNC Triangle     (int n, double amp, double tri[]);
AnalysisLibErrType CVIFUNC SinePattern  (int n, double amp, double phase,
                                         double cycles, double sine[]);
AnalysisLibErrType CVIFUNC Uniform      (int n, int seed, double x[]);
AnalysisLibErrType CVIFUNC WhiteNoise   (int n, double amp, int seed,
                                         double noise[]);
AnalysisLibErrType CVIFUNC GaussNoise   (int n, double sDev, int seed,
                                         double noise[]);
AnalysisLibErrType CVIFUNC ArbitraryWave(int n, double amp, double f,
                                         double *phase, const double wavetable[],
                                         int wavesize, int wavetype, double x[]);
AnalysisLibErrType CVIFUNC Chirp        (int n, double amp, double f1,
                                         double f2, double x[]);
AnalysisLibErrType CVIFUNC SawtoothWave (int n, double amp, double f,
                                         double *phase, double x[]);
AnalysisLibErrType CVIFUNC Sinc         (int n, double amp, double delay,
                                         double dt, double x[]);
AnalysisLibErrType CVIFUNC SineWave     (int n, double amp, double f,
                                         double *phase, double x[]);
AnalysisLibErrType CVIFUNC SquareWave   (int n, double amp, double f,
                                         double *phase, double duty, double x[]);
AnalysisLibErrType CVIFUNC TriangleWave (int n, double amp, double f,
                                         double *phase, double x[]);



/*- 1-D Array Operations -----------------------------------------------------*/


AnalysisLibErrType CVIFUNC Clear1D  (double x[], int n);
AnalysisLibErrType CVIFUNC Set1D    (double x[], int n, double a);
AnalysisLibErrType CVIFUNC Copy1D   (const double x[], int n, double y[]);
AnalysisLibErrType CVIFUNC Add1D    (const double x[], const double y[], int n,
                                     double z[]);
AnalysisLibErrType CVIFUNC Sub1D    (const double x[], const double y[], int n,
                                     double z[]);
AnalysisLibErrType CVIFUNC Mul1D    (const double x[], const double y[], int n,
                                     double z[]);
AnalysisLibErrType CVIFUNC Div1D    (const double x[], const double y[], int n,
                                     double z[]);
AnalysisLibErrType CVIFUNC Abs1D    (const double x[], int n, double y[]);
AnalysisLibErrType CVIFUNC Neg1D    (const double x[], int n, double y[]);
AnalysisLibErrType CVIFUNC LinEv1D  (const double x[], int n, double a,
                                     double b, double y[]);
AnalysisLibErrType CVIFUNC PolyEv1D (const double x[], int n,
                                     const double coef[], int k, double y[]);
AnalysisLibErrType CVIFUNC Scale1D  (const double x[], int n, double y[],
                                     double *offset, double *scale);
AnalysisLibErrType CVIFUNC QScale1D (const double x[], int n, double y[],
                                     double *scale);
AnalysisLibErrType CVIFUNC MaxMin1D (const double x[], int n, double *max,
                                     int *imax, double *min, int *imin);
AnalysisLibErrType CVIFUNC Sum1D    (const double x[], int n, double * sum);
AnalysisLibErrType CVIFUNC Prod1D   (const double x[], int n, double * prod);
AnalysisLibErrType CVIFUNC Subset1D (const double x[], int n, int index,
                                     int length, double y[]);
AnalysisLibErrType CVIFUNC Normal1D (const double x[], int n, double y[],
                                     double *ave, double *sDev);

AnalysisLibErrType CVIFUNC Reverse  (const double x[], int n, double y[]);
AnalysisLibErrType CVIFUNC Shift    (const double x[], int n, int shifts,
                                     double y[]);
AnalysisLibErrType CVIFUNC Clip     (const double x[], int n, double upper,
                                     double lower, double y[]);
AnalysisLibErrType CVIFUNC Sort     (const double x[], int n, int direction,
                                     double y[]);


/*- 2-D Array Operations -----------------------------------------------------*/

AnalysisLibErrType CVIFUNC Add2D    (const void *x, const void *y, int n, int m,
                                     void *z);
AnalysisLibErrType CVIFUNC Sub2D    (const void *x, const void *y, int n, int m,
                                     void *z);
AnalysisLibErrType CVIFUNC Mul2D    (const void *x, const void *y, int n, int m,
                                     void *z);
AnalysisLibErrType CVIFUNC Div2D    (const void *x, const void *y, int n, int m,
                                     void *z);
AnalysisLibErrType CVIFUNC LinEv2D  (const void *x, int n, int m, double a,
                                     double b, void *y);
AnalysisLibErrType CVIFUNC PolyEv2D (const void *x, int n, int m, double coef[],
                                     int k, void *y);
AnalysisLibErrType CVIFUNC Scale2D  (const void *x, int n, int m, void *y,
                                     double *offset, double *scale);
AnalysisLibErrType CVIFUNC QScale2D (const void *x, int n, int m, void *y,
                                     double *scale);
AnalysisLibErrType CVIFUNC MaxMin2D (const void *x, int n, int m, double *max,
                                     int *imax, int *jmax, double *min,
                                     int *imin, int *jmin);
AnalysisLibErrType CVIFUNC Sum2D    (const void *x, int n, int m, double *sum);
AnalysisLibErrType CVIFUNC Normal2D (const void *x, int n, int m, void *y,
                                     double *ave, double *sDev);


/*- Complex Number Operations ------------------------------------------------*/

AnalysisLibErrType CVIFUNC CxAdd   (double xr, double xi, double yr, double yi,
                                    double *zr, double *zi);
AnalysisLibErrType CVIFUNC CxSub   (double xr, double xi, double yr, double yi,
                                    double *zr, double *zi);
AnalysisLibErrType CVIFUNC CxMul   (double xr, double xi, double yr, double yi,
                                    double *zr, double *zi);
AnalysisLibErrType CVIFUNC CxDiv   (double xr, double xi, double yr, double yi,
                                    double *zr, double *zi);
AnalysisLibErrType CVIFUNC CxRecip (double xr, double xi, double *yr, double *yi);
AnalysisLibErrType CVIFUNC CxSqrt  (double xr, double xi, double *yr, double *yi);
AnalysisLibErrType CVIFUNC CxLog   (double xr, double xi, double *yr, double *yi);
AnalysisLibErrType CVIFUNC CxLn    (double xr, double xi, double *yr, double *yi);
AnalysisLibErrType CVIFUNC CxPow   (double xr, double xi, double a, double *yr,
                                    double *yi);
AnalysisLibErrType CVIFUNC CxExp   (double xr, double xi, double *yr, double *yi);
AnalysisLibErrType CVIFUNC ToPolar (double x, double y, double *mag,
                                    double *phase);
AnalysisLibErrType CVIFUNC ToRect  (double mag, double phase, double *x,
                                    double *y);


/*- 1-D Complex Array Operations ---------------------------------------------*/

AnalysisLibErrType CVIFUNC CxAdd1D    (const double xr[], const double xi[],
                                       const double yr[], const double yi[], 
                                       int n, double zr[], double zi[]);

AnalysisLibErrType CVIFUNC CxSub1D    (const double xr[], const double xi[],
                                       const double yr[], const double yi[],
                                       int n, double zr[], double zi[]);

AnalysisLibErrType CVIFUNC CxMul1D    (const double xr[], const double xi[],
                                       const double yr[], const double yi[],
                                       int n, double zr[], double zi[]);

AnalysisLibErrType CVIFUNC CxDiv1D    (const double xr[], const double xi[],
                                       const double yr[], const double yi[],
                                       int n, double zr[], double zi[]);

AnalysisLibErrType CVIFUNC CxLinEv1D  (const double xr[], const double xi[],
                                       int n, double ar, double ai, double br,
                                       double bi, double yr[], double yi[]);

AnalysisLibErrType CVIFUNC ToPolar1D  (const double x[], const double y[],
                                       int n, double mag[], double phase[]);

AnalysisLibErrType CVIFUNC ToRect1D   (const double mag[], const double phase[],
                                       int n, double x[], double y[]);


/*- Frequency Domain Analysis ------------------------------------------------*/

AnalysisLibErrType CVIFUNC FFT      (double x[], double y[], int n);
AnalysisLibErrType CVIFUNC InvFFT   (double x[], double y[], int n);
AnalysisLibErrType CVIFUNC ReFFT    (double x[], double y[], int n);
AnalysisLibErrType CVIFUNC ReInvFFT (double x[], double y[], int n);
AnalysisLibErrType CVIFUNC Spectrum (double x[], int n);
AnalysisLibErrType CVIFUNC FHT      (double x[], int n);
AnalysisLibErrType CVIFUNC InvFHT   (double x[], int n);
AnalysisLibErrType CVIFUNC FastHilbertTransform(double x[], int n);       
AnalysisLibErrType CVIFUNC InvFastHilbertTransform(double x[], int n);

AnalysisLibErrType CVIFUNC CrossSpectrum(const double x[], const double y[],
                                         int n, double zr[], double zi[]);


/*- Time Domain Analysis -----------------------------------------------------*/

AnalysisLibErrType CVIFUNC Convolve   (const double x[], int n, const double y[],
                                       int m, double cxy[]);
AnalysisLibErrType CVIFUNC Correlate  (const double x[], int n, const double y[],
                                       int m, double rxy[]);
AnalysisLibErrType CVIFUNC Integrate  (const double x[], int n, double dt,
                                       double xInit, double xFinal, double y[]);
AnalysisLibErrType CVIFUNC Difference (const double x[], int n, double dt,
                                       double xInit, double xFinal, double y[]);
/*AnalysisLibErrType CVIFUNC PulseParam (const double pulsePattern[], int n,
                                       double *amp, double *amp90,
                                       double *amp50, double *amp10,
                                       double *top, double *base,
                                       double *topOvershoot,
                                       double *baseOvershoot, int *delay,
                                       int *width, int *riseTime, int *fallTime,
                                       double *slewRate);*/
AnalysisLibErrType CVIFUNC Decimate   (const double x[], int n, int D, int avg,
                                       double *y);
AnalysisLibErrType CVIFUNC Deconvolve (const double y[], int ny,
                                       const double x[], int nx, double h[]);
AnalysisLibErrType CVIFUNC UnWrap1D   (double phase[], int n);


/*- IIR Digital Filters ------------------------------------------------------*/

AnalysisLibErrType CVIFUNC Bw_LPF     (const double x[], int n, double fs,
                                       double fc, int order, double y[]);

AnalysisLibErrType CVIFUNC Bw_HPF     (const double x[], int n, double fs,
                                       double fc, int order, double y[]);

AnalysisLibErrType CVIFUNC Bw_BPF     (const double x[], int n, double fs,
                                       double fl, double fh, int order,
                                       double y[]);

AnalysisLibErrType CVIFUNC Bw_BSF     (const double x[], int n, double fs,
                                       double fl, double fh, int order,
                                       double y[]);

AnalysisLibErrType CVIFUNC Ch_LPF     (const double x[], int n, double fs,
                                       double fc, double ripple,
                                       int order, double y[]);

AnalysisLibErrType CVIFUNC Ch_HPF     (const double x[], int n, double fs,
                                       double fc, double ripple,
                                       int order, double y[]);

AnalysisLibErrType CVIFUNC Ch_BPF     (const double x[], int n, double fs,
                                       double fl, double fh,
                                       double ripple, int order, double y[]);

AnalysisLibErrType CVIFUNC Ch_BSF     (const double x[], int n, double fs,
                                       double fl, double fh,
                                       double ripple, int order, double y[]);

AnalysisLibErrType CVIFUNC InvCh_LPF  (const double x[], int n, double fs,
                                       double fc, double atten, int order,
                                       double y[]);

AnalysisLibErrType CVIFUNC InvCh_HPF  (const double x[], int n, double fs,
                                       double fc, double atten, int order,
                                       double y[]);

AnalysisLibErrType CVIFUNC InvCh_BPF  (const double x[], int n, double fs,
                                       double fl, double fh, double atten,
                                       int order, double y[]);

AnalysisLibErrType CVIFUNC InvCh_BSF  (const double x[], int n, double fs,
                                       double fl, double fh, double atten,
                                       int order, double y[]);

AnalysisLibErrType CVIFUNC Elp_LPF    (const double x[], int n, double fs,
                                       double fc, double ripple, double atten,
                                       int order, double y[]);

AnalysisLibErrType CVIFUNC Elp_HPF    (const double x[], int n, double fs,
                                       double fc, double ripple, double atten,
                                       int order, double y[]);

AnalysisLibErrType CVIFUNC Elp_BPF    (const double x[], int n, double fs,
                                       double fl, double fh, double ripple,
                                       double atten, int order, double y[]);

AnalysisLibErrType CVIFUNC Elp_BSF    (const double x[], int n, double fs,
                                       double fl, double fh, double ripple,
                                       double atten, int order, double y[]);

AnalysisLibErrType CVIFUNC Bessel_CascadeCoef(double fs, double fl, double fh,
                                              IIRFilterPtr filterInfo);

AnalysisLibErrType CVIFUNC Bw_CascadeCoef    (double fs, double fl, double fh,
                                              IIRFilterPtr filterInfo);

AnalysisLibErrType CVIFUNC Ch_CascadeCoef    (double fs, double fl, double fh,
                                              double r, IIRFilterPtr filterInfo);

AnalysisLibErrType CVIFUNC Elp_CascadeCoef   (double fs, double fl, double fh,
                                              double ripple, double atten, 
                                              IIRFilterPtr filterInfo);

AnalysisLibErrType CVIFUNC InvCh_CascadeCoef (double fs, double fl, double fh,
                                              double atten, IIRFilterPtr filterInfo);

AnalysisLibErrType CVIFUNC IIRCascadeFiltering(const double x[], int n,
                                               IIRFilterPtr filterInfo, double y[]);

AnalysisLibErrType CVIFUNC CascadeToDirectCoef(IIRFilterPtr filterInfo, double a[],
                                               int na, double b[], int nb);
        
IIRFilterPtr       CVIFUNC AllocIIRFilterPtr(int type, int order);
        
void               CVIFUNC ResetIIRFilter   (IIRFilterPtr filterInfo);

void               CVIFUNC FreeIIRFilterPtr (IIRFilterPtr filterInfo);


  /*- Old-style IIR Filter Functions -*/
AnalysisLibErrType CVIFUNC Bessel_Coef(int type, int order, double fs, 
                                       double fl, double fh, double a[], 
                                       int na, double b[], int nb);

AnalysisLibErrType CVIFUNC Bw_Coef    (int type, int order, double fs,
                                       double fl, double fh, double a[],
                                       int na, double b[], int nb);

AnalysisLibErrType CVIFUNC Ch_Coef    (int type, int order, double fs,
                                       double fl, double fh, double r,
                                       double a[], int na, double b[], int nb);

AnalysisLibErrType CVIFUNC Elp_Coef   (int type, int order, double fs,
                                       double fl, double fh, double r1,
                                       double r2, double a[], int na,
                                       double b[], int nb);

AnalysisLibErrType CVIFUNC InvCh_Coef (int type, int order, double fs,
                                       double fl, double fh, double fr,
                                       double a[], int na, double b[], int nb);

AnalysisLibErrType CVIFUNC IIRFiltering(const double x[], int n,
                                        const double a[], double y1[], int na,
                                        const double b[], double x1[], int nb,
                                        double y[]);


/*- FIR Digital Filters ------------------------------------------------------*/

AnalysisLibErrType CVIFUNC Wind_LPF    (double fs, double fc, int n,
                                        double coef[], int windType);
AnalysisLibErrType CVIFUNC Wind_HPF    (double fs, double fc, int n,
                                        double coef[], int windType);
AnalysisLibErrType CVIFUNC Wind_BPF    (double fs, double fl, double fh, int n,
                                        double coef[], int windType);
AnalysisLibErrType CVIFUNC Wind_BSF    (double fs, double fl, double fh, int n,
                                        double coef[], int windType);
AnalysisLibErrType CVIFUNC Ksr_LPF     (double fs, double fc, int n,
                                        double coef[], double beta);
AnalysisLibErrType CVIFUNC Ksr_HPF     (double fs, double fc, int n,
                                        double coef[], double beta);
AnalysisLibErrType CVIFUNC Ksr_BPF     (double fs, double fl, double fh, int n,
                                        double coef[], double beta);
AnalysisLibErrType CVIFUNC Ksr_BSF     (double fs, double fl, double fh, int n,
                                        double coef[], double beta);
AnalysisLibErrType CVIFUNC Equi_Ripple (int bands, const double A[],
                                        const double wts[], double fs,
                                        const double cutoffs[], int type, int n,
                                        double coef[], double *delta);
AnalysisLibErrType CVIFUNC EquiRpl_LPF (double fs, double f1, double f2, int n,
                                        double coef[], double *delta);
AnalysisLibErrType CVIFUNC EquiRpl_HPF (double fs, double f1, double f2, int n,
                                        double coef[], double *delta);
AnalysisLibErrType CVIFUNC EquiRpl_BPF (double fs, double f1, double f2,
                                        double f3, double f4, int n,
                                        double coef[], double *delta);
AnalysisLibErrType CVIFUNC EquiRpl_BSF (double fs, double f1, double f2,
                                        double f3, double f4, int n,
                                        double coef[], double *delta);
AnalysisLibErrType CVIFUNC FIR_Coef    (int type, double fs, double fl,
                                        double fh, int taps, double *coef);


/*- Measurement --------------------------------------------------------------*/

AnalysisLibErrType CVIFUNC ACDCEstimator     (const double x[], int n,
                                              double *acestimate,
                                              double *dcestimate);
AnalysisLibErrType CVIFUNC AmpPhaseSpectrum  (const double x[], int n,
                                              int unwrap, double dt,
                                              double ampspectrum[],
                                              double phasespectrum[],
                                              double *df);
AnalysisLibErrType CVIFUNC AutoPowerSpectrum (const double x[], int n,
                                              double dt, double autospectrum[],
                                              double *df);
AnalysisLibErrType CVIFUNC CrossPowerSpectrum(const double x[], const double y[],
                                              int n, double dt, double magsxy[],
                                              double phasesxy[], double *df);
AnalysisLibErrType CVIFUNC ImpulseResponse   (const double stimulus[],
                                              const double response[], int n,
                                              double impulse[]);
AnalysisLibErrType CVIFUNC NetworkFunctions  (void *stimulus, void *response,
                                              int n, int numframes, double dt,
                                              double magsxy[],
                                              double phasesxy[],
                                              double magtransfer[],
                                              double phasetransfer[],
                                              double coherence[],
                                              double impulse[], double *df);
AnalysisLibErrType CVIFUNC PowerFrequencyEstimate (const double autospectrum[],
                                                   int n, double searchfreq,
                                                   WindowConst windowconstants,
                                                   double df, int span,
                                                   double *freqpeak,
                                                   double *powerpeak);
AnalysisLibErrType CVIFUNC ScaledWindow      (double x[], int n, int window,
                                              WindowConst *windowconstants);
AnalysisLibErrType CVIFUNC SpectrumUnitConversion (const double spectrum[],
                                                   int ns, int type, int loglin,
                                                   int unitselector, double df,
                                                   WindowConst windowconstants,
                                                   double convertedspectrum[],
                                                   char *unitstring);
AnalysisLibErrType CVIFUNC TransferFunction  (const double stimulus[],
                                              const double response[], int n,
                                              double dt, double magtransfer[],
                                              double phasetransfer[],
                                              double *df);
AnalysisLibErrType CVIFUNC HarmonicAnalyzer (const double *x, int n, int frame_size, int number_of_harmonics,
                                             int window_type, double sampling_rate, double fundamental_frequency, 
                                             double harmonic_amplitudes[], double harmonic_frequencies[], 
                                             double *thd, double *thdnoise);     
/*- Windows ------------------------------------------------------------------*/

AnalysisLibErrType CVIFUNC TriWin        (double x[], int n);
AnalysisLibErrType CVIFUNC HanWin        (double x[], int n);
AnalysisLibErrType CVIFUNC HamWin        (double x[], int n);
AnalysisLibErrType CVIFUNC BkmanWin      (double x[], int n);
AnalysisLibErrType CVIFUNC KsrWin        (double x[], int n, double beta);
AnalysisLibErrType CVIFUNC BlkHarrisWin  (double x[], int n);
AnalysisLibErrType CVIFUNC CosTaperedWin (double x[], int n);
AnalysisLibErrType CVIFUNC ExBkmanWin    (double x[], int n);
AnalysisLibErrType CVIFUNC ExpWin        (double x[], int n, double final);
AnalysisLibErrType CVIFUNC FlatTopWin    (double x[], int n);
AnalysisLibErrType CVIFUNC ForceWin      (double x[], int n, double duty);
AnalysisLibErrType CVIFUNC GenCosWin     (double x[], int n, const double a[],
                                          int m);


/*- General Statistics -------------------------------------------------------*/

AnalysisLibErrType CVIFUNC Mean      (const double x[], int n, double *mean);
AnalysisLibErrType CVIFUNC StdDev    (const double x[], int n, double *mean,
                                      double *sDev);
AnalysisLibErrType CVIFUNC Variance  (const double x[], int n, double *mean,
                                      double *var);
AnalysisLibErrType CVIFUNC RMS       (const double x[], int n, double *rms);
AnalysisLibErrType CVIFUNC Moment    (const double x[], int n, int order,
                                      double *moment);
AnalysisLibErrType CVIFUNC Median    (const double x[], int n, double *median);
AnalysisLibErrType CVIFUNC Mode      (const double x[], int n, double xBase,
                                      double xTop, int intervals, double *mode);
AnalysisLibErrType CVIFUNC Histogram (const double x[], int n, double xBase,
                                      double xTop, int hist[], double Axis[],
                                      int intervals);


/*- Probability Distribution -------------------------------------------------*/

AnalysisLibErrType CVIFUNC N_Dist     (double x, double *p);
AnalysisLibErrType CVIFUNC T_Dist     (double t, int n, double *p);
AnalysisLibErrType CVIFUNC F_Dist     (double f, int n, int m, double *p);
AnalysisLibErrType CVIFUNC XX_Dist    (double x, int n, double *p);
AnalysisLibErrType CVIFUNC InvN_Dist  (double p, double *x);
AnalysisLibErrType CVIFUNC InvT_Dist  (double p, int n, double *t);
AnalysisLibErrType CVIFUNC InvF_Dist  (double p, int n, int m, double *f);
AnalysisLibErrType CVIFUNC InvXX_Dist (double p, int n, double *x);


/*- Analysis of Variance -----------------------------------------------------*/

AnalysisLibErrType CVIFUNC ANOVA1Way (const double y[], const int level[],
                                      int n, int k, double *ssa, double *msa,
                                      double *f, double *sig, double *sse,
                                      double *mse, double *tss);
AnalysisLibErrType CVIFUNC ANOVA2Way (const double y[], const int levelA[],
                                      const int levelB[], int N, int L,
                                      int a, int b, double info[4][4],
                                      double *sigA, double *sigB, double *sigAB);
AnalysisLibErrType CVIFUNC ANOVA3Way (const double y[], const int levelA[],
                                      const int levelB[], const int levelC[],
                                      int N, int L, int a, int b, int c, 
                                      double info[8][4], double *sigA,
                                      double *sigB, double *sigC, double *sigAB,
                                      double *sigAC, double *sigBC,
                                      double *sigABC);


/*- Nonparametric Statistics -------------------------------------------------*/

AnalysisLibErrType CVIFUNC Contingency_Table (int s, int k, const void *y,
                                              double *Test_Stat, double *Sig);
                                              
AnalysisLibErrType CVIFUNC Erf (double x, double *erfx); 
AnalysisLibErrType CVIFUNC Erfc (double x, double *erfcx);                                              


/*- Curve Fitting ------------------------------------------------------------*/

AnalysisLibErrType CVIFUNC LinFit       (const double x[], const double y[],
                                         int n, double z[], double *slope,
                                         double *intercept, double *mse);

AnalysisLibErrType CVIFUNC ExpFit       (const double x[], const double y[],
                                         int n, double z[], double *a,
                                         double *b, double *mse);

AnalysisLibErrType CVIFUNC PolyFit      (const double x[], const double y[],
                                         int n, int order, double z[],
                                         double coef[], double *mse);

AnalysisLibErrType CVIFUNC GenLSFit     (const void *H, int row, int col,
                                         const double y[], const double stddev[],
                                         int algorithm, 
                                         double z[], double coef[],
                                         void *covar, double *mse);

AnalysisLibErrType CVIFUNC NonLinearFit (const double x[], const double y[],
                                         double z[], int n, ModelFun *func,
                                         double coef[], int m, double *mse);
                                     
AnalysisLibErrType CVIFUNC NonLinearFitWithMaxIters (const double x[], const double y[], 
                                                    const double z[], int n,
                                                    int maxiters, ModelFun *func, 
                                                    double coef[], int m, double *mse);
                                                    
  /*- Old-style Curve Fitting Function (replaced by GenLSFit) -*/
AnalysisLibErrType CVIFUNC GenLSFitCoef (const void *H, int row, int col,
                                         const double y[], double coef[],
                                         int algorithm);


/*- Vector and Matrix Algebra ------------------------------------------------*/
/*- Real Matrices ----------------*/

AnalysisLibErrType CVIFUNC DotProduct    (const double x[], const double y[],
                                          int n, double *dotProd);
AnalysisLibErrType CVIFUNC MatrixMul     (const void *x, const void *y, int n,
                                          int k, int m, void *z);
AnalysisLibErrType CVIFUNC InvMatrix     (const void *x, int n, void *y);
AnalysisLibErrType CVIFUNC Transpose     (const void *x, int n, int m, void *y);
AnalysisLibErrType CVIFUNC Determinant   (const void *x, int n, double *det);
AnalysisLibErrType CVIFUNC Trace         (const void *x, int n, double *traceval);
AnalysisLibErrType CVIFUNC LinEqs        (const void *A, const double y[],
                                          int n, double x[]);
AnalysisLibErrType CVIFUNC LU            (void *a, int n, int p[], int *sign);
AnalysisLibErrType CVIFUNC ForwSub       (const void *a, const double y[],
                                          int n, double x[], const int p[]);
AnalysisLibErrType CVIFUNC BackSub       (const void *a, const double y[],
                                          int n, double x[]);
AnalysisLibErrType CVIFUNC SVD           (void *a, int n, int m, void *u, double s[], void *v);
AnalysisLibErrType CVIFUNC SVDS          (void *a, int n, int m, double s[]);
AnalysisLibErrType CVIFUNC QR            (void *a, int n, int m, int algorithm, 
                                          void *q, void *r);
AnalysisLibErrType CVIFUNC OuterProduct  (const double vectorX[], int nx,
                                          const double vectorY[], int ny,
                                          void *z);
AnalysisLibErrType CVIFUNC MatrixRank    (void *a, int n, int m, double tolerance, int *rank);
AnalysisLibErrType CVIFUNC MatrixNorm    (void *a, int n, int m, int normType, double *norm);
AnalysisLibErrType CVIFUNC SymEigenValueVector (void *a, int n, int outputChoice, 
                                                double eigenValues[], void *eigenVectors);
AnalysisLibErrType CVIFUNC GenEigenValueVector (void *a, int n, int outputChoice, 
                                                ComplexNum eigenValues[], void *eigenVectors);
AnalysisLibErrType CVIFUNC ConditionNumber     (void *a, int n, int m, int normType, 
                                                double *c);
AnalysisLibErrType CVIFUNC SpecialMatrix       (int type, int m, const double x[], int nx, 
                                                const double y[], int ny, void *z);
AnalysisLibErrType CVIFUNC CheckPosDef         (void *a, int n, int *positiveDefinite);
AnalysisLibErrType CVIFUNC PseudoInverse       (void *a, int n, int m, double tolerance, 
                                                void *mpi);
AnalysisLibErrType CVIFUNC GenInvMatrix        (void *a, int n, int type, void *mi);  
AnalysisLibErrType CVIFUNC GenDeterminant      (void *a, int n, int type, double *determinant);   
AnalysisLibErrType CVIFUNC GenLinEqs           (void *a, int n, int m, const double y[], int type, 
                                                double x[]);
AnalysisLibErrType CVIFUNC Cholesky            (void *a, int n, void *r); 


/*- Complex Matrices ---------------------*/

AnalysisLibErrType CVIFUNC CxPseudoInverse     (void *a, int n, int m, double tolerance, 
                                                void *mpi);
AnalysisLibErrType CVIFUNC CxMatrixNorm        (void *a, int n, int m, int normType, 
                                                double *norm);
AnalysisLibErrType CVIFUNC CxLU                (void *a, int n, int p[], int *sign);
AnalysisLibErrType CVIFUNC CxQR                (void *a, int n, int m, void *q, void *r);
AnalysisLibErrType CVIFUNC CxSpecialMatrix     (int matrixType, int m, const ComplexNum x[],
                                                int nx, const ComplexNum y[], int ny,
                                                void *z);
AnalysisLibErrType CVIFUNC CxCheckPosDef       (void *a, int n, int *positiveDefinite);
AnalysisLibErrType CVIFUNC CxTrace             (void *a, int n, int m, ComplexNum *trace);
AnalysisLibErrType CVIFUNC CxSVDS              (void *a, int n, int m, ComplexNum s[]);
AnalysisLibErrType CVIFUNC CxSVD               (void *a, int n, int m, void *u, ComplexNum s[], 
                                                void *v);
AnalysisLibErrType CVIFUNC CxTranspose         (void *a, int n, int m, void *b);
AnalysisLibErrType CVIFUNC CxConditionNumber   (void *a, int n, int m, int normType, 
                                                double *c);
AnalysisLibErrType CVIFUNC CxOuterProduct      (const ComplexNum x[], int nx, const ComplexNum y[], 
                                                int ny, void *outerProduct);
AnalysisLibErrType CVIFUNC CxDotProduct        (const ComplexNum x[], const ComplexNum y[], int n,
                                                ComplexNum *dotProduct);
AnalysisLibErrType CVIFUNC CxEigenValueVector  (void *a, int n, int matrixType, int outputChoice,
                                                ComplexNum eigenValues[], void *eigenVectors);
AnalysisLibErrType CVIFUNC CxGenInvMatrix      (void *a, int n, int matrixType, void *mi);
AnalysisLibErrType CVIFUNC CxMatrixMul         (void *x, void *y, int n, int k, int m, void *z);
AnalysisLibErrType CVIFUNC CxMatrixRank        (void *a, int n, int m, double tolerance, int *rank);
AnalysisLibErrType CVIFUNC CxGenLinEqs         (void *a, int n, int m, const ComplexNum y[], int matrixType, 
                                                ComplexNum x[]);
AnalysisLibErrType CVIFUNC CxDeterminant       (void *a, int n, int matrixType, ComplexNum *det);
AnalysisLibErrType CVIFUNC CxCholesky          (void *a, int n, void *r);


/*- Interpolation ------------------------------------------------------------*/

AnalysisLibErrType CVIFUNC PolyInterp (const double x[], const double y[],
                                       int n, double x_val, double *Interp_Val,
                                       double *Error);
AnalysisLibErrType CVIFUNC RatInterp  (const double x[], const double y[],
                                       int n, double x_val, double *Interp_Val,
                                       double *Error);
AnalysisLibErrType CVIFUNC SpInterp   (const double x[], const double y[],
                                       const double y2[], int n, double x_val,
                                       double *Interp_Val);
AnalysisLibErrType CVIFUNC Spline     (const double x[], const double y[],
                                       int n, double b1, double b2, double y2[]);

/*- Additional Numeric Functions ---------------------------------------------*/
AnalysisLibErrType CVIFUNC NumericIntegration (const double x[], int n, double dt, 
                                               int integrationMethod, double *ir);
AnalysisLibErrType CVIFUNC CxPolyRoots (const double x[], int n, ComplexNum y[]);

AnalysisLibErrType CVIFUNC PeakDetector (const double x[], int n, double threshold, int width, 
                                         int polarity, int initialize, int endOfData, int *count,
                                         double **pL, double **pA, double **pSD);
/*- Error String -------------------------------------------------------------*/
char * CVIFUNC GetAnalysisErrorString(AnalysisLibErrType errorNum);

void CVIFUNC FreeAnalysisMem (void *p); 
/*- The End ------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

#endif /* !defined(_ANALYSIS_H) */
