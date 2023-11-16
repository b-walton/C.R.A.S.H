#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "JerkMinimizationTestOpenLoop_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block JerkMinimizationTestOpenLoop/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64> Sub_JerkMinimizationTestOpenLoop_166;

// For Block JerkMinimizationTestOpenLoop/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64> Sub_JerkMinimizationTestOpenLoop_124;

// For Block JerkMinimizationTestOpenLoop/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64> Pub_JerkMinimizationTestOpenLoop_121;

void slros_node_init(int argc, char** argv);

#endif
