#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <string.h> 
#include <curses.h> 
#include<unistd.h> 

void initial();
void owellc();

void oserv12();
void oserv13();
void oserv14();
void oserv15();
static char passwd[]="dfsadfasda";
static int used=0;
int serv11() {
	int ch;

	initial();
	clear();
	mvaddstr(
			2,
			0,
			"================================================================================");
	mvaddstr(5, 0,
			"                             CI �� �� �� �� �� �� ��                            ");
	mvaddstr(
			8,
			0,
			"================================================================================");

	mvaddstr(10, 16, " [1] . CI �� �� �� ��; ");
	mvaddstr(12, 16, " [2] . CI �� �� �� ��; ");
	mvaddstr(14, 16, " [3] . �� ��; ");

	int opt=0;
	mvaddstr(10+opt*2, 13, "->");
	do {
		ch=getch();
		switch (ch) {
		case KEY_UP:
			if (opt!=0) {
				opt--;
			} else {
				opt+=2;
			}
			break;
		case KEY_DOWN:
			if (opt!=2) {
				opt++;
			} else {
				opt-=2;
			}
			break;
		case KEY_RIGHT:
			return opt;
			break;
		case '\r':
			return opt;
			break;
		default:
			break;
		}
		mvaddstr(12, 13, "  ");
		mvaddstr(14, 13, "  ");
		mvaddstr(10, 13, "  ");
		mvaddstr(10+opt*2, 13, "->");
	} while (1);

	return -1;

}

int Pserv12() {

	initial();
	clear();
	mvaddstr(
			2,
			0,
			"================================================================================");
	mvaddstr(5, 0,
			"                                CI �� �� �� ��                             ");
	mvaddstr(
			8,
			0,
			"================================================================================");

	mvaddstr(10, 4, " ��ѡ������Ҫ�ķ������ͣ� ");
	mvaddstr(12, 4, " [1] . BEA Weblogic 813; ");
	mvaddstr(13, 4, " [2] . BEA Weblogic 816; ");
	mvaddstr(14, 4, " [3] . BEA Weblogic 920; ");
	mvaddstr(15, 4, " [4] . IBM Websphere 5.2; ");
	mvaddstr(16, 4, " [5] . IBM Websphere 6.0; ");
	mvaddstr(17, 4, " [6] . Tomcat 5.0; ");
	mvaddstr(18, 4, " [7] . Tomcat 6.0; ");
	mvaddstr(19, 4, " [8] . �˳�; ");

	int ch, opt=0;
	mvaddstr(12+opt, 1, "->");
	do {
		ch=getch();
		switch (ch) {
		case KEY_UP:
			if (opt!=0) {
				opt--;
			} else {
				opt+=7;
			}
			break;
		case KEY_DOWN:
			if (opt!=7) {
				opt++;
			} else {
				opt-=7;
			}

			break;
		case KEY_RIGHT:
			return opt;
			break;
		case KEY_LEFT:
			return -1;
			break;
		case '\r':
			return opt;
			break;
		default:
			break;
		}

		mvaddstr(12, 1, "  ");
		mvaddstr(13, 1, "  ");
		mvaddstr(14, 1, "  ");
		mvaddstr(15, 1, "  ");
		mvaddstr(16, 1, "  ");
		mvaddstr(17, 1, "  ");
		mvaddstr(18, 1, "  ");
		mvaddstr(19, 1, "  ");
		mvaddstr(12+opt, 1, "->");
	} while (1);

	echo();
	char string1[80];
	getstr(string1);

	return -2;
}


void Pserv14b(char *string) {

	
	initial();
	clear();
	mvaddstr(
			2,
			0,
			"================================================================================");
	mvaddstr(5, 0,
			"                                CI �� �� �� ��                             ");
	mvaddstr(
			8,
			0,
			"================================================================================");

	mvaddstr(10, 4, " ���벻�����������������룬���������������Ա���������ʼ���");
	mvaddstr(11, 4, " ֱ�ӻس�������һ��");
	mvaddstr(13, 4, " Password��");
	echo();
	wgetstr(stdscr,string);
	
	endwin();

}

void Pserv14(char *string) {

	
	initial();
	clear();
	mvaddstr(
			2,
			0,
			"================================================================================");
	mvaddstr(5, 0,
			"                                CI �� �� �� ��                             ");
	mvaddstr(
			8,
			0,
			"================================================================================");

	mvaddstr(10, 4, " �������ʹ�����޹�����������ʹ����������");
	mvaddstr(11, 4,	" ���������룬���������������Ա���������ʼ���");
	mvaddstr(12, 4, " ֱ�ӻس�������һ��");
	mvaddstr(14, 4, " Password��");
	echo();
	wgetstr(stdscr,string);
	
	endwin();

}
void Pserv15(char *string) {

	
	initial();
	clear();
	mvaddstr(
			2,
			0,
			"================================================================================");
	mvaddstr(5, 0,
			"                                CI �� �� �� ��                             ");
	mvaddstr(
			8,
			0,
			"================================================================================");

	mvaddstr(10, 4, " ���������ķ�����;��");
	mvaddstr(11, 4, " ֱ�ӻس�������һ��");
	mvaddstr(13, 4, " ʹ���ڣ�");
	echo();
	wgetstr(stdscr,string);
	
	endwin();

}


int Pserv13() {
	

	initial();
	clear();

	mvaddstr(
			2,
			0,
			"================================================================================");
	mvaddstr(5, 0,
			"                                CI �� �� �� ��                             ");
	mvaddstr(
			8,
			0,
			"================================================================================");

	mvaddstr(10, 4, " ��ѡ������Ҫ��ʹ�����ޣ� ");
	mvaddstr(12, 4, " [1] . 1��������; ");
	mvaddstr(13, 4, " [2] . 2��������; ");
	mvaddstr(14, 4, " [3] . 3��������; ");
	mvaddstr(15, 4, " [4] . 5�������գ����ʼ����룩; ");
	mvaddstr(16, 4, " [5] . 10�������գ����ʼ����룩; ");
	mvaddstr(17, 4, " [6] . �˳� ");

	int ch, opt=0;
	mvaddstr(12+opt, 1, "->");
	do {
		ch=getch();
		switch (ch) {
		case KEY_UP:
			if (opt!=0) {
				opt--;
			} else {
				opt+=5;
			}
			break;
		case KEY_DOWN:
			if (opt!=5) {
				opt++;
			} else {
				opt-=5;
			}

			break;
		case KEY_RIGHT:
			return opt;
			break;
		case KEY_LEFT:
			return -1;
			break;
		case '\r':
			return opt;
			break;
		default:
			break;
		}

		mvaddstr(12, 1, "  ");
		mvaddstr(13, 1, "  ");
		mvaddstr(14, 1, "  ");
		mvaddstr(15, 1, "  ");
		mvaddstr(16, 1, "  ");
		mvaddstr(17, 1, "  ");
		mvaddstr(12+opt, 1, "->");
	} while (1);

	return -2;
}

void owellc() {
	int opt=0;
	opt=serv11();
	if (opt==0) {
		endwin();
		oserv12();
	} else if (opt==1) {
		endwin();
		oserv13();
	} else {
		endwin();
	}
}

//��ÿ��÷������//������룬���ܣ�//����Ƿ��Ѿ��з�����
void oserv12() {
	int opt=0;
	opt=Pserv12();
	if (opt==-1) {
		endwin();
		owellc();
	} else if (opt==7) {
		endwin();
	} else {
		endwin();
		oserv13();
	}
}


void oserv13() {
	int opt=0;
	opt=Pserv13();

	if (opt==-1) {
		endwin();
		oserv12();
	} 
	else if(opt<3 && used==0){
		endwin();
		oserv15();
	}else if (opt==5) {
		endwin();
	} 
	else {
		endwin();
		oserv14();
	}

}


void oserv14(){
	
	char string[16];
	memset(string,0x00,16);
	Pserv14(string);
//	while(strcmp(string,passwd)!=0){
//		if(strlen(string)==0){
//			oserv13();
//		}
//		memset(string,0x00,16);
//		Pserv14b(string);
//	}
	while(strlen(string)!=0){
		if(strcmp(string,passwd)!=0){
			memset(string,0x00,16);
			Pserv14b(string);	
		}
		else {
			oserv15();
		}
	}
	oserv13();
	//printf("%s",string);
	

}

//���������ͣ��û�����ʹ�����޷�����������
void oserv15(){
	
	char string[128];
	memset(string,0x00,128);
	Pserv15(string);
	if(strlen(string)==0){
		oserv13();
	}
	else{
		printf("%s",string);
		//oserv16();
	}

}
int main(void) {

	owellc();
	return 0;
}

void initial() {
	initscr();
	cbreak();
	nonl();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	refresh();
}
