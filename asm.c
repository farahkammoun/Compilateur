/*************************************************

Fichier : ASM.C
Date 	: 07/03/2017
Auteurs : AUBERVAL/DELAHAYE

*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********Fichier que l'on a cree**************/
#include "asm.H"

/*************************************************
****************Fonction main :*******************
*************************************************/
int main(int argc, char **argv)
{
/*****************************************/
/*On va ici tester l'ouverture du fichier*/
/*****************************************/
	FILE* file=fopen("assembleur.asm","r"); //ouverture du fichier

	if (file==NULL) 
	{
		printf("Ouverture du fichier impossible\n");
		exit (EXIT_FAILURE);
	}
	else
	{	
		EXIT_SUCCESS;
	}
/*****************************************/
	

	// Construction du dictionnaire d’instruction 

	addInstructionName("add", I_ADD, 0, "", 0);
	currentInst++;
	addInstructionName("pushi", I_PUSHI, 0, "", 0);
	currentInst++;
	addInstructionName("mult", I_MULT, 0, "", 0);
	currentInst++;
	addInstructionName("push", I_PUSH, 0, "", 0);
	currentInst++;
	addInstructionName("pop", I_POP, 0, "", 0);
	currentInst++;
	addInstructionName("and", I_AND, 0, "", 0);
	currentInst++;
	addInstructionName("jf", I_JF, 0, "", 0);
	currentInst++;
	addInstructionName("j", I_J, 0, "", 0);	
	currentInst++;
	addInstructionName("eq", I_EQ, 0, "", 0);
	currentInst++;
	addInstructionName("ls", I_LS, 0, "", 0);
	currentInst++;
	addInstructionName("gt", I_GT, 0, "", 0);
	currentInst++;	
	addInstructionName("halt", I_HALT, 0, "", 0);
	currentInst++;

	// Parseur phase 1
	parseAsm(fin);

	// Parseur phase 2
	resolveReferences();

	// Génération du code
	generateBinary(fout);
	
	fclose(file);
	return 0;
	

}

