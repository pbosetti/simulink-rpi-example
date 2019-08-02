/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: linax0.h
 *
 * Code generated for Simulink model 'linax0'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Fri Aug  2 16:41:18 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_linax0_h_
#define RTW_HEADER_linax0_h_
#include <string.h>
#ifndef linax0_COMMON_INCLUDES_
# define linax0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* linax0_COMMON_INCLUDES_ */

#include "rt_zcfcn.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T xdot;                         /* '<S7>/Integrator' */
  real_T xdot_f;                       /* '<S5>/Integrator' */
  real_T xdot_p;                       /* '<S6>/Integrator' */
  real_T F;
  real_T Gain;                         /* '<S6>/Gain' */
  real_T F_g;
  real_T Gain_j;                       /* '<S5>/Gain' */
  real_T F_gy;
  real_T Gain_a;                       /* '<S7>/Gain' */
  real_T Integrator_DSTATE;            /* '<S125>/Integrator' */
  real_T UD_DSTATE;                    /* '<S120>/UD' */
  real_T Integrator_DSTATE_n;          /* '<S81>/Integrator' */
  real_T UD_DSTATE_e;                  /* '<S76>/UD' */
  real_T Integrator_DSTATE_a;          /* '<S37>/Integrator' */
  real_T UD_DSTATE_o;                  /* '<S32>/UD' */
  real_T F_Buffer0;                    /* synthesized block */
  real_T F_Buffer0_g;                  /* synthesized block */
  real_T F_Buffer0_gh;                 /* synthesized block */
  real_T TmpRTBAtSum2Outport1_Buffer;  /* synthesized block */
  real_T TmpRTBAtSum1Outport1_Buffer;  /* synthesized block */
  real_T TmpRTBAtSumOutport1_Buffer;   /* synthesized block */
  int8_T Integrator_PrevResetState;    /* '<S125>/Integrator' */
  int8_T Integrator_PrevResetState_e;  /* '<S81>/Integrator' */
  int8_T Integrator_PrevResetState_o;  /* '<S37>/Integrator' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S5>/Integrator1' */
  real_T Integrator1_CSTATE_e;         /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_k;         /* '<S7>/Integrator1' */
  real_T Integrator_CSTATE;            /* '<S7>/Integrator' */
  real_T Integrator_CSTATE_o;          /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_p;          /* '<S6>/Integrator' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S5>/Integrator1' */
  real_T Integrator1_CSTATE_e;         /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_k;         /* '<S7>/Integrator1' */
  real_T Integrator_CSTATE;            /* '<S7>/Integrator' */
  real_T Integrator_CSTATE_o;          /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_p;          /* '<S6>/Integrator' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S5>/Integrator1' */
  boolean_T Integrator1_CSTATE_e;      /* '<S6>/Integrator1' */
  boolean_T Integrator1_CSTATE_k;      /* '<S7>/Integrator1' */
  boolean_T Integrator_CSTATE;         /* '<S7>/Integrator' */
  boolean_T Integrator_CSTATE_o;       /* '<S5>/Integrator' */
  boolean_T Integrator_CSTATE_p;       /* '<S6>/Integrator' */
} XDis;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState UD_Reset_ZCE;             /* '<S120>/UD' */
  ZCSigState UD_Reset_ZCE_g;           /* '<S76>/UD' */
  ZCSigState UD_Reset_ZCE_j;           /* '<S32>/UD' */
} PrevZCX;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Type definition for custom storage class: Struct */
typedef struct AX_params_tag {
  real_T c[3];                         /* Resistence */
  real_T m[3];                         /* Mass */
} AX_params_type;

typedef struct PID_params_tag {
  real_T D[3];                         /* PID D */
  real_T I[3];                         /* PID I */
  real_T P[3];                         /* PID P */
  real_T sat[3];                       /* PID output saturation */
} PID_params_type;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  PrevZCX *prevZCSigState;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
  ODE3_IntgData intgData;
  DW *dwork;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID1_2;
    } RateInteraction;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Model entry point functions */
extern void linax0_initialize(RT_MODEL *const rtM);
extern void linax0_step0(RT_MODEL *const rtM, real_T rtU_setpoint[3], real_T
  rtU_reset, real_T rtY_x[3], real_T rtY_xdot[3]);
extern void linax0_step2(RT_MODEL *const rtM, real_T rtU_reset);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern AX_params_type AX_params;
extern PID_params_type PID_params;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S32>/DTDup' : Unused code path elimination
 * Block '<S76>/DTDup' : Unused code path elimination
 * Block '<S120>/DTDup' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('linax/linax')    - opens subsystem linax/linax
 * hilite_system('linax/linax/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'linax'
 * '<S1>'   : 'linax/linax'
 * '<S2>'   : 'linax/linax/Discrete PID Controller'
 * '<S3>'   : 'linax/linax/Discrete PID Controller1'
 * '<S4>'   : 'linax/linax/Discrete PID Controller2'
 * '<S5>'   : 'linax/linax/Subsystem'
 * '<S6>'   : 'linax/linax/Subsystem1'
 * '<S7>'   : 'linax/linax/Subsystem2'
 * '<S8>'   : 'linax/linax/Discrete PID Controller/Anti-windup'
 * '<S9>'   : 'linax/linax/Discrete PID Controller/D Gain'
 * '<S10>'  : 'linax/linax/Discrete PID Controller/Filter'
 * '<S11>'  : 'linax/linax/Discrete PID Controller/Filter ICs'
 * '<S12>'  : 'linax/linax/Discrete PID Controller/I Gain'
 * '<S13>'  : 'linax/linax/Discrete PID Controller/Ideal P Gain'
 * '<S14>'  : 'linax/linax/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S15>'  : 'linax/linax/Discrete PID Controller/Integrator'
 * '<S16>'  : 'linax/linax/Discrete PID Controller/Integrator ICs'
 * '<S17>'  : 'linax/linax/Discrete PID Controller/N Copy'
 * '<S18>'  : 'linax/linax/Discrete PID Controller/N Gain'
 * '<S19>'  : 'linax/linax/Discrete PID Controller/P Copy'
 * '<S20>'  : 'linax/linax/Discrete PID Controller/Parallel P Gain'
 * '<S21>'  : 'linax/linax/Discrete PID Controller/Reset Signal'
 * '<S22>'  : 'linax/linax/Discrete PID Controller/Saturation'
 * '<S23>'  : 'linax/linax/Discrete PID Controller/Saturation Fdbk'
 * '<S24>'  : 'linax/linax/Discrete PID Controller/Sum'
 * '<S25>'  : 'linax/linax/Discrete PID Controller/Sum Fdbk'
 * '<S26>'  : 'linax/linax/Discrete PID Controller/Tracking Mode'
 * '<S27>'  : 'linax/linax/Discrete PID Controller/Tracking Mode Sum'
 * '<S28>'  : 'linax/linax/Discrete PID Controller/postSat Signal'
 * '<S29>'  : 'linax/linax/Discrete PID Controller/preSat Signal'
 * '<S30>'  : 'linax/linax/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S31>'  : 'linax/linax/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S32>'  : 'linax/linax/Discrete PID Controller/Filter/Differentiator'
 * '<S33>'  : 'linax/linax/Discrete PID Controller/Filter ICs/Internal IC - Differentiator'
 * '<S34>'  : 'linax/linax/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S35>'  : 'linax/linax/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S36>'  : 'linax/linax/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'linax/linax/Discrete PID Controller/Integrator/Discrete'
 * '<S38>'  : 'linax/linax/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S39>'  : 'linax/linax/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S40>'  : 'linax/linax/Discrete PID Controller/N Gain/Passthrough'
 * '<S41>'  : 'linax/linax/Discrete PID Controller/P Copy/Disabled'
 * '<S42>'  : 'linax/linax/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'linax/linax/Discrete PID Controller/Reset Signal/External Reset'
 * '<S44>'  : 'linax/linax/Discrete PID Controller/Saturation/Enabled'
 * '<S45>'  : 'linax/linax/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S46>'  : 'linax/linax/Discrete PID Controller/Sum/Sum_PID'
 * '<S47>'  : 'linax/linax/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S48>'  : 'linax/linax/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S49>'  : 'linax/linax/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'linax/linax/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S51>'  : 'linax/linax/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S52>'  : 'linax/linax/Discrete PID Controller1/Anti-windup'
 * '<S53>'  : 'linax/linax/Discrete PID Controller1/D Gain'
 * '<S54>'  : 'linax/linax/Discrete PID Controller1/Filter'
 * '<S55>'  : 'linax/linax/Discrete PID Controller1/Filter ICs'
 * '<S56>'  : 'linax/linax/Discrete PID Controller1/I Gain'
 * '<S57>'  : 'linax/linax/Discrete PID Controller1/Ideal P Gain'
 * '<S58>'  : 'linax/linax/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S59>'  : 'linax/linax/Discrete PID Controller1/Integrator'
 * '<S60>'  : 'linax/linax/Discrete PID Controller1/Integrator ICs'
 * '<S61>'  : 'linax/linax/Discrete PID Controller1/N Copy'
 * '<S62>'  : 'linax/linax/Discrete PID Controller1/N Gain'
 * '<S63>'  : 'linax/linax/Discrete PID Controller1/P Copy'
 * '<S64>'  : 'linax/linax/Discrete PID Controller1/Parallel P Gain'
 * '<S65>'  : 'linax/linax/Discrete PID Controller1/Reset Signal'
 * '<S66>'  : 'linax/linax/Discrete PID Controller1/Saturation'
 * '<S67>'  : 'linax/linax/Discrete PID Controller1/Saturation Fdbk'
 * '<S68>'  : 'linax/linax/Discrete PID Controller1/Sum'
 * '<S69>'  : 'linax/linax/Discrete PID Controller1/Sum Fdbk'
 * '<S70>'  : 'linax/linax/Discrete PID Controller1/Tracking Mode'
 * '<S71>'  : 'linax/linax/Discrete PID Controller1/Tracking Mode Sum'
 * '<S72>'  : 'linax/linax/Discrete PID Controller1/postSat Signal'
 * '<S73>'  : 'linax/linax/Discrete PID Controller1/preSat Signal'
 * '<S74>'  : 'linax/linax/Discrete PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S75>'  : 'linax/linax/Discrete PID Controller1/D Gain/Internal Parameters'
 * '<S76>'  : 'linax/linax/Discrete PID Controller1/Filter/Differentiator'
 * '<S77>'  : 'linax/linax/Discrete PID Controller1/Filter ICs/Internal IC - Differentiator'
 * '<S78>'  : 'linax/linax/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S79>'  : 'linax/linax/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S80>'  : 'linax/linax/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S81>'  : 'linax/linax/Discrete PID Controller1/Integrator/Discrete'
 * '<S82>'  : 'linax/linax/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S83>'  : 'linax/linax/Discrete PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S84>'  : 'linax/linax/Discrete PID Controller1/N Gain/Passthrough'
 * '<S85>'  : 'linax/linax/Discrete PID Controller1/P Copy/Disabled'
 * '<S86>'  : 'linax/linax/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S87>'  : 'linax/linax/Discrete PID Controller1/Reset Signal/External Reset'
 * '<S88>'  : 'linax/linax/Discrete PID Controller1/Saturation/Enabled'
 * '<S89>'  : 'linax/linax/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S90>'  : 'linax/linax/Discrete PID Controller1/Sum/Sum_PID'
 * '<S91>'  : 'linax/linax/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S92>'  : 'linax/linax/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S93>'  : 'linax/linax/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S94>'  : 'linax/linax/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S95>'  : 'linax/linax/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S96>'  : 'linax/linax/Discrete PID Controller2/Anti-windup'
 * '<S97>'  : 'linax/linax/Discrete PID Controller2/D Gain'
 * '<S98>'  : 'linax/linax/Discrete PID Controller2/Filter'
 * '<S99>'  : 'linax/linax/Discrete PID Controller2/Filter ICs'
 * '<S100>' : 'linax/linax/Discrete PID Controller2/I Gain'
 * '<S101>' : 'linax/linax/Discrete PID Controller2/Ideal P Gain'
 * '<S102>' : 'linax/linax/Discrete PID Controller2/Ideal P Gain Fdbk'
 * '<S103>' : 'linax/linax/Discrete PID Controller2/Integrator'
 * '<S104>' : 'linax/linax/Discrete PID Controller2/Integrator ICs'
 * '<S105>' : 'linax/linax/Discrete PID Controller2/N Copy'
 * '<S106>' : 'linax/linax/Discrete PID Controller2/N Gain'
 * '<S107>' : 'linax/linax/Discrete PID Controller2/P Copy'
 * '<S108>' : 'linax/linax/Discrete PID Controller2/Parallel P Gain'
 * '<S109>' : 'linax/linax/Discrete PID Controller2/Reset Signal'
 * '<S110>' : 'linax/linax/Discrete PID Controller2/Saturation'
 * '<S111>' : 'linax/linax/Discrete PID Controller2/Saturation Fdbk'
 * '<S112>' : 'linax/linax/Discrete PID Controller2/Sum'
 * '<S113>' : 'linax/linax/Discrete PID Controller2/Sum Fdbk'
 * '<S114>' : 'linax/linax/Discrete PID Controller2/Tracking Mode'
 * '<S115>' : 'linax/linax/Discrete PID Controller2/Tracking Mode Sum'
 * '<S116>' : 'linax/linax/Discrete PID Controller2/postSat Signal'
 * '<S117>' : 'linax/linax/Discrete PID Controller2/preSat Signal'
 * '<S118>' : 'linax/linax/Discrete PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S119>' : 'linax/linax/Discrete PID Controller2/D Gain/Internal Parameters'
 * '<S120>' : 'linax/linax/Discrete PID Controller2/Filter/Differentiator'
 * '<S121>' : 'linax/linax/Discrete PID Controller2/Filter ICs/Internal IC - Differentiator'
 * '<S122>' : 'linax/linax/Discrete PID Controller2/I Gain/Internal Parameters'
 * '<S123>' : 'linax/linax/Discrete PID Controller2/Ideal P Gain/Passthrough'
 * '<S124>' : 'linax/linax/Discrete PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S125>' : 'linax/linax/Discrete PID Controller2/Integrator/Discrete'
 * '<S126>' : 'linax/linax/Discrete PID Controller2/Integrator ICs/Internal IC'
 * '<S127>' : 'linax/linax/Discrete PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S128>' : 'linax/linax/Discrete PID Controller2/N Gain/Passthrough'
 * '<S129>' : 'linax/linax/Discrete PID Controller2/P Copy/Disabled'
 * '<S130>' : 'linax/linax/Discrete PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S131>' : 'linax/linax/Discrete PID Controller2/Reset Signal/External Reset'
 * '<S132>' : 'linax/linax/Discrete PID Controller2/Saturation/Enabled'
 * '<S133>' : 'linax/linax/Discrete PID Controller2/Saturation Fdbk/Disabled'
 * '<S134>' : 'linax/linax/Discrete PID Controller2/Sum/Sum_PID'
 * '<S135>' : 'linax/linax/Discrete PID Controller2/Sum Fdbk/Disabled'
 * '<S136>' : 'linax/linax/Discrete PID Controller2/Tracking Mode/Disabled'
 * '<S137>' : 'linax/linax/Discrete PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S138>' : 'linax/linax/Discrete PID Controller2/postSat Signal/Forward_Path'
 * '<S139>' : 'linax/linax/Discrete PID Controller2/preSat Signal/Forward_Path'
 */

/*-
 * Requirements for '<Root>': linax0
 */
#endif                                 /* RTW_HEADER_linax0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
