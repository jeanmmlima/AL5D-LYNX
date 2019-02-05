#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Posicao inicial para todos os servos
#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500"

void handlePos(char[]);

void handlePos(char cmd[]){
	printf("Desired Position: %s\n", cmd);

	int tam = (int)strlen(cmd);
	char temp[3] = "000,"; //range de operacao 500 a 2500
	int pos = 0;
	float position = atof(temp);
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

int main()
{	
	int vecJointPos[8];

	handlePos(HOME_POS);
	
	printf("\n");
	return 0;
}