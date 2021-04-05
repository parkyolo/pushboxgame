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
	//level 이 1 일 때
	if(lev == 1){
		//박스와 골 a의 위치가 같아지면 a = 1
		if(YPosition == 5 && XPosition == 11){
			*a = 1;
		}
		//박스와 골 b의 위치가 같아지면 b = 1
		else if(YPosition == 6 && XPosition == 11){
			*b = 1;
		}
		//박스와 골 c의 위치가 같아지면 c = 1
		else if(YPosition == 7 && XPosition == 11){
			*c = 1;
		}
	}
	//level 이 2 일 때
	else if(lev == 2){
		//박스와 골 a의 위치가 같아지면 a = 1
		if(YPosition == 6 && XPosition == 11){
			*a = 1;
		}
		//박스와 골 b의 위치가 같아지면 b = 1
		else if(YPosition == 6 && XPosition == 12){
			*b = 1;
		}
		//박스와 골 c의 위치가 같아지면 c = 1
		else if(YPosition == 6 && XPosition == 13){
			*c = 1;
		}
	}
	else if(lev == 3){
		//박스와 골 a의 위치가 같아지면 a = 1
		if(YPosition == 5 && XPosition == 11){
			*a = 1;
		}
		//박스와 골 b의 위치가 같아지면 b = 1
		else if(YPosition == 6 && XPosition == 12){
			*b = 1;
		}
		//박스와 골 c의 위치가 같아지면 c = 1
		else if(YPosition == 7 && XPosition == 11){
			*c = 1;
		}
	}
	else if(lev == 4){
		//박스와 골 a의 위치가 같아지면 a = 1
		if(YPosition == 6 && XPosition == 12){
			*a = 1;
		}
		//박스와 골 b의 위치가 같아지면 b = 1
		else if(YPosition == 6 && XPosition == 14){
			*b = 1;
		}
		//박스와 골 c의 위치가 같아지면 c = 1
		else if(YPosition == 7 && XPosition == 13){
			*c = 1;
		}
		//박스와 골 d의 위치가 같아지면 c = 1
		else if(YPosition == 8 && XPosition == 12){
			*d = 1;
		}//박스와 골 e의 위치가 같아지면 c = 1
		else if(YPosition == 8 && XPosition == 14){
			*e = 1;
		}
		//박스와 골 f의 위치가 같아지면 c = 1
		else if(YPosition == 9 && XPosition == 13){
			*f = 1;
		}
	}
	else if(lev == 5){
		//박스와 골 a의 위치가 같아지면 a = 1
		if(YPosition == 8 && XPosition == 11){
			*a = 1;
		}
		//박스와 골 b의 위치가 같아지면 b = 1
		else if(YPosition == 8 && XPosition == 13){
			*b = 1;
		}
		//박스와 골 c의 위치가 같아지면 c = 1
		else if(YPosition == 10 && XPosition == 13){
			*c = 1;
		}
	}
}

void SuccessMessage(int a, int b, int c, int d, int e, int f) {
	//박스와 사용자가 모두 Match 되었을 때 "Success" 메세지 출력
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
    bool restart = false; //맵을 restart 하는지 판별
 	int a, b, c, d, e, f; //임의의 골
    chtype up, lf, dw, rg, oup, olf, odw, org;
    up = (mvinch(obj[0].yPosition-1, obj[0].xPosition) & A_CHARTEXT); //사용자 커서의 한 칸 위
    lf = (mvinch(obj[0].yPosition, obj[0].xPosition-1) & A_CHARTEXT); //사용자 커서의 한 칸 왼쪽
    dw = (mvinch(obj[0].yPosition+1, obj[0].xPosition) & A_CHARTEXT); //사용자 커서의 한 칸 아래
    rg = (mvinch(obj[0].yPosition, obj[0].xPosition+1) & A_CHARTEXT); //사용자 커서의 한 칸 오른쪽
    oup = (mvinch(obj[0].yPosition-2, obj[0].xPosition) & A_CHARTEXT); //사용자 커서의 두 칸 위
    olf = (mvinch(obj[0].yPosition, obj[0].xPosition-2) & A_CHARTEXT); //사용자 커서의 두 칸 왼쪽
    odw = (mvinch(obj[0].yPosition+2, obj[0].xPosition) & A_CHARTEXT); //사용자 커서의 두 칸 아래
    org = (mvinch(obj[0].yPosition, obj[0].xPosition+2) & A_CHARTEXT); //사용자 커서의 두 칸 오른쪽

	//x좌표와 y좌표에 사용자의 위치 설정
    for(int o = 0; o<=wbox; o++) { mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].ozn);}

    switch (input)
    {
        case 'w':
        case 'W':
		case KEY_UP:		
        if(up != 35) //up 이 벽이 아닐 때
        {
			step += 1; //step 횟수 증가
			mvprintw(2,30,"Step : %d", step); //step 횟수 출력
            if (up == 64 && (oup == 45 || oup ==120)) //up이 박스이고 박스의 up이 빈 공간('-')이거나 골('x') 일 때
            {

                obj[0].yPosition -= 1; //사용자 위로 이동
                for(int o = 1; o <=wbox; o++)
                {
					//사용자의 위치와 PUSHBOX의 위치가 같을 때
                    if((obj[0].yPosition == obj[o].yPosition)&&(obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX가 위로 이동
                       	obj[o].yPosition -= 1;
						//골에 도착했는지 확인
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//박스가 이동할 때 push 횟수 증가
						push += 1;
						//push 횟수 출력
						mvprintw(2,15,"Push : %d", push);
               		}
				}
            }
			//벽을 만나면 이동하지 않음
            else if(up != 64) obj[0].yPosition -= 1;
        }
		//success 메세지 출력
	    SuccessMessage(a, b, c, d, e, f);
		break;

        case 's':
        case 'S':
		case KEY_DOWN:
        if(dw != 35) //down 이 벽이 아닐 때
        {
   			step += 1; //step 횟수 증가
			mvprintw(2,30,"Step : %d", step); //step 횟수 출력
            if(dw == 64 && (odw == 45 || odw == 120)) //down이 박스이고 박스의 down이 빈 공간('-')이거나 골('x')일 때
            {
                obj[0].yPosition += 1; //사용자 위로 이동
                for (int o = 1; o<= wbox; o++)
                {
					//사용자의 위치와 PUSHBOX의 위치가 같을 때
                    if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX가 아래로 이동
                        obj[o].yPosition += 1;
						//골에 도착했는지 확인
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//박스가 이동할 때 push 횟수 증가
						push += 1;
						//push 횟수 출력
						mvprintw(2,15,"Push : %d", push);
            		}
				}
            }
			//벽을 만나면 이동하지 않음
            else if (dw != 64) obj[0].yPosition += 1;
        }
		//success 메세지 출력
	    SuccessMessage(a, b, c, d, e, f);
		break;

        case 'a':
        case 'A':
		case KEY_LEFT: 
        if(lf != 35) //left 가 벽이 아닐 때
        {
			step += 1; //step 횟수 증가
			mvprintw(2,30,"Step : %d", step); //step 횟수 출력
            if(lf == 64 && (olf == 45 || olf == 120)) //left가 박스이고 박스의 left가 빈 공간('-')이거나 골('x')일 때
            {
				//사용자 왼쪽으로 이동
                obj[0].xPosition -= 1;
                for (int o = 1; o<= wbox; o++)
                {
					//사용자의 위치와 PUSHBOX의 위치가 같을 때
                    if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX가 왼쪽으로 이동
                        obj[o].xPosition -= 1;
						//골에 도착했는지 확인
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//박스가 이동할 때 push 횟수 증가
						push += 1;
						//push 횟수 출력
						mvprintw(2,15,"Push : %d", push);
              		}
				}
            }
			//벽을 만나면 이동하지 않음
            else if (lf != 64) obj[0].xPosition -= 1;
        }
		//success 메세지 출력
	    SuccessMessage(a, b, c, d, e, f);
		break;

        case 'd':
        case 'D':
		case KEY_RIGHT:
        if(rg != 35) //right 가 벽이 아닐 때
        {
			step += 1; //step 횟수 증가
			mvprintw(2,30,"Step : %d", step); //step 횟수 출력
            if(rg == 64 && (org == 45 || org == 120)) //right가 박스이고 박스의 right가 빈 공간('-')이거나 골('x')일 때
            {
                obj[0].xPosition += 1; //사용자 오른쪽으로 이동
                for (int o = 1; o<= wbox; o++)
                {
					//사용자의 위치와 PUSHBOX의 위치가 같을 때
                    if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                    {
						//PUSHBOX가 오른쪽로 이동
                        obj[o].xPosition += 1;
						//골에 도착했는지 확인
						Match(obj[o].xPosition, obj[o].yPosition, &a, &b, &c, &d, &e, &f);
						//박스가 이동할 때 push 횟수 증가
						push += 1;
						//push 횟수 출력
						mvprintw(2,15,"Push : %d", push);
               		}
				}	
            }
			//벽을 만나면 이동하지 않음
            else if (rg != 64) obj[0].xPosition += 1;
        }
		//success 메세지 출력
	    SuccessMessage(a, b, c, d, e, f);
		break;


        case 'm' :
        case 'M' :
		//초기화
		restart=TRUE;
		step = 0;
		push = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		//다음 맵으로 넘어감
		lev=lev%5 +1;
        Level(lev);
        break;
                
        case 'r' :
        case 'R' :
		//restart 할 때 초기화
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
	//restart가 아닐 때
    if(!restart)
    {
        for(int o=0;o<=wbox;o++)
        {
            obj[o].ozn = mvinch(obj[o].yPosition,obj[o].xPosition); //사용자의 위치
            mvaddch(obj[o].yPosition,obj[o].xPosition,obj[o].zn | ((o==0) ? COLOR_PAIR(3) : COLOR_PAIR(5))); //x좌표와 y좌표에 'P' 출력
        }
        move(obj[0].yPosition,obj[0].xPosition); //x좌표, y좌표로 커서 이동
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
