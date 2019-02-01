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

	/*Para conectar um server, usar a funcao simxStart()
	  
		simxStart(connectionAddress, connection Port,
					waitUntilConnected, doNotReconnectOnceDisconnected,
					timeOutInMs, commThreadCycleInMs)

	*/
  	int clientID=simxStart((simxChar*)serverIP.c_str(),serverPort,true,true,2000,5);

  	if(clientID  != -1){

  		cout << "Servidor conectado!" << endl;

  		//iniciando modelo base

  		if(simxGetObjectHandle(clientID,(const simxChar*) "PhantomXPincher",(simxInt *) &modelBase, (simxInt) simx_opmode_oneshot_wait) != simx_return_ok)
      		cout << "Handle do modelo base nao encontrado!" << endl;  
    	else
      		cout << "Conectado ao modelo base!" << endl;

      	//iniciando as juntas

      	for(int i = 0; i < 4; i++){
      		sensorNome[i] = "PhantomXPincher_joint" + to_string(i + 1);
      
     		if(simxGetObjectHandle(clientID,(const simxChar*) jointNames[i].c_str(),(simxInt *) &jointHandles[i], (simxInt) simx_opmode_oneshot_wait) != simx_return_ok)
				cout << "Handle da junta " << jointNames[i] << " nao encontrado!" << endl;
      		else{
        		cout << "Conectado ao sensor " << sensorNome[i] << std::endl;				
      		}
    	}


    	// Enquanto a simulacao for ativa
    	while(simxGetConnectionId(clientID)!=-1){

    	}
    

  	}
  	else{
  		cout << "Não foi possível conectar ao servidor!" << endl;
  		return 0;
  	}


	


}
