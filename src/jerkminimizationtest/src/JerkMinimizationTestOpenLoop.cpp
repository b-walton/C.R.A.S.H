//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: JerkMinimizationTestOpenLoop.cpp
//
// Code generated for Simulink model 'JerkMinimizationTestOpenLoop'.
//
// Model version                  : 8.22
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Nov 16 10:48:31 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "JerkMinimizationTestOpenLoop.h"
#include "rtwtypes.h"
#include "JerkMinimizationTestOpenLoop_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "JerkMinimizationTestOpenLoop_types.h"

// Block signals (default storage)
B_JerkMinimizationTestOpenLoo_T JerkMinimizationTestOpenLoop_B;

// Continuous states
X_JerkMinimizationTestOpenLoo_T JerkMinimizationTestOpenLoop_X;

// Disabled State Vector
XDis_JerkMinimizationTestOpen_T JerkMinimizationTestOpenLo_XDis;

// Block states (default storage)
DW_JerkMinimizationTestOpenLo_T JerkMinimizationTestOpenLoop_DW;

// External inputs (root inport signals with default storage)
ExtU_JerkMinimizationTestOpen_T JerkMinimizationTestOpenLoop_U;

// External outputs (root outports fed by signals with default storage)
ExtY_JerkMinimizationTestOpen_T JerkMinimizationTestOpenLoop_Y;

// Real-time model
RT_MODEL_JerkMinimizationTest_T JerkMinimizationTestOpenLoop_M_ =
  RT_MODEL_JerkMinimizationTest_T();
RT_MODEL_JerkMinimizationTest_T *const JerkMinimizationTestOpenLoop_M =
  &JerkMinimizationTestOpenLoop_M_;

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
  JerkMinimizationTestOpenLoop_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  JerkMinimizationTestOpenLoop_step();
  JerkMinimizationTestOpenLoop_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  JerkMinimizationTestOpenLoop_step();
  JerkMinimizationTestOpenLoop_derivatives();

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
void JerkMinimizationTestOpenLoop_step(void)
{
  // local block i/o variables
  real_T rtb_Switch2;
  real_T rtb_safeValue;
  boolean_T rtb_SourceBlock_o1;
  SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64 b_varargout_2;
  SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64 rtb_BusAssignment;
  real_T rtb_Memory1_p;
  real_T rtb_Saturation;
  boolean_T rtb_timedOut_b;
  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    // set solver stop time
    rtsiSetSolverStopTime(&JerkMinimizationTestOpenLoop_M->solverInfo,
                          ((JerkMinimizationTestOpenLoop_M->Timing.clockTick0+1)*
      JerkMinimizationTestOpenLoop_M->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    JerkMinimizationTestOpenLoop_M->Timing.t[0] = rtsiGetT
      (&JerkMinimizationTestOpenLoop_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    // Sum: '<Root>/Add' incorporates:
    //   Constant: '<Root>/Constant'
    //   Gain: '<Root>/Gain3'

    rtb_Memory1_p = JerkMinimizationTestOpenLoop_P.Gain3_Gain *
      JerkMinimizationTestOpenLoop_P.Constant_Value_m +
      JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput;

    // Switch: '<S3>/Switch2' incorporates:
    //   Inport: '<Root>/accel_raw'
    //   RelationalOperator: '<S3>/LowerRelop1'

    if (JerkMinimizationTestOpenLoop_U.accel_raw > rtb_Memory1_p) {
      // Sum: '<Root>/Add1' incorporates:
      //   Switch: '<S3>/Switch2'

      rtb_Switch2 = rtb_Memory1_p;
    } else {
      // Sum: '<Root>/Add1' incorporates:
      //   Constant: '<Root>/Constant'
      //   Gain: '<Root>/Gain2'

      rtb_Switch2 = JerkMinimizationTestOpenLoop_P.Gain2_Gain *
        JerkMinimizationTestOpenLoop_P.Constant_Value_m +
        JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput;

      // Switch: '<S3>/Switch' incorporates:
      //   RelationalOperator: '<S3>/UpperRelop'

      if (!(JerkMinimizationTestOpenLoop_U.accel_raw < rtb_Switch2)) {
        // Sum: '<Root>/Add1' incorporates:
        //   Switch: '<S3>/Switch2'

        rtb_Switch2 = JerkMinimizationTestOpenLoop_U.accel_raw;
      }

      // End of Switch: '<S3>/Switch'
    }

    // End of Switch: '<S3>/Switch2'

    // Outport: '<Root>/accel_jerk_min'
    JerkMinimizationTestOpenLoop_Y.accel_jerk_min = rtb_Switch2;

    // Memory: '<S10>/Memory1'
    rtb_Memory1_p = JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput_c;

    // Sum: '<S10>/Add' incorporates:
    //   Constant: '<S10>/Constant'
    //   Gain: '<S10>/Gain3'
    //   Memory: '<S10>/Memory1'

    JerkMinimizationTestOpenLoop_B.Add =
      JerkMinimizationTestOpenLoop_P.Gain3_Gain_h *
      JerkMinimizationTestOpenLoop_P.Constant_Value_b +
      JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput_c;

    // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
    // MATLABSystem: '<S5>/SourceBlock'
    rtb_SourceBlock_o1 = Sub_JerkMinimizationTestOpenLoop_124.getLatestMessage
      (&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S8>/Enable'

    if (rtb_SourceBlock_o1) {
      // SignalConversion generated from: '<S8>/In1' incorporates:
      //   MATLABSystem: '<S5>/SourceBlock'
      //
      JerkMinimizationTestOpenLoop_B.In1 = b_varargout_2;
    }

    // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe1'

    // Outputs for Atomic SubSystem: '<S9>/Dead Man's Switch'
    // Outputs for Atomic SubSystem: '<S9>/Dead Man's Switch'
    JerkMinimization_DeadMansSwitch(rtb_SourceBlock_o1,
      JerkMinimizationTestOpenLoop_B.In1.Data, &rtb_safeValue, &rtb_timedOut_b,
      JerkMinimizationTestOpenLoop_P.DeadMansSwitch_stepSize,
      JerkMinimizationTestOpenLoop_P.DeadMansSwitch_timeout,
      &JerkMinimizationTestOpenLoop_DW.DeadMansSwitch);

    // End of Outputs for SubSystem: '<S9>/Dead Man's Switch'
    // End of Outputs for SubSystem: '<S9>/Dead Man's Switch'

    // Gain: '<S51>/Proportional Gain'
    JerkMinimizationTestOpenLoop_B.ProportionalGain =
      JerkMinimizationTestOpenLoop_P.PIDController_P * rtb_safeValue;

    // Gain: '<S40>/Derivative Gain'
    JerkMinimizationTestOpenLoop_B.DerivativeGain =
      JerkMinimizationTestOpenLoop_P.PIDController_D * rtb_safeValue;
  }

  // Gain: '<S49>/Filter Coefficient' incorporates:
  //   Integrator: '<S41>/Filter'
  //   Sum: '<S41>/SumD'

  JerkMinimizationTestOpenLoop_B.FilterCoefficient =
    (JerkMinimizationTestOpenLoop_B.DerivativeGain -
     JerkMinimizationTestOpenLoop_X.Filter_CSTATE) *
    JerkMinimizationTestOpenLoop_P.PIDController_N;

  // Sum: '<S55>/Sum' incorporates:
  //   Integrator: '<S46>/Integrator'

  rtb_Saturation = (JerkMinimizationTestOpenLoop_B.ProportionalGain +
                    JerkMinimizationTestOpenLoop_X.Integrator_CSTATE) +
    JerkMinimizationTestOpenLoop_B.FilterCoefficient;

  // Saturate: '<S53>/Saturation'
  if (rtb_Saturation >
      JerkMinimizationTestOpenLoop_P.PIDController_UpperSaturationLi) {
    rtb_Saturation =
      JerkMinimizationTestOpenLoop_P.PIDController_UpperSaturationLi;
  } else if (rtb_Saturation <
             JerkMinimizationTestOpenLoop_P.PIDController_LowerSaturationLi) {
    rtb_Saturation =
      JerkMinimizationTestOpenLoop_P.PIDController_LowerSaturationLi;
  }

  // End of Saturate: '<S53>/Saturation'
  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    // Sum: '<S10>/Add1' incorporates:
    //   Constant: '<S10>/Constant'
    //   Gain: '<S10>/Gain2'

    JerkMinimizationTestOpenLoop_B.Add1 =
      JerkMinimizationTestOpenLoop_P.Gain2_Gain_d *
      JerkMinimizationTestOpenLoop_P.Constant_Value_b + rtb_Memory1_p;
  }

  // Switch: '<S63>/Switch2' incorporates:
  //   RelationalOperator: '<S63>/LowerRelop1'
  //   RelationalOperator: '<S63>/UpperRelop'
  //   Switch: '<S63>/Switch'

  if (rtb_Saturation > JerkMinimizationTestOpenLoop_B.Add) {
    // Switch: '<S63>/Switch2'
    JerkMinimizationTestOpenLoop_B.Switch2 = JerkMinimizationTestOpenLoop_B.Add;
  } else if (rtb_Saturation < JerkMinimizationTestOpenLoop_B.Add1) {
    // Switch: '<S63>/Switch' incorporates:
    //   Switch: '<S63>/Switch2'

    JerkMinimizationTestOpenLoop_B.Switch2 = JerkMinimizationTestOpenLoop_B.Add1;
  } else {
    // Switch: '<S63>/Switch2' incorporates:
    //   Switch: '<S63>/Switch'

    JerkMinimizationTestOpenLoop_B.Switch2 = rtb_Saturation;
  }

  // End of Switch: '<S63>/Switch2'
  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    // Outputs for Atomic SubSystem: '<Root>/Subscribe'
    // MATLABSystem: '<S4>/SourceBlock'
    rtb_timedOut_b = Sub_JerkMinimizationTestOpenLoop_166.getLatestMessage
      (&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S7>/Enable'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    if (rtb_timedOut_b) {
      // SignalConversion generated from: '<S7>/In1'
      JerkMinimizationTestOpenLoop_B.In1_i = b_varargout_2;
    }

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe'

    // Outputs for Atomic SubSystem: '<S11>/Dead Man's Switch'
    // Outputs for Atomic SubSystem: '<S11>/Dead Man's Switch'
    JerkMinimization_DeadMansSwitch(rtb_SourceBlock_o1,
      JerkMinimizationTestOpenLoop_B.In1_i.Data,
      &JerkMinimizationTestOpenLoop_B.safeValue, &rtb_timedOut_b,
      JerkMinimizationTestOpenLoop_P.DeadMansSwitch_stepSize_m,
      JerkMinimizationTestOpenLoop_P.DeadMansSwitch_timeout_j,
      &JerkMinimizationTestOpenLoop_DW.DeadMansSwitch_a);

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

  rtb_Saturation = (JerkMinimizationTestOpenLoop_B.safeValue -
                    (JerkMinimizationTestOpenLoop_B.Switch2 *
                     JerkMinimizationTestOpenLoop_P.Constant1_Value +
                     rtb_Saturation) * JerkMinimizationTestOpenLoop_P.Gain_Gain)
    * JerkMinimizationTestOpenLoop_P.Gain1_Gain *
    JerkMinimizationTestOpenLoop_B.Switch2;

  // MinMax: '<S6>/MinMax'
  if ((JerkMinimizationTestOpenLoop_B.Switch2 <= rtb_Saturation) || rtIsNaN
      (rtb_Saturation)) {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = JerkMinimizationTestOpenLoop_B.Switch2;
  } else {
    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = rtb_Saturation;
  }

  // End of MinMax: '<S6>/MinMax'

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // MATLABSystem: '<S2>/SinkBlock'
  Pub_JerkMinimizationTestOpenLoop_121.publish(&rtb_BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'
  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    // Gain: '<S43>/Integral Gain'
    JerkMinimizationTestOpenLoop_B.IntegralGain =
      JerkMinimizationTestOpenLoop_P.PIDController_I * rtb_safeValue;
  }

  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
      // Update for Memory: '<Root>/Memory1'
      JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput = rtb_Switch2;

      // Update for Memory: '<S10>/Memory1'
      JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput_c =
        JerkMinimizationTestOpenLoop_B.Switch2;
    }
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep(JerkMinimizationTestOpenLoop_M)) {
    rt_ertODEUpdateContinuousStates(&JerkMinimizationTestOpenLoop_M->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++JerkMinimizationTestOpenLoop_M->Timing.clockTick0;
    JerkMinimizationTestOpenLoop_M->Timing.t[0] = rtsiGetSolverStopTime
      (&JerkMinimizationTestOpenLoop_M->solverInfo);

    {
      // Update absolute timer for sample time: [0.05s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.05, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      JerkMinimizationTestOpenLoop_M->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void JerkMinimizationTestOpenLoop_derivatives(void)
{
  XDot_JerkMinimizationTestOpen_T *_rtXdot;
  _rtXdot = ((XDot_JerkMinimizationTestOpen_T *)
             JerkMinimizationTestOpenLoop_M->derivs);

  // Derivatives for Integrator: '<S46>/Integrator'
  _rtXdot->Integrator_CSTATE = JerkMinimizationTestOpenLoop_B.IntegralGain;

  // Derivatives for Integrator: '<S41>/Filter'
  _rtXdot->Filter_CSTATE = JerkMinimizationTestOpenLoop_B.FilterCoefficient;
}

// Model initialize function
void JerkMinimizationTestOpenLoop_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
                          &JerkMinimizationTestOpenLoop_M->Timing.simTimeStep);
    rtsiSetTPtr(&JerkMinimizationTestOpenLoop_M->solverInfo, &rtmGetTPtr
                (JerkMinimizationTestOpenLoop_M));
    rtsiSetStepSizePtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
                       &JerkMinimizationTestOpenLoop_M->Timing.stepSize0);
    rtsiSetdXPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
                 &JerkMinimizationTestOpenLoop_M->derivs);
    rtsiSetContStatesPtr(&JerkMinimizationTestOpenLoop_M->solverInfo, (real_T **)
                         &JerkMinimizationTestOpenLoop_M->contStates);
    rtsiSetNumContStatesPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
      &JerkMinimizationTestOpenLoop_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
      &JerkMinimizationTestOpenLoop_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (&JerkMinimizationTestOpenLoop_M->solverInfo,
       &JerkMinimizationTestOpenLoop_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr
      (&JerkMinimizationTestOpenLoop_M->solverInfo,
       &JerkMinimizationTestOpenLoop_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
      (boolean_T**) &JerkMinimizationTestOpenLoop_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
                          (&rtmGetErrorStatus(JerkMinimizationTestOpenLoop_M)));
    rtsiSetRTModelPtr(&JerkMinimizationTestOpenLoop_M->solverInfo,
                      JerkMinimizationTestOpenLoop_M);
  }

  rtsiSetSimTimeStep(&JerkMinimizationTestOpenLoop_M->solverInfo,
                     MAJOR_TIME_STEP);
  JerkMinimizationTestOpenLoop_M->intgData.y =
    JerkMinimizationTestOpenLoop_M->odeY;
  JerkMinimizationTestOpenLoop_M->intgData.f[0] =
    JerkMinimizationTestOpenLoop_M->odeF[0];
  JerkMinimizationTestOpenLoop_M->intgData.f[1] =
    JerkMinimizationTestOpenLoop_M->odeF[1];
  JerkMinimizationTestOpenLoop_M->intgData.f[2] =
    JerkMinimizationTestOpenLoop_M->odeF[2];
  JerkMinimizationTestOpenLoop_M->contStates = ((X_JerkMinimizationTestOpenLoo_T
    *) &JerkMinimizationTestOpenLoop_X);
  JerkMinimizationTestOpenLoop_M->contStateDisabled =
    ((XDis_JerkMinimizationTestOpen_T *) &JerkMinimizationTestOpenLo_XDis);
  JerkMinimizationTestOpenLoop_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&JerkMinimizationTestOpenLoop_M->solverInfo, static_cast<
                    void *>(&JerkMinimizationTestOpenLoop_M->intgData));
  rtsiSetIsMinorTimeStepWithModeChange
    (&JerkMinimizationTestOpenLoop_M->solverInfo, false);
  rtsiSetSolverName(&JerkMinimizationTestOpenLoop_M->solverInfo,"ode3");
  rtmSetTPtr(JerkMinimizationTestOpenLoop_M,
             &JerkMinimizationTestOpenLoop_M->Timing.tArray[0]);
  JerkMinimizationTestOpenLoop_M->Timing.stepSize0 = 0.05;

  {
    int32_T i;
    char_T b_zeroDelimTopic_0[11];
    char_T b_zeroDelimTopic[9];
    static const char_T b_zeroDelimTopic_1[9] = "/rel_vel";
    static const char_T b_zeroDelimTopic_2[11] = "/lead_dist";
    static const char_T b_zeroDelimTopic_3[11] = "/cmd_accel";

    // InitializeConditions for Memory: '<Root>/Memory1'
    JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput =
      JerkMinimizationTestOpenLoop_P.Memory1_InitialCondition;

    // InitializeConditions for Memory: '<S10>/Memory1'
    JerkMinimizationTestOpenLoop_DW.Memory1_PreviousInput_c =
      JerkMinimizationTestOpenLoop_P.Memory1_InitialCondition_c;

    // InitializeConditions for Integrator: '<S46>/Integrator'
    JerkMinimizationTestOpenLoop_X.Integrator_CSTATE =
      JerkMinimizationTestOpenLoop_P.PIDController_InitialConditio_k;

    // InitializeConditions for Integrator: '<S41>/Filter'
    JerkMinimizationTestOpenLoop_X.Filter_CSTATE =
      JerkMinimizationTestOpenLoop_P.PIDController_InitialConditionF;

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    JerkMinimizationTestOpenLoop_B.In1 =
      JerkMinimizationTestOpenLoop_P.Out1_Y0_h;

    // End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem'

    // Start for MATLABSystem: '<S5>/SourceBlock'
    JerkMinimizationTestOpenLoop_DW.obj_d.matlabCodegenIsDeleted = false;
    JerkMinimizationTestOpenLoop_DW.obj_d.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_1[i];
    }

    Sub_JerkMinimizationTestOpenLoop_124.createSubscriber(&b_zeroDelimTopic[0],
      1);
    JerkMinimizationTestOpenLoop_DW.obj_d.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S7>/In1' incorporates:
    //   Outport: '<S7>/Out1'

    JerkMinimizationTestOpenLoop_B.In1_i =
      JerkMinimizationTestOpenLoop_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    JerkMinimizationTestOpenLoop_DW.obj_n.matlabCodegenIsDeleted = false;
    JerkMinimizationTestOpenLoop_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_2[i];
    }

    Sub_JerkMinimizationTestOpenLoop_166.createSubscriber(&b_zeroDelimTopic_0[0],
      1);
    JerkMinimizationTestOpenLoop_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S2>/SinkBlock'
    JerkMinimizationTestOpenLoop_DW.obj.matlabCodegenIsDeleted = false;
    JerkMinimizationTestOpenLoop_DW.obj.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_3[i];
    }

    Pub_JerkMinimizationTestOpenLoop_121.createPublisher(&b_zeroDelimTopic_0[0],
      1);
    JerkMinimizationTestOpenLoop_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S2>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish'
  }
}

// Model terminate function
void JerkMinimizationTestOpenLoop_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!JerkMinimizationTestOpenLoop_DW.obj_d.matlabCodegenIsDeleted) {
    JerkMinimizationTestOpenLoop_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!JerkMinimizationTestOpenLoop_DW.obj_n.matlabCodegenIsDeleted) {
    JerkMinimizationTestOpenLoop_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S2>/SinkBlock'
  if (!JerkMinimizationTestOpenLoop_DW.obj.matlabCodegenIsDeleted) {
    JerkMinimizationTestOpenLoop_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S2>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
