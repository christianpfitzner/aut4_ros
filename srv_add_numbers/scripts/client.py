#!/usr/bin/env python

import sys
import rospy
from srv_add_numbers.srv import add_to_int

def add_two_ints_client(x, y):
    rospy.wait_for_service('add_two_ints')
    try:
        srv = rospy.ServiceProxy('add_two_ints', add_to_int)
        resp1 = srv(x, y)
        return resp1.sum
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def usage():
    return "Please call the node with %s [x y]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 3:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    else:
        print usage()
        sys.exit(1)
    print "Requesting %s+%s"%(x, y)
    add_two_ints_client(x, y)
    #print "%s + %s = %s"%(x, y, )
