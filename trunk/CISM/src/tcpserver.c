#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"

#define MAXBUF 1024
char *servdeal[12];
serv * aserv;
serv * newaserv;

static char servertxt[]="D:\\xxx.txt";
static char Passwd[9]="abcdefgh";
static int zifuji[62];
static int lastserver=0;

int Radom(int a, int b) {
	return a+rand()%(b-a);
}

void makezifuji() {
	int i=0;
	for (; i<10; i++) {
		zifuji[i]=i+48;
	}
	for (i=0; i<27; i++) {
		zifuji[i+10]=i+65;
	}
	for (i=0; i<27; i++) {
		zifuji[i+36]=i+97;
	}
}

void makepassword(char * mypasswd) {
	int i;
	for (i=0; i<8; i++) {
		mypasswd[i]=zifuji[Radom(0,62)];
	}
	mypasswd[8]='\0';
}

char * itoas(int num, const char * wei) {
	char *str, *buf;
	str=(char *)malloc(strlen(wei));
	buf=(char *)malloc(strlen(wei));
	sprintf(buf, "%d", num);
	memset(str, 0x00, strlen(wei));
	strncpy(str, wei, strlen(wei)-strlen(buf));
	strncat(str, buf, strlen(buf));
	return str;
}

int deletserver(char *questr) {
	char mystr[5][32];
	int i=0;
	int count=0;
	char *str,*pst;
	str=pst=questr;
	char buf[32];
	memset(buf,0x00,32);
	pst=strstr(str,"\t");
	strncpy(buf,str,pst-str);
	str=pst+1;
	pst=strstr(str,"\t");
	memset(mystr[0], 0x00, 32);
	strncpy(mystr[0],str,pst-str);
	
	for (i=1; i<5; i++) {
		memset(mystr[i], 0x00, 32);
		strcpy(mystr[i], "NULL");
	}



	serv *newsevr;

	newsevr=servquery(aserv, NSID, mystr[0], 1, &count);
	if (count==0) {
		return 1;
	}
	if(strcmp(newsevr->next->user,buf)!=0){
		return 2;
	}
	modifybyfind(aserv, newsevr, mystr);
	free(newsevr);
	servwrite(aserv, servertxt);
	return 0;
}
int makeserver(char *questr) {

	char mystr[5][32];
	char thismachine[32];
	if (lastserver==0) {
		memset(thismachine, 0x00, 32);
		strcpy(thismachine, "10.2.12.61");
	} else {
		memset(thismachine, 0x00, 32);
		strcpy(thismachine, "10.2.12.62");
	}
	int i=0;
	int count=0;
	char *str, *pst;
	str=pst=questr;
	while ((pst=strstr(str, "\t"))!=NULL) {
		memset(mystr[i], 0x00, 32);
		strncpy(mystr[i], str, pst-str);
		i++;
		str=pst+1;
	}
	serv *newsevr;

	newsevr=servquery(aserv, NSERVIP, thismachine, -1, &count);
	if (count==0) {
		return 1;
	}
	newsevr=servquery(newsevr, NMIDWARE, mystr[0], -1, &count);
	if (count==0) {
		return 2;
	}
	newsevr=servquery(newsevr, NUSER, "NULL", 1, &count);
	if (count==0) {
		return 3;
	}
	modifybyfind(aserv, newsevr, mystr);
	free(newsevr);
	servwrite(aserv, servertxt);
	return 0;
}

int listyserv(char *uname, char *tstr) {
	serv *newserv;
	int count=0;
	newserv=servquery(aserv, NUSER, uname, -1, &count);

	memset(tstr, 0x00, MAXBUF+1);
	serv2str(newserv, tstr);
	return count;
}
int firstcall(char *uname, char *str) {
	char *tp;
	char buf[32];
	memset(buf,0x00,32);
	tp=strstr(uname,"\t");
	strncpy(buf,uname,tp-uname);
	uname=buf;
	memset(str, 0x00, MAXBUF+1);
	int count=0;
	int n=-1;

	free(servquery(aserv, NUSER, uname, 1, &count));

	if (count==1) {
		str=strzcpy(str, "1", -1);
	} else {
		str=strzcpy(str, "0", -1);
	}

	free(servquery(aserv, NMIDWARE, "weblogic813", n, &count));
	str=strzcpy(str, itoas(count, "00"), -1);

	free(servquery(aserv, NMIDWARE, "weblogic920", n, &count));

	str=strzcpy(str, itoas(count, "00"), -1);
	free(servquery(aserv, NMIDWARE, "websphere51", n, &count));
	str=strzcpy(str, itoas(count, "00"), -1);
	free(servquery(aserv, NMIDWARE, "websphere61", n, &count));
	str=strzcpy(str, itoas(count, "00"), -1);
	free(servquery(aserv, NMIDWARE, "tomcat5", n, &count));
	str=strzcpy(str, itoas(count, "00"), -1);
	free(servquery(aserv, NMIDWARE, "tomcat6", n, &count));
	str=strzcpy(str, itoas(count, "00"), -1);
	free(servquery(aserv, NMIDWARE, "weblogic816", n, &count));
	str=strzcpy(str, itoas(count, "00"), -1);
	str[strlen(str)]='\0';
	return 1;
}

int longer(char *questr) {
	char mystr[5][32];
	int i=0;
	int count=0;
	char *str, *pst;
	str=pst=questr;
	while ((pst=strstr(str, "\t"))!=NULL) {
		memset(mystr[i], 0x00, 32);
		strncpy(mystr[i], str, pst-str);
		i++;
		str=pst+1;
	}

	if(strcmp(mystr[0],Passwd)!=0){
		return -1;
	}
	if(strcmp(servquery(aserv, NSID, mystr[2], 1, &count)->next->user,mystr[1])!=0){
		return -1;
	}
	
	longerserv(aserv, mystr[2], mystr[3], mystr[4]);
	servwrite(aserv, servertxt);
	return 0;
}
void getpasswod(char *str) {
	memset(str, 0x00, MAXBUF+1);
	strncpy(str, Passwd, 8);
	str[strlen(str)]='\0';
}

int judque(char *str){
	return str[0]-65;
}

int process(char *in,char *out){
	int mycase=judque(in);
	in++;
	switch(mycase){
	case 1:
		//A��Ҫ���г������������Ƿ����з���
		//A	username	
		//�Ƿ���������+�Ƿ����з���+2λ��������*8
		firstcall(in, out);
		break
	case 2:
		//B��Ҫ�󷵻����룬
		//����8λ����
		getpasswod(out);
		break;
	case 3:
		//C��������񣬷��ط�����Ϣ
		//C	midware	username	startdate	outdate	
		//����1λ����
		makeserver(in);
	case 4:
		
		//D���������������
		//D	passwd	username	midware	startdate	outdate	
		//����1λ����
	case 5:
		//E:�г����й������
		//E	username
		//serv*n
	case 6:
		//F:�ӳ�����ʹ��ʱ��
		//F	passwd	username	sid	thisdate	outdate
		//����1λ���֣�
		longer(in);
		break;
	case 7:
		//G:�˻ط���
		//G	username	sid
		//����1λ���֣�
		deletserver(in);
		break;
	case 8:
		//H,��������
		//H	username	sid
		//����1λ����
	case 9:
		//I,ֹͣ����
		//H	username	sid
		//����1λ����
	case 10:
		//J ǿ�ƹر�
		//H	username	sid
		//����1λ����
	default: break;
	};
	return 0;
}

int main() {
	initservdeal(servdeal);
	makezifuji();
	srand((int)time(NULL));
	aserv=servread(servertxt);
	char str[MAXBUF + 1];
	//makepassword(Passwd);
	//getpasswod(str);
	//printf("%s\n",str);
	//printf("%d\n",lastserver);
//	makeserver("weblogic813	aa	NUSERTO	sdsad	dsfsaa	");
	//deletserver("4");
//	firstcall("zhangzeng", str);
	longer("abcdefgh	sdas	16	11111	22222	");
	listyserv("NULL", str);
	//servprint(aserv);
	printf("%s", str);

	//	int sockfd, new_fd;
	//	socklen_t len;
	//	
	//	
	//	struct sockaddr_in my_addr, their_addr;
	//	unsigned int myport, lisnum;
	//	char buf[MAXBUF + 1];
	//	
	//	myport = 7838;
	//	lisnum = 2;
	//
	//	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
	//		perror("socket");
	//		exit(1);
	//	} else
	//		printf("socket created\n");
	//
	//	bzero(&my_addr, sizeof(my_addr));
	//	my_addr.sin_family = PF_INET;
	//	my_addr.sin_port = htons(myport);
	//
	//	my_addr.sin_addr.s_addr = INADDR_ANY;
	//
	//	if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))
	//			== -1) {
	//		perror("bind");
	//		exit(1);
	//	} else
	//		printf("binded\n");
	//
	//	if (listen(sockfd, lisnum) == -1) {
	//		perror("listen");
	//		exit(1);
	//	} else
	//		printf("begin listen\n");
	//
	//	while (1) {
	//		len = sizeof(struct sockaddr);
	//		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &len))
	//				== -1) {
	//			perror("accept");
	//			exit(errno);
	//		} else
	//			printf("server: got connection from %s, port %d, socket %d\n",
	//					inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port),
	//					new_fd);
	//
	//		/* ��ʼ����ÿ���������ϵ������շ� */
	//
	//		bzero(buf, MAXBUF + 1);
	//		/* ���տͻ��˵���Ϣ */
	//		len = recv(new_fd, buf, MAXBUF, 0);
	//		if (len > 0)
	//			printf("������Ϣ�ɹ�:'%s'����%d���ֽڵ�����\n", buf, len);
	//		else
	//			printf("��Ϣ����ʧ�ܣ����������%d��������Ϣ��'%s'\n", errno, strerror(errno));
	//	
	//	bzero(buf, MAXBUF + 1);
	//	strcpy(buf, "���������ӽ����ɹ�����ͻ��˷��͵ĵ�һ����Ϣ\n");
	//	/* ����Ϣ���ͻ��� */
	//	len = send(new_fd, buf, strlen(buf), 0);
	//	if (len < 0) {
	//		printf("��Ϣ'%s'����ʧ�ܣ����������%d��������Ϣ��'%s'\n", buf, errno, strerror(errno));
	//	} else
	//		printf("��Ϣ'%s'���ͳɹ�����������%d���ֽڣ�\n", buf, len);
	//
	//	/* ����ÿ���������ϵ������շ����� */
	//	close(new_fd);
	//	}
	//	close(sockfd);
	return 0;
}
