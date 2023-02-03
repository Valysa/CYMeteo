#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree{
	float value;
	int IDstat;
	float min;
	float max;
	float moy;
	float height;
	float longitude;
	float latitude;
	float wind_o;
	float wind_moy;
	long date;
	struct tree* pLeft;
	struct tree* pRight;
	int equilibre;
}TreeNode;

typedef struct chainon {
	float value;
	int IDstat;
	float min;
	float max;
	float moy;
	float height;
	float longitude;
	float latitude;
	float wind_o;
	float wind_moy;
	long date;
	struct chainon*pNext;
}Chainon;

Chainon* createChainon(int n, float val, float x, float z, float o, float w, long d) {
	Chainon* pChainon=NULL;
	pChainon=malloc(sizeof(Chainon));
	if(pChainon==NULL) {
		exit(1);
	}
	pChainon->IDstat=n;
	pChainon->value=1;
	pChainon->min=val;
	pChainon->max=val;
	pChainon->moy=val;
	pChainon->height=val;
	pChainon->longitude=x;
	pChainon->latitude=z;
	pChainon->wind_o=o;
	pChainon->wind_moy=w;
	pChainon->date=d;
	pChainon->pNext=NULL;
	return pChainon;
}

void destroyChainon(Chainon* pChainon) {
	if(pChainon==NULL) {
		exit(2);
	}
	free(pChainon);
}

Chainon* createList() {
	return NULL;
}

Chainon* addStart(Chainon* pHead, int n, float val, float x, float z, float o, float w, long d) {
	Chainon* pNew=createChainon(n, val, x, z, o, w, d);
	if(pNew==NULL) {
		exit(3);
	}
	pNew->pNext=pHead;
	pHead=pNew;
	return pHead;
}

void addEnd(Chainon* pHead, int n, float val, float x, float z, float o, float w, long d) {
	Chainon* pNew=createChainon(n, val, x, z, o, w, d);
	if(pNew==NULL) {
		exit(5);
	}
	while(pHead->pNext!=NULL) {
		pHead=pHead->pNext;
	}
	pHead->pNext=pNew;
}	

void displayList(Chainon* pHead) {
	while(pHead!=NULL) {
		printf("[%02f]", pHead->value);
		pHead=pHead->pNext;
	}
}

void displayList_t1(Chainon* pHead, FILE *fp1) { //Chained list mode t1 
	while(pHead!=NULL){
		fprintf(fp1, "%05d;%f;%f;%f\n", pHead->IDstat, pHead->moy/pHead->value, pHead->min, pHead->max);
		pHead=pHead->pNext;
	}
}

void displayList_t2(Chainon* pHead, FILE *fp1) { //Chained list mode t2
	while(pHead!=NULL) {
		fprintf(fp1, "%ld;%f\n", pHead->date, pHead->moy/pHead->value);
		pHead=pHead->pNext;
	}
}

void displayList_t3(Chainon* pHead, FILE *fp1) { //Chained list mode t3
	while(pHead!=NULL) {
		fprintf(fp1, "%ld;%d;%f\n", pHead->date, pHead->IDstat, pHead->moy/pHead->value);
		pHead=pHead->pNext;
	}
}

void displayList_w(Chainon* pHead, FILE *fp1) { //Chained list mode w
	while(pHead!=NULL) {
		fprintf(fp1, "%05d;%f;%f;%f;%f\n", pHead->IDstat, pHead->wind_o/pHead->value, pHead->wind_moy/pHead->value, pHead->longitude, pHead->latitude);
		pHead=pHead->pNext;
	}
}

void displayList_h(Chainon* pHead, FILE *fp1) { //Chained list mode h
	while(pHead!=NULL) {
		fprintf(fp1, "%f;%d;%f;%f\n", pHead->height, pHead->IDstat, pHead->longitude, pHead->latitude);
		pHead=pHead->pNext;
	}
}

void displayList_m(Chainon* pHead, FILE *fp1) { //Chained list mode m
	while(pHead!=NULL) {
		fprintf(fp1, "%f;%d;%f;%f\n", pHead->max, pHead->IDstat, pHead->longitude, pHead->latitude);
		pHead=pHead->pNext;
	}
}

TreeNode* createTree(int n, float val, float x, float z, float o, float w, long d){
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
	pTree->latitude=z;
	pTree->wind_o=o;
	pTree->wind_moy=w;
	pTree->date=d;
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
		printf("\n|%ld | %f", pTree->date, pTree->moy);
	}
}

void walkthrough_inf_t1(TreeNode* pTree, FILE *fp1){ //mode t1
	if(!isEmpty(pTree)){
		walkthrough_inf_t1(pTree->pLeft, fp1);
		fprintf(fp1, "%05d;%f;%f;%f\n", pTree->IDstat, pTree->moy/pTree->value, pTree->min, pTree->max);
		walkthrough_inf_t1(pTree->pRight, fp1);
	}
}

void walkthrough_inf_t2(TreeNode* pTree, FILE *fp1){ //mode t2
	if(!isEmpty(pTree)){
		walkthrough_inf_t2(pTree->pLeft, fp1);
		fprintf(fp1, "%ld;%f\n", pTree->date, pTree->moy/pTree->value);
		walkthrough_inf_t2(pTree->pRight, fp1);
	}
}

void walkthrough_inf_t3(TreeNode* pTree, FILE *fp1){ //mode t3
	if(!isEmpty(pTree)){
		walkthrough_inf_t3(pTree->pLeft, fp1);
		fprintf(fp1, "%ld;%d;%f\n", pTree->date, pTree->IDstat, pTree->moy/pTree->value);
		walkthrough_inf_t3(pTree->pRight, fp1);
	}
}

void walkthrough_inf_w(TreeNode* pTree, FILE *fp1){ //mode w
	if(!isEmpty(pTree)){
		walkthrough_inf_w(pTree->pLeft, fp1);
		fprintf(fp1, "%05d;%f;%f;%f;%f\n", pTree->IDstat, pTree->wind_o/pTree->value, pTree->wind_moy/pTree->value, pTree->longitude, pTree->latitude);
		walkthrough_inf_w(pTree->pRight, fp1);
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

void createFileOutChainedList(Chainon* pHead, char *pArg, int i){ //Sort file for chained list
	if(pHead==NULL){
		exit(1);
	}
	FILE *fp1=NULL;
	fp1 = fopen(pArg, "w+");
	if(fp1==NULL){
		exit(3);
	}
	if(i==1){
		displayList_t1(pHead, fp1);
	}
	else if(i==2){
		displayList_t2(pHead, fp1);
	}
	else if(i==3){
		displayList_t3(pHead, fp1);
	}
	else if(i==4){
		displayList_w(pHead, fp1);
	}
	else if(i==5){
		displayList_h(pHead, fp1);
	}
	else if(i==6){
		displayList_m(pHead, fp1);
	}
	destroyChainon(pHead);
	fclose(fp1);
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

TreeNode* insertionAVL(TreeNode* pTree, int n, float val, float x, float y, float o, float w, int* h){
	if(pTree==NULL){
		*h=1;
		return createTree(n, val, x, y, o, w, 0);
	}
	else if(pTree->IDstat>n){
		pTree->pLeft=insertionAVL(pTree->pLeft, n, val, x, y, o, w, h);
		*h=-*h;
	}
	else if(pTree->IDstat<n){
		pTree->pRight=insertionAVL(pTree->pRight, n, val, x, y, o, w, h);
	}
	else{ //si l'�l�ment est d�j� dans l'arbre
		*h=0;
		pTree->value++;
		pTree->moy=pTree->moy+val;
		pTree->min=minf(pTree->min, val);
		pTree->max=maxf(pTree->max, val);
		pTree->wind_o=pTree->wind_o+o;
		pTree->wind_moy=pTree->wind_moy+w;
		return pTree;
	}
	if(*h!=0){ //si le facteur d'�quilibre est diff�rent de 0
		pTree->equilibre=pTree->equilibre+*h; //mise � jour du facteur d'�quilibre
		pTree=equilibrerAVL(pTree);
		if(pTree->equilibre==0){ //si l'arbre est de nouveau �quilibr�
			*h=0; //ses ancetres ne changent pas
		}
		else{
			*h=1;
		}
	}
	return pTree;
}

TreeNode* insertionAVL_t2(TreeNode* pTree, int n, float val, long d, int* h){
	if(pTree==NULL){
		*h=1;
		return createTree(n, val, 0, 0, 0, 0, d);
	}
	else if(pTree->date>d){
		pTree->pLeft=insertionAVL_t2(pTree->pLeft, n, val, d, h);
		*h=-*h;
	}
	else if(pTree->date<d){
		pTree->pRight=insertionAVL_t2(pTree->pRight, n, val, d, h);
	}
	else{ //si l'�l�ment est d�j� dans l'arbre
		*h=0;
		pTree->value++;
		pTree->date=d;
		pTree->moy=pTree->moy+val;
		return pTree;
	}
	if(*h!=0){ //si le facteur d'�quilibre est diff�rent de 0
		pTree->equilibre=pTree->equilibre+*h; //mise � jour du facteur d'�quilibre
		pTree=equilibrerAVL(pTree);
		if(pTree->equilibre==0){ //si l'arbre est de nouveau �quilibr�
			*h=0; //ses ancetres ne changent pas
		}
		else{
			*h=1;
		}
	}
	return pTree;
}

TreeNode* insertionAVL_t3(TreeNode* pTree, int n, float val, long d, int* h){
	if(pTree==NULL){
		*h=1;
		return createTree(n, val, 0, 0, 0, 0, d);
	}
	else if(pTree->date>d){
		pTree->pLeft=insertionAVL_t3(pTree->pLeft, n, val, d, h);
		*h=-*h;
	}
	else if(pTree->date<d){
		pTree->pRight=insertionAVL_t3(pTree->pRight, n, val, d, h);
	}
	else{ //si l'�l�ment est d�j� dans l'arbre
		if(pTree->IDstat==n){
			*h=0;
			pTree->value++;
			pTree->date=d;
			pTree->moy=pTree->moy+val;
			return pTree;
		}
		else if(pTree->IDstat>n){
			pTree->pLeft=insertionAVL_t3(pTree->pLeft, n, val, d, h);
			*h=-*h;
		}
		else if(pTree->IDstat<n){
			pTree->pRight=insertionAVL_t3(pTree->pRight, n, val, d, h);
		}
	}
	if(*h!=0){ //si le facteur d'�quilibre est diff�rent de 0
		pTree->equilibre=pTree->equilibre+*h; //mise � jour du facteur d'�quilibre
		pTree=equilibrerAVL(pTree);
		if(pTree->equilibre==0){ //si l'arbre est de nouveau �quilibr�
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
		return createTree(n, val, x, y, 0, 0, 0);
	}
	else if(pTree->height>val){
		pTree->pLeft=insertionAVL_h(pTree->pLeft, n, val, x, y, h);
		*h=-*h;
	}
	else if(pTree->height<val){
		pTree->pRight=insertionAVL_h(pTree->pRight, n, val, x, y, h);
	}
	else{ //si l'�l�ment est d�j� dans l'arbre
		*h=0;
		return pTree;
	}
	if(*h!=0){ //si le facteur d'�quilibre est diff�rent de 0
		pTree->equilibre=pTree->equilibre+*h; //mise � jour du facteur d'�quilibre
		pTree=equilibrerAVL(pTree);
		if(pTree->equilibre==0){ //si l'arbre est de nouveau �quilibr�
			*h=0; //ses ancetres ne changent pas
		}
		else{
			*h=1;
		}
	}
	return pTree;
}

void createFileOut(TreeNode* pTree, char *pArg, int i){
	if(pTree==NULL){
		exit(1);
	}
	FILE *fp1=NULL;
	fp1 = fopen(pArg, "w+");
	if(fp1==NULL){
		exit(3);
	}
	if(i==1){
		puts("oui");
		walkthrough_inf_t1(pTree, fp1);
	}
	else if(i==2){
		walkthrough_inf_t2(pTree, fp1);
	}
	else if(i==3){
		puts("yes t3");
		walkthrough_inf_t3(pTree, fp1);
	}
	else if(i==4){
		walkthrough_inf_w(pTree, fp1);
	}
	else if(i==5){
		walkthrough_inf_h(pTree, fp1);
	}
	else if(i==6){
		walkthrough_inf_m(pTree, fp1);
	}
	free(pTree);
	fclose(fp1);
}
	
void SortAVLt1(char *pArg, char *pArg2, int k){
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
		pRoot=insertionAVL(pRoot, ID, x, 0, 0, 0, 0, p1);
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
	createFileOut(pRoot, pArg2, k);
}

void SortAVL_t2(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int eq=0, i=0;
	long d=0;
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
		fscanf(fp, "%ld;%f", &d, &x);
		pRoot=insertionAVL_t2(pRoot, 0, x, d, p1);
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
	puts("fin2");
	createFileOut(pRoot, pArg2, k);
}

void SortAVL_t3(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int eq=0, i=0, ID=0;
	long d=0;
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
		fscanf(fp, "%d;%ld;%f", &ID, &d, &x);
		pRoot=insertionAVL_t3(pRoot, ID, x, d, p1);
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
	puts("fin2");
	createFileOut(pRoot, pArg2, k);
}

void SortAVL_w(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int eq=0, i=0, ID=0;
	float o=0, w=0, x=0, y=0;
	int* p1=&eq;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f;%f;%f;%f", &ID, &o, &w, &x, &y); 
		pRoot=insertionAVL(pRoot, ID, 0, x, y, o, w, p1);
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
	puts("fin w");
	createFileOut(pRoot, pArg2, k);
}

void SortAVL_m(char *pArg, char *pArg2, int k){
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
		pRoot=insertionAVL(pRoot, ID, x, y, z, 0, 0, p1);
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
	puts("fin m");
	createFileOut(pRoot, pArg2, k);
}

void SortAVL_h(char *pArg, char *pArg2, int k){
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
	createFileOut(pRoot, pArg2, k);
}

TreeNode* ajoutABR_t1(TreeNode* pTree, int n, float val, float x, float y, float o, float w){
	if(pTree==NULL){
		return createTree(n, val, x, y, o, w, 0);
	}
	else if(pTree->IDstat>n){
		pTree->pLeft=ajoutABR_t1(pTree->pLeft, n, val, x, y, o, w);
	}
	else if(pTree->IDstat<n){
		pTree->pRight=ajoutABR_t1(pTree->pRight, n, val, x, y, o, w);
	}
	else{
		pTree->value++;
		pTree->moy=pTree->moy+val;
		pTree->min=minf(pTree->min, val);
		pTree->max=maxf(pTree->max, val);
		pTree->wind_o=pTree->wind_o+o;
		pTree->wind_moy=pTree->wind_moy+w;
	}
	return pTree;
}

TreeNode* ajoutABR_t2(TreeNode* pTree, int n, float val, long d){
	if(pTree==NULL){
		return createTree(n, val, 0, 0, 0, 0, d);
	}
	else if(pTree->date>d){
		pTree->pLeft=ajoutABR_t2(pTree->pLeft, n, val, d);
	}
	else if(pTree->date<d){
		pTree->pRight=ajoutABR_t2(pTree->pRight, n, val, d);
	}
	else{
		pTree->value++;
		pTree->moy=pTree->moy+val;
		pTree->date=d;
	}
	return pTree;
}

TreeNode* ajoutABR_t3(TreeNode* pTree, int n, float val, long d){
	if(pTree==NULL){
		return createTree(n, val, 0, 0, 0, 0, d);
	}
	else if(pTree->date>d){
		pTree->pLeft=ajoutABR_t3(pTree->pLeft, n, val, d);
	}
	else if(pTree->date<d){
		pTree->pRight=ajoutABR_t3(pTree->pRight, n, val, d);
	}
	else{
		if(pTree->IDstat==n){
			pTree->value++;
			pTree->moy=pTree->moy+val;
			pTree->date=d;
		}
		else if(pTree->IDstat>n){
			pTree->pLeft=ajoutABR_t3(pTree->pLeft, n, val, d);
		}
		else if(pTree->IDstat<n){
			pTree->pRight=ajoutABR_t3(pTree->pRight, n, val, d);
		}
	}
	return pTree;
}

TreeNode* ajoutABR_h(TreeNode* pTree, int n, float val, float x, float y){
	if(pTree==NULL){
		return createTree(n, val, x, y, 0, 0, 0);
	}
	else if(pTree->height>val){
		pTree->pLeft=ajoutABR_h(pTree->pLeft, n, val, x, y);
	}
	else if(pTree->height<val){
		pTree->pRight=ajoutABR_h(pTree->pRight, n, val, x, y);
	}
	return pTree;
}

void SortABR_t1(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int i=0, ID=0;
	float x=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	puts("ça marche");
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f", &ID, &x); 
		pRoot=ajoutABR_t1(pRoot, ID, x, 0, 0, 0, 0);
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
	createFileOut(pRoot, pArg2, k);
}

void SortABR_t2(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int i=0;
	long d=0;
	float x=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%ld;%f", &d, &x);
		pRoot=ajoutABR_t2(pRoot, 0, x, d);
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
	puts("fin2");
	createFileOut(pRoot, pArg2, k);
}

void SortABR_t3(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int i=0, ID=0;
	long d=0;
	float x=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%ld;%f", &ID, &d, &x);
		pRoot=ajoutABR_t3(pRoot, ID, x, d);
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
	puts("fin2");
	createFileOut(pRoot, pArg2, k);
}

void SortABR_w(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int i=0, ID=0;
	float o=0, w=0, x=0, y=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f;%f;%f;%f", &ID, &o, &w, &x, &y); 
		pRoot=ajoutABR_t1(pRoot, ID, 0, x, y, o, w);
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
	puts("fin w");
	createFileOut(pRoot, pArg2, k);
}

void SortABR_m(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int i=0, ID=0;
	float x=0, y=0, z=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f;%f;%f", &ID, &x, &y, &z);
		pRoot=ajoutABR_t1(pRoot, ID, x, y, z, 0, 0);
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
	puts("fin m");
	createFileOut(pRoot, pArg2, k);
}

void SortABR_h(char *pArg, char *pArg2, int k){
	TreeNode* pRoot=NULL;
	int i=0, ID=0;
	float x=0, y=0, z=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f;%f;%f", &ID, &x, &y, &z);
		pRoot=ajoutABR_h(pRoot, ID, z, x, y);
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
	createFileOut(pRoot, pArg2, k);
}

Chainon* addChained(Chainon* pHead, int n, float val, float x, float z, float o, float w, long d){
	 if(pHead==NULL){
		return createChainon(n, val, 0, 0, 0, 0, 0);
	 }
		return pHead;
}	

void SortChainedList_t1(char *pArg, char *pArg2, int k){
	Chainon* pList=createList();
	int i=0, ID=0;
	float x=0;
	int c='a';
	FILE *fp=NULL;
	fp = fopen(pArg, "r");
	if(fp==NULL){
		exit(3);
	}
	while(c!=EOF){
		fseek(fp, i-1, SEEK_SET);
		fscanf(fp, "%d;%f", &ID, &x);
		pList=addChained(pList, ID, x, 0, 0, 0, 0, 0); 
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
	createFileOutChainedList(pList, pArg2, k);
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
}

int checkMode(char* pArg){
	if(pArg==NULL){
		exit(4);
	}
	if(strcmp(pArg, "-t1")==0){
		puts("ok t1");
		return 1;
	}
	else if(strcmp(pArg, "-t2")==0){
		puts("ok t2");
		return 2;
	}
	else if(strcmp(pArg, "-t3")==0){
		puts("ok t3");
		return 3;
	}
	else if(strcmp(pArg, "-p1")==0){
		puts("ok p1");
		return 1;
	}
	else if(strcmp(pArg, "-p2")==0){
		puts("ok p2");
		return 2;
	}
	else if(strcmp(pArg, "-p3")==0){
		puts("ok p3");
		return 3;
	}
	else if(strcmp(pArg, "-w")==0){
		puts("ok w");
		return 4;
	}
	else if(strcmp(pArg, "-h")==0){
		puts("ok h");
		return 5;
	}
	else if(strcmp(pArg, "-m")==0){
		puts("ok m");
		return 6;
	}
	else{
		puts("erreur mode");
		exit(1);
	}
}

void checkReverse(char* pArg){
	if(strcmp(pArg, "-r")==0){
		puts("sens d�croissant");
	}
	else if(pArg!=NULL){
		puts("Erreur du sens de tri");
		exit(1);
	}
	else{
		puts("sens croissant");
	}
}

void Sort(char *pArg2, char* pArg3, int i, int j){
	if(j==3){ //if AVL mode is requested
		if(i==1){
			SortAVLt1(pArg2, pArg3, i);
		}
		else if(i==2){
			SortAVL_t2(pArg2, pArg3, i);
		}
		else if(i==3){
			SortAVL_t3(pArg2, pArg3, i);
		}
		else if(i==4){
			SortAVL_w(pArg2, pArg3, i);
		}
		else if(i==5){
			SortAVL_h(pArg2, pArg3, i);
		}
		else if(i==6){
			SortAVL_m(pArg2, pArg3, i);
		}
	}
	else if(j==2){ //if ABR mode is requested
		if(i==1){
			SortABR_t1(pArg2, pArg3, i);
		}
		else if(i==2){
			SortABR_t2(pArg2, pArg3, i);
		}
		else if(i==3){
			SortABR_t3(pArg2, pArg3, i);
		}
		else if(i==4){
			SortABR_w(pArg2, pArg3, i);
		}
		else if(i==5){
			SortABR_h(pArg2, pArg3, i);
		}
		else if(i==6){
			SortABR_m(pArg2, pArg3, i);
		}
	}
	else if(j==1){ //if Chained list mode is requested
		if(i==1){
			SortChainedList_t1(pArg2, pArg3, i);
		}
	}
}

int checkTri(char* pArg, char* pArg2, char* pArg3, int i){
	if(strcmp(pArg, "--tab")==0){
		return 1;
	}
	else if(strcmp(pArg, "--abr")==0){
		return 2;
	}
	else if(strcmp(pArg, "--avl")==0){
		return 3;
	}
	else if(strcmp(pArg, "-r")!=0){ //si le mode de tri n'est pas demand� et que -r est demand�
		return 3;
	}
	else{
		checkReverse(pArg);
		return 3;
	}
}

int main(int argc, char **argv){
	if(argc!=4 && argc!=5 && argc!=6){
		puts("Erreur de argc");
		exit(1);
	}
	int j=3;
	checkFileIn(argv[1]);
	checkFileOut(argv[2]);
	int i=checkMode(argv[3]);
	if(argc==4){
		puts("mode avl par d�faut");
	}
	else if(argc>=5){
		j=checkTri(argv[4], argv[1], argv[2], i);
		if(argc==6){
			checkReverse(argv[5]);
		}
	}
	Sort(argv[1], argv[2], i, j);
	return 0 ;
}

