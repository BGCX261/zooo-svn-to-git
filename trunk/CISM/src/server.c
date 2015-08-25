#include "server.h"

char *strzcpy(char *str, char *content, int len) {
	if (len==-1) {
		len=strlen(content);
	}
	strncpy(str, content, len);
	return str+len;
}

int initservdeal(char *servdeal[12]) {
	int i=0;
	for (; i<12; i++) {
		if ((servdeal[i]=(char *)malloc(sizeof(char)*32))==NULL) {
			return -1;
		}
	}
	return 1;
}

void preordain(serv *a, char *serverdeal[12]) {
	serverdeal[0]=a->servip;
	serverdeal[1]=a->servport;
	serverdeal[2]=a->staut;
	serverdeal[3]=a->user;
	serverdeal[4]=a->midware;
	serverdeal[5]=a->userto;
	serverdeal[6]=a->thisdate;
	serverdeal[7]=a->outdate;
	serverdeal[8]=a->startcmd;
	serverdeal[9]=a->stopcmd;
	serverdeal[10]=a->forcestop;
	serverdeal[11]=a->sid;
}

serv *newserv() {
	serv *myserv;
	if ((myserv=(serv *)malloc(sizeof(serv)))==NULL) {
		printf("\n不能创建链表");
		exit(1);
	}
	myserv->next=NULL;
	return myserv;
}
void copyserv(char *soudeal[], serv *tagvar) {
	tagvar->next=newserv();
	char *tmpdeal[12];
	int i;
	initservdeal(tmpdeal);
	preordain(tagvar->next, tmpdeal);
	for (i=0; i<12; i++) {
		strncpy(tmpdeal[i], soudeal[i], strlen(soudeal[i]));
	}
}
void servprint(serv * thisserv) {

	int i;
	//head=thisserv;
	temp=thisserv->next;
	printf("\n");
	while (temp!=NULL) {
		preordain(temp, servdeal);
		for (i=0; i<12; i++) {
			printf("%s ", servdeal[i]);
		}
		printf("\n");
		temp=temp->next;
	}
}

serv * str1serv(char *values) {
	initservdeal(servdeal);
	int i;
	char *str, *pst;
	if ((cur=(serv *)malloc(sizeof(serv)))==NULL) {
		printf("\n不能创建链表");
		exit(1);
	}
	memset(cur, 0x00, sizeof(serv));
	preordain(cur, servdeal);
	str=pst=values;
	for (i=0; i<12; i++) {
		if ((pst=strstr(str, "\t"))!=NULL) {
			strncpy(servdeal[i], str, pst-str);
			str=pst+strlen("\t");
		}
	}
	return cur;
}

serv * str2serv(char *servstr) {
	char *pst, *str, *buf;
	str=pst=servstr;
	buf=(char *)malloc(sizeof(serv)+32);
	van=head=newserv();
	while ((pst=strstr(str, "\n"))!=NULL) {
		memset(buf, 0x00, sizeof(serv)+32);
		strncpy(buf, str, pst-str);
		cur=van;
		cur->next=str1serv(buf);
		van=cur;
		str=pst+strlen("\n");
	}
	return head;
}
serv * servread(char *servname) {
	FILE *servdat;
	char *servstr;
	int fsize;

	if ((head=(serv *)malloc(sizeof(serv)))==NULL) {
		printf("\n不能创建链表");
		exit(1);
	}

	if ((servdat= fopen(servname, "rb")) == NULL) {
		printf("dread");
		exit(1);
	}
	rewind(servdat);
	fseek(servdat, 0L, SEEK_END);
	fsize=ftell(servdat);
	servstr=(char *)malloc(sizeof(char)*fsize);
	rewind(servdat);
	fread(servstr, sizeof(char), fsize, servdat);
	fclose(servdat);
	servstr=strstr(servstr, "\n")+strlen("\n");
	head=str2serv(servstr);
	return head;

}

char * serv1str(serv * thisserv) {
	initservdeal(servdeal);
	char *buf, *tbuf;
	int i;
	tbuf=buf=(char *)malloc(sizeof(serv)+32);
	memset(buf, 0x00, strlen(buf));
	preordain(thisserv->next, servdeal);
	for (i=0; i<12; i++) {
		buf=strzcpy(buf, servdeal[i], -1);
		buf=strzcpy(buf, "\t", -1);
	}
	buf=strzcpy(buf, "\n", -1);
	return tbuf;
}

int serv2str(serv * thisserv, char *str) {
	char *buf;
	temp=thisserv;
	while (temp->next!=NULL) {
		buf=serv1str(temp);
		str=strzcpy(str, buf, -1);
		temp=temp->next;
	}
	free(buf);
	return 1;
}

int servwrite(serv *thisserv, char *servname) {
	FILE *servdat;
	head=thisserv;
	temp=head;
	char *buf;
	if ((servdat= fopen(servname, "wb")) == NULL) {
		printf("dwrite error 1");
		return -1;
	}

	fwrite(
			"servip\tservport\tstaut\tuser\tmidware\tuserto\tthisdate\toutdate\tstartcmd\tstopcmd\tforcestop\tsid\t\n",
			sizeof(char),
			strlen("servip\tservport\tstaut\tuser\tmidware\tuserto\tthisdate\toutdate\tstartcmd\tstopcmd\tforcestop\tsid\t\n"),
			servdat);
	fclose(servdat);
	if ((servdat= fopen(servname, "ab")) == NULL) {
		printf("dwrite error 2");
		return -1;
	}
	while (temp->next!=NULL) {
		buf=(char *)malloc(sizeof(serv)+32);
		buf=serv1str(temp);
		fwrite(buf, sizeof(char), strlen(buf), servdat);
		temp=temp->next;
		free(buf);
	}
	fclose(servdat);
	return 0;
}

serv *servquery(serv *thisserv, int thicase, char *searchvalue, int n,
		int *count)/*查找接点函数*/
{
	int tmp=0;
	initservdeal(servdeal);
	serv *tcur, *thead;
	tcur=thead=newserv();

	temp=thisserv;

	while (temp!=NULL) {
		if (n==0) {
			break;
		}
		preordain(temp, servdeal);
		if (strcmp(servdeal[thicase], searchvalue)==0) {
			copyserv(servdeal, tcur);
			//tcur->next=temp;
			tcur=tcur->next;
			n--;
			tmp++;
		}

		temp=temp->next;
	}
	tcur->next=NULL;
	*count=tmp;
	return thead;
}

serv *servfind(serv *thisserv, serv *searchvalue)/*查找接点函数*/
{

	serv *tcur, *thead;
	tcur=thead=newserv();

	temp=thisserv->next;

	while (temp!=NULL) {

		if (strcmp(temp->sid, searchvalue->sid)==0) {
			tcur->next=temp;
			break;
		}
		temp=temp->next;
	}

	return thead;
}

int modify(serv *thisserv, int newcase, char *newvalue) {
	//initservdeal(servdeal);
	serv *buf;
	buf=thisserv->next;
	while (buf!=NULL) {
		preordain(buf, servdeal);
		memset(servdeal[newcase], 0x00, 32);
		strncpy(servdeal[newcase], newvalue, strlen(newvalue));
		buf=buf->next;
	}
	return 0;
}

int modifybyfind(serv *thisserv, serv *index, char mystr[5][32]) {

	initservdeal(servdeal);

	temp=thisserv;

	while (temp!=NULL) {
		preordain(temp, servdeal);
		if (strcmp(servdeal[NSID], index->next->sid)==0) {
			preordain(temp, servdeal);
			memset(servdeal[NUSER], 0x00, 32);
			strncpy(servdeal[NUSER], mystr[1], strlen(mystr[1]));
			memset(servdeal[NUSERTO], 0x00, 32);
			strncpy(servdeal[NUSERTO], mystr[2], strlen(mystr[2]));
			memset(servdeal[NTHISDATE], 0x00, 32);
			strncpy(servdeal[NTHISDATE], mystr[3], strlen(mystr[3]));
			memset(servdeal[NOUTDATE], 0x00, 32);
			strncpy(servdeal[NOUTDATE], mystr[4], strlen(mystr[4]));
			return 1;
		}
		temp=temp->next;
	}

	return 0;
}
int changstatu(serv *thisserv, serv *index, char * status) {

	temp=thisserv;

	while (temp!=NULL) {
		preordain(temp, servdeal);
		if (strcmp(servdeal[NSID], index->next->sid)==0) {
	
			memset(servdeal[NSTAUT], 0x00, 32);
			strncpy(servdeal[NSTAUT], status, strlen(status));
			
			return 1;
		}
		temp=temp->next;
	}

	return 0;
}
int longerserv(serv *thisserv, char * sid, char * thisdata,char *outdate) {

	temp=thisserv;

	while (temp!=NULL) {
		preordain(temp, servdeal);
		if (strcmp(servdeal[NSID], sid)==0) {
	
			memset(servdeal[NTHISDATE], 0x00, 32);
			strncpy(servdeal[NTHISDATE], thisdata, strlen(thisdata));
			memset(servdeal[NOUTDATE], 0x00, 32);
			strncpy(servdeal[NOUTDATE], outdate, strlen(outdate));
			
			return 1;
		}
		temp=temp->next;
	}

	return 0;
}
