/*

UFRN-CT-DCA

AL5D-LYNX 2.0 SIMULATOR ON V-REP

DEVELOPED BY: Eng. Msc. Jean M. M. Lima.

*/

#include "remoteApi/extApi.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> //if your system provides it. That defines a number of macros, including bool, false, and true (defined to _Bool, 0, and 1 respectively).

//Posicao inicial para todos os servos
#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500"

//Handles
int jointHandles[4];
int modelBase = 0;
char gripper[] = "PhantomXPincher_gripperClose";


int abre_porta();
void setup(int);
void fecha_porta(int);
int simulacao_ativa(int);
void envia_comando(char[]);


int abre_porta(){

	char serverIP[] = "127.0.0.1";
	int serverPort = 19999;


	return simxStart((simxChar*)serverIP,serverPort,true,true,2000,5);
}

void setup(int clientID){

	char jointNames[4][22]; //4 juntos, 22 caracteres em cada

	//iniciando modelo base

  	if(simxGetObjectHandle(clientID,(const simxChar*) "PhantomXPincher",(simxInt *) &modelBase, (simxInt) simx_opmode_oneshot_wait) != simx_return_ok)
      	printf("Handle do modelo base nao encontrado!\n");
    else
      	printf("Conectado ao modelo base!\n");

      //iniciando as juntas

     for(int i = 0; i < 4; i++){

      	sprintf(jointNames[i],"%s%i","PhantomXPincher_joint",i+1);
      		
      
     	if(simxGetObjectHandle(clientID,(const simxChar*) jointNames[i],(simxInt *) &jointHandles[i], (simxInt) simx_opmode_oneshot_wait) != simx_return_ok)
			printf("Handle da junta %s nao encontrado!\n", jointNames[i]);
      	else{
        	printf("Conectado ao sensor %s \n", jointNames[i]);			
      	}
    }

}

void fecha_porta(int clientID){
	simxFinish(clientID); // fechando conexao com o servidor
    printf("%s\n", "Conexao fechada!");
}

int simulacao_ativa(int clientID){
	return simxGetConnectionId(clientID);
}

void envia_comando(char cmd[]){

	int tam = (int)strlen(cmd);
	char temp[3] = "000,"; //range de operacao 500 a 2500
	int pos = 0;
	int positionInt = atoi(temp);

	for(int i = 0; i < tam; i++){
	

		if(cmd[i] == '#' && i == 0){
			printf("\nNovo comando: \n");
			pos = 0;
		}
		else if(cmd[i] == '#' && i != 0){
			position = atof(temp);
			positionInt = atoi(temp);
			printf("\nPosicao valor float: %f",position);
			printf("\nPosicao valor inteiro: %i",positionInt);
			printf("\nNovo comando: \n");
			pos = 0;
		}
		else if(cmd[i-1]=='#'){
			printf("Servo %c ",cmd[i]);
		}
		else if(cmd[i] !='P'){
			temp[pos] = cmd[i];
			printf("%c",temp[pos]);
			pos = pos + 1;

			if(i == tam-1){
				position = atof(temp);
				positionInt = atoi(temp);
				printf("\nPosicao valor float: %f",position);
				printf("\nPosicao valor inteiro: %i",positionInt);
			}
			
		}
	}
}

int main(){

	//inicial variables	
	//char serverIP[] = "127.0.0.1";
	//int serverPort = 19999;
	//int jointHandles[4];
	//char jointNames[4][22]; //4 juntos, 22 caracteres em cada
	//int modelBase = 0;
	//char modelBaseName[] = "";
	//char gripper[] = "PhantomXPincher_gripperClose";

	
	int clientID = abre_porta();
	if(clientID  != -1){

  		printf("Servidor conectado!\n");

  		setup(clientID);
  		


    	// Enquanto a simulacao for ativa
    	while(simulacao_ativa()!=-1){

    		//Abre e fecha a garra a cada segundo
    		simxSetIntegerSignal(clientID,(const simxChar*) gripper,(simxInt) 1, (simxInt) simx_opmode_oneshot);
			extApi_sleepMs(1000);    		
			simxSetIntegerSignal(clientID,(const simxChar*) gripper,(simxInt) 0, (simxInt) simx_opmode_oneshot);
			extApi_sleepMs(1000); 

			// Base - joint[0]

			simxSetJointTargetPosition(clientID,jointHandles[0], (simxFloat) 90*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);
			simxSetJointTargetPosition(clientID,jointHandles[0], (simxFloat) 0*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);

			/* - joint[1]

			simxSetJointTargetPosition(clientID,jointHandles[1], (simxFloat) 90*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);
			simxSetJointTargetPosition(clientID,jointHandles[1], (simxFloat) 0*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);	

			*/	

			// Cotovelo - joint[2]

			simxSetJointTargetPosition(clientID,jointHandles[2], (simxFloat) 90*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);
			simxSetJointTargetPosition(clientID,jointHandles[2], (simxFloat) 0*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);	

			// Punho - joint[3]

			simxSetJointTargetPosition(clientID,jointHandles[3], (simxFloat) 90*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);
			simxSetJointTargetPosition(clientID,jointHandles[3], (simxFloat) 0*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(1000);

    	}

    	fecha_porta(clientID);


  	}
  	else {
  		printf("Servidor não foi conectado!\n");
  		return 0;
  	}


	
}