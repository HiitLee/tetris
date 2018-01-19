#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define UP 72 //위
#define DOWN 80 //아래
#define RIGHT 77 //오른쪽
#define LEFT 75 //왼쪽
#define SPACE 32  //스페이스바
#define Height (20) //판 높이
#define Width (20) // 판 넓이

int t=0;
int numx=9;
int numy=1;
int block_1[4][4]=
	{
		{0,0,0,0},
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0}
	};
	int block_2[4][4]=
	{
		{0,0,0,0},
		{1,1,1,0},
		{1,0,0,0},
		{0,0,0,0}
	};

	int block_3[4][4]=
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0}
	};
	int block_4[4][4]=
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	};
	int block_5[4][4]=
	{
		{0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0}
	};

	int block_6[4][4]=
	{
		{0,0,0,0},
		{0,1,0,0},
		{1,1,1,0},
		{0,0,0,0}
	};
	int block_7[4][4]=
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	};

int pan[20][20];

void gotoxy(int x,int y);  //gotoxy 함수	
int rotate(int block[4][4]); //회전 함수
void Pan(); //판 함수
void Game(void); // 난수를 통해 임의의 블록만드는 함수
void Intial(int block[4][4]); // 초기 블록 생성함수
void Delete(int block[4][4]); //블록 지우는 함수
int DownMove(int block[4][4]); // 블록이 밑으로 내려가는 함수
int LeftMove(int block[4][4]); //블록 왼쪽으로 움직이는 함수
int RightMove(int block[4][4]);//블록 오른쪽으로 움직이는 함수
int Let(int block[4][4]); //블록 실행함수.

void gotoxy(int x,int y)
{
     COORD Cur;
     Cur.X=x;
     Cur.Y=y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
int rotate(int block[4][4])
{
	int arr[4][4];
	int arr1[4][4];
	int i,j;
	int a,b;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			arr[i][j]=block[i][j];
			arr1[i][j]=block[i][j];
		}
	
	
	for(i=0; i<4 ;i++)
	{
		for(j=0; j<4; j++)
		{
			
			for(a=0; a<4; a++)   //회전할때 2가 되면 멈추게 하도록 하기 위해 만듬
				for(b=0;b<4;b++)
				{
					arr1[a][b]=arr[b][3-a];
					if(pan[numy+a][numx+b]==2 ||arr1[a][b]*pan[numy+a][numx+b]==1)
						return 0;
				}
				block[i][j]=arr[j][3-i];
		}
	}
	return 0;	
}
void Pan()
{
	int x=0, y=0;
	
	for(x=0; x<Height ; x++)
	{
		y=0;
		
		for(y=0; y<Width ; y++)
		{	
			if( y==0 || y==19|| x==0 || x==19)
			{
				gotoxy(y,x);
				pan[y][x]=2;
				printf("%d",pan[y][x]);
			}
		}
		printf("\n");
	}
}
void Game(void)
{
	int num;
	srand((int)time(NULL));
	num=rand()%7;

	switch(num)
	{
		case 0:
			Let(block_1);
			break;
		case 1:
			Let(block_2);
			break;
		case 2:
			Let(block_3);
			break;
		case 3:
			Let(block_4);
			break;
		case 4:
			Let(block_5);
			break;
		case 5:
			Let(block_6);
			break;
		case 6:
			Let(block_7);
			break;
		default:
			break;
	}
}
void Intial(int block[4][4])
{
	int i, j;

	for(i=0; i<4 ; i++)
		{
			for(j=0; j<4; j++)
			{
				if(block[i][j]==1)
				{
					gotoxy(numx+j,numy+i);
					printf("%d", block[i][j]);
				}
					
			}
		}
}
void Delete(int block[4][4])
{
	int i, j;
	for(i=0; i<4 ; i++)
		{
			for(j=0; j<4; j++)
			{
				gotoxy(numx+j,numy+i);
				if(block[i][j]==1 && pan[numy+i][numx+j]!=2 && pan[numy+i][numx+j]!=1)
					printf(" ");			
			}
		}
}
int DownMove(int block[4][4])
{
	int i, j;
	int a,b;

	while(numy!=17 || numx!=17)
	{	
	   for(i=0; i<4 ; i++)
	  {
			for(j=0; j<4; j++)
			{	
				if(block[i][j]==1)
				{
					
					gotoxy(numx+j,(numy+1)+i);
					for(a=0; a<4 ;a++)  //아래로 내려갈때 1이 생기는걸 방지하기 위해 만듬
						for(b=0; b<4; b++)
						{							
							if(block[a][b]+pan[(numy+1)+a][numx+b]==3 || block[a][b]*pan[numy+1+a][numx+b]==1)						
								return 3;					
						}
				
					gotoxy(numx+j,(numy+1)+i);
					printf("%d", block[i][j]);
					//pan[(numy+1)+i][numx+j]=block[i][j]; // pan에 block값을 추가하기 위해 넣었음 10월9일,,,					
				}								
			}
		}	
	numy=numy+1;	
	break;
	}	
	return 3;	
}
int LeftMove(int block[4][4])
{
	int i, j;
	int a,b;

	while(numx!=-2 || numy!=17)
	{
	for(i=0; i<4 ; i++)
		{
			for(j=0; j<4; j++)
			{
				if(block[i][j]==1)
				{
					gotoxy((numx-1)+j,numy+i);
					for(a=0; a<4; a++)   //왼쪽으로갈때 1이 생기는걸 방지하기 위해 만듬.
						for(b=0; b<4; b++)
						{
							if(block[a][b]+pan[numy+a][(numx-1)+b]==3 || block[a][b]*pan[numy+a][numx-1+b]==1)
								return 0;
						}
					gotoxy((numx-1)+j,numy+i);
						printf("%d", block[i][j]);
				}
				
					
			}
		}
	numx=numx-1;
	break;
	}
	return 0;
}
int RightMove(int block[4][4])
{
	int i, j;
	int a,b;

	while(numx!=17 || numy!=17)
	{
	for(i=0; i<4 ; i++)
		{
			for(j=0; j<4; j++)
			{
			

				if(block[i][j]==1 )
				{		
					
					gotoxy((numx+1)+j,numy+i);
					for(a=0; a<4; a++)  //오른쪽으로 가서 1이 생기는걸 방지하기 위해만듬.
						for(b=0; b<4; b++)
						{
							if(block[a][b]+pan[numy+a][(numx+1)+b]==3 || block[a][b]*pan[numy+a][numx+1+b]==1)
								return 0;
						}

						
		
					gotoxy((numx+1)+j,numy+i);
					printf("%d", block[i][j]);
				}
				
					
			}
		}
	numx=numx+1;
	break;
	}
	return 0;
}   //오른쪽에서 오류가일어나는것같다...
int Let(int block[4][4])
{
	int a=0,c,d,e=0,x=0,y;
	int h=0,p=0,u=0;
	int n,m;
	int k=0;
	int i, j;
	clock_t base_time,curr_time;

	while(1)
	{	
		gotoxy(30,2);puts("□□□□□□□□□□□");
		gotoxy(30,3);puts("□                  □");
		gotoxy(30,4);puts("□                  □");
		gotoxy(30,5);puts("□                  □");
		gotoxy(30,6);puts("□□□□□□□□□□□");
		gotoxy(37,4); printf("점수:%d\n",t*100);
		
		Intial(block);
		base_time=clock();
		while(1){
			curr_time=clock();
			if(curr_time-base_time>=500)
			{
				Intial(block);
				Delete(block);
				DownMove(block);
				base_time=curr_time;
			}
			if(kbhit())
				break;
		}

		a=getch();
			switch(a)
			{		
			case UP:
				Delete(block);
				rotate(block);
				break;
			case DOWN:
				for(i=0; i<4; i++) //이거 넣은이유는 바닥으로 내려갔을때 main에서 Game을 반복하도록
					for(j=0; j<4 ;j++)
					{		
						gotoxy(numx+j,(numy+1)+i);
		
						if(block[i][j]+pan[(numy+1)+i][numx+j]==3 || block[i][j]*pan[(numy+1)+i][numx+j]==1)
						{	
							for(c=0; c<4; c++)
								for(d=0; d<4; d++)
								{
									
									if(block[c][d]==1)
									{										
									pan[numy+c][numx+d]=block[c][d];
									}//판에다가 1을 채워넣음									
								}
						
									for(x=0; x<4; x++)  //1이 차면 없어지는것,,
										{
											
											e=0;h=0;p=0;u=0;
											for(y=1; y<19; y++)
											{												
				
												if(pan[numy+i-x][y]==1)
												{
													e++;
												}
												if(pan[numy+i-x][y]==1 && pan[numy+i-x-1][y]==1)
												{
													h++;
													
												}
												if(pan[numy+i-x][y]==1 && pan[numy+i-x-1][y]==1 && pan[numy+i-x-2][y]==1)
												{
													p++;
												}
												if(pan[numy+i-x][y]==1 && pan[numy+i-x-1][y]==1 && pan[numy+i-x-2][y]==1 && pan[numy+i-x-3][y]==1)
												{
													u++;
												}
											
											
													if(e==18 && h!=18 && p!=18 && u!=18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x);
															printf(" ");
															for(n=numy+i-x; n>1; n--)
																pan[n][y]=pan[n-1][y];      //블록이 4줄 없어져야되는데 2줄밖에 안없어짐,, 문제점이?
														}
							
														t++;
														break;
																																										
													}													
													else if(e==18 && h==18 && p!=18 && u!=18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x-1);
															printf(" ");
															for(n=numy+i-x;n>2;n--)
																pan[n][y]=pan[n-2][y];
														}
														t+=2;
														break;
													}
													else if(e==18 && h==18 && p==18 && u!=18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x-2);
															printf(" ");
															for(n=numy+i-x;n>3;n--)
																pan[n][y]=pan[n-3][y];
														}
														t+=3;
														break;
													}
													else if(e==18 && h==18 && p==18 && u==18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x-3);
															printf(" ");
															for(n=numy+i-x;n>4;n--)
																pan[n][y]=pan[n-4][y];
														}
														t+=4;
														break;
													}
													
											}
										}							
											for(n=1; n<19; n++)
												for(m=1; m<19; m++)
													{
														gotoxy(m,n);
														
														if(pan[n][m]==1)
															printf("%d", pan[n][m]);
														else
															printf(" ");
													}
							numx=9;	numy=1;
							return 0;
							
						}
						
					}
				Delete(block);
				DownMove(block);										
				break;
			case LEFT:
				Delete(block);
				LeftMove(block);
				break;
			case RIGHT:
				Delete(block);
				RightMove(block);
				break;
			case SPACE:
				while(1){
				if(curr_time-base_time>=0)
			{
				Intial(block);
				Delete(block);
				DownMove(block);
				base_time=curr_time;
			}
				for(i=0; i<4; i++) //이거 넣은이유는 바닥으로 내려갔을때 main에서 Game을 반복하도록
					for(j=0; j<4 ;j++)
					{		
						gotoxy(numx+j,(numy+1)+i);
		
						if(block[i][j]+pan[(numy+1)+i][numx+j]==3 || block[i][j]*pan[(numy+1)+i][numx+j]==1)
						{	
							for(c=0; c<4; c++)
								for(d=0; d<4; d++)
								{
									
									if(block[c][d]==1)
									{										
									pan[numy+c][numx+d]=block[c][d];
									}//판에다가 1을 채워넣음									
								}
						
									for(x=0; x<4; x++)  //1이 차면 없어지는것,,
										{
											
											e=0;h=0;p=0;u=0;
											for(y=1; y<19; y++)
											{												
				
												if(pan[numy+i-x][y]==1)
												{
													e++;
												}
												if(pan[numy+i-x][y]==1 && pan[numy+i-x-1][y]==1)
												{
													h++;
													
												}
												if(pan[numy+i-x][y]==1 && pan[numy+i-x-1][y]==1 && pan[numy+i-x-2][y]==1)
												{
													p++;
												}
												if(pan[numy+i-x][y]==1 && pan[numy+i-x-1][y]==1 && pan[numy+i-x-2][y]==1 && pan[numy+i-x-3][y]==1)
												{
													u++;
												}
											
											
													if(e==18 && h!=18 && p!=18 && u!=18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x);
															printf(" ");
															for(n=numy+i-x; n>1; n--)
																pan[n][y]=pan[n-1][y];      //블록이 4줄 없어져야되는데 2줄밖에 안없어짐,, 문제점이?
														}
							
														t++;
														break;
																																										
													}													
													else if(e==18 && h==18 && p!=18 && u!=18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x-1);
															printf(" ");
															for(n=numy+i-x;n>2;n--)
																pan[n][y]=pan[n-2][y];
														}
														t+=2;
														break;
													}
													else if(e==18 && h==18 && p==18 && u!=18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x-2);
															printf(" ");
															for(n=numy+i-x;n>3;n--)
																pan[n][y]=pan[n-3][y];
														}
														t+=3;
														break;
													}
													else if(e==18 && h==18 && p==18 && u==18)
													{
														for(y=1; y<19; y++)
														{
															gotoxy(y,numy+i-x-3);
															printf(" ");
															for(n=numy+i-x;n>4;n--)
																pan[n][y]=pan[n-4][y];
														}
														t+=4;
														break;
													}
													
											}
										}							
											for(n=1; n<19; n++)
												for(m=1; m<19; m++)
													{
														gotoxy(m,n);
														
														if(pan[n][m]==1)
															printf("%d", pan[n][m]);
														else
															printf(" ");
													}
							numx=9;	numy=1;
																
				return 0;
							
						}
						
					}
				
				}
			
					
			default:
				break;
		}
		
	}
	return 0;
}
int main(void)
{	
	Pan();
	while(1)
	{
	Game();
	}
	return 0;
}
		
		
