#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<time.h>
#pragma comment ( lib, "Winmm.lib" )//���������õ�

#define W 676

void shuaxin(int *a);
void startup();
void fx(int i, int x, int y);
void show();
void change(int input);
void play();
boolean again();
void getscore();
void setscore();
void showinfo();

IMAGE back, replay, win, lose, info;
MOUSEMSG mouse;

int a[10];//����ȫ�ֱ������ڲ���
int step[10];// ˢ�����̵Ĳ��� 
int ischeat = 0;//����
int count = 0;//����
int  wintime = 0;
int  losetime = 0;
//Ӯ����Ĵ���
int w1 = 0, w2 = 0, w3 = 0, l1 = 0, unknow = 0;
//Ӯ�óɾ�123����ģ�δ֪����

void showinfo() {
	putimage(0, 0, &info);
	//�ɾ�
	{
		if (w1)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 30, 30);
		if (w2)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 130, 30);
		if (w3)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 238, 30);
		if (l1)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 350, 30);
		if (unknow)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 467, 30);
	}
	//����
	{
		settextstyle(100, 0, _T("�����п�"));
		settextcolor(RGB(255, 255, 255));
		TCHAR a[5], b[5];
		sprintf(a, "%d", wintime);//������aת�����ַ���
		outtextxy(44, 166, a);
		sprintf(b, "%d", losetime);//������aת�����ַ���
		outtextxy(44, 508, b);
	}
	//����
	{
		if (ischeat) {
			settextstyle(80, 0, _T("�����п�"));
			settextcolor(RGB(255, 255, 255));
			TCHAR s[15] = { '\0' }, t[15];
			//sprintf(s,"step");//����������stepת�����ַ���
			for (int i = 0; i < 10; i++) {
				sprintf(t, "%d", step[i]);//ÿ���ŵ��м����t��
				strcat(s, t);//�е�s��
			}
			outtextxy(233, 580, s);
		}
	}
	FlushBatchDraw();
}
//չʾ�ɾͺ����׺�ʤ��ʧ����
void getscore() {
	FILE * fp;
	fp = fopen("rec/score.txt", "r");
	if (fp == NULL) {
		fp = fopen("rec/score.txt", "w");
		fprintf(fp, "%d %d", wintime, losetime);
	}
	else
		fscanf(fp, "%d %d", &wintime, &losetime);

	fclose(fp);
}
//���ļ��ڻ�ȡ������д��wintime��losetime
void setscore() {
	FILE * fp;
	fp = fopen("rec/score.txt", "w");
	fprintf(fp, "%d %d", wintime, losetime);
	fclose(fp);
}
//д��wintime��losetime
boolean again() {
	HWND window = GetHWnd();//��ȡ����
	SetWindowText(window, _T("������"));//���ô��ڱ���

	cleardevice();//���֮ǰ������������
	putimage(0, 0, &replay);//repaly��ͼƬ
	FlushBatchDraw();
	//long timeend,time ;
	//settextstyle(100, 0, _T("����"));
	//setcolor(RGB(255, 255, 255));
	TCHAR s[5];
	while (true)//ѭ��ʵ��
	{
		mouse = GetMouseMsg();
		if (mouse.mkLButton) {
			if (mouse.x > 50 && mouse.y > 450 && mouse.x < 200 && mouse.y < 600)
				return false;
			//���ؼٲ�����exit��������
			//����������������
			if (mouse.x > 470 && mouse.y > 450 && mouse.x < 600 && mouse.y < 600)
				return true;
			//���������exit
		}
		//time������ʱȷʵ��������˼·a 
	}
}
//���������Ľ���
void startup() {
	initgraph(W, W);
	setbkcolor(RGB(32, 13, 6));//��Ҫ��Ϊʲô�������ɫ�ʾ������߾ȹ�again

	loadimage(&win, "rec/win.jpg");
	loadimage(&lose, "rec/lose.jpg");
	loadimage(&back, "rec/back.jpg");
	loadimage(&replay, "rec/replay.jpg");
	loadimage(&info, "rec/info.jpg");
	//����ͼƬ
	mciSendString("open rec/bg.mp3 alias bgmusic", NULL, 0, NULL);
	mciSendString("play bgmusic repeat", NULL, 0, NULL);
	//��ʼ���ű������֣�ѭ����
	getscore();
	//�÷�
	BeginBatchDraw();
	//��ʼ������ͼ
}
//��ʼ��
void fx(int i, int x, int y) {
	if (a[i] == -1) {
		setfillcolor(RGB(255, 255, 255));
		setcolor(RGB(0, 0, 0));
	}
	//-1�ǰ�ɫ���ɫ��
	else {
		setfillcolor(RGB(0, 0, 0));
		setcolor(RGB(255, 255, 255));
	}
	//�����Ǻ���ױ�
	fillcircle(x, y, 55);
	//����Բ
}
//������ɫ
void show() {
	putimage(0, 0, &back);
	//����ͼƬ����
	fx(1, 205, 205);
	fx(2, 335, 205);
	fx(3, 469, 205);
	fx(4, 205, 335);
	fx(5, 335, 335);
	fx(6, 469, 335);
	fx(7, 205, 469);
	fx(8, 335, 469);
	fx(9, 469, 469);
}
//������ 
void change(int input) {
	switch (input) {
	case '1':
	case 1://�������̺�playʱ���õĲ�һ��һ����getchһ����������д�������ⶫ������Ӧ 
		a[1] *= -1;
		a[2] *= -1;
		a[4] *= -1;
		break;
	case '2':
	case 2:
		a[2] *= -1;
		a[1] *= -1;
		a[3] *= -1;
		a[5] *= -1;
		break;
	case '3':
	case 3:
		a[3] *= -1;
		a[2] *= -1;
		a[6] *= -1;
		break;
	case '4':
	case 4:
		a[4] *= -1;
		a[1] *= -1;
		a[5] *= -1;
		a[7] *= -1;
		break;
	case '5':
	case 5:
		a[5] *= -1;
		a[2] *= -1;
		a[4] *= -1;
		a[6] *= -1;
		a[8] *= -1;
		break;
	case '6':
	case 6:
		a[6] *= -1;
		a[3] *= -1;
		a[5] *= -1;
		a[9] *= -1;
		break;
	case '7':
	case 7:
		a[7] *= -1;
		a[4] *= -1;
		a[8] *= -1;
		break;
	case '8':
	case 8:
		a[8] *= -1;
		a[5] *= -1;
		a[7] *= -1;
		a[9] *= -1;
		break;
	case '9':
	case 9:
		a[9] *= -1;
		a[6] *= -1;
		a[8] *= -1;
	}
}
//��������
void shuaxin(int *a) {
	for (int i = 1; i < 10; i++)
		a[i] = -1;
	//����ȫΪ-1��Ҳ���ǳɹ���
	srand((unsigned)time(NULL));
	//ʱ������
	for (int i = 0; i < 10; i++) {
		int suiji = rand() % 9 + 1;
		//1-9���ȡֵ
		step[i] = suiji;
		change(suiji);
		//�Գɹ�����������10�α�֤15���ڿ��Գ���
	}
	for (int i = 0; i < 5; i++)	//���������������
	{
		int p;
		p = step[i];
		step[i] = step[10 - i - 1];
		step[10 - 1 - i] = p;
	}
}
//�����µ�����
void play() {
	count = 0;
	//�߹��Ĵ���
	while (true)
	{
		HWND window = GetHWnd();//��ȡ����
		SetWindowText(window, _T("�任��"));//���ô��ڱ���

		FlushBatchDraw();
		//����һ֡ˢ��
		show();
		//���ú���������
		if (count >= 15) {//�ж��Ƿ�����	
			count = 0;
			ischeat = 0;
			//��ʼ��
			losetime++;
			//���������������ļ�ȡ��
			putimage(0, 0, &lose);
			//չʾʧ��ͼƬ
			FlushBatchDraw();
			//��֡
			Sleep(1000);
			if (again()) {
				setscore();
				exit(0);
			}
			else
				return;
		}
		int winflag = 0;
		for (int i = 1; i < 10; i++) {
			if (a[i] == -1)
				winflag++;
		}// 9�����Ӷ���-1
		if (winflag == 9) {
			winflag = 0;
			ischeat = 0;
			//��ʼ��
			wintime++;
			//ʤ��������һ
			putimage(0, 0, &win);
			//Ӯ��ͼƬ
			FlushBatchDraw();
			//ˢ��֡
			Sleep(1000);
			if (again()) {
				setscore();
				exit(0);
			}
			else
				return;
		}
		mouse = GetMouseMsg();
		//ѭ����ȡ����������mousehit
		switch (mouse.uMsg) {
		case WM_LBUTTONDOWN:
		{
			if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 136 && mouse.y <= 272))
				change(1);
			if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 136 && mouse.y <= 272))
				change(2);
			if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 136 && mouse.y <= 272))
				change(3);

			if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 273 && mouse.y <= 408))
				change(4);
			if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 273 && mouse.y <= 408))
				change(5);
			if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 273 && mouse.y <= 408))
				change(6);

			if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 409 && mouse.y <= 544))
				change(7);
			if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 409 && mouse.y <= 544))
				change(8);
			if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 409 && mouse.y <= 544))
				change(9);
			FlushBatchDraw();
			count++;
			//������һ
			mciSendString("close click", NULL, 0, NULL);
			mciSendString("open rec/click.mp3 alias click", NULL, 0, NULL);
			mciSendString("play click", NULL, 0, NULL);
			//����һ��������
		}
		break;
		case WM_RBUTTONDOWN:
			showinfo();
			break;
		case WM_MBUTTONDOWN:
			ischeat = 1;//����м�����ģʽ
			unknow = 1;
			break;
		}
		/*if (mouse.mkRButton) {
			//�Ҽ�����
			showinfo();
		}

		if (mouse.mkLButton) {
			//�������
			//if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 136 && mouse.y <= 272))
					change(1);
				if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 136 && mouse.y <= 272))
					change(2);
				if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 136 && mouse.y <= 272))
					change(3);

				if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 273 && mouse.y <= 408))
					change(4);
				if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 273 && mouse.y <= 408))
					change(5);
				if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 273 && mouse.y <= 408))
					change(6);

				if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 409 && mouse.y <= 544))
					change(7);
				if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 409 && mouse.y <= 544))
					change(8);
				if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 409 && mouse.y <= 544))
					change(9);
				FlushBatchDraw();
				count++;
				//������һ
				mciSendString("close click", NULL, 0, NULL);
				mciSendString("open rec/click.mp3 alias click", NULL, 0, NULL);
				mciSendString("play click", NULL, 0, NULL);
				//����һ��������
			}
		}

		if (mouse.mkMButton) {
			ischeat = 1;//����м�����ģʽ
			unknow = 1;
		}*/


		if (wintime >= 10)
			w1 = 1;
		if (wintime >= 50)
			w2 = 1;
		if (wintime >= 100)
			w3 = 1;
		if (losetime >= 100)
			l1 = 1;

		if (kbhit())
		{
			int input;
			input = getch();
			if (input == 27) {//����
				setscore();
				exit(0);
			}
		}
	}
}
//��ʼ��Ϸ��������������ʧ�ܡ��ɹ��жϣ����̵��ʵ��
int main() {
	startup();
	while (true)
	{
		shuaxin(a);
		show();
		play();
		setscore();
		//ÿ��ѭ����д���ļ�
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
//������