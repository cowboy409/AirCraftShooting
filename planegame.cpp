#include "position.h"
// stdio,stdlib,conio,time,windows ��������� ��Ŭ��� ����.
// ������ Ŀ�� �̵��� ���� �Լ� gotoxy,setcursortype�� �ִ�.

#define MAXBULLET 1000 //�ִ� �Ѿ� ����

//�Ѿ˿� ���� ����
struct bullet
{
     BOOL exist;		//�Ѿ��� ���翩��
     int x,y;			//�Ѿ���ġ
     int nFrame;		//�̵��ֱ� Ʋ
     int nStay;			//�̵��ֱ⸶�� ��ȣ�� �������� ��.
} BULLET[MAXBULLET];

////////////////////////////////////////////////////////////
////////////////////�Լ��� ����κ�//////////////////////////

void Start();//������ ���� �Լ�.
void AllyUnitPosition(int* ax,int* ay);// �Ʊ� ��ġ ���
void bulletset(int BulletNumControl); // �Ѿ� ����
void bulletmm(int BulletNumControl); // �Ѿ� ��°� ����ó��;
void background();// ��� ���
void TimeCalc(int* timeh,unsigned int* Time,int* stage); //�ð�
void Bang(int* ax, int BulletNumControl); //�浹 ����
void Leftmove(int* ax,int* ay);//�������� �̵�
void Rightmove(int* ax,int* ay);//���������� �̵�
bool IsKeyDown(int key);//Ű�� ���������� ����

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

//main�Լ��� ����
int main()
{
	int i=0;
	int ax,ay;//�Ʊ� ������ x��ǥ y��ǥ
	int move=0;
	int stage=1;
	int BulletNumControl; //�Ѿ� ������ �����ϴ� �����̴�.
	int timeh=0;
	unsigned int Time=0; //�ð� 
	ax=15;ay=20;
	
	background(); //����� �׸��� �Լ�
	gotoxy(62,6);
	printf("��ƾ �ð�");
	gotoxy(62,7);
	printf("%6d��",Time);
	gotoxy(62,9);
	printf("Stage :");
	gotoxy(70,9);
	printf("%d",stage);

	Start(); //������ �˸��� �Լ�
	
	srand((unsigned int)time(NULL)); // rand�� �ʱ�ȭ

	while(1)
	{

	BulletNumControl=100/stage;

	if(IsKeyDown('J')) //�·� �̵�
	{
		Leftmove(&ax,&ay);
	}
	if(IsKeyDown('L')) //��� �̵�
	{
		Rightmove(&ax,&ay);
	}

	AllyUnitPosition(&ax,&ay); //��ġ ���
	bulletset(BulletNumControl);//�Ѿ� ����
	bulletmm(BulletNumControl);//�Ѿ��� �̵��� ����ó��
	TimeCalc(&timeh,&Time,&stage); //�ð��� ���+����մϴ�.
	Bang(&ax, BulletNumControl); //�浹�� �����մϴ�.
	Sleep(10);

	}
	return 0;
}

//������ ���� �Լ�
void Start()
{
	setcursortype(NOCURSOR);
	gotoxy(20,10);
	printf("�Ѿ� ���ϱ� �����Դϴ�.");
	gotoxy(20,12);
	printf("������ : ������");
	gotoxy(20,13);
	printf("         ���缺");
	Sleep(2000);
	gotoxy(20,12);
	printf("                    ");//�������� ���������
	gotoxy(20,13);
	printf("                     ");//�������� ���������
	
	for(int i=3;i>=1;i--)
	{
	gotoxy(20,10);
	printf("     %d�� �� Start      ",i);
	Sleep(1000);
	} 
	gotoxy(20,10);
	printf("                    ");//�������� ���������
	return;
}

//�ð�
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
	printf("%6d��",*Time);
	gotoxy(70,9);
	printf("%d",*stage);
	return;
}

//�浹 ����
void Bang(int* ax, int BulletNumControl)
{
	//�浹 ó��
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
			printf("���� ������ ������������");
			Sleep(1000);
			system("PAUSE");
			exit(1);
		}
	}
	return;
}

//�������� �����̱�
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

//���������� �����̱�
void Rightmove(int* ax,int* ay)
{
	gotoxy(*ax,*ay);
	putch(' ');
	gotoxy(*ax-1,*ay+1);
	putch(' ');
	if(*ax<53)
		(*ax)++;
}

//��ġ����� ���� �Լ�
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

//�Ѿ� ����
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

//�Ѿ� ��°� ����ó��
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

//��� �׸��� �Լ�
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
		printf("  Ű ����");
	if(j==16)
		printf(" ���� ����Ű : J");
	if(j==17)
		printf(" ������ ����Ű : L");
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

//Ű�� ���ȴ��� Ȯ�����ִ� �Լ�
bool IsKeyDown(int key) //bool Ÿ���� yes or no�� �Ǻ��ϴµ� �پ��.
{
	return((GetAsyncKeyState(key) & 0x8000) !=0);
}
