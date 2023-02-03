#include "functions.h"

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
