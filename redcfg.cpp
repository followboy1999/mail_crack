/***************************************** 
* 
* 
*    FileName:    redcfg.cpp 
* 
* 
******************************************/ 
 
#include "hackdic.h" 
 
void redcfg() 
{ 

	int i; 

    FILE *cfg; 
    if((cfg=fopen("hackdic.ini","rt"))==NULL){ 
        exit(2); 
    } 
 
    fscanf(cfg,"%*s %*s "); 
    for(i=0;i<80 && !feof(cfg);i++) 
        fscanf(cfg,"%c ",&kw[i]); 
 
    fclose(cfg); 
} 

