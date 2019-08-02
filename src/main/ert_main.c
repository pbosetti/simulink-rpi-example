/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'linax0'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Fri Aug  2 13:26:22 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "../linax0.h"                    /* Model's header file */
#include "../rtwtypes.h"
#include "../zero_crossing_types.h"
#include "../lcfg.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_; /* Real-time model */
static DW rtDW;                        /* Observable states */
static X rtX;                          /* Observable continuous states */
static PrevZCX rtPrevZCX;              /* Triggered events */

/* '<Root>/setpoint' */
static real_T rtU_setpoint[3];

/* '<Root>/reset' */
static real_T rtU_reset;

/* '<Root>/x' */
static real_T rtY_x[3];

/* '<Root>/xdot' */
static real_T rtY_xdot[3];

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlags[3] = { 0, 0, 0 };

  static boolean_T eventFlags[3] = { 0, 0, 0 };/* Model has 3 rates */

  static int_T taskCounter[3] = { 0, 0, 0 };

  /* Disable interrupts here */

  /* Check base rate for overrun */
  if (OverrunFlags[0]) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlags[0] = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */

  /*
   * For a bare-board target (i.e., no operating system), the
   * following code checks whether any subrate overruns,
   * and also sets the rates that need to run this time step.
   */
  if (taskCounter[2] == 0) {
    if (eventFlags[2]) {
      OverrunFlags[0] = false;
      OverrunFlags[2] = true;

      /* Sampling too fast */
      rtmSetErrorStatus(rtM, "Overrun");
      return;
    }

    eventFlags[2] = true;
  }

  taskCounter[1]++;
  if (taskCounter[1] == 1) {
    taskCounter[1]= 0;
  }

  taskCounter[2]++;
  if (taskCounter[2] == 5) {
    taskCounter[2]= 0;
  }

  /* Set model inputs associated with base rate here */

  /* Step the model for base rate */
  linax0_step0(rtM, rtU_setpoint, rtU_reset, rtY_x, rtY_xdot);

  /* Get model outputs here */

  /* Indicate task for base rate complete */
  OverrunFlags[0] = false;

  /* If task 1 is running, don't run any lower priority task */
  if (OverrunFlags[1]) {
    return;
  }

  /* Step the model for subrate */
  if (eventFlags[2]) {
    OverrunFlags[2] = true;

    /* Set model inputs associated with subrates here */

    /* Step the model for subrate 2 */
    linax0_step2(rtM, rtU_reset);

    /* Get model outputs here */

    /* Indicate task complete for subrate */
    OverrunFlags[2] = false;
    eventFlags[2] = false;
  }

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  struct lcfg *cfg = NULL;
  RT_MODEL *const rtM = rtMPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  
  if (!(cfg = cfg_new("linax configuration", "./cfg.lua"))) {
    exit(EXIT_FAILURE);
  }

  AX_params.m[0] = cfg_get_data(cfg, "x.m");
  AX_params.c[0] = cfg_get_data(cfg, "x.c");
  PID_params.P[0] = cfg_get_data(cfg, "x.P");
  PID_params.I[0] = cfg_get_data(cfg, "x.I");
  PID_params.D[0] = cfg_get_data(cfg, "x.D");
  PID_params.sat[0] = cfg_get_data(cfg, "x.sat");

  AX_params.m[1] = cfg_get_data(cfg, "y.m");
  AX_params.c[1] = cfg_get_data(cfg, "y.c");
  PID_params.P[1] = cfg_get_data(cfg, "y.P");
  PID_params.I[1] = cfg_get_data(cfg, "y.I");
  PID_params.D[1] = cfg_get_data(cfg, "y.D");
  PID_params.sat[1] = cfg_get_data(cfg, "y.sat");

  AX_params.m[2] = cfg_get_data(cfg, "z.m");
  AX_params.c[2] = cfg_get_data(cfg, "z.c");
  PID_params.P[2] = cfg_get_data(cfg, "z.P");
  PID_params.I[2] = cfg_get_data(cfg, "z.I");
  PID_params.D[2] = cfg_get_data(cfg, "z.D");
  PID_params.sat[2] = cfg_get_data(cfg, "z.sat");
  cfg_free(cfg);

  /* Pack model data into RTM */
  rtM->dwork = &rtDW;
  rtM->contStates = &rtX;
  rtM->prevZCSigState = &rtPrevZCX;

  /* Initialize model */
  linax0_initialize(rtM);
  rtU_setpoint[0] = 0.0;
  rtU_setpoint[1] = 0.0;
  rtU_setpoint[2] = 0.0;

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  printf("t, x, y, z, xdot, ydot, zdot\n");
  while ((rtmGetErrorStatus(rtM) == (NULL)) && !rtmGetStopRequested(rtM)) {
    if (rtmGetT(rtM) >= 0.1) {
      rtU_setpoint[0] = 1.0;
      rtU_setpoint[1] = 1.0;
      rtU_setpoint[2] = 1.0;
    }
    rt_OneStep(rtM);
    printf("%f, %f, %f, %f, %f, %f, %f\n", rtmGetT(rtM), rtY_x[0], rtY_x[1], rtY_x[2], rtY_xdot[0], rtY_xdot[1], rtY_xdot[2]);
    if (rtmGetT(rtM) >= 1.0) {
      rtmSetStopRequested(rtM, true);
    }
  }

  /* Disable rt_OneStep() here */
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
