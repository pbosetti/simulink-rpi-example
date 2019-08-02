/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: linax0.c
 *
 * Code generated for Simulink model 'linax0'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Fri Aug  2 14:28:38 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "linax0.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* Exported data definition */

/* Definition for custom storage class: Struct */
AX_params_type AX_params = {
  /* c */
  { 0.01, 0.01, 0.01 },

  /* m */
  { 1.5, 1.1, 1.0 }
};

PID_params_type PID_params = {
  /* PID_params */
  { 5.0, 5.0, 5.0 },

  /* I */
  { 11.0, 11.0, 11.0 },

  /* P */
  { 2501.0, 2001.0, 2001.0 },

  /* sat */
  { 3001.0, 3000.0, 3000.0 }
};

/* private model entry point functions */
extern void linax0_derivatives(RT_MODEL *const rtM);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , RT_MODEL *const
  rtM, real_T rtU_setpoint[3], real_T rtU_reset, real_T rtY_x[3], real_T
  rtY_xdot[3])
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  linax0_derivatives(rtM);

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  linax0_step0(rtM, rtU_setpoint, rtU_reset, rtY_x, rtY_xdot);
  linax0_derivatives(rtM);

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  linax0_step0(rtM, rtU_setpoint, rtU_reset, rtY_x, rtY_xdot);
  linax0_derivatives(rtM);

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function for TID0 */
void linax0_step0(RT_MODEL *const rtM, real_T rtU_setpoint[3], real_T rtU_reset,
                  real_T rtY_x[3], real_T rtY_xdot[3]) /* Sample time: [0.0s, 0.0s] */
{
  DW *rtDW = ((DW *) rtM->dwork);
  X *rtX = ((X *) rtM->contStates);
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));

    /* Update the flag to indicate when data transfers from
     *  Sample time: [0.001s, 0.0s] to Sample time: [0.005s, 0.0s]  */
    (rtM->Timing.RateInteraction.TID1_2)++;
    if ((rtM->Timing.RateInteraction.TID1_2) > 4) {
      rtM->Timing.RateInteraction.TID1_2 = 0;
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* Outport: '<Root>/x' incorporates:
   *  Integrator: '<S5>/Integrator1'
   *  Integrator: '<S6>/Integrator1'
   *  Integrator: '<S7>/Integrator1'
   */
  rtY_x[0] = rtX->Integrator1_CSTATE;
  rtY_x[1] = rtX->Integrator1_CSTATE_e;
  rtY_x[2] = rtX->Integrator1_CSTATE_k;

  /* Integrator: '<S7>/Integrator' */
  rtDW->xdot = rtX->Integrator_CSTATE;

  /* Integrator: '<S5>/Integrator' */
  rtDW->xdot_f = rtX->Integrator_CSTATE_o;

  /* Integrator: '<S6>/Integrator' */
  rtDW->xdot_p = rtX->Integrator_CSTATE_p;

  /* Outport: '<Root>/xdot' */
  rtY_xdot[0] = rtDW->xdot_f;
  rtY_xdot[1] = rtDW->xdot_p;
  rtY_xdot[2] = rtDW->xdot;

  /* RateTransition: '<S6>/F' incorporates:
   *  RateTransition: '<S5>/F'
   */
  if (rtmIsMajorTimeStep(rtM)) {
    if (rtM->Timing.RateInteraction.TID1_2 == 1) {
      rtDW->F = rtDW->F_Buffer0;
    }

    if (rtM->Timing.RateInteraction.TID1_2 == 1) {
      rtDW->F_g = rtDW->F_Buffer0_g;
    }
  }

  /* End of RateTransition: '<S6>/F' */

  /* Gain: '<S6>/Gain' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Sum: '<S6>/Sum1'
   */
  rtDW->Gain = (rtDW->F - 1.0 / AX_params.c[1] * rtDW->xdot_p) * (1.0 /
    AX_params.m[1]);

  /* Gain: '<S5>/Gain' incorporates:
   *  Gain: '<S5>/Gain1'
   *  Sum: '<S5>/Sum1'
   */
  rtDW->Gain_j = (rtDW->F_g - 1.0 / AX_params.c[0] * rtDW->xdot_f) * (1.0 /
    AX_params.m[0]);

  /* RateTransition: '<S7>/F' */
  if (rtmIsMajorTimeStep(rtM) && (rtM->Timing.RateInteraction.TID1_2 == 1)) {
    rtDW->F_gy = rtDW->F_Buffer0_gh;
  }

  /* End of RateTransition: '<S7>/F' */

  /* Gain: '<S7>/Gain' incorporates:
   *  Gain: '<S7>/Gain1'
   *  Sum: '<S7>/Sum1'
   */
  rtDW->Gain_a = (rtDW->F_gy - 1.0 / AX_params.c[2] * rtDW->xdot) * (1.0 /
    AX_params.m[2]);

  /* RateTransition: '<S1>/TmpRTBAtSum2Outport1' incorporates:
   *  Inport: '<Root>/setpoint'
   *  Integrator: '<S5>/Integrator1'
   *  Integrator: '<S6>/Integrator1'
   *  Integrator: '<S7>/Integrator1'
   *  RateTransition: '<S1>/TmpRTBAtSum1Outport1'
   *  RateTransition: '<S1>/TmpRTBAtSumOutport1'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum2'
   */
  if (rtmIsMajorTimeStep(rtM) && (rtM->Timing.RateInteraction.TID1_2 == 1)) {
    rtDW->TmpRTBAtSum2Outport1_Buffer = rtU_setpoint[2] -
      rtX->Integrator1_CSTATE_k;
    rtDW->TmpRTBAtSum1Outport1_Buffer = rtU_setpoint[1] -
      rtX->Integrator1_CSTATE_e;
    rtDW->TmpRTBAtSumOutport1_Buffer = rtU_setpoint[0] - rtX->Integrator1_CSTATE;
  }

  /* End of RateTransition: '<S1>/TmpRTBAtSum2Outport1' */
  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo, rtM, rtU_setpoint,
      rtU_reset, rtY_x, rtY_xdot);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void linax0_derivatives(RT_MODEL *const rtM)
{
  DW *rtDW = ((DW *) rtM->dwork);
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = rtDW->xdot_f;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_e = rtDW->xdot_p;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_k = rtDW->xdot;

  /* Derivatives for Integrator: '<S7>/Integrator' */
  _rtXdot->Integrator_CSTATE = rtDW->Gain_a;

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE_o = rtDW->Gain_j;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE_p = rtDW->Gain;
}

/* Model step function for TID2 */
void linax0_step2(RT_MODEL *const rtM, real_T rtU_reset) /* Sample time: [0.005s, 0.0s] */
{
  DW *rtDW = ((DW *) rtM->dwork);
  PrevZCX *rtPrevZCX = ((PrevZCX *) rtM->prevZCSigState);

  /* local block i/o variables */
  real_T rtb_TSamp;
  real_T rtb_Switch;
  real_T rtb_Saturation;
  real_T rtb_TSamp_o;
  real_T rtb_Switch_e;
  real_T rtb_Saturation_k;
  real_T rtb_TSamp_p;
  real_T rtb_Switch_d;
  real_T rtb_Saturation_ke;
  real_T rtb_IntegralGain;
  real_T rtb_Sum;
  boolean_T rtb_NotEqual;
  int8_T rtb_DataTypeConv2;
  real_T rtb_Sum_0;

  /* DiscreteIntegrator: '<S125>/Integrator' incorporates:
   *  Inport: '<Root>/reset'
   */
  if ((rtU_reset > 0.0) && (rtDW->Integrator_PrevResetState <= 0)) {
    rtDW->Integrator_DSTATE = 0.0;
  }

  /* SampleTimeMath: '<S120>/TSamp' incorporates:
   *  Gain: '<S119>/Derivative Gain'
   *  RateTransition: '<S1>/TmpRTBAtSum2Outport1'
   *
   * About '<S120>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = PID_params.PID_params[2] * rtDW->TmpRTBAtSum2Outport1_Buffer *
    200.0;

  /* Delay: '<S120>/UD' incorporates:
   *  Inport: '<Root>/reset'
   */
  if (rt_ZCFcn(RISING_ZERO_CROSSING,&rtPrevZCX->UD_Reset_ZCE,
               (rtU_reset)) != NO_ZCEVENT) {
    rtDW->UD_DSTATE = 0.0;
  }

  /* Sum: '<S134>/Sum' incorporates:
   *  Delay: '<S120>/UD'
   *  DiscreteIntegrator: '<S125>/Integrator'
   *  Gain: '<S130>/Proportional Gain'
   *  RateTransition: '<S1>/TmpRTBAtSum2Outport1'
   *  Sum: '<S120>/Diff'
   */
  rtb_IntegralGain = (PID_params.P[2] * rtDW->TmpRTBAtSum2Outport1_Buffer +
                      rtDW->Integrator_DSTATE) + (rtb_TSamp - rtDW->UD_DSTATE);

  /* DeadZone: '<S118>/DeadZone' */
  if (rtb_IntegralGain > PID_params.sat[2]) {
    rtb_Sum = rtb_IntegralGain - PID_params.sat[2];
  } else if (rtb_IntegralGain >= -PID_params.sat[2]) {
    rtb_Sum = 0.0;
  } else {
    rtb_Sum = rtb_IntegralGain - (-PID_params.sat[2]);
  }

  /* End of DeadZone: '<S118>/DeadZone' */

  /* RelationalOperator: '<S118>/NotEqual' incorporates:
   *  Gain: '<S118>/ZeroGain'
   */
  rtb_NotEqual = (0.0 != rtb_Sum);

  /* Signum: '<S118>/SignPreSat' */
  if (rtb_Sum < 0.0) {
    rtb_Sum = -1.0;
  } else {
    if (rtb_Sum > 0.0) {
      rtb_Sum = 1.0;
    }
  }

  /* End of Signum: '<S118>/SignPreSat' */

  /* DataTypeConversion: '<S118>/DataTypeConv1' */
  rtb_DataTypeConv2 = (int8_T)rtb_Sum;

  /* Gain: '<S122>/Integral Gain' incorporates:
   *  RateTransition: '<S1>/TmpRTBAtSum2Outport1'
   */
  rtb_Sum = PID_params.I[2] * rtDW->TmpRTBAtSum2Outport1_Buffer;

  /* Signum: '<S118>/SignPreIntegrator' */
  if (rtb_Sum < 0.0) {
    rtb_Sum_0 = -1.0;
  } else if (rtb_Sum > 0.0) {
    rtb_Sum_0 = 1.0;
  } else {
    rtb_Sum_0 = rtb_Sum;
  }

  /* End of Signum: '<S118>/SignPreIntegrator' */

  /* Switch: '<S118>/Switch' incorporates:
   *  Constant: '<S118>/Constant1'
   *  DataTypeConversion: '<S118>/DataTypeConv2'
   *  Logic: '<S118>/AND3'
   *  RelationalOperator: '<S118>/Equal1'
   */
  if (rtb_NotEqual && (rtb_DataTypeConv2 == (int8_T)rtb_Sum_0)) {
    rtb_Switch = 0.0;
  } else {
    rtb_Switch = rtb_Sum;
  }

  /* End of Switch: '<S118>/Switch' */

  /* Saturate: '<S132>/Saturation' */
  if (rtb_IntegralGain > PID_params.sat[2]) {
    rtb_Saturation = PID_params.sat[2];
  } else if (rtb_IntegralGain < -PID_params.sat[2]) {
    rtb_Saturation = -PID_params.sat[2];
  } else {
    rtb_Saturation = rtb_IntegralGain;
  }

  /* End of Saturate: '<S132>/Saturation' */

  /* DiscreteIntegrator: '<S81>/Integrator' incorporates:
   *  Inport: '<Root>/reset'
   */
  if ((rtU_reset > 0.0) && (rtDW->Integrator_PrevResetState_e <= 0)) {
    rtDW->Integrator_DSTATE_n = 0.0;
  }

  /* SampleTimeMath: '<S76>/TSamp' incorporates:
   *  Gain: '<S75>/Derivative Gain'
   *  RateTransition: '<S1>/TmpRTBAtSum1Outport1'
   *
   * About '<S76>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_o = PID_params.PID_params[1] * rtDW->TmpRTBAtSum1Outport1_Buffer *
    200.0;

  /* Delay: '<S76>/UD' incorporates:
   *  Inport: '<Root>/reset'
   */
  if (rt_ZCFcn(RISING_ZERO_CROSSING,&rtPrevZCX->UD_Reset_ZCE_g,
               (rtU_reset)) != NO_ZCEVENT) {
    rtDW->UD_DSTATE_e = 0.0;
  }

  /* Sum: '<S90>/Sum' incorporates:
   *  Delay: '<S76>/UD'
   *  DiscreteIntegrator: '<S81>/Integrator'
   *  Gain: '<S86>/Proportional Gain'
   *  RateTransition: '<S1>/TmpRTBAtSum1Outport1'
   *  Sum: '<S76>/Diff'
   */
  rtb_Sum = (PID_params.P[1] * rtDW->TmpRTBAtSum1Outport1_Buffer +
             rtDW->Integrator_DSTATE_n) + (rtb_TSamp_o - rtDW->UD_DSTATE_e);

  /* DeadZone: '<S74>/DeadZone' */
  if (rtb_Sum > PID_params.sat[1]) {
    rtb_IntegralGain = rtb_Sum - PID_params.sat[1];
  } else if (rtb_Sum >= -PID_params.sat[1]) {
    rtb_IntegralGain = 0.0;
  } else {
    rtb_IntegralGain = rtb_Sum - (-PID_params.sat[1]);
  }

  /* End of DeadZone: '<S74>/DeadZone' */

  /* RelationalOperator: '<S74>/NotEqual' incorporates:
   *  Gain: '<S74>/ZeroGain'
   */
  rtb_NotEqual = (0.0 != rtb_IntegralGain);

  /* Signum: '<S74>/SignPreSat' */
  if (rtb_IntegralGain < 0.0) {
    rtb_IntegralGain = -1.0;
  } else {
    if (rtb_IntegralGain > 0.0) {
      rtb_IntegralGain = 1.0;
    }
  }

  /* End of Signum: '<S74>/SignPreSat' */

  /* DataTypeConversion: '<S74>/DataTypeConv1' */
  rtb_DataTypeConv2 = (int8_T)rtb_IntegralGain;

  /* Gain: '<S78>/Integral Gain' incorporates:
   *  RateTransition: '<S1>/TmpRTBAtSum1Outport1'
   */
  rtb_IntegralGain = PID_params.I[1] * rtDW->TmpRTBAtSum1Outport1_Buffer;

  /* Signum: '<S74>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0) {
    rtb_Sum_0 = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    rtb_Sum_0 = 1.0;
  } else {
    rtb_Sum_0 = rtb_IntegralGain;
  }

  /* End of Signum: '<S74>/SignPreIntegrator' */

  /* Switch: '<S74>/Switch' incorporates:
   *  Constant: '<S74>/Constant1'
   *  DataTypeConversion: '<S74>/DataTypeConv2'
   *  Logic: '<S74>/AND3'
   *  RelationalOperator: '<S74>/Equal1'
   */
  if (rtb_NotEqual && (rtb_DataTypeConv2 == (int8_T)rtb_Sum_0)) {
    rtb_Switch_e = 0.0;
  } else {
    rtb_Switch_e = rtb_IntegralGain;
  }

  /* End of Switch: '<S74>/Switch' */

  /* Saturate: '<S88>/Saturation' */
  if (rtb_Sum > PID_params.sat[1]) {
    rtb_Saturation_k = PID_params.sat[1];
  } else if (rtb_Sum < -PID_params.sat[1]) {
    rtb_Saturation_k = -PID_params.sat[1];
  } else {
    rtb_Saturation_k = rtb_Sum;
  }

  /* End of Saturate: '<S88>/Saturation' */

  /* DiscreteIntegrator: '<S37>/Integrator' incorporates:
   *  Inport: '<Root>/reset'
   */
  if ((rtU_reset > 0.0) && (rtDW->Integrator_PrevResetState_o <= 0)) {
    rtDW->Integrator_DSTATE_a = 0.0;
  }

  /* SampleTimeMath: '<S32>/TSamp' incorporates:
   *  Gain: '<S31>/Derivative Gain'
   *  RateTransition: '<S1>/TmpRTBAtSumOutport1'
   *
   * About '<S32>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_p = PID_params.PID_params[0] * rtDW->TmpRTBAtSumOutport1_Buffer *
    200.0;

  /* Delay: '<S32>/UD' incorporates:
   *  Inport: '<Root>/reset'
   */
  if (rt_ZCFcn(RISING_ZERO_CROSSING,&rtPrevZCX->UD_Reset_ZCE_j,
               (rtU_reset)) != NO_ZCEVENT) {
    rtDW->UD_DSTATE_o = 0.0;
  }

  /* Sum: '<S46>/Sum' incorporates:
   *  Delay: '<S32>/UD'
   *  DiscreteIntegrator: '<S37>/Integrator'
   *  Gain: '<S42>/Proportional Gain'
   *  RateTransition: '<S1>/TmpRTBAtSumOutport1'
   *  Sum: '<S32>/Diff'
   */
  rtb_Sum = (PID_params.P[0] * rtDW->TmpRTBAtSumOutport1_Buffer +
             rtDW->Integrator_DSTATE_a) + (rtb_TSamp_p - rtDW->UD_DSTATE_o);

  /* DeadZone: '<S30>/DeadZone' */
  if (rtb_Sum > PID_params.sat[0]) {
    rtb_IntegralGain = rtb_Sum - PID_params.sat[0];
  } else if (rtb_Sum >= -PID_params.sat[0]) {
    rtb_IntegralGain = 0.0;
  } else {
    rtb_IntegralGain = rtb_Sum - (-PID_params.sat[0]);
  }

  /* End of DeadZone: '<S30>/DeadZone' */

  /* RelationalOperator: '<S30>/NotEqual' incorporates:
   *  Gain: '<S30>/ZeroGain'
   */
  rtb_NotEqual = (0.0 != rtb_IntegralGain);

  /* Signum: '<S30>/SignPreSat' */
  if (rtb_IntegralGain < 0.0) {
    rtb_IntegralGain = -1.0;
  } else {
    if (rtb_IntegralGain > 0.0) {
      rtb_IntegralGain = 1.0;
    }
  }

  /* End of Signum: '<S30>/SignPreSat' */

  /* DataTypeConversion: '<S30>/DataTypeConv1' */
  rtb_DataTypeConv2 = (int8_T)rtb_IntegralGain;

  /* Gain: '<S34>/Integral Gain' incorporates:
   *  RateTransition: '<S1>/TmpRTBAtSumOutport1'
   */
  rtb_IntegralGain = PID_params.I[0] * rtDW->TmpRTBAtSumOutport1_Buffer;

  /* Signum: '<S30>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0) {
    rtb_Sum_0 = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    rtb_Sum_0 = 1.0;
  } else {
    rtb_Sum_0 = rtb_IntegralGain;
  }

  /* End of Signum: '<S30>/SignPreIntegrator' */

  /* Switch: '<S30>/Switch' incorporates:
   *  Constant: '<S30>/Constant1'
   *  DataTypeConversion: '<S30>/DataTypeConv2'
   *  Logic: '<S30>/AND3'
   *  RelationalOperator: '<S30>/Equal1'
   */
  if (rtb_NotEqual && (rtb_DataTypeConv2 == (int8_T)rtb_Sum_0)) {
    rtb_Switch_d = 0.0;
  } else {
    rtb_Switch_d = rtb_IntegralGain;
  }

  /* End of Switch: '<S30>/Switch' */

  /* Saturate: '<S44>/Saturation' */
  if (rtb_Sum > PID_params.sat[0]) {
    rtb_Saturation_ke = PID_params.sat[0];
  } else if (rtb_Sum < -PID_params.sat[0]) {
    rtb_Saturation_ke = -PID_params.sat[0];
  } else {
    rtb_Saturation_ke = rtb_Sum;
  }

  /* End of Saturate: '<S44>/Saturation' */

  /* Update for RateTransition: '<S6>/F' */
  rtDW->F_Buffer0 = rtb_Saturation_k;

  /* Update for RateTransition: '<S5>/F' */
  rtDW->F_Buffer0_g = rtb_Saturation_ke;

  /* Update for RateTransition: '<S7>/F' */
  rtDW->F_Buffer0_gh = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S125>/Integrator' incorporates:
   *  DiscreteIntegrator: '<S81>/Integrator'
   *  Inport: '<Root>/reset'
   */
  rtDW->Integrator_DSTATE += 0.005 * rtb_Switch;
  if (rtU_reset > 0.0) {
    rtDW->Integrator_PrevResetState = 1;
    rtDW->Integrator_PrevResetState_e = 1;
  } else {
    if (rtU_reset < 0.0) {
      rtDW->Integrator_PrevResetState = -1;
    } else if (rtU_reset == 0.0) {
      rtDW->Integrator_PrevResetState = 0;
    } else {
      rtDW->Integrator_PrevResetState = 2;
    }

    if (rtU_reset < 0.0) {
      rtDW->Integrator_PrevResetState_e = -1;
    } else if (rtU_reset == 0.0) {
      rtDW->Integrator_PrevResetState_e = 0;
    } else {
      rtDW->Integrator_PrevResetState_e = 2;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S125>/Integrator' */

  /* Update for Delay: '<S120>/UD' */
  rtDW->UD_DSTATE = rtb_TSamp;

  /* Update for DiscreteIntegrator: '<S81>/Integrator' */
  rtDW->Integrator_DSTATE_n += 0.005 * rtb_Switch_e;

  /* Update for Delay: '<S76>/UD' */
  rtDW->UD_DSTATE_e = rtb_TSamp_o;

  /* Update for DiscreteIntegrator: '<S37>/Integrator' incorporates:
   *  Inport: '<Root>/reset'
   */
  rtDW->Integrator_DSTATE_a += 0.005 * rtb_Switch_d;
  if (rtU_reset > 0.0) {
    rtDW->Integrator_PrevResetState_o = 1;
  } else if (rtU_reset < 0.0) {
    rtDW->Integrator_PrevResetState_o = -1;
  } else if (rtU_reset == 0.0) {
    rtDW->Integrator_PrevResetState_o = 0;
  } else {
    rtDW->Integrator_PrevResetState_o = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S37>/Integrator' */

  /* Update for Delay: '<S32>/UD' */
  rtDW->UD_DSTATE_o = rtb_TSamp_p;
}

/* Model initialize function */
void linax0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = ((DW *) rtM->dwork);
  X *rtX = ((X *) rtM->contStates);
  PrevZCX *rtPrevZCX = ((PrevZCX *) rtM->prevZCSigState);

  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((X *) rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.001;
  rtPrevZCX->UD_Reset_ZCE = UNINITIALIZED_ZCSIG;
  rtPrevZCX->UD_Reset_ZCE_g = UNINITIALIZED_ZCSIG;
  rtPrevZCX->UD_Reset_ZCE_j = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<S5>/Integrator1' */
  rtX->Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  rtX->Integrator1_CSTATE_e = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator1' */
  rtX->Integrator1_CSTATE_k = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  rtX->Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  rtX->Integrator_CSTATE_o = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  rtX->Integrator_CSTATE_p = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S125>/Integrator' */
  rtDW->Integrator_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S81>/Integrator' */
  rtDW->Integrator_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S37>/Integrator' */
  rtDW->Integrator_PrevResetState_o = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
