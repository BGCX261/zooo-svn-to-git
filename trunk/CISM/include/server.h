#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

#define NSERVIP 0
#define NSERVPORT 1
#define NSTAUT 2
#define NUSER 3
#define NMIDWARE 4
#define NUSERTO 5
#define NTHISDATE 6
#define NOUTDATE 7
#define NSTARTCMD 8
#define NSTOPCMD 9
#define NFORCESTOP 10
#define NSID 11

typedef struct servlink {
	char servip[32];
	char servport[32];
	char staut[32];
	char user[32];
	char midware[32];
	char userto[32];
	char thisdate[32];
	char outdate[32];
	char startcmd[32];
	char stopcmd[32];
	char forcestop[32];
	char sid[32];
	struct servlink *next;
} serv;

char *servdeal[12];


serv *head, *van, *cur, *temp;

/*
char *strzcpy(char *str, char *content, int len);
int initservdeal(char *servdeal[11]);
void preordain(serv *a, char *serverdeal[11]);
serv *newserv()
void servprint(serv * thisserv)
serv * str1serv(char *values)
serv * str2serv(char *servstr)
serv * servread(char *servname) 
char * serv1str(serv * thisserv) 
int serv2str(serv * thisserv, char *str) 
int servwrite(serv *thisserv, char *servname) 
serv *servquery(serv *thisserv, int thicase, char *searchvalue)
int modify(serv *thisserv, int newcase, char *newvalue) 
*/
char *strzcpy(char *, char *, int );
int initservdeal(char *[12]);
void preordain(serv *a, char *[12]);
serv *newserv();
void servprint(serv * );
serv * str1serv(char *);
serv * str2serv(char *);
serv * servread(char *) ;
char * serv1str(serv * ) ;
int serv2str(serv * , char *) ;
int servwrite(serv *, char *) ;
serv *servquery(serv *, int , char *,int,int*);
serv *servfind(serv *, serv *);
int modify(serv *, int , char *) ;
int modifybyfind(serv *, serv *, char [5][32]);
int changstatu(serv *, serv *, char * );
int longerserv(serv *, char *, char * ,char *);

#endif /*SERVER_H_*/
