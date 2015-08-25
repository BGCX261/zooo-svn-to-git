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
	/* 创建一个 socket 用于 tcp 通信 */
	bzero(&dest, sizeof(dest));
		dest.sin_family = AF_INET;
		dest.sin_port = htons(7838);
		if (inet_aton("10.2.7.99", (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
			perror("10.2.7.99");
			exit(errno);
		}
		printf("address created\n");
		

		/* 连接服务器 */
		if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
			perror("Connect ");
			exit(errno);
		}
		printf("server connected\n");

}

void csend(char *buffer,int len,int sockfd){
//	bzero(buffer, MAXBUF + 1);
//		strcpy(buffer, "这是客户端发给服务器端的消息\n");
		/* 发消息给服务器 */
		len = send(sockfd, buffer, strlen(buffer), 0);
		if (len < 0)
			printf("消息'%s'发送失败！错误代码是%d，错误信息是'%s'\n", buffer, errno, strerror(errno));
		else
			printf("消息'%s'发送成功，共发送了%d个字节！\n", buffer, len);
}

void crecv(char *buffer,int len,int sockfd){
	bzero(buffer, MAXBUF + 1);
		/* 接收服务器来的消息 */
		len = recv(sockfd, buffer, MAXBUF, 0);
		if (len > 0)
			printf("接收消息成功:'%s'，共%d个字节的数据\n", buffer, len);
		else
			printf("消息接收失败！错误代码是%d，错误信息是'%s'\n", errno, strerror(errno));
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

		/* 初始化服务器端（对方）的地址和端口信息 */
		
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
//	/* 初始化服务器端（对方）的地址和端口信息 */
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
	/* 创建一个 socket 用于 tcp 通信 */
//	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//		perror("Socket");
//		exit(errno);
//	}
//	printf("socket created\n");
//
//	/* 初始化服务器端（对方）的地址和端口信息 */
//	bzero(&dest, sizeof(dest));
//	dest.sin_family = AF_INET;
//	dest.sin_port = htons(7838);
//	if (inet_aton("10.2.7.99", (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
//		perror("10.2.7.99");
//		exit(errno);
//	}
//	printf("address created\n");
//
//	/* 连接服务器 */
//	if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
//		perror("Connect ");
//		exit(errno);
//	}
//	printf("server connected\n");
//
//	/* 接收对方发过来的消息，最多接收 MAXBUF 个字节 */
//	
//
//	bzero(buffer, MAXBUF + 1);
//	strcpy(buffer, "aaa\n");
//	/* 发消息给服务器 */
//	len = send(sockfd, buffer, strlen(buffer), 0);
//	if (len < 0)
//		printf("消息'%s'发送失败！错误代码是%d，错误信息是'%s'\n", buffer, errno, strerror(errno));
//	else
//		printf("消息'%s'发送成功，共发送了%d个字节！\n", buffer, len);
//	
//	bzero(buffer, MAXBUF + 1);
//		/* 接收服务器来的消息 */
//		len = recv(sockfd, buffer, MAXBUF, 0);
//		if (len > 0)
//			printf("接收消息成功:'%s'，共%d个字节的数据\n", buffer, len);
//		else
//			printf("消息接收失败！错误代码是%d，错误信息是'%s'\n", errno, strerror(errno));

	/* 关闭连接 */
	//close(sockfd);
	return 0;
}
