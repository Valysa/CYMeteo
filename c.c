#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	if(argc!=2){
		puts("Erreur de argc");
		exit(1);
	}
	FILE *fichier=NULL;
	fichier = fopen("data.csv", "r+");
	fclose(fichier); 
	return 0 ;
}