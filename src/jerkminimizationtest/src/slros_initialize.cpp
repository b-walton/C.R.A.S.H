#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "JerkMinimizationTestOpenLoop";

// For Block JerkMinimizationTestOpenLoop/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64> Sub_JerkMinimizationTestOpenLoop_166;

// For Block JerkMinimizationTestOpenLoop/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64> Sub_JerkMinimizationTestOpenLoop_124;

// For Block JerkMinimizationTestOpenLoop/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_JerkMinimizationTestOpenLoop_std_msgs_Float64> Pub_JerkMinimizationTestOpenLoop_121;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

