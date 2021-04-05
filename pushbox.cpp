#include <ncurses.h>
#include <stdlib.h>

struct Object
{
    int xPosition;
    int yPosition;
    unsigned char zn;
    chtype ozn;
};

#define N 10
struct Object obj[N] = {};

int wbox=0;
int lev= 1;
int push = 0;
int step = 0;
int next=0;

void levList(int *h, int *w, int *array, int y, int x, int n)
{
    if (n==1)
    {
        *h=9;
        *w=7;
        int map1[9][7]={
        {1,1,1,1,4,4,4},
        {1,3,0,1,1,4,4},
        {1,3,5,0,1,4,4},
        {1,3,0,2,1,4,4},
        {1,1,2,0,1,1,1},
        {4,1,0,2,0,0,1},
        {4,1,0,0,0,0,1},
   		{4,1,0,0,1,1,1},
   		{4,1,1,1,1,4,4}};
        *array = map1[y][x];
    }
    else if(n==2)
    {
        *h=7;
        *w=6;
        int map2[7][6]={
        {1,1,1,1,1,4},
        {1,0,0,0,1,4},
        {1,3,3,3,1,4},
        {1,2,2,2,1,1},
        {1,0,0,0,0,1},
        {1,0,5,0,0,1},
        {1,1,1,1,1,1}};
        *array = map2[y][x];
    }    
    else if(n==3)
    {
        *h = 6;
        *w = 8;
        int map3[6][8]={
        {1,1,1,1,1,1,1,1},
        {1,3,0,0,0,0,0,1},
        {1,0,3,2,2,2,5,1},
        {1,3,0,0,0,0,0,1},
        {1,1,1,1,1,0,0,1},
        {4,4,4,4,1,1,1,1}};
        *array=map3[y][x];
    }
    else if(n==4)
    {
        *h = 8;
        *w = 7;
        int map4[8][7]={
        {1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1},
        {1,0,3,2,3,0,1},
        {1,0,2,3,2,0,1},
        {1,0,3,2,3,0,1},
        {1,0,2,3,2,0,1},
        {1,0,0,5,0,0,1},
        {1,1,1,1,1,1,1}};
        *array=map4[y][x];
    }
    else if(n==5){
        *h=8;
        *w=10;
        int map5[8][10]={
        {4,1,1,1,1,4,4,4,4,4},
        {4,1,0,0,1,1,1,1,4,4},
        {4,1,0,0,0,0,0,1,1,4},
        {1,1,0,1,1,0,0,0,1,4},
        {1,3,0,3,1,0,5,2,1,1},
        {1,0,0,0,1,0,2,2,0,1},
        {1,0,0,3,1,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}};
        *array=map5[y][x];
    }
}

void palette()
{
    init_color(COLOR_BLACK,0,0,0);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
	init_pair(6,COLOR_RED,COLOR_YELLOW);
}

void Level(int n)
{
    clear();
    attron(COLOR_PAIR(6));
    mvprintw(1,12," PUSH BOX GAME! ");
    attroff(COLOR_PAIR(6));
    mvprintw(2,1, "MAP : %d",lev);
    mvprintw(3,1,"Restart : R    Map : M       Exit : Q");
    mvprintw(2,15,"PUSH : %d", push);
    mvprintw(2,30, "STEP : %d", step);
    int x =0, y=0, h=1, w=1, map;
    wbox=0;

    for(y=0;y<h;y++)
    {
        for(x=0;x<w;x++)
        {
            levList(&h, &w, &map, y, x, n);
            switch(map)
            {	
				case 4 : mvaddch(y+4,x+10,'~' | COLOR_PAIR(3)); break;
                case 0 : mvaddch(y+4,x+10,'-' | COLOR_PAIR(4)); break;
                case 1 : mvaddch(y+4,x+10,'#' | COLOR_PAIR(1)); break;
                case 3 : mvaddch(y+4,x+10,'x' | COLOR_PAIR(2)); break;
                case 2 : 
               		mvaddch(y+4,x+10,'-' | COLOR_PAIR(4));
               		wbox+=1;
               		obj[wbox].ozn = mvinch(y+4,x+10);
               		obj[wbox].yPosition=y+4;
               		obj[wbox].xPosition=x+10;
               		obj[wbox].zn='@';
               		mvaddch(obj[wbox].yPosition,obj[wbox].xPosition,obj[wbox].zn | COLOR_PAIR(5));
                    break;
                case 5 :
                    mvaddch(y+4,x+10,'-' |COLOR_PAIR(4));
                    obj[0].ozn = mvinch(y+4,x+10);
                    obj[0].yPosition = y+4;
                    obj[0].xPosition = x+10;
                    obj[0].zn='P';
                    mvaddch(obj[0].yPosition,obj[0].xPosition,obj[0].zn | COLOR_PAIR(3));
                    break;
               }
            }
        }
	move(obj[0].yPosition,obj[0].xPosition);
}

void Match(int XPosition, int YPosition, int *a, int *b, int *c, int *d, int *e, int *f) {
	//level �� 1 �� ��
	if(lev == 1){
		//�ڽ��� �� a�� ��ġ�� �������� a = 1
		if(YPosition == 5 && XPosition == 11){
			*a = 1;
		}
		//�ڽ��� �� b�� ��ġ�� �������� b = 1
		else if(YPosition == 6 && XPosition == 11){
			*b = 1;
		}
		//�ڽ��� �� c�� ��ġ�� �������� c = 1
		else if(YPosition == 7 && XPosition == 11){
			*c = 1;
		}
	}
	//level �� 2 �� ��
	else if(lev == 2){
		//�ڽ��� �� a�� ��ġ�� �������� a = 1
		if(YPosition == 6 && XPosition == 11){
			*a = 1;
		}
		//�ڽ��� �� b�� ��ġ�� �������� b = 1
		else if(YPosition == 6 && XPosition == 12){
			*b = 1;
		}
		//�ڽ��� �� c�� ��ġ�� �������� c = 1
		else if(YPosition == 6 && XPosition == 13){
			*c = 1;
		}
	}
	else if(lev == 3){
		//�ڽ��� �� a�� ��ġ�� �������� a = 1
		if(YPosition == 5 && XPosition == 11){
			*a = 1;
		}
		//�ڽ��� �� b�� ��ġ�� �������� b = 1
		else if(YPosition == 6 && XPosition == 12){
			*b = 1;
		}
		//�ڽ��� �� c�� ��ġ�� �������� c = 1
		else if(YPosition == 7 && XPosition == 11){
			*c = 1;
		}
	}
	else if(lev == 4){
		//�ڽ��� �� a�� ��ġ�� �������� a = 1
		if(YPosition == 6 && XPosition == 12){
			*a = 1;
		}
		//�ڽ��� �� b�� ��ġ�� �������� b = 1
		else if(YPosition == 6 && XPosition == 14){
			*b = 1;
		}
		//�ڽ��� �� c�� ��ġ�� �������� c = 1
		else if(YPosition == 7 && XPosition == 13){
			*c = 1;
		}
		//�ڽ��� �� d�� ��ġ�� �������� c = 1
		else if(YPosition == 8 && XPosition == 12){
			*d = 1;
		}//�ڽ��� �� e�� ��ġ�� �������� c = 1
		else if(YPosition == 8 && XPosition == 14){
			*e = 1;
		}
		//�ڽ��� �� f�� ��ġ�� �������� c = 1
		else if(YPosition == 9 && XPosition == 13){
			*f = 1;
		}
	}
	else if(lev == 5){
		//�ڽ��� �� a�� ��ġ�� �������� a = 1
		if(YPosition == 8 && XPosition == 11){
			*a = 1;
		}
		//�ڽ��� �� b�� ��ġ�� �������� b = 1
		else if(YPosition == 8 && XPosition == 13){
			*b = 1;
		}
		//�ڽ��� �� c�� ��ġ�� �������� c = 1
		else if(YPosition == 10 && XPosition == 13){
			*c = 1;
		}
	}
}

void SuccessMessage(int a, int b, int c, int d, int e, int f) {
	//�ڽ��� ����ڰ� ��� Match �Ǿ��� �� "Success" �޼��� ���
	if (lev == 4){
	    if(a+b+c+d+e+f ==6){
		   	mvprintw(8, 40, "Success");
			mvprintw(9, 40, "Next Stage, Push 'M'");
		}
	}
	else if (lev == 5) {
		if (a+b+c == 3) {
			mvprintw(8, 40, "Success");
			mvprintw(9, 40, "Congratulation! All Stages Cleared!");
			mvprintw(10, 40, "Restart -> M");
		}
	}
	else {
		if(a+b+c == 3){
			mvprintw(8, 40, "Success");
			mvprintw(9, 40, "Next Stage, Push 'M'");
		}
	}
}

void Play(int input)
{
    bool restart = false; //���� restart �ϴ��� �Ǻ�
 	int a, b, c, d, e, f; //������ ��
    chtype up, lf, dw, rg, oup, olf, odw, org;
    up = (mvinch(obj[0].yPosition-1, obj[0].xPosition) & A_CHARTEXT); //����� Ŀ���� �� ĭ ��
    lf = (mvinch(obj[0].yPosition, obj[0].xPosition-1) & A_CHARTEXT); //����� Ŀ���� �� ĭ ����
    dw = (mvinch(obj[0].yPosition+1, obj[0].xPosition) & A_CHARTEXT); //����� Ŀ���� �� ĭ �Ʒ�
    rg = (mvinch(obj[0].yPosition, obj[0].xPosition+1) & A_CHARTEXT); //����� Ŀ���� �� ĭ ������
    oup = (mvinch(obj[0].yPosition-2, obj[0].xPosition) & A_CHARTEXT); //����� Ŀ���� �� ĭ ��
    olf = (mvinch(obj[0].yPosition, obj[0].xPosition-2) & A_CHARTEXT); //����� Ŀ���� �� ĭ ����
    odw = (mvinch(obj[0].yPosition+2, obj[0].xPosition) & A_CHARTEXT); //����� Ŀ���� �� ĭ �Ʒ�
    org = (mvinch(obj[0].yPosition, obj[0].xPosition+2) & A_CHARTEXT); //����� Ŀ���� �� ĭ ������

	//x��ǥ�� y��ǥ�� ������� ��ġ ����
    for(int o = 0; o<=wbox; o++) { mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].ozn);}

    switch (input)
    {
        case 'w':
        case 'W':
		case KEY_UP:		
        if(up != 35) //up �� ���� �ƴ� ��
        {
			step += 1; //step Ƚ�� ����
			mvprintw(2,30,"Step : %d", step); //step Ƚ�� ���
            if (up == 64 && (oup == 45 || oup ==120)) //up�� �ڽ��̰� �ڽ��� up�� �� ����('-')�̰ų� ��('x') �� ��
            {

                obj[0].yPosition -= 1; //����� ���� �̵�
                for(int o = 1; o <=wbox; o++)
                {
					//������� ��ġ�� PUSHBOX�� ��ġ�� ���� ��
                    if((obj[0].yPosition == obj[o].yPosition)&&(obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX�� ���� �̵�
                       	obj[o].yPosition -= 1;
						//�� �����ߴ��� Ȯ��
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//�ڽ��� �̵��� �� push Ƚ�� ����
						push += 1;
						//push Ƚ�� ���
						mvprintw(2,15,"Push : %d", push);
               		}
				}
            }
			//���� ������ �̵����� ����
            else if(up != 64) obj[0].yPosition -= 1;
        }
		//success �޼��� ���
	    SuccessMessage(a, b, c, d, e, f);
		break;

        case 's':
        case 'S':
		case KEY_DOWN:
        if(dw != 35) //down �� ���� �ƴ� ��
        {
   			step += 1; //step Ƚ�� ����
			mvprintw(2,30,"Step : %d", step); //step Ƚ�� ���
            if(dw == 64 && (odw == 45 || odw == 120)) //down�� �ڽ��̰� �ڽ��� down�� �� ����('-')�̰ų� ��('x')�� ��
            {
                obj[0].yPosition += 1; //����� ���� �̵�
                for (int o = 1; o<= wbox; o++)
                {
					//������� ��ġ�� PUSHBOX�� ��ġ�� ���� ��
                    if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX�� �Ʒ��� �̵�
                        obj[o].yPosition += 1;
						//�� �����ߴ��� Ȯ��
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//�ڽ��� �̵��� �� push Ƚ�� ����
						push += 1;
						//push Ƚ�� ���
						mvprintw(2,15,"Push : %d", push);
            		}
				}
            }
			//���� ������ �̵����� ����
            else if (dw != 64) obj[0].yPosition += 1;
        }
		//success �޼��� ���
	    SuccessMessage(a, b, c, d, e, f);
		break;

        case 'a':
        case 'A':
		case KEY_LEFT: 
        if(lf != 35) //left �� ���� �ƴ� ��
        {
			step += 1; //step Ƚ�� ����
			mvprintw(2,30,"Step : %d", step); //step Ƚ�� ���
            if(lf == 64 && (olf == 45 || olf == 120)) //left�� �ڽ��̰� �ڽ��� left�� �� ����('-')�̰ų� ��('x')�� ��
            {
				//����� �������� �̵�
                obj[0].xPosition -= 1;
                for (int o = 1; o<= wbox; o++)
                {
					//������� ��ġ�� PUSHBOX�� ��ġ�� ���� ��
                    if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX�� �������� �̵�
                        obj[o].xPosition -= 1;
						//�� �����ߴ��� Ȯ��
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//�ڽ��� �̵��� �� push Ƚ�� ����
						push += 1;
						//push Ƚ�� ���
						mvprintw(2,15,"Push : %d", push);
              		}
				}
            }
			//���� ������ �̵����� ����
            else if (lf != 64) obj[0].xPosition -= 1;
        }
		//success �޼��� ���
	    SuccessMessage(a, b, c, d, e, f);
		break;

        case 'd':
        case 'D':
		case KEY_RIGHT:
        if(rg != 35) //right �� ���� �ƴ� ��
        {
			step += 1; //step Ƚ�� ����
			mvprintw(2,30,"Step : %d", step); //step Ƚ�� ���
            if(rg == 64 && (org == 45 || org == 120)) //right�� �ڽ��̰� �ڽ��� right�� �� ����('-')�̰ų� ��('x')�� ��
            {
                obj[0].xPosition += 1; //����� ���������� �̵�
                for (int o = 1; o<= wbox; o++)
                {
					//������� ��ġ�� PUSHBOX�� ��ġ�� ���� ��
                    if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX�� �����ʷ� �̵�
                        obj[o].xPosition += 1;
						//�� �����ߴ��� Ȯ��
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//�ڽ��� �̵��� �� push Ƚ�� ����
						push += 1;
						//push Ƚ�� ���
						mvprintw(2,15,"Push : %d", push);
               		}
				}	
            }
			//���� ������ �̵����� ����
            else if (rg != 64) obj[0].xPosition += 1;
        }
		//success �޼��� ���
	    SuccessMessage(a, b, c, d, e, f);
		break;


        case 'm' :
        case 'M' :
		//�ʱ�ȭ
		restart=TRUE;
		step = 0;
		push = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		//���� ������ �Ѿ
		lev=lev%5 +1;
        Level(lev);
        break;
                
        case 'r' :
        case 'R' :
		//restart �� �� �ʱ�ȭ
        restart=TRUE;
		step = 0;
		push = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		Level(lev);
        break;
        
		default:
        break;
    }
	//restart�� �ƴ� ��
    if(!restart)
    {
        for(int o=0;o<=wbox;o++)
        {
            obj[o].ozn = mvinch(obj[o].yPosition,obj[o].xPosition); //������� ��ġ
            mvaddch(obj[o].yPosition,obj[o].xPosition,obj[o].zn | ((o==0) ? COLOR_PAIR(3) : COLOR_PAIR(5))); //x��ǥ�� y��ǥ�� 'P' ���
        }
        move(obj[0].yPosition,obj[0].xPosition); //x��ǥ, y��ǥ�� Ŀ�� �̵�
    }
    else { restart = false; }
}

int main()
{
    int ch;
    
    initscr();

    keypad(stdscr, true);
    
    if(!has_colors())
    {
        endwin();
        printf("Error initialising colors.n");
        exit(1);
    }
    
    start_color();
    
    palette();
    
    Level(lev);
    
    while((ch=getch()) !='q')
    {
        Play(ch);
    }
    endwin();
    
    return 0;
}
