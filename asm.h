/*************************************************

Fichier : ASM.H
Date 	: 07/03/2017
Auteurs : AUBERVAL/DELAHAYE

*************************************************
*************************************************


		ADDINSTRUCTION 
		PARSASM		----> ADDLABEL ----> 	LABEL 
				----> DECODEINSTRUCTION ----> ADDCODE	
							----> 
							----> 		

MAIN 	----> 	RESOLVEREFERENCE ----> 	FINDLABEL
		PRINTLABELS
		DUMPBINARYCODE
		GENERATEBIN


*************************************************/

#ifndef _ASM_H_
#define _ASM_H_

#include <string.h>

/*************************************************
******************Variables :*********************
/*************************************************/

#define MAX_IDENTS_SIZE 100
#define MAX_LABELS_SIZE 100

int currentLabel = 0; 
int currentInst  = 0; //Incremente le compteur de label (variable globale)
int currentRef   = 0;

/*************************************************
*****************Structures :*********************
/*************************************************/

struct instructionName 
{
	char *name;	// Le nom de l'instruction
	
	int opcod;	// son codop, extrait de vm_codops.h
	int type;	// son type
	
	char *format;	// son format
	
	int nbops;	// le nombre d'operandes de l'inst
	
} tabInstructionNames[MAX_IDENTS_SIZE];

/*************************************************/
struct label 
{
	char *label;
	int addr;
} tabLabels[MAX_LABELS_SIZE];
/*************************************************/
struct ref 
{
	char *label;
	int addrInCode;

} tabReferences[MAX_LABELS_SIZE];

/*************************************************
******************Fonctions:**********************
/*************************************************/
void addInstructionName(char *name, int opcode, int type, char *format, int nbops);
void parseAsm(FILE *fin);
void resolveReferences();
void addLabel(char *labelname,int addr);
void printLabel();
void decodeInstruction(char *line);
void dumpBinaryCode();
void generateBinaryCode();
void addCode();

/*************************************************/
/******************PARSEASM :*********************
	Cette fonction parcourt les lignes du fichier source assembleur tant qu'elle n'a pas
	rencontré de ligne avec "end". Pour chaque ligne il y a 3 cas de figure:
	• si la ligne de texte contient : il s'agit d'une étiquette, on appelle la fonction
	addLabel
	• si on trouve # , c'est un commentaire
	• sinon, il s'agit d'une instruction et on appelle la fonction
	decodeInstruction
*/
void parseAsm(FILE *fin)
{
	char *s;
	s = fscanf(fin,"%s",s);
	//int currentInst=0;
	while (s!="end")/*on va parcourir le fichier jusqu'a trouver end*/
	{		
		if (strchr(s,'#')!=NULL){
		}else{ 
	
			if (strchr(s, ':')!=NULL){
			addLabel(s,currentInst);} // addLabel(line,currentInst);
		}else {
			decodeInstruction(s);
		}
	  s=fscanf(fin,"%s",s);
	}
}
/*************************************************
***************addInstructionName*****************
Construction du dictionnaire :

	Instructions de Type 0:
Elles ne demandent pas de décodage d'operandes supplementaires. Leur chaine de format
est "" et leur nombre d'argument est 0 :
addInstructionName("add", OP_ADD, 0, "", 0);

	Instructions de Type 1:
Le décodage d'un entier est necessaire. La chaine de format est donc "%s %d". Le
%s represente l'instruction et le %d l'operande. Il y a une operande pour ce genre
d'instruction
addInstructionName("push", OP_PUSH, 1, "%s %d", 1);

	Instructions de Type 3:
le decodage d'une chaine de caracteres representant une etiquette est necessaire.
La chaine de format est donc "%s %s" et le deuxieme %s represente l'etiquette. Il y
a une operande pour ce genre d'instructions
addInstructionName("jp", OP_JP, 3, "%s %s", 1);

*/
void addInstructionName(char *name, int opcode, int type, char *format, int nbops)
{
	// on remplit la structure
	strcpy(tabInstructionNames[MAX_IDENTS_SIZE] -> name, name);

	tabInstructionNames[MAX_IDENTS_SIZE] -> opcode = opcode;

	tabInstructionNames[MAX_IDENTS_SIZE] -> type = type;

	strcpy(tabInstructionNames[MAX_IDENTS_SIZE] -> format , format);

	tabInstructionNames[MAX_IDENTS_SIZE] -> nbops = nbops;
		
}
/*************************************************
*********************addLabel*********************
Appel:

	addLabel(line,currentInst);
line: ligne courante
currentInst: Variable globale indiquant la position de l’instruction
courante, incrémentée après l’ajout de chaque instruction.

Complète le tableau de structure contenant les labels (variable globale)

Fonctions utiles:
	fgets(line,100,fin);
	strstr(line,"end");
*/
void addLabel(char *labelname,int addr)
{
	strcpy(tabLabels[MAX_LABELS_SIZE] -> labelname, label);//remplir la structure
	tabLabels[MAX_LABELS_SIZE] -> addr = addr;
	
}
/*************************************************
*********************findLabel*********************
Fonction permettant de trouver le nom du label
Il faudrait parcourir tout le code pour trouver 
le label et le mettre dans la structure label
*/
void findLabel()
{
	
	
}
/*************************************************
******************printLabels*********************
fonction debug
elle servira à afficher l'opcode 
exemple :
a la l13 il y a :	toto:
et il devra renvoyer ici y a toto
*/

void printLabels()
{
	pintf( "adresse = %d\n", addr);
	pintf( "label = %s\n", label);
}
/*************************************************
***************decodeInstruction******************
Appel:
decodeInstruction(line);
line: ligne courante
Cette fonction fait le gros du travail:
• Identifie le type de l'instruction
• Fait le décodage supplémentaire
• Appel addCode pour remplir codeSegment (tableau global unsigned int)
• Ajoute des références si l'instruction décodée fait référence à une étiquette encore
inconnue (tableau global)

en gros il faut que l'on compare (avec un if) si l'instruction décodée fait référence à une étiquette encore
	inconnue (tableau global) alors on ajoute une ref/un label
si j'ai un jump false, il faut aller mettre l'instruction 
*/
*/
void decodeInstruction(char *line)
{
	//int trouvé=0;
	int i=0;
	// Compare l'instruction dans le fichier avec notre tableau d'instructions
	while (strcmp(tabInstructionNames[i].name,line)!=0)
	{
		i++;
	}
/*
	if (label == -1) //il faut utiliser la fonction findLabel 
	{
		label++; // on va chercher s'il y a une reference inconnue, (un label) et du coup en ajouter une 
	}
*/	
	addCode();	
}
/**************************************************
*********************addCode***********************
ajoute le code
*/
void addCode()
{

}
/*************************************************
****************resolveReferences*****************
fonction qui, lorsqu'elle voit -1, devra mettre l'etiquette 
label
donc venant de findLabel? en gros ce que va retourner findLabel
se retrouvera ici pour resoudre si jamais c'est un label non identifie 

il doit renvoyer la ligne de l'etiquette
*/
void resolveReferences()
{
	
		

}
/*************************************************
*****************dumpBinaryCode*******************
Fonction de désassamblage du code (fonction de vérification)
Elle permet de générer le code assembleur correspondant aux OP_CODE stockés
dans codeSegment
Sortie :
	Fichier.ASM
	Ou dans la console
*/
void dumpBinaryCode()
{

}
/*************************************************
****************generateBinaryCode****************
Fontion qui va generer le code binaire
Sortie :
	Fichier.BIN
*/
void generateBinaryCode()
{

}
#endif

