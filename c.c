#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkArg(char* pArg){
	if(pArg==NULL) {
		exit(4);
	}
	if(pArg[0]!='-'){
		exit(1);
	}
	switch(pArg[1]){
		case 't': printf("température 1"); break;
		case 'y': printf("température 2"); break;
		case 'u': printf("température 3"); break;
		case 'p': printf("pression 1"); break;
		case 'q': printf("pression 2"); break;
		case 's': printf("pression 3"); break;
		case 'w': printf("vent"); break;
		case 'h': printf("altitude"); break;
		case 'm': printf("humidité"); break;
		default: printf("Erreur"); exit(1); break;
	}
}

void checkTri(char* pArg){
	if(pArg==NULL) {
		exit(4);
	}
	switch(pArg[0]){
		case '1': printf("avl"); break;
		case '2': printf("abr"); break;
		case '3': printf("tab"); break;
		default: printf("avl"); break;
	}
	puts("");
}

int main(int argc, char **argv) {
	if(argc!=2 && argc!=3){
		puts("Erreur de argc");
		exit(1);
	}
	checkArg(*(argv+1));
	puts("");
	checkTri(*(argv+2));
	FILE *fichier=NULL;
	fichier = fopen("area.csv", "w+");
	if(fichier==NULL){
		exit(3);
	}
	fclose(fichier); 
	return 0 ;
}
