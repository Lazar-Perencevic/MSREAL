#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"test_image.h"
#include "10images.h"
int main(void){

FILE *fp;
int i=0;
char text[7];
char start1[]="start=1";
char start0[]="start=0";
char trigger[]="trigger_start";
int broj=0,j=0,k=0;
char *str;
size_t nbytes=6;
int procitano[784];
int stanje_ready_registra=0;
fp=fopen("/dev/vga","w");
if(fp==NULL)
  {
 	printf("Ne moze se otvoriti fajl /dev/vga\n");
  return -1;
  }
for(i=0;i<784;i++){
 	fprintf(fp,"%x\n",input_image[i]);
	fflush(fp);
} 
  fprintf(fp,"start=1\n");
  fflush(fp);
  fprintf(fp,"start=0\n");
  fflush(fp);
	      
  if(fclose(fp)==EOF)
 	{
	printf("Ne moze se zatvoriti fajl /dev/vga\n");
	return -1;
	}

  //POCINJE CITANJE
  fp=fopen("/dev/vga","r");
  if(fp==NULL)
  	{
        printf("Ne moze se otvoriti fajl /dev/vga\n");
	} 

   str=(char *)malloc(nbytes+1);
   getline(&str,&nbytes,fp);
   sscanf(str,"%d",&stanje_ready_registra);
   printf("STANJE READY REGISTRA:%d\n",stanje_ready_registra);
if(stanje_ready_registra==1){   
  for(i=0;i<784;i++){ 
         getline(&str,&nbytes,fp);
     sscanf(str,"%x",&procitano[i]);
   		
 }
 for(j=0;j<784;j++){
	if(output_image[j]==procitano[j])
 		broj++;
		   }
 for(k=0;k<784;k++){
  printf(" %x ", procitano[k]);
}

 } 

 if(fclose(fp)==EOF){
	puts("Problem pri zatvaranju");
 return -1;

 }  
 free(str);
  printf("BROJ ISTIH JE %d\n", broj);





  return 0;
}


