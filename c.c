#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree{
	float value;
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
	switch(pArg[0]){
		case '1': 
			printf("avl"); 
			SortAVL(); break;
		case '2': printf("abr"); break;
		case '3': printf("tab"); break;
		default: printf(" mode par défaut avl"); break;
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
	if(argc==3){
		checkTri(*(argv+2));
	}
	return 0 ;
}
