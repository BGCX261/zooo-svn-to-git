#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
//#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUF 1024


void initsock(int sockfd,int len,struct sockaddr_in dest){
	/* ����һ�� socket ���� tcp ͨ�� */
	bzero(&dest, sizeof(dest));
		dest.sin_family = AF_INET;
		dest.sin_port = htons(7838);
		if (inet_aton("10.2.7.99", (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
			perror("10.2.7.99");
			exit(errno);
		}
		printf("address created\n");
		

		/* ���ӷ����� */
		if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
			perror("Connect ");
			exit(errno);
		}
		printf("server connected\n");

}

void csend(char *buffer,int len,int sockfd){
//	bzero(buffer, MAXBUF + 1);
//		strcpy(buffer, "���ǿͻ��˷����������˵���Ϣ\n");
		/* ����Ϣ�������� */
		len = send(sockfd, buffer, strlen(buffer), 0);
		if (len < 0)
			printf("��Ϣ'%s'����ʧ�ܣ����������%d��������Ϣ��'%s'\n", buffer, errno, strerror(errno));
		else
			printf("��Ϣ'%s'���ͳɹ�����������%d���ֽڣ�\n", buffer, len);
}

void crecv(char *buffer,int len,int sockfd){
	bzero(buffer, MAXBUF + 1);
		/* ���շ�����������Ϣ */
		len = recv(sockfd, buffer, MAXBUF, 0);
		if (len > 0)
			printf("������Ϣ�ɹ�:'%s'����%d���ֽڵ�����\n", buffer, len);
		else
			printf("��Ϣ����ʧ�ܣ����������%d��������Ϣ��'%s'\n", errno, strerror(errno));
}

void fuck(char *buf,char *buf2){
	int sockfd, len;
		struct sockaddr_in dest;
		//char buffer[MAXBUF + 1];

		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("Socket");
			exit(errno);
		}
		printf("socket created\n");

		/* ��ʼ���������ˣ��Է����ĵ�ַ�Ͷ˿���Ϣ */
		
		initsock(sockfd,len,dest);
		csend(buf,len,sockfd);
		crecv(buf2,len,sockfd);
		close(sockfd);
}
int main() {
	char buf[]="aaabbbbvvv";
	//char buf1[]="ssssss";
	char buf2[255];
	fuck(buf,buf2);
	printf("this is a %s\n",buf2);
//	int sockfd, len;
//	struct sockaddr_in dest;
//	char buffer[MAXBUF + 1];
//
//	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//		perror("Socket");
//		exit(errno);
//	}
//	printf("socket created\n");
//
//	/* ��ʼ���������ˣ��Է����ĵ�ַ�Ͷ˿���Ϣ */
//	
//	initsock(sockfd,len,dest);
//	csend("aaa",len,sockfd);
//	crecv(buffer,len,sockfd);
//	close(sockfd);
//	
//	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//			perror("Socket");
//			exit(errno);
//		}
//	printf("socket created\n");
//	initsock(sockfd,len,dest);
//	csend("bbb",len,sockfd);
//	crecv(buffer,len,sockfd);


//
	/* ����һ�� socket ���� tcp ͨ�� */
//	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//		perror("Socket");
//		exit(errno);
//	}
//	printf("socket created\n");
//
//	/* ��ʼ���������ˣ��Է����ĵ�ַ�Ͷ˿���Ϣ */
//	bzero(&dest, sizeof(dest));
//	dest.sin_family = AF_INET;
//	dest.sin_port = htons(7838);
//	if (inet_aton("10.2.7.99", (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
//		perror("10.2.7.99");
//		exit(errno);
//	}
//	printf("address created\n");
//
//	/* ���ӷ����� */
//	if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
//		perror("Connect ");
//		exit(errno);
//	}
//	printf("server connected\n");
//
//	/* ���նԷ�����������Ϣ�������� MAXBUF ���ֽ� */
//	
//
//	bzero(buffer, MAXBUF + 1);
//	strcpy(buffer, "aaa\n");
//	/* ����Ϣ�������� */
//	len = send(sockfd, buffer, strlen(buffer), 0);
//	if (len < 0)
//		printf("��Ϣ'%s'����ʧ�ܣ����������%d��������Ϣ��'%s'\n", buffer, errno, strerror(errno));
//	else
//		printf("��Ϣ'%s'���ͳɹ�����������%d���ֽڣ�\n", buffer, len);
//	
//	bzero(buffer, MAXBUF + 1);
//		/* ���շ�����������Ϣ */
//		len = recv(sockfd, buffer, MAXBUF, 0);
//		if (len > 0)
//			printf("������Ϣ�ɹ�:'%s'����%d���ֽڵ�����\n", buffer, len);
//		else
//			printf("��Ϣ����ʧ�ܣ����������%d��������Ϣ��'%s'\n", errno, strerror(errno));

	/* �ر����� */
	//close(sockfd);
	return 0;
}
