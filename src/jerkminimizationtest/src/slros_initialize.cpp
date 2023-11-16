#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "JerkMinimizationTest";

// For Block JerkMinimizationTest/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTest_std_msgs_Float64> Sub_JerkMinimizationTest_166;

// For Block JerkMinimizationTest/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_JerkMinimizationTest_std_msgs_Float64> Sub_JerkMinimizationTest_124;

// For Block JerkMinimizationTest/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_JerkMinimizationTest_std_msgs_Float64> Pub_JerkMinimizationTest_121;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

