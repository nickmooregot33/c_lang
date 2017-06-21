/*******************************************************************

			Random Show Picker

This program chooses a random television show from a list, then it
picks a season and episode.The program's purpose is to randomly 
choose a tv episode to watch so we don't have to.  It uses linked
lists to keep track of the data, and populates the linked lists
by reading data from text files.  It's up to the user to manage 
the text files.

Data file format will be the name of the show, followed by the numbers
of episodes in each season, in chronological order, and separated by spaces.
Each show's data will be on one line, and in lowercase.  Spaces will
be represented by underscores.

*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100


typedef struct {char name[MAX],SEASON* seasons=NULL;}NODE;
typedef struct {int season,numshows; SEASON* next = NULL;}SEASON;
int nodecount;
NODE* nodes;
//int getDataNumber(char );					//returns number of distinct shows in the file
											//accepts the character array of the written address of the data file

int populateList(NODE **,char);		//populates the linked list of structs from a text file.
											//accepts filename, pointer, array index to position it.

//void getShowSeasons(int number, int array);	//to be used by populateList() to store season data needed for populating list
											//accepts number of shows and an array to store the number of seasons for each show
						
//void getEpisodes(int number, int episodeArray);	//accepts an array for a show with an index for each season and fills the array with
											//the number of episodes in that season

int createArray(NODE *,int);		//dynamically allocates memory for using pointer as an array
											//returns 0 for success, -1 for fail
											//accepts size of array needed
				
int randomGet(int min, int max);			//returns random integer, accepts minimum, maximum 


int newList(NODE);
int newNode(NODE);

int main(){
	int quantdata;	
	int showSelect,seasonSelect,episodeSelect;
	char filename[MAX];	
	NODE *lists=NULL;
		

	printf("\nWhich file do you want to use?");
	scanf("%s",filename);

	if ((quantdata=getDataNumber(filename))==-1){
		printf("Failed to get number of entries from file.\n");
		return -1;
	}
	if (createArray(lists,quantdata)==-1){
		printf("Failed to create the array to store the lists in.\n");
		return -1;
	}
	if (populateList(lists,filename,quantdata)==-1){
		printf("Failed to populate list.\n");
		return -1;
	}

	return 0;
}

int getDataNumber(char filename){
	int scanner,count;
	FILE *input=NULL;

//open the file to read from
	if ((input=fopen(filename,"r"))==NULL){
		printf("Failed to open file %s. Check your path.",filename);
		return -1;
	}

//count the data entries, 1 entry per line
	count=0;
	while (scanner != EOF){
		if ((scanner=fgetc(filename))=='\n')
			count++;
	}

//close the file and return
	fclose(filename);
	return count;
}

int createArray(NODE *nodepointer,int arraysize){
	
	NODE *temppointer=NULL;
	
	if ((nodepointer=(NODE*)realloc(temppointer,arraysize*sizeof(NODE)))==NULL){
	return -1;
	}
	else return 0;	
}

/*int populateList(NODE **pointer,char filename,int numelements){
	int datapoint;
	char name[MAX];
	FILE *input=NULL;

	if ((input=fopen(filename,"r"))==NULL){
		printf("Failed to open file %s. Check your data.",filename);
		return -1;
	}
	for (i=0;i<numelements;i++){
		if (newList(*(*pointer+i),name)==-1){
			printf("Failed to create list in index %d",i);
			return -1;
	}	
	fclose(filename);
}
int newList(NODE head,char* name,char* filename){
	int dataname[MAX],datanumber[10],i=0;
	
	fscanf(filename,"%s",&name);
	while (datanumber=fgetc(filename)

}*/
NODE* newNode(){
	NODE* temp=NULL;

	if ((temp=(NODE*)malloc(sizeof(NODE)))==NULL){
		printf("Failed to create new node.");
		return NULL;
	}
	return temp;	
}
int makeNode(char filename[],NODE * point){
	int ;


}
int getLine(char filename[],int limit,char line[]){
	int i=0;

	while ((c=fgetc(filename))!='\n' && 0<limit--)
		line[i++]=c;
	if (c=='\n')
		line[i++]=c;
	line[i]='\0';
	return i;
}
int addNode(char *name){
/*accepts string for naming node*/ 
//creates new node

       int i = 0;
        NODE *newnode = NULL;

        for (i=0;i<nodeCount;i++){
                if ((strcmp((nodes+i)->name,name)==0)||((nodes+i)->x==x && (nodes+i)->y==y)){
                        return -1;
                }
        }
        if ((newnode = (NODE*)realloc(nodes, (nodeCount+1)*sizeof(NODE)))== NULL){
                free(newnode);
                printf("\n\nFailure (re)allocating memory.\n\n EXITING\n");
                return -1
        }
        else{
                nodes = newnode;
                strcpy(nodes[nodeCount].name, name);
                (nodes+nodeCount)->seasons = NULL;
                nodeCount++;

        }
        return 0;
}
int addSeason(char* name,int data,int *pointer){
	int count=1;
	SEASON *newseason = NULL;
	SEASON *traverse = NULL;
//get a new season and assign
	if ((newseason = (SEASON*)malloc(sizeof(SEASON)))==NULL){
                printf("Failed to create new season.\n");
      		return -1;
        }
	if ((nodes+nodecount)->seasons==NULL)
		(nodes+nodecount)->seasons=newseason;	
	traverse=(nodes+nodecount)->seasons;

	while (traverse->next!=NULL){
		traverse=traverse->next;
		count++;
	}
	if (traverse!=newseason){
		traverse->next=newseason;
		count++;
		traverse=traverse->next;
	}


	traverse->numshows=*data;
	traverse->season=count;
        return 0;
}
int nameGetter (char oldline[],char newline[]){
	int i;
	for (i=0;isspace(oldline[i]) && oldline[i]!='\0';i++)
		;	
	while (oldline[i]!=' '&& oldline[i]!='\n'&& oldline[i]!='\0')
		newline[i++]=oldline[i];
	newline[i]='\0';
	return i;
}
int numberGetter (char oldline[],char newline[],int* i){
	int number,j,k;

	for (j=*i;isspace(oldline[j] && oldline[j]!='\0';j++)
		;
	for(k=0;oldline[j]!=' ' && oldline[j]!='\0';j++,k++)
		newline[k]=oldline[j];
	newline[k]='\0';
	number=atoi(newline);
	number=(oldline[j-1]=='\n')?-number:number;
	*i=j;
	if (number<100 && number>0)
		return number;
	if (number<0 && number >-100)
		return number;
	if (k==0)
		return 0;	
}
