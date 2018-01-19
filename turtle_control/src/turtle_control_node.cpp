/* turtle_control_node.cpp */



#include "ros/ros.h"                    // allgemeiner Header für ROS
#include <geometry_msgs/Twist.h>        // Nachricht zum Verschicken von Geschwindigkeitsbefehlen
#include <turtlesim/Spawn.h>            // Spawn Service
#include <turtlesim/Pose.h>             // Nachricht für die Pose der Schildkröte
#include <turtlesim/Kill.h>
#include <turtlesim/SetPen.h>


void callbackPose(const turtlesim::Pose& msg)
{
   // ... 
}


int main(int argc, char **argv)
{
  if(argc<2)
  {
    std::cout << "Too less parameters. Expected: " << argv[0] << " <turtlename>" << std::endl;
    return -1;
  }


  /**
   * Name des eigenen Knotens
   */
  char node[64];
  sprintf(node, "%s%s", argv[1], "_node");
  printf("Neuer Knoten: %s\n", node);

  ros::init(argc, argv, node);
  ros::NodeHandle n;


  /**
   * Name des publishers
   */
  char pubname[64];
  sprintf(pubname, "%s/%s", argv[1], "cmd_vel");
  printf("Publisher: %s\n", pubname);


char penname[64]; 
sprintf(penname, "%s/%s", argv[1], "set_pen"); 
  /**
   * Implementieren Sie hier den Aufruf des Dienstes spawn
   */
   ros::ServiceClient client      = n.serviceClient<turtlesim::Spawn>("spawn"); 
   ros::ServiceClient kill_client = n.serviceClient<turtlesim::Kill>("kill");    
   ros::ServiceClient pen_client  = n.serviceClient<turtlesim::SetPen>(penname);   
/*
    * Senden Sie einen Service-Call über den Service client ab
    * Beachten Sie, dass der name der Schildkröte mit argv[1] gesetzt wird, so dass
    * jede Schildkröte im Netzwerk nur einmal vorkommt.
    */
   turtlesim::Spawn srv;
   // ... 


   /* Für Schnelle:
    * 1) Ändern Sie die Farbe der Schildkröte in abhängigkeit ihrer x, y Position.
    *    Seien Sie kreativ!
    * 2) Lassen Sie die Schildkröte ein Rechteck abfahren.
    *
    */
  ros::Subscriber pose_sub = n.subscribe("chris/pose", 1, callbackPose);


  /**
   * Implementieren Sie hier das Versenden von Nachrichten
   * zur Steuerung der Schildkröte
   */
   ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>(pubname, 1); 

   ros::Rate r(10); 



   while(ros::ok())
   {
      /*
       * Erstellen Sie an dieser Stelle eine Nachricht vom Typ geometry_msgs::Twist
       * Füllen Sie den Inhalt der Nachricht, so dass die Schildkröte eine Kreis-
       * bahn fährt.
       * Schicken Sie die Nachricht
       */
      geometry_msgs::Twist msg; 
      // ... 

      ros::spinOnce();  
      r.sleep(); 
   }

   turtlesim::Kill kill_srv; 
   // ...


  return 0;
}

