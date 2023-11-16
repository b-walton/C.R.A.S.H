#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "JerkMinimizationTest_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block JerkMinimizationTest/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTest_std_msgs_Float64> Sub_JerkMinimizationTest_166;

// For Block JerkMinimizationTest/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTest_std_msgs_Float64> Sub_JerkMinimizationTest_124;

// For Block JerkMinimizationTest/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_JerkMinimizationTest_std_msgs_Float64> Pub_JerkMinimizationTest_121;

void slros_node_init(int argc, char** argv);

#endif
