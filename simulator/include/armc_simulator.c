/*

UFRN-CT-DCA

AL5D-LYNX 2.0 SIMULATOR ON V-REP

DEVELOPED BY: Eng. Msc. Jean M. M. Lima.

*/

#include "armc_simulator.h"

//Handles
int jointHandles[4];
int modelBase = 0;
char gripper[] = "PhantomXPincher_gripperClose";

/*
int abre_porta();
void setup(int);
void fecha_porta(int);
int simulacao_ativa(int);
void envia_comando(int,char[]);

//500-2500 position TO angles 

//base: 500 - 2400

//ombro: 1100 - 2000

//cotovelo: 1100 - 2100

//punho: 500 - 2500

float getPos(int,int);
*/

void ufrn_header()
{
	printf("/***********************************************************/\n");
	printf("       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         \n");
	printf("   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    \n");
	printf("							                               \n");
	printf("        SIMULADOR DO BRAÇO ROBÓTICO LYNX AL5D - v2.0 	   \n");
	printf("							                               \n");
	printf("   DESENVOLVEDOR:					                       \n");
	printf("	- ENG. M.SC. JEAN MARIO MOREIRA DE LIMA                \n");
	printf("/************************************************************/\n\n");
}

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

float getPos(int servo, int pos){

	if(servo == 0)
		return ((0.0947 * pos) - 137.3684);
	else if(servo == 1) 
		return ((-0.09 * pos) + 135);
	else if(servo == 2)
		return ((0.1 * pos) - 60);
	else if(servo == 3)
		return ((-0.09 * pos) + 135);
	else{
		if(pos >= 1500)
			return 1;
		else
			return 0;
	}

}

void envia_comando(int clientID, char cmd[]){

	int tam = (int)strlen(cmd);
	char temp[3]; //range de operacao 500 a 2500
	sprintf(temp,"000,");
	int pos = 0;
	int positionInt = atoi(temp);
	int serv;

	for(int i = 0; i < tam; i++){
	

		if(cmd[i] == '#' && i == 0){
		//	printf("\nNovo comando: \n");
			pos = 0;
		}
		else if(cmd[i] == '#' && i != 0){
			positionInt = atoi(temp);
			float jointPos = getPos(serv,positionInt);
			simxSetJointTargetPosition(clientID,jointHandles[serv], (simxFloat) jointPos*M_PI/180, (simxInt) simx_opmode_streaming);
			extApi_sleepMs(TIME);


			if(serv != 4){

				simxSetJointTargetPosition(clientID,jointHandles[serv], (simxFloat) jointPos*M_PI/180, (simxInt) simx_opmode_streaming);
				extApi_sleepMs(TIME);

			}
			else{
				simxSetIntegerSignal(clientID,(const simxChar*) gripper,(simxInt) ((int)jointPos), (simxInt) simx_opmode_oneshot);
				extApi_sleepMs(TIME); 
			}


			//printf("\nNovo comando: \n");
			pos = 0;
			sprintf(temp,"000,");
		}
		else if(cmd[i-1]=='#'){
			serv = (int) cmd[i] - '0';
			//printf("Servo %i ",serv);
		}
		else if(cmd[i] !='P'){
			temp[pos] = cmd[i];
			//printf("%c",temp[pos]);
			pos = pos + 1;

			if(i == tam-1){
				positionInt = atoi(temp);
				float jointPos = getPos(serv,positionInt);

				if(serv != 4){

					simxSetJointTargetPosition(clientID,jointHandles[serv], (simxFloat) jointPos*M_PI/180, (simxInt) simx_opmode_streaming);
					extApi_sleepMs(TIME);

				}
				else{
					simxSetIntegerSignal(clientID,(const simxChar*) gripper,(simxInt) ((int)jointPos), (simxInt) simx_opmode_oneshot);
					extApi_sleepMs(TIME); 
				}
				sprintf(temp,"000,");
			}
			
		}
	}
}
