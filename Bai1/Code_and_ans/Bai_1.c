#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct Word{
	char word[100];
	int count;
	int lines[1000]
};
struct Word A[10000];
char NotValid[100][100];
char c;
int NotValidCount=0;
int NotValidId=0;
int ACount=0;
bool PreIsDot=false;
bool IsUpper=false;
bool SkipThisWord=false;
FILE* fptr;
char s[100];
int slen=0;
int tempt;
int CurrentLine=1;
int Rank[10000];

int FindWord(){
	for (int i=0;i<ACount;++i){
		if (0==strcmp(A[i].word,s)){
			return i;
		}
	}
	return ACount;
}

bool IsValid(){
	int result;
	for (int i=0;i<NotValidCount;++i){
		result=strcmp(NotValid[i],s);
		//printf("%s %s %d\n",NotValid[i],s,result);

		if (result==0){
			return false;
		}
	}
	return true;
}

int main() {
	fptr=fopen("stopw.txt","r");// <====== Stop Word file name
	if (fptr==NULL){
		printf("File not found.\n");
	}
	c=fgetc(fptr);
	while (c!=EOF){
		if (c=='\n'){
			NotValid[NotValidCount][NotValidId]='\0';
			NotValidCount+=1;
			NotValidId=0;
		}
		else{
			NotValid[NotValidCount][NotValidId]=c;
			++NotValidId;
		}
		//printf("=> %c<=\n",c);
		c=fgetc(fptr);
	}
	fclose(fptr);
	/*
	printf("-------------------------------\n");
	for (int i=0;i<NotValidCount;++i){
		printf("=>%s<=\n",NotValid[i]);
	}
	printf("-------------------------------\n");*/


	fptr=fopen("alice30.txt","r");// <======== Input file name
	if (fptr==NULL){
		printf("File not found.\n");
	}
	c=fgetc(fptr);
	//printf("->%c<-\n",c);
	while (c!=EOF){
		if ('A'<=c && c<'Z'){
			IsUpper=true;
			c+=32;
		}
		else{
			IsUpper=false;
		}

		if ('a'<=c && c<='z'){
			if (IsUpper&&slen==0){
				SkipThisWord=true;
			}
			if (!SkipThisWord){
				s[slen]=c;
				slen++;
			}
		}
		else{ // C is not in a->z
			SkipThisWord=false;
			if (slen>0){
				s[slen]='\0';
				if (IsValid()){
					tempt=FindWord();
					if (tempt==ACount){
						strcpy(A[tempt].word,s);
						A[tempt].lines[0]=CurrentLine;
						A[tempt].count=1;
						ACount++;
					}
					else{
						if (A[tempt].lines[A[tempt].count-1]!=CurrentLine){
							A[tempt].lines[A[tempt].count]=CurrentLine;
							A[tempt].count++;
						}
					}
				}
			}
			slen=0;
			s[0]='\0';
		}
		if (c=='\n') CurrentLine++;
		if (c=='.'){
			PreIsDot=true;
		}
		else{
			PreIsDot=false;
		}

		c=fgetc(fptr);
		//printf("->%c<-\n",c);
	}
	fclose(fptr);
	for (int i=1;i<ACount;++i){
		Rank[i]=i;
	}

	// Sort index
	for (int i=0;i<ACount;++i){
		for (int j=1;j<ACount-i;++j){
			if (strcmp(A[Rank[j-1]].word,A[Rank[j]].word)>0){
				tempt=Rank[j];
				Rank[j]=Rank[j-1];
				Rank[j-1]=tempt;
			}
		}
	}

	//printf("-------------------------------\n");

	for (int i=0;i<ACount;++i){
		printf("%s %d  %d",A[Rank[i]].word,A[Rank[i]].count,A[Rank[i]].lines[0]);
		int j=1;
		while (A[Rank[i]].lines[j]!=0){
			printf(", %d",A[Rank[i]].lines[j]);
			++j;
		}
		printf("\n");
	}
    return 0;
}
