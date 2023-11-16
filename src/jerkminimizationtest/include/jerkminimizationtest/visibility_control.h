#ifndef JERKMINIMIZATIONTEST__VISIBILITY_CONTROL_H_
#define JERKMINIMIZATIONTEST__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define JERKMINIMIZATIONTEST_EXPORT __attribute__ ((dllexport))
    #define JERKMINIMIZATIONTEST_IMPORT __attribute__ ((dllimport))
  #else
    #define JERKMINIMIZATIONTEST_EXPORT __declspec(dllexport)
    #define JERKMINIMIZATIONTEST_IMPORT __declspec(dllimport)
  #endif
  #ifdef JERKMINIMIZATIONTEST_BUILDING_LIBRARY
    #define JERKMINIMIZATIONTEST_PUBLIC JERKMINIMIZATIONTEST_EXPORT
  #else
    #define JERKMINIMIZATIONTEST_PUBLIC JERKMINIMIZATIONTEST_IMPORT
  #endif
  #define JERKMINIMIZATIONTEST_PUBLIC_TYPE JERKMINIMIZATIONTEST_PUBLIC
  #define JERKMINIMIZATIONTEST_LOCAL
#else
  #define JERKMINIMIZATIONTEST_EXPORT __attribute__ ((visibility("default")))
  #define JERKMINIMIZATIONTEST_IMPORT
  #if __GNUC__ >= 4
    #define JERKMINIMIZATIONTEST_PUBLIC __attribute__ ((visibility("default")))
    #define JERKMINIMIZATIONTEST_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define JERKMINIMIZATIONTEST_PUBLIC
    #define JERKMINIMIZATIONTEST_LOCAL
  #endif
  #define JERKMINIMIZATIONTEST_PUBLIC_TYPE
#endif
#endif  // JERKMINIMIZATIONTEST__VISIBILITY_CONTROL_H_
// Generated 15-Nov-2023 17:38:21
// Copyright 2019-2020 The MathWorks, Inc.
