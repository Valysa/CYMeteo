#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree{
	float value;
	int IDstat;
	/*int year;
	int month:
	int day;
	int hour;
	float moisture;
	float wind;
	float temperature;*/
	float min;
	float max;
	float moy;
	float height;
	float longitude;
	float latitude;
	struct tree* pLeft;
	struct tree* pRight;
	int equilibre;
}TreeNode;

TreeNode* createTree(int n, float val, float x, float y){
	TreeNode* pTree=malloc(sizeof(TreeNode));
	if(pTree==NULL){
		exit(1);
	}
	pTree->IDstat=n;
	pTree->value=1;
	pTree->min=val;
	pTree->max=val;
	pTree->moy=val;
	pTree->height=val;
	pTree->longitude=x;
	pTree->latitude=y;
	pTree->pLeft=NULL;
	pTree->pRight=NULL;
	pTree->equilibre=0;	
	return pTree;
}

int isEmpty(TreeNode* pTree){
	return (pTree==NULL);
}

void process(TreeNode* pTree){
	if(!isEmpty(pTree)){
		printf("\n|%f | %d", pTree->value, pTree->IDstat);
	}
}

void walkthrough_inf_t1(TreeNode* pTree, FILE *fp1){ //mode t1
	if(!isEmpty(pTree)){
		walkthrough_inf_t1(pTree->pLeft, fp1);
		fprintf(fp1, "%05d;%f;%f;%f\n", pTree->IDstat, pTree->moy/pTree->value, pTree->min, pTree->max);
		walkthrough_inf_t1(pTree->pRight, fp1);
	}
}

void walkthrough_inf_h(TreeNode* pTree, FILE *fp1){ //mode h
	if(!isEmpty(pTree)){
		walkthrough_inf_h(pTree->pRight, fp1);
		fprintf(fp1, "%f;%d;%f;%f\n", pTree->height, pTree->IDstat, pTree->longitude, pTree->latitude);
		walkthrough_inf_h(pTree->pLeft, fp1);
	}
}

void walkthrough_inf_m(TreeNode* pTree, FILE *fp1){ //mode m
	if(!isEmpty(pTree)){
		walkthrough_inf_m(pTree->pRight, fp1);
		fprintf(fp1, "%f;%d;%f;%f\n", pTree->max, pTree->IDstat, pTree->longitude, pTree->latitude);
		walkthrough_inf_m(pTree->pLeft, fp1);
	}
}

void walkthrough_inf1(TreeNode* pTree){ //parcours infixe
	if(!isEmpty(pTree)){
		walkthrough_inf1(pTree->pLeft);
		process(pTree);
		walkthrough_inf1(pTree->pRight);
	}
}

float maxf(float a, float b){
	if(a>=b){
		return a;
	}
	else{
		return b;
	}
}

float minf(float a, float b){
	if(a<=b){
		return a;
	}
	else{
		return b;
	}
}

int max(int a, int b){
	if(a>=b){
		return a;
	}
	else{
		return b;
	}
}

int min(int a, int b){
	if(a<=b){
		return a;
	}
	else{
		return b;
	}
}

int max2(int a, int b, int c){
	if(a>=b){
		if(a>=c){
			return a;
		}
		return c;
	}
	else{
		if(b>=c){
			return b;
		}
		return c;
	}
}

int min2(int a, int b, int c){
	if(a<=b){
		if(a<=c){
			return a;
		}
		return c;
	}
	else{
		if(b<=c){
			return b;
		}
		return c;
	}
}

TreeNode* RotationGauche(TreeNode* pTree){
	TreeNode* pivot=pTree->pRight;
	pTree->pRight=pivot->pLeft;
	pivot->pLeft=pTree;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	int eq_a=pTree->equilibre;
	int eq_p=pivot->equilibre;
	pTree->equilibre=eq_a-max(eq_p, 0)-1;
	pivot->equilibre=min2(eq_a-2, eq_a+eq_p-2, eq_p-1);
	pTree=pivot;
	return pTree;
}

TreeNode* RotationDroite(TreeNode* pTree){
	TreeNode* pivot=pTree->pLeft;
	pTree->pLeft=pivot->pRight;
	pivot->pRight=pTree;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	int eq_a=pTree->equilibre;
	int eq_p=pivot->equilibre;
	pTree->equilibre=eq_a-min(eq_p, 0)+1;
	pivot->equilibre=max2(eq_a+2, eq_a+eq_p+2, eq_p+1);
	pTree=pivot;
	return pTree;
}

TreeNode* DoubleRotationGauche(TreeNode* pTree){
	pTree->pRight=RotationDroite(pTree->pRight);
	return RotationGauche(pTree);
}

TreeNode* DoubleRotationDroite(TreeNode* pTree){
	pTree->pLeft=RotationGauche(pTree->pLeft);
	return RotationDroite(pTree);
}

TreeNode* equilibrerAVL(TreeNode* pTree){
	if(pTree->equilibre>=2){ //sous-arbre droit plus profond
		if(pTree->pRight->equilibre>=0){
			return RotationGauche(pTree);
		}
		else{
			return DoubleRotationGauche(pTree);
		}
	}
	else if(pTree->equilibre<=-2){ //sous-arbre gauche plus profond
		if(pTree->pLeft->equilibre<=0){ 
			return RotationDroite(pTree);
		}
		else{
			return DoubleRotationDroite(pTree);
		}
	}
	return pTree;
}		

TreeNode* insertionAVL(TreeNode* pTree, int n, float val, float x, float y, int* h){
	if(pTree==NULL){
		*h=1;
		return createTree(n, val, x, y);
	}
	else if(pTree->IDstat>n){
		pTree->pLeft=insertionAVL(pTree->pLeft, n, val, x, y, h);
		*h=-*h;
	}
	else if(pTree->IDstat<n){
		pTree->pRight=insertionAVL(pTree->pRight, n, val, x, y, h);
	}
	else{ //si l'élément est déjà dans l'arbre
		*h=0;
		pTree->value++;
		pTree->moy=(pTree->moy+val);
		pTree->min=minf(pTree->min, val);
		pTree->max=maxf(pTree->max, val);
		return pTree;
	}
	if(*h!=0){ //si le facteur d'équilibre est différent de 0
		pTree->equilibre=pTree->equilibre+*h; //mise à jour du facteur d'équilibre
		pTree=equilibrerAVL(pTree);
		if(pTree->equilibre==0){ //si l'arbre est de nouveau équilibré
			*h=0; //ses ancetres ne changent pas
		}
		else{
			*h=1;
		}
	}
	return pTree;
}


TreeNode* insertionAVL_h(TreeNode* pTree, int n, float val, float x, float y, int* h){
	if(pTree==NULL){
		*h=1;
		return createTree(n, val, x, y);
	}
	else if(pTree->height>val){
		pTree->pLeft=insertionAVL_h(pTree->pLeft, n, val, x, y, h);
		*h=-*h;
	}
	else if(pTree->height<val){
		pTree->pRight=insertionAVL_h(pTree->pRight, n, val, x,y, h);
	}
	else{ //si l'élément est déjà dans l'arbre
		*h=0;
		return pTree;
	}
	if(*h!=0){ //si le facteur d'équilibre est différent de 0
		pTree->equilibre=pTree->equilibre+*h; //mise à jour du facteur d'équilibre
		pTree=equilibrerAVL(pTree);
		if(pTree->equilibre==0){ //si l'arbre est de nouveau équilibré
			*h=0; //ses ancetres ne changent pas
		}
		else{
			*h=1;
		}
	}
	return pTree;
}

void createFileOut(TreeNode* pTree, char *pArg, char *pArg2){
	if(pTree==NULL){
		exit(1);
	}
	FILE *fp1=NULL;
	fp1 = fopen(pArg, "w+");
	if(fp1==NULL){
		exit(3);
	}
	if(strcmp(pArg2, "-t1")==0 ||strcmp(pArg2, "-p1")==0){
		walkthrough_inf_t1(pTree, fp1);
	}
	else if(strcmp(pArg2, "-h")==0){
		puts("yeah");
		walkthrough_inf_h(pTree, fp1);
	}
	else if(strcmp(pArg2, "-m")==0){
		walkthrough_inf_m(pTree, fp1);
	}
	fclose(fp1);
}
	
void SortAVLt1(char *pArg, char *pArg2, char *pArg3){
	TreeNode* pRoot=NULL;
	int eq=0, i=0, ID=0;
	float x=0;
	int* p1=&eq;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f", &ID, &x); 
		pRoot=insertionAVL(pRoot, ID, x, 0, 0, p1);
		while(c!='\n') {
			fseek(fp, i, SEEK_SET);
			i++;
			c=fgetc(fp);
			if(c==EOF){
				c='\n';
			}
		}
		c=fgetc(fp);
	}
	fclose(fp);
	puts("fin1");
	createFileOut(pRoot, pArg2, pArg3);
}

void SortAVL_m(char *pArg, char *pArg2, char *pArg3){
	TreeNode* pRoot=NULL;
	int eq=0, i=0, ID=0;
	float x=0, y=0, z=0;
	int* p1=&eq;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f;%f;%f", &ID, &x, &y, &z);
		pRoot=insertionAVL(pRoot, ID, x, y, z, p1);
		while(c!='\n') {
			fseek(fp, i, SEEK_SET);
			i++;
			c=fgetc(fp);
			if(c==EOF){
				c='\n';
			}
		}
		c=fgetc(fp);
	}
	fclose(fp);
	puts("fin1");
	createFileOut(pRoot, pArg2, pArg3);
}

void SortAVL_h(char *pArg, char *pArg2, char *pArg3){
	TreeNode* pRoot=NULL;
	int eq=0, i=0, ID=0;
	float x=0, y=0, z=0;
	int* p1=&eq;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f;%f;%f", &ID, &x, &y, &z);
		pRoot=insertionAVL_h(pRoot, ID, z, x, y, p1);
		while(c!='\n') {
			fseek(fp, i, SEEK_SET);
			i++;
			c=fgetc(fp);
			if(c==EOF){
				c='\n';
			}
		}
		c=fgetc(fp);
	}
	fclose(fp);
	puts("fin");
	createFileOut(pRoot, pArg2, pArg3);
}

void checkFileIn(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(pArg[0]!='-' || pArg[1]!='f'){
		puts("Erreur sur le nom du fichier entrant");
		exit(1);
	}
	int n=strlen(pArg);
	for(int i=0; i<n; i++){
		pArg[i]=pArg[i+2];
	}
	printf("\n(%s)", pArg);
}

void checkFileOut(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(pArg[0]!='-' || pArg[1]!='o'){
		puts("Erreur sur le nom du fichier sortant");
		exit(1);
	}
	int n=strlen(pArg);
	for(int i=0; i<n; i++){
		pArg[i]=pArg[i+2];
	}
	printf("\n(%s)", pArg);
}

void checkMode(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(strcmp(pArg, "-t1")==0){
		puts("ok t1");
	}
	else if(strcmp(pArg, "-t2")==0){
		puts("ok t2");
	}
	else if(strcmp(pArg, "-t3")==0){
		puts("ok t3");
	}
	else if(strcmp(pArg, "-p1")==0){
		puts("ok p1");
	}
	else if(strcmp(pArg, "-p2")==0){
		puts("ok p2");
	}
	else if(strcmp(pArg, "-p3")==0){
		puts("ok p3");
	}
	else if(strcmp(pArg, "-w")==0){
		puts("ok w");
	}
	else if(strcmp(pArg, "-h")==0){
		puts("ok h");
	}
	else if(strcmp(pArg, "-m")==0){
		puts("ok m");
	}
	else{
		puts("erreur mode");
		exit(1);
	}
}

void checkReverse(char* pArg){
	if(strcmp(pArg, "-r")==0){
		puts("sens décroissant");
	}
	else if(pArg!=NULL){
		puts("Erreur du sens de tri");
		exit(1);
	}
	else{
		puts("sens croissant");
	}
}

void checkTri(char* pArg){
	if(strcmp(pArg, "--tab")==0){
		puts("tab");
	}
	else if(strcmp(pArg, "--abr")==0){
		puts("abr");
	}
	else if(strcmp(pArg, "--avl")==0){
		puts("avl");
	}
	else if(strcmp(pArg, "-r")!=0){ //si le mode de tri n'est pas demandé et que -r est demandé
		puts("Erreur de tri");
		exit(1);
	}
	else{
		puts("avl par défaut");
		checkReverse(pArg);
	}
}

int main(int argc, char **argv){
	if(argc!=4 && argc!=5 && argc!=6){
		puts("Erreur de argc");
		exit(1);
	}
	printf("%s", argv[1]);
	puts("");
	printf("%s", argv[2]);
	puts("");
	printf("%s", argv[3]);
	printf("\n%d", argc);
	checkFileIn(argv[1]);
	checkFileOut(argv[2]);
	puts("hey");
	checkMode(argv[3]);
	puts("cool");
	if(argc==4){
		puts("mode avl par défaut");
	}
	if(argc>=5){
		checkTri(*(argv+4));
		if(argc==6){
			checkReverse(*(argv+5));
		}
	}
	puts("");
	printf("%s", argv[1]);
	puts("");
	printf("%s", argv[2]);
	if(strcmp(argv[3], "-t1")==0 || strcmp(argv[3], "-p1")==0){
		SortAVLt1(argv[1], argv[2], argv[3]);
	}
	else if(strcmp(argv[3], "-m")==0){
		SortAVL_m(argv[1], argv[2], argv[3]);
	}
	else if(strcmp(argv[3], "-h")==0){
		SortAVL_h(argv[1], argv[2], argv[3]);
	}
	return 0 ;
}
