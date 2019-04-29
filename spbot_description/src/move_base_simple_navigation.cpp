#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "simple_navigation_goals_node");

    //tell the action client to spin thread by default TODO understand better
    MoveBaseClient ac("move_base", true);

    //wait for action server to come up 
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("waiting for the move_base action server");
    }

    move_base_msgs::MoveBaseGoal goal;

    //send goal to robot to move 1m forward
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 7.0; //3.0;
    goal.target_pose.pose.position.y = 0.0; //2.5;
    // goal.target_pose.pose.orientation.z = std::sqrt(0.5);
    goal.target_pose.pose.orientation.w = 1.0; //std::sqrt(0.5);

    ROS_INFO("Sending Goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Hooray!");
    }
    else{
        ROS_INFO("FAIL");
    }

    return 0;


}