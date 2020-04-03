/*
Zachary Ikpefua
ECE 2220
Project 3
Spring 2018

Purpose: Write a program to set, clear, and shift bits in order
to produce normal operations at home such as turning on the lights

Estimations: I assumed that this project would take only a few days, however
it only took about a few well put in hours to accomplish this program

Knwon Bugs:

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 30

void printBitmask(unsigned short int);

int main(void){

   int programLoop = 0;
 	char function[MAXLINE] = "";
 	char action[MAXLINE] = "";
   unsigned short int portB = 0;
   unsigned short int BCD = 0;
	char line[MAXLINE];
	int n = 0;
 	char *p;
	int i = 0;
	int strcheck = 0;
 	int mode_number = 0; //Number has to be between 0 and 99

  	fprintf(stdout,"\a\nWelcome to the program! The bits 4 through 11 are in BCD format.\n");
  	printBitmask(portB);

  while(programLoop == 0){
    fprintf(stdout,"Type a command to adjust the bits, type [HELP] for list of valid options: ");

    p = fgets(line,MAXLINE,stdin);
    if(p != NULL){ //Check if there is an input
    sscanf(line,"%s %s",function, action);
  }
	n = strlen(action);
    if(strcmp(function, "Mode") == 0){

		 for(i = 0; i < n; i++){
			 if(isalpha(action[i])){
				 strcheck++;
			 }
		 }

		 if(strcheck != 0){
			 fprintf(stdout,"\aPlease do not enter a character for the mode number.\n");
			 strcheck = 0;
		 }

		 else{
			strcheck = 0;
        mode_number = atoi(action);
		    if(mode_number < 0 || mode_number > 99){
			       fprintf(stdout,"\aPlease enter a number for mode between 0 and 99.\n");
		    }
        else{
          //Clear all inner bits
          portB = portB & (0xF00F);
          //portB = portB | (mode_number << 4); Original Non-BCD code
          BCD = (mode_number / 10 << 4) | (mode_number % 10);
          portB = portB | (BCD << 4);
          printBitmask(portB);
        }
		 }
    } //end of strcmp(function, "Mode")

    else if(strcmp(function,"Light") == 0){
      if(strcmp(action,"Off") == 0){
			     portB = portB & (0x3FFF); //Clear Only the 15th and 14th Bits
        	 printBitmask(portB);
      }
      else if(strcmp(action,"Dim") == 0){
        portB = portB | (1 << 14); //Set
       	portB = portB & (~(1<< 15)); //Clear
       	printBitmask(portB);
      }
      else if(strcmp(action, "Bright")== 0){
        portB = portB | (1 << 14); //set
       	portB = portB | (1 << 15); //set
       	printBitmask(portB);
      }
      else {
        	fprintf(stdout,"\aPlease enter a correct action for \"Light\"\n");
      }
    } //end of else if(strcmp(function, "Light")

    else if(strcmp(function,"Heater") == 0){
      if(strcmp(action,"Off") == 0){
			portB = portB & (0xCFFF); //Clears Both 12th and 13th bits
  	      printBitmask(portB);
      }
      else if(strcmp(action,"Warm") == 0){
       	portB = portB | (1 << 12); //set
		   portB = portB & (~(1<< 13)); //clear
      	printBitmask(portB);
      }
      else if(strcmp(action, "Hot")== 0){
       	portB = portB | (1 << 12); //set
  		  	portB = portB | (1 << 13); //set
        	printBitmask(portB);
      }
      else {
        	fprintf(stdout,"\aPlease enter a correct action for \"Heater\"\n");
      }
    } //end of else if(strcmp(function,"Heater")

  else if(strcmp(function,"Compressor") == 0){
    if(strcmp(action,"Off") == 0){
      	portB = portB & (0xFFF3); //Clear both 2nd and 3th bit
      	printBitmask(portB);
    }
    else if(strcmp(action,"Cool") == 0){
      	portB = portB | (1 << 2); //set
			portB = portB & (~(1<< 3)); //clear
      	printBitmask(portB);
    }
    else if(strcmp(action, "Cold")== 0){
      portB = portB | (1 << 2);//set
		portB = portB | (1 << 3); //set
      printBitmask(portB);
    }
    else {
      fprintf(stdout,"\aPlease enter a correct action for \"Compressor\"\n");
    }
  } //end of else if(strcmp(function, "Compressor")

  else if(strcmp(function,"Fan") == 0){
    if(strcmp(action,"Off") == 0){
      portB = portB & (0xFFFC);
      printBitmask(portB);
    }
    else if(strcmp(action,"Low") == 0){
     	portB = portB & (~(1<< 1)); //clear
		portB = portB | (1 << 0); //set
      printBitmask(portB);
    }
    else if(strcmp(action, "High")== 0){
      portB = portB | (1 << 1); //set
		portB = portB | (1 << 0); //set
      printBitmask(portB);
    }
    else {
      fprintf(stdout,"\aPlease enter a correct action for \"Fan\"\n");
    }
  } //end of else if(strcmp(function,"Fan")

  else if(strcmp(function,"QUIT")== 0){
	  	fprintf(stdout,"\n\aThank you for using the program.\n");
      return 0;
    }

  else if(strcmp(function,"HELP")== 0){
    fprintf(stdout,"\n/*********************************************/\n");
	  fprintf(stdout,"Help Commands:\n\nLight:\n\t[Off]\t[Dim]\t[Bright]\n\n");
	  fprintf(stdout,"Heater:\n\t[Off]\t[Warm]\t[Hot]\n\nCompressor:\n\t[Off]\t[Cool]\t{Cold]\n\n");
	  fprintf(stdout,"Fan:\n\t[Off]\t[Low]\t[High]\n\nMode:\n\t[*Number between 0-99*]\n\nOther Commands:\n\t[QUIT]\t[HELP]\t[RESET]\n");
    fprintf(stdout,"/*********************************************/\n\n");
    }

  else if(strcmp(function,"RESET")== 0){
	 //Clear all of portB, mode_number, and BCD
		portB = portB & (0x0000);
		mode_number = 0;
		BCD = BCD & (0x0000);
      fprintf(stdout,"//\a\n\nAll Data has been Cleared//\n\n");
  }

  else{ //User enters an invalid entry
    fprintf(stdout,"\a\nPlease enter a valid function, type [HELP] for comands\n");
  }

  } //end of while(programmingLoop == 0)
  return 0;
}

/*
FUNCTION:	printBitmask
INPUTS:		port (portB)
OUTPUTS:		None, is void
PURPOSE:		To print the control word and portB as a
				result of shifting, clearing, and seting
				the bits
*/

void printBitmask(unsigned short int port){
  int b = 0;

  fprintf(stdout,"\nControl word: 0x%04X\n",port); //Hex value of portB
   fprintf(stdout," 15 14 13 12  11 10  9  8   7  6  5  4   3  2  1  0\n");

  for(b = 15; b >= 0; b--){
	 if(b == 11 || b == 7 || b == 3){

    fprintf(stdout,"%4d",(port & (1 << b)) >> b); //Reading bits to output
	 }
	 else {
    fprintf(stdout,"%3d",(port & (1 << b)) >> b); //Reading bits to output
	 }
  }
  fprintf(stdout,"\n\n");
}
