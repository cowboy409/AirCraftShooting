#include "position.h"
// stdio,stdlib,conio,time,windows 헤더파일이 인클루드 했음.
// 덤으로 커서 이동에 관한 함수 gotoxy,setcursortype가 있다.

#define MAXBULLET 1000 //최대 총알 갯수

//총알에 대한 정보
struct bullet
{
     BOOL exist;		//총알의 존재여부
     int x,y;			//총알위치
     int nFrame;		//이동주기 틀
     int nStay;			//이동주기마다 신호를 보내도록 함.
} BULLET[MAXBULLET];

////////////////////////////////////////////////////////////
////////////////////함수의 선언부분//////////////////////////

void Start();//시작을 위한 함수.
void AllyUnitPosition(int* ax,int* ay);// 아군 위치 출력
void bulletset(int BulletNumControl); // 총알 세팅
void bulletmm(int BulletNumControl); // 총알 출력과 제거처리;
void background();// 배경 출력
void TimeCalc(int* timeh,unsigned int* Time,int* stage); //시간
void Bang(int* ax, int BulletNumControl); //충돌 조사
void Leftmove(int* ax,int* ay);//왼쪽으로 이동
void Rightmove(int* ax,int* ay);//오른쪽으로 이동
bool IsKeyDown(int key);//키가 눌려졌는지 조사

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

//main함수의 시작
int main()
{
	int i=0;
	int ax,ay;//아군 유닛의 x좌표 y좌표
	int move=0;
	int stage=1;
	int BulletNumControl; //총알 갯수를 제어하는 변수이다.
	int timeh=0;
	unsigned int Time=0; //시간 
	ax=15;ay=20;
	
	background(); //배경을 그리는 함수
	gotoxy(62,6);
	printf("버틴 시간");
	gotoxy(62,7);
	printf("%6d초",Time);
	gotoxy(62,9);
	printf("Stage :");
	gotoxy(70,9);
	printf("%d",stage);

	Start(); //시작을 알리는 함수
	
	srand((unsigned int)time(NULL)); // rand의 초기화

	while(1)
	{

	BulletNumControl=100/stage;

	if(IsKeyDown('J')) //좌로 이동
	{
		Leftmove(&ax,&ay);
	}
	if(IsKeyDown('L')) //우로 이동
	{
		Rightmove(&ax,&ay);
	}

	AllyUnitPosition(&ax,&ay); //위치 출력
	bulletset(BulletNumControl);//총알 셋팅
	bulletmm(BulletNumControl);//총알의 이동과 제거처리
	TimeCalc(&timeh,&Time,&stage); //시간을 계산+출력합니다.
	Bang(&ax, BulletNumControl); //충돌을 조사합니다.
	Sleep(10);

	}
	return 0;
}

//시작을 위한 함수
void Start()
{
	setcursortype(NOCURSOR);
	gotoxy(20,10);
	printf("총알 피하기 게임입니다.");
	gotoxy(20,12);
	printf("제작자 : 김진현");
	gotoxy(20,13);
	printf("         원재성");
	Sleep(2000);
	gotoxy(20,12);
	printf("                    ");//공백으로 문자지우기
	gotoxy(20,13);
	printf("                     ");//공백으로 문자지우기
	
	for(int i=3;i>=1;i--)
	{
	gotoxy(20,10);
	printf("     %d초 후 Start      ",i);
	Sleep(1000);
	} 
	gotoxy(20,10);
	printf("                    ");//공백으로 문자지우기
	return;
}

//시간
void TimeCalc(int* timeh,unsigned int* Time,int* stage)
{
	(*timeh)++;
	if(*timeh%100==0)
	{
		(*Time)++;
	}
	if(*timeh==2000 && *stage!=100)
	{
		*timeh=0;
		(*stage)++;
	}
	
	gotoxy(62,7);
	printf("%6d초",*Time);
	gotoxy(70,9);
	printf("%d",*stage);
	return;
}

//충돌 조사
void Bang(int* ax, int BulletNumControl)
{
	//충돌 처리
	for (int i=0;i<(MAXBULLET/BulletNumControl);i++) 
	{
		if (BULLET[i].exist==FALSE)
		{
			continue;
		}
		if ( *ax==BULLET[i].x && (BULLET[i].y==21) )
		{
			gotoxy(*ax-4,21);
			printf("...:::...");
            Sleep(500);
			gotoxy(*ax-3,20);
			printf("  :v: ");
			Sleep(500);
			gotoxy(*ax-3,19);
			printf("  :::  ");
			Sleep(500);
			gotoxy(*ax-3,18);
			printf("'':::''");
			Sleep(500);
			gotoxy(*ax-3,17);
			printf(":::::::");
			Sleep(500);
			gotoxy(*ax-3,16);
			printf(" .:^:. ");
			Sleep(500);
			gotoxy(20,12);
			printf("게임 오버다 쿠케케케케케");
			Sleep(1000);
			system("PAUSE");
			exit(1);
		}
	}
	return;
}

//왼쪽으로 움직이기
void Leftmove(int* ax,int* ay)
{
	gotoxy(*ax,*ay);
	putch(' ');
	gotoxy(*ax+1,*ay+1);
	putch(' ');
	if(*ax>6)
		(*ax)--;
	return;
}

//오른쪽으로 움직이기
void Rightmove(int* ax,int* ay)
{
	gotoxy(*ax,*ay);
	putch(' ');
	gotoxy(*ax-1,*ay+1);
	putch(' ');
	if(*ax<53)
		(*ax)++;
}

//위치출력을 위한 함수
void AllyUnitPosition(int* ax,int* ay)
{
	gotoxy(*ax,*ay);
	putch('w');
	for(int i=0;i<=2;i++)
	{
		gotoxy((*ax-1)+i,*ay+1);
		putch('M');
	}
	return;
}

//총알 셋팅
void bulletset(int BulletNumControl)
{
	if(rand()%5==0)
	{
	for(int i=0;i<(MAXBULLET/BulletNumControl);i++)
	{
		if(BULLET[i].exist!=TRUE)
		{
			BULLET[i].exist=TRUE;
			BULLET[i].x=rand()%47+6;
			BULLET[i].y=3;
			BULLET[i].nFrame=BULLET[i].nStay=rand()%15+5;
			break;
		}
	}
	}
	return;
}

//총알 출력과 제거처리
void bulletmm(int BulletNumControl)
{
	for(int i=0;i<(MAXBULLET/BulletNumControl);i++)
	{
		if(BULLET[i].exist==FALSE)
		{
			continue;
		}
		else
		{
			if(--BULLET[i].nStay==0)
			{
				BULLET[i].nStay=BULLET[i].nFrame;
				if(BULLET[i].y<21)
				{
					gotoxy(BULLET[i].x,BULLET[i].y);
					putch(' ');
					BULLET[i].y++;
					gotoxy(BULLET[i].x,BULLET[i].y);
					putch('I');
				}
				else
				{
					gotoxy(BULLET[i].x,BULLET[i].y);
					putch(' ');
					BULLET[i].exist=FALSE;
				}
			}
		}
	}	

	return;
}

//배경 그리는 함수
void background()
{
	gotoxy(0,0);
	for(int j=0;j<2;j++)
	{
	for(int i=0;i<60;i++)
	{
		printf("0");
	}
	printf("\n");
	}

	for(int j=0;j<20;j++)
	{
	for(int i=0;i<5;i++)
	{
		printf("0");
	}
	for(int i=0;i<50;i++)
	{
		printf(" ");
	}
	for(int i=0;i<5;i++)
	{
		printf("0");
	}
	if(j==15)
		printf("  키 조작");
	if(j==16)
		printf(" 왼쪽 방향키 : J");
	if(j==17)
		printf(" 오른쪽 방향키 : L");
	printf("\n");
	}

	for(int j=0;j<2;j++)
	{
	for(int i=0;i<60;i++)
	{
		printf("0");
	}
	printf("\n");
	}
	return;
}

//키가 눌렸는지 확인해주는 함수
bool IsKeyDown(int key) //bool 타입은 yes or no를 판별하는데 뛰어나다.
{
	return((GetAsyncKeyState(key) & 0x8000) !=0);
}
