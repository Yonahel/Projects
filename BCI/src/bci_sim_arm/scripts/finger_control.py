#!/usr/bin/env python
import rospy
from sensor_msgs import JointState

def thumb_open(position):
	position[0] = 0
	position[5] = 0
	position[6] = 0
def thumb_close(position):
	position[0] = -1.57
	position[5] = 1.57
	position[6] = 1.57
def index_open(position):
	position[1] = 0
	position[7] = 0
	position[8] = 0
def index_close(position):
	position[1] = 1.57
	position[7] = 1.57
	position[8] = 1.57
def middle_open(position):
	position[2] = 0
	position[9] = 0
	position[10] = 0
def middle_close(position):
	position[2] = 1.57
	position[9] = 1.57
	position[10] = 1.57
def ring_open(position):
	position[3] = 0
	position[11] = 0
	position[12] = 0
def ring_close(position):	
	position[3] = 1.57
	position[11] = 1.57
	position[12] = 1.57
def pinky_open(position):
	position[4] = 0
	position[13] = 0
	position[14] = 0
def pinky_close(position):
	position[4] = 1.57
	position[13] = 1.57
	position[14] = 1.57
	
#Joint States Arrays Initialized
header = []
name = ['base_thumb_joint', 'base_index_joint', 'base_middle_joint', 'base_ring_joint', 'base_pinky_joint', 'first_thumb_joint', 'second_thumb_joint', 'first_index_joint', 'second_index_joint', 'first_middle_joint', 'second_middle_joint', 'first_ring_joint', 'second_ring_joint', 'first_pinky_joint', 'second_pinky_joint']
position = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
velocity = []
effort = []

js = JointState()
js.header = header
js.name = name
js.position = position
js.velocity = velocity
js.effort = effort

pub = rospy.Publisher('joint_states', JointState, queue_size = 100)
rospy.init_node('joint_states')
rate = rospy.Rate(10)
while not rospy.is_shutdown():
	
	rospy.loginfo(js)
	pub.publish(js)

