

#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <bz2_transport/bz2_publisher.h>
#include <bz2_transport/bz2_subscriber.h>

int main()
{
    bz2_transport::BZ2Publisher<std_msgs::Header> pub;
    bz2_transport::BZ2Subscriber<std_msgs::Header> sub;

    sleep(1);

    return 0;
}
