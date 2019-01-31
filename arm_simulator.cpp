/*

UFRN-CT-DCA

AL5D-LYNX 2.0 SIMULATOR ON V-REP

DEVELOPED BY: Eng. Msc. Jean M. M. Lima.

*/

extern "C" {
  #include "remoteApi/extApi.h"
}

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv){
	
	//inicial variables	
	string serverIP = "127.0.0.1";
	int serverPort = 19999;
	int jointHandles[4];
	string jointNames[4];
	int modelBase = 0;
	string modelBaseName = "";
	
	//setup some of the RML vectors
	
	float vel=180;
	float accel=40;
	float jerk=80;
	float currentVel[4] = {0,0,0,0};
	float maxVel[4] = {vel*M_PI/180,vel*M_PI/180,vel*M_PI/180,vel*M_PI/180};
	float maxAccel[4] = {accel*M_PI/180,accel*M_PI/180,accel*M_PI/180,accel*M_PI/180};
	float maxJerk[4] = {jerk*M_PI/180,jerk*M_PI/180,jerk*M_PI/180,jerk*M_PI/180};
	float targetVel = {0,0,0,0};
	
}
