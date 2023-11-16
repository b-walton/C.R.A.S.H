//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: JerkMinimizationTest.cpp
//
// Code generated for Simulink model 'JerkMinimizationTest'.
//
// Model version                  : 8.20
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Wed Nov 15 17:37:14 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "JerkMinimizationTest.h"
#include "rtwtypes.h"
#include "JerkMinimizationTest_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "JerkMinimizationTest_types.h"

// Block signals (default storage)
B_JerkMinimizationTest_T JerkMinimizationTest_B;

// Continuous states
X_JerkMinimizationTest_T JerkMinimizationTest_X;

// Disabled State Vector
XDis_JerkMinimizationTest_T JerkMinimizationTest_XDis;

// Block states (default storage)
DW_JerkMinimizationTest_T JerkMinimizationTest_DW;

// External inputs (root inport signals with default storage)
ExtU_JerkMinimizationTest_T JerkMinimizationTest_U;

// External outputs (root outports fed by signals with default storage)
ExtY_JerkMinimizationTest_T JerkMinimizationTest_Y;

// Real-time model
RT_MODEL_JerkMinimizationTest_T JerkMinimizationTest_M_ =
  RT_MODEL_JerkMinimizationTest_T();
RT_MODEL_JerkMinimizationTest_T *const JerkMinimizationTest_M =
  &JerkMinimizationTest_M_;

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
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
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  JerkMinimizationTest_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  JerkMinimizationTest_step();
  JerkMinimizationTest_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  JerkMinimizationTest_step();
  JerkMinimizationTest_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

//
// Output and update for atomic system:
//    '<S9>/Dead Man's Switch'
//    '<S11>/Dead Man's Switch'
//
void JerkMinimization_DeadMansSwitch(boolean_T rtu_IsNew, real_T rtu_value,
  real_T *rty_safeValue, boolean_T *rty_timedOut, real_T rtp_stepSize, real_T
  rtp_timeout, DW_DeadMansSwitch_JerkMinimiz_T *localDW)
{
  boolean_T timedOut;

  // MATLAB Function: '<S12>/timeout set to 0 output' incorporates:
  //   Constant: '<S12>/Simulate step size'
  //   Constant: '<S12>/Timeout in seconds'

  if (!localDW->sinceLastMsg_not_empty) {
    localDW->sinceLastMsg = rtp_timeout / rtp_stepSize + 1.0;
    localDW->sinceLastMsg_not_empty = true;
  }

  *rty_safeValue = 0.0;
  if (rtu_IsNew) {
    localDW->sinceLastMsg = 0.0;
  } else {
    localDW->sinceLastMsg++;
  }

  timedOut = !(localDW->sinceLastMsg < rtp_timeout / rtp_stepSize);
  if (!timedOut) {
    *rty_safeValue = rtu_value;
  }

  *rty_timedOut = timedOut;

  // End of MATLAB Function: '<S12>/timeout set to 0 output'
}

// Model step function
void JerkMinimizationTest_step(void)
{
  // local block i/o variables
  real_T rtb_Switch2;
  real_T rtb_safeValue;
  boolean_T rtb_SourceBlock_o1;
  SL_Bus_JerkMinimizationTest_std_msgs_Float64 b_varargout_2;
  SL_Bus_JerkMinimizationTest_std_msgs_Float64 rtb_BusAssignment;
  real_T rtb_Memory1_b;
  real_T rtb_Saturation;
  boolean_T rtb_timedOut_f;
  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    // set solver stop time
    rtsiSetSolverStopTime(&JerkMinimizationTest_M->solverInfo,
                          ((JerkMinimizationTest_M->Timing.clockTick0+1)*
      JerkMinimizationTest_M->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep(JerkMinimizationTest_M)) {
    JerkMinimizationTest_M->Timing.t[0] = rtsiGetT
      (&JerkMinimizationTest_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    // Sum: '<Root>/Add' incorporates:
    //   Constant: '<Root>/Constant'
    //   Gain: '<Root>/Gain3'

    rtb_Memory1_b = JerkMinimizationTest_P.Gain3_Gain *
      JerkMinimizationTest_P.Constant_Value_m +
      JerkMinimizationTest_DW.Memory1_PreviousInput;

    // Switch: '<S3>/Switch2' incorporates:
    //   Inport: '<Root>/accel_raw'
    //   RelationalOperator: '<S3>/LowerRelop1'

    if (JerkMinimizationTest_U.accel_raw > rtb_Memory1_b) {
      // Sum: '<Root>/Add1' incorporates:
      //   Switch: '<S3>/Switch2'

      rtb_Switch2 = rtb_Memory1_b;
    } else {
      // Sum: '<Root>/Add1' incorporates:
      //   Constant: '<Root>/Constant'
      //   Gain: '<Root>/Gain2'

      rtb_Switch2 = JerkMinimizationTest_P.Gain2_Gain *
        JerkMinimizationTest_P.Constant_Value_m +
        JerkMinimizationTest_DW.Memory1_PreviousInput;

      // Switch: '<S3>/Switch' incorporates:
      //   RelationalOperator: '<S3>/UpperRelop'

      if (!(JerkMinimizationTest_U.accel_raw < rtb_Switch2)) {
        // Sum: '<Root>/Add1' incorporates:
        //   Switch: '<S3>/Switch2'

        rtb_Switch2 = JerkMinimizationTest_U.accel_raw;
      }

      // End of Switch: '<S3>/Switch'
    }

    // End of Switch: '<S3>/Switch2'

    // Outport: '<Root>/accel_jerk_min'
    JerkMinimizationTest_Y.accel_jerk_min = rtb_Switch2;

    // Memory: '<S10>/Memory1'
    rtb_Memory1_b = JerkMinimizationTest_DW.Memory1_PreviousInput_d;

    // Sum: '<S10>/Add' incorporates:
    //   Constant: '<S10>/Constant'
    //   Gain: '<S10>/Gain3'
    //   Memory: '<S10>/Memory1'

    JerkMinimizationTest_B.Add = JerkMinimizationTest_P.Gain3_Gain_o *
      JerkMinimizationTest_P.Constant_Value_c +
      JerkMinimizationTest_DW.Memory1_PreviousInput_d;

    // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
    // MATLABSystem: '<S5>/SourceBlock'
    rtb_SourceBlock_o1 = Sub_JerkMinimizationTest_124.getLatestMessage
      (&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S8>/Enable'

    if (rtb_SourceBlock_o1) {
      // SignalConversion generated from: '<S8>/In1' incorporates:
      //   MATLABSystem: '<S5>/SourceBlock'
      //
      JerkMinimizationTest_B.In1 = b_varargout_2;
    }

    // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe1'

    // Outputs for Atomic SubSystem: '<S9>/Dead Man's Switch'
    // Outputs for Atomic SubSystem: '<S9>/Dead Man's Switch'
    JerkMinimization_DeadMansSwitch(rtb_SourceBlock_o1,
      JerkMinimizationTest_B.In1.Data, &rtb_safeValue, &rtb_timedOut_f,
      JerkMinimizationTest_P.DeadMansSwitch_stepSize,
      JerkMinimizationTest_P.DeadMansSwitch_timeout,
      &JerkMinimizationTest_DW.DeadMansSwitch);

    // End of Outputs for SubSystem: '<S9>/Dead Man's Switch'
    // End of Outputs for SubSystem: '<S9>/Dead Man's Switch'

    // Gain: '<S51>/Proportional Gain'
    JerkMinimizationTest_B.ProportionalGain =
      JerkMinimizationTest_P.PIDController_P * rtb_safeValue;

    // Gain: '<S40>/Derivative Gain'
    JerkMinimizationTest_B.DerivativeGain =
      JerkMinimizationTest_P.PIDController_D * rtb_safeValue;
  }

  // Gain: '<S49>/Filter Coefficient' incorporates:
  //   Integrator: '<S41>/Filter'
  //   Sum: '<S41>/SumD'

  JerkMinimizationTest_B.FilterCoefficient =
    (JerkMinimizationTest_B.DerivativeGain -
     JerkMinimizationTest_X.Filter_CSTATE) *
    JerkMinimizationTest_P.PIDController_N;

  // Sum: '<S55>/Sum' incorporates:
  //   Integrator: '<S46>/Integrator'

  rtb_Saturation = (JerkMinimizationTest_B.ProportionalGain +
                    JerkMinimizationTest_X.Integrator_CSTATE) +
    JerkMinimizationTest_B.FilterCoefficient;

  // Saturate: '<S53>/Saturation'
  if (rtb_Saturation > JerkMinimizationTest_P.PIDController_UpperSaturationLi) {
    rtb_Saturation = JerkMinimizationTest_P.PIDController_UpperSaturationLi;
  } else if (rtb_Saturation <
             JerkMinimizationTest_P.PIDController_LowerSaturationLi) {
    rtb_Saturation = JerkMinimizationTest_P.PIDController_LowerSaturationLi;
  }

  // End of Saturate: '<S53>/Saturation'
  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    // Sum: '<S10>/Add1' incorporates:
    //   Constant: '<S10>/Constant'
    //   Gain: '<S10>/Gain2'

    JerkMinimizationTest_B.Add1 = JerkMinimizationTest_P.Gain2_Gain_b *
      JerkMinimizationTest_P.Constant_Value_c + rtb_Memory1_b;
  }

  // Switch: '<S63>/Switch2' incorporates:
  //   RelationalOperator: '<S63>/LowerRelop1'
  //   RelationalOperator: '<S63>/UpperRelop'
  //   Switch: '<S63>/Switch'

  if (rtb_Saturation > JerkMinimizationTest_B.Add) {
    // Switch: '<S63>/Switch2'
    JerkMinimizationTest_B.Switch2 = JerkMinimizationTest_B.Add;
  } else if (rtb_Saturation < JerkMinimizationTest_B.Add1) {
    // Switch: '<S63>/Switch' incorporates:
    //   Switch: '<S63>/Switch2'

    JerkMinimizationTest_B.Switch2 = JerkMinimizationTest_B.Add1;
  } else {
    // Switch: '<S63>/Switch2' incorporates:
    //   Switch: '<S63>/Switch'

    JerkMinimizationTest_B.Switch2 = rtb_Saturation;
  }

  // End of Switch: '<S63>/Switch2'
  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    // Outputs for Atomic SubSystem: '<Root>/Subscribe'
    // MATLABSystem: '<S4>/SourceBlock'
    rtb_timedOut_f = Sub_JerkMinimizationTest_166.getLatestMessage
      (&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S7>/Enable'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    if (rtb_timedOut_f) {
      // SignalConversion generated from: '<S7>/In1'
      JerkMinimizationTest_B.In1_i = b_varargout_2;
    }

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe'

    // Outputs for Atomic SubSystem: '<S11>/Dead Man's Switch'
    // Outputs for Atomic SubSystem: '<S11>/Dead Man's Switch'
    JerkMinimization_DeadMansSwitch(rtb_SourceBlock_o1,
      JerkMinimizationTest_B.In1_i.Data, &JerkMinimizationTest_B.safeValue,
      &rtb_timedOut_f, JerkMinimizationTest_P.DeadMansSwitch_stepSize_d,
      JerkMinimizationTest_P.DeadMansSwitch_timeout_m,
      &JerkMinimizationTest_DW.DeadMansSwitch_e);

    // End of Outputs for SubSystem: '<S11>/Dead Man's Switch'
    // End of Outputs for SubSystem: '<S11>/Dead Man's Switch'
  }

  // Product: '<S6>/Product1' incorporates:
  //   Constant: '<S6>/Constant1'
  //   Gain: '<S6>/Gain'
  //   Gain: '<S6>/Gain1'
  //   Product: '<S6>/Product'
  //   Sum: '<S6>/Subtract'
  //   Sum: '<S6>/Sum'

  rtb_Saturation = (JerkMinimizationTest_B.safeValue -
                    (JerkMinimizationTest_B.Switch2 *
                     JerkMinimizationTest_P.Constant1_Value + rtb_Saturation) *
                    JerkMinimizationTest_P.Gain_Gain) *
    JerkMinimizationTest_P.Gain1_Gain * JerkMinimizationTest_B.Switch2;

  // MinMax: '<S6>/MinMax'
  if ((JerkMinimizationTest_B.Switch2 <= rtb_Saturation) || rtIsNaN
      (rtb_Saturation)) {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = JerkMinimizationTest_B.Switch2;
  } else {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = rtb_Saturation;
  }

  // End of MinMax: '<S6>/MinMax'

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // MATLABSystem: '<S2>/SinkBlock'
  Pub_JerkMinimizationTest_121.publish(&rtb_BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'
  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    // Gain: '<S43>/Integral Gain'
    JerkMinimizationTest_B.IntegralGain = JerkMinimizationTest_P.PIDController_I
      * rtb_safeValue;
  }

  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
      // Update for Memory: '<Root>/Memory1'
      JerkMinimizationTest_DW.Memory1_PreviousInput = rtb_Switch2;

      // Update for Memory: '<S10>/Memory1'
      JerkMinimizationTest_DW.Memory1_PreviousInput_d =
        JerkMinimizationTest_B.Switch2;
    }
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep(JerkMinimizationTest_M)) {
    rt_ertODEUpdateContinuousStates(&JerkMinimizationTest_M->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++JerkMinimizationTest_M->Timing.clockTick0;
    JerkMinimizationTest_M->Timing.t[0] = rtsiGetSolverStopTime
      (&JerkMinimizationTest_M->solverInfo);

    {
      // Update absolute timer for sample time: [0.05s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.05, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      JerkMinimizationTest_M->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void JerkMinimizationTest_derivatives(void)
{
  XDot_JerkMinimizationTest_T *_rtXdot;
  _rtXdot = ((XDot_JerkMinimizationTest_T *) JerkMinimizationTest_M->derivs);

  // Derivatives for Integrator: '<S46>/Integrator'
  _rtXdot->Integrator_CSTATE = JerkMinimizationTest_B.IntegralGain;

  // Derivatives for Integrator: '<S41>/Filter'
  _rtXdot->Filter_CSTATE = JerkMinimizationTest_B.FilterCoefficient;
}

// Model initialize function
void JerkMinimizationTest_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&JerkMinimizationTest_M->solverInfo,
                          &JerkMinimizationTest_M->Timing.simTimeStep);
    rtsiSetTPtr(&JerkMinimizationTest_M->solverInfo, &rtmGetTPtr
                (JerkMinimizationTest_M));
    rtsiSetStepSizePtr(&JerkMinimizationTest_M->solverInfo,
                       &JerkMinimizationTest_M->Timing.stepSize0);
    rtsiSetdXPtr(&JerkMinimizationTest_M->solverInfo,
                 &JerkMinimizationTest_M->derivs);
    rtsiSetContStatesPtr(&JerkMinimizationTest_M->solverInfo, (real_T **)
                         &JerkMinimizationTest_M->contStates);
    rtsiSetNumContStatesPtr(&JerkMinimizationTest_M->solverInfo,
      &JerkMinimizationTest_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&JerkMinimizationTest_M->solverInfo,
      &JerkMinimizationTest_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&JerkMinimizationTest_M->solverInfo,
      &JerkMinimizationTest_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&JerkMinimizationTest_M->solverInfo,
      &JerkMinimizationTest_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&JerkMinimizationTest_M->solverInfo, (boolean_T**)
      &JerkMinimizationTest_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&JerkMinimizationTest_M->solverInfo,
                          (&rtmGetErrorStatus(JerkMinimizationTest_M)));
    rtsiSetRTModelPtr(&JerkMinimizationTest_M->solverInfo,
                      JerkMinimizationTest_M);
  }

  rtsiSetSimTimeStep(&JerkMinimizationTest_M->solverInfo, MAJOR_TIME_STEP);
  JerkMinimizationTest_M->intgData.y = JerkMinimizationTest_M->odeY;
  JerkMinimizationTest_M->intgData.f[0] = JerkMinimizationTest_M->odeF[0];
  JerkMinimizationTest_M->intgData.f[1] = JerkMinimizationTest_M->odeF[1];
  JerkMinimizationTest_M->intgData.f[2] = JerkMinimizationTest_M->odeF[2];
  JerkMinimizationTest_M->contStates = ((X_JerkMinimizationTest_T *)
    &JerkMinimizationTest_X);
  JerkMinimizationTest_M->contStateDisabled = ((XDis_JerkMinimizationTest_T *)
    &JerkMinimizationTest_XDis);
  JerkMinimizationTest_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&JerkMinimizationTest_M->solverInfo, static_cast<void *>
                    (&JerkMinimizationTest_M->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&JerkMinimizationTest_M->solverInfo,
    false);
  rtsiSetSolverName(&JerkMinimizationTest_M->solverInfo,"ode3");
  rtmSetTPtr(JerkMinimizationTest_M, &JerkMinimizationTest_M->Timing.tArray[0]);
  JerkMinimizationTest_M->Timing.stepSize0 = 0.05;

  {
    int32_T i;
    char_T b_zeroDelimTopic_1[15];
    char_T b_zeroDelimTopic_0[11];
    char_T b_zeroDelimTopic[9];
    static const char_T b_zeroDelimTopic_2[9] = "/rel_vel";
    static const char_T b_zeroDelimTopic_3[11] = "/lead_dist";
    static const char_T b_zeroDelimTopic_4[15] = "/cmd_accel_sim";

    // InitializeConditions for Memory: '<Root>/Memory1'
    JerkMinimizationTest_DW.Memory1_PreviousInput =
      JerkMinimizationTest_P.Memory1_InitialCondition;

    // InitializeConditions for Memory: '<S10>/Memory1'
    JerkMinimizationTest_DW.Memory1_PreviousInput_d =
      JerkMinimizationTest_P.Memory1_InitialCondition_o;

    // InitializeConditions for Integrator: '<S46>/Integrator'
    JerkMinimizationTest_X.Integrator_CSTATE =
      JerkMinimizationTest_P.PIDController_InitialConditio_k;

    // InitializeConditions for Integrator: '<S41>/Filter'
    JerkMinimizationTest_X.Filter_CSTATE =
      JerkMinimizationTest_P.PIDController_InitialConditionF;

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    JerkMinimizationTest_B.In1 = JerkMinimizationTest_P.Out1_Y0_h;

    // End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem'

    // Start for MATLABSystem: '<S5>/SourceBlock'
    JerkMinimizationTest_DW.obj_d.matlabCodegenIsDeleted = false;
    JerkMinimizationTest_DW.obj_d.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_2[i];
    }

    Sub_JerkMinimizationTest_124.createSubscriber(&b_zeroDelimTopic[0], 1);
    JerkMinimizationTest_DW.obj_d.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S7>/In1' incorporates:
    //   Outport: '<S7>/Out1'

    JerkMinimizationTest_B.In1_i = JerkMinimizationTest_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    JerkMinimizationTest_DW.obj_n.matlabCodegenIsDeleted = false;
    JerkMinimizationTest_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_3[i];
    }

    Sub_JerkMinimizationTest_166.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    JerkMinimizationTest_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S2>/SinkBlock'
    JerkMinimizationTest_DW.obj.matlabCodegenIsDeleted = false;
    JerkMinimizationTest_DW.obj.isInitialized = 1;
    for (i = 0; i < 15; i++) {
      b_zeroDelimTopic_1[i] = b_zeroDelimTopic_4[i];
    }

    Pub_JerkMinimizationTest_121.createPublisher(&b_zeroDelimTopic_1[0], 1);
    JerkMinimizationTest_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S2>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish'
  }
}

// Model terminate function
void JerkMinimizationTest_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!JerkMinimizationTest_DW.obj_d.matlabCodegenIsDeleted) {
    JerkMinimizationTest_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!JerkMinimizationTest_DW.obj_n.matlabCodegenIsDeleted) {
    JerkMinimizationTest_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S2>/SinkBlock'
  if (!JerkMinimizationTest_DW.obj.matlabCodegenIsDeleted) {
    JerkMinimizationTest_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S2>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
