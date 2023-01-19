#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree{
	float value;
	/*int IDstat;
	int year;
	int month:
	int day;
	int hour;
	float moisture;
	float wind;
	float height;
	float temperature;*/
	struct tree* pLeft;
	struct tree* pRight;
	int equilibre;
}TreeNode;

TreeNode* createTree(float val){
	TreeNode* pTree=malloc(sizeof(TreeNode));
	if(pTree==NULL){
		exit(1);
	}
	pTree->value=val;
	pTree->pLeft=NULL;
	pTree->pRight=NULL;
	pTree->equilibre=0;	
	return pTree;
}

int isEmpty(TreeNode* pTree){ //estVide
	return (pTree==NULL);
}

void process(TreeNode* pTree){
	if(!isEmpty(pTree)){
		printf("|%f", pTree->value);
	}
}

void walkthrough_inf(TreeNode* pTree){ //parcours infixe
	if(!isEmpty(pTree)){
		walkthrough_inf(pTree->pLeft);
		process(pTree);
		walkthrough_inf(pTree->pRight);
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

TreeNode* insertionAVL(TreeNode* pTree, float val, int* h){
	if(pTree==NULL){
		*h=1;
		return createTree(val);
	}
	else if(pTree->value>val){
		pTree->pLeft=insertionAVL(pTree->pLeft, val, h);
		*h=-*h;
	}
	else if(pTree->value<val){
		pTree->pRight=insertionAVL(pTree->pRight, val, h);
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

void SortAVL(){
	puts("ok");
	TreeNode* pRoot=NULL;
	int eq=0, i=0;
	float x=0;
	int* p1=&eq;
	int c='a';
	FILE *fp=NULL;
	fp = fopen("data.txt", "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		while(c!=';'){
			fseek(fp, i, SEEK_SET);
			i++;
			c=fgetc(fp);
		}
		fseek(fp, i, SEEK_SET);
		fscanf(fp, "%f", &x); 
		pRoot=insertionAVL(pRoot, x, p1);
		printf("%f", x);
		puts("");
		while(c!='\n' && c!=EOF) {
			fseek(fp, i, SEEK_SET);
			i++;
			c=fgetc(fp);
		}
	}
	puts("fin");
	//walkthrough_inf(pRoot);
}

void checkFileIn(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(strcmp(pArg, "-f <data.txt>")!=0){
		puts("ok1");
		exit(1);
	}
	puts("yes");
}

void checkFileOut(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(strcmp(pArg, "-o <tutedebrouille.txt>")!=0){
		puts("ok2");
		exit(1);
	}
}

void checkMode(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(pArg[0]!='-'){
		exit(1);
	}
	switch(pArg[1]){
		case 't': printf("t1"); break;
		case 'y': printf("t2"); break;
		case 'u': printf("t3"); break;
		case 'p': printf("p1"); break;
		case 'q': printf("p2"); break;
		case 's': printf("p3"); break;
		case 'w': printf("vent"); break;
		case 'h': printf("altitude"); break;
		case 'm': printf("humidité"); break;
		default : printf("erreur"); exit(1);
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
	else{
		puts("avl par défaut");
	}
}

void checkReverse(char* pArg){
	if(strcmp(pArg, "-r")==0){
		puts("sens décroissant");
	}
	puts("sens croissant");
}

int main(int argc, char **argv){
	/*if(argc!=3 && argc!=4 && argc!=5){
		puts("Erreur de argc");
		exit(1);
	}*/
	printf("%s", argv[1]);
	printf("%s", argv[2]);
	/*checkFileIn(*(argv+1));
	checkFileOut(*(argv+2));
	puts("hey");
	checkMode(*(argv+3));
	checkTri(*(argv+4));
	if(argc==4){
		checkReverse(*(argv+4));
	}
	if(argc==5){
		checkReverse(*(argv+5));
	}
	puts("");*/
	return 0 ;
}
