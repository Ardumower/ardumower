#!/usr/bin/env python
# Ardumower ROS driver

import rospy
import tf
import serial
import math
import sys
import termios
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from tf.broadcaster import TransformBroadcaster

DEBUG = False


class ArdumowerNode:

    def __init__(self):
        self.left = 0
        self.right = 0
        self.odoX = 0
        self.odoY = 0
        self.odoTh = 0
        self.yaw = 0
        self.pitch =0
        self.roll = 0
        self.printTime = 0
        rospy.init_node('ardumower')
        # disable reset after hangup
        #with open(rospy.get_param('~device')) as f:
        #	attrs = termios.tcgetattr(f)
        #	attrs[2] = attrs[2] & ~termios.HUPCL
        #	termios.tcsetattr(f, termios.TCSAFLUSH, attrs)	 
        # open serial port 
        self.port = serial.Serial(port=rospy.get_param('~device'), baudrate=115200, timeout=0)
        self.port.flush()

        # The Twist has units of m/s for the linear terms, as well as radian/s for the angular terms.
        rospy.Subscriber(rospy.get_param('~cmd_vel'), Twist, self.cmdVelCb)        
        self.odomPub = rospy.Publisher(rospy.get_param('~odom_topic'), Odometry, queue_size=10)
        self.odomBroadcaster = TransformBroadcaster()

        self.cmd_vel = [0,0] 

    def sendMotorSpeed(self, l, r, m):
        # motor speed: linear (m/s), angular (rad/s)
        s = "$ROS,M1,"+str(l)+","+str(r)+","+str(int(m))
        #print "sending: ", s
        self.port.write(s + "\r\n")

    def poll(self):
        while self.port.inWaiting() > 0:
          line = self.port.readline()
          if DEBUG:
            sys.stdout.write(line)
          items = line.split(",")
          if len(items) >= 17:
            if items[0] == '$ROS':
              if items[1] == 'I1':
                self.loopsPerSec = float(items[2])
                self.batVoltage = float(items[3])
                self.chgVoltage = float(items[4])
                self.chgCurrent = float(items[5])
                self.left = float(items[6])
                self.right = float(items[7])
                self.yaw = float(items[11])
                self.pitch = float(items[12])
                self.roll = float(items[13])
                self.odoX = float(items[14])
                self.odoY = float(items[15])
                self.odoTh = float(items[16])
                if rospy.get_time() > self.printTime:
                  self.printTime = rospy.get_time() + 10     
                  print "lps=",self.loopsPerSec, " bat=",self.batVoltage, " ypr=",self.yaw, self.pitch, self.roll, "odoXYT=",self.odoX, self.odoY, self.odoTh

    def spin(self):        
        odo = [0,0,0]

        then = rospy.Time.now()
        start = rospy.get_time() + 10

        # things that don't ever change
        odom = Odometry(header=rospy.Header(frame_id=rospy.get_param('~odom_frame')), child_frame_id=rospy.get_param('~base_link'))
    
        # main loop of driver
        counter = 0
        r = rospy.Rate(10)        
        print "ardumower spin start"
        while not rospy.is_shutdown():
            stamp = rospy.Time.now()             
            # get motor encoder values
            self.poll()

            # send updated movement commands
            if rospy.get_time() > start:
              if counter == 0:
                self.sendMotorSpeed(0,0,0)
                start = rospy.get_time() + 2
                counter=1
              else:
                self.sendMotorSpeed(self.cmd_vel[0], self.cmd_vel[1], 0)
                start = rospy.get_time() + 0.2                

            # now update position information
            dt = (stamp - then).to_sec()
            then = stamp

            # odo unit is meters
            d_X = (self.odoX - odo[0])
            d_Y = (self.odoY - odo[1])
            dth = (self.odoTh - odo[2])
            odo = [self.odoX, self.odoY, self.odoTh]
            
            dx = math.sqrt(d_X*d_X + d_Y*d_Y)

            # prepare tf from base_link to odom
            q = tf.transformations.quaternion_from_euler(self.roll, self.pitch, self.odoTh)
            #print q
            quaternion = Quaternion()
            quaternion.x = q[0]
            quaternion.y = q[1]
            quaternion.z = q[2]
            quaternion.w = q[3]
            #quaternion.z = math.sin(self.odoTh/2.0)
            #quaternion.w = math.cos(self.odoTh/2.0)

            # prepare odometry
            odom.header.stamp = rospy.Time.now()
            odom.pose.pose.position.x = self.odoX
            odom.pose.pose.position.y = self.odoY
            odom.pose.pose.position.z = 0
            odom.pose.pose.orientation = quaternion
            odom.twist.twist.linear.x = dx/dt
            odom.twist.twist.angular.z = dth/dt

            # publish everything
            self.odomBroadcaster.sendTransform( (self.odoX, self.odoY, 0), (quaternion.x, quaternion.y, quaternion.z, quaternion.w), then, rospy.get_param('~base_link'), rospy.get_param('~odom_frame') )
            self.odomPub.publish(odom)
            
            # wait, then do it again
            r.sleep()            

        # shut down
        self.port.close()
        print "Ardumower node shutting down"
	

    def cmdVelCb(self,req):
        # linear speed is meter/sec, angular speed is radian/sec 
        self.cmd_vel = [ req.linear.x , req.angular.z ]

if __name__ == "__main__":    
        robot = ArdumowerNode()
        robot.spin()





