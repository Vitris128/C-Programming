#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 7
#define N 7
#define MINE -1
int MapOfMines[M][N];
int Status[M][N];
void PrintMap(); // In bang do boom //
void CountMines(); // Kiem tra so luong boom xung quanh //
void Open_cell(int r, int c); // Mo o duoc chon va xung quanh //
int Count_remain(); // Kiem tra so o khong chua boom con lai //
void openAll(); // Mo tat ca o //
int Open_check(int r, int c); // Kiem tra trang thai o //
void Init_mines(int k); // Tao boom //

int main()
{
    int k = 3; //  So luong boom //
    Init_mines(k);
    int r,c;
    CountMines();
    while(1)
    {
        PrintMap();
        do {
            do {
                fflush(stdin);
                printf("Choose your cell(Row-> Column): ");
                scanf("%d%d", &r, &c);
                }
            while(Open_check(r,c)==1);
        }
        while(r>M-1 || r<0 || c>N-1 || c<0);

        if(MapOfMines[r][c] == MINE) {
            openAll();
            PrintMap();
            printf("\n#---------- GAME OVER ----------#\n");
            break;
        }
        Open_cell(r,c);
        if(Count_remain() == k)
        {
            openAll();
            PrintMap();
            printf("\n#---------- Congratulations ----------#\n#---------- YOU WIN ----------#\n");
            break;
        }
    }
    return 0;
}

void PrintMap()
{
    int i,j;
    printf("  ");
    for(j=0;j<M;j++)
            printf("%2d ",j);
    printf("\n");
    for(i=0;i<M;i++)
    {
        printf("%d ",i);
        for(j=0;j<N;j++)
        {
            if(MapOfMines[i][j] ==MINE && Status[i][j] ==1)
                printf(" x ");
            else if(MapOfMines[i][j] !=0 && Status[i][j] ==1)
                printf("%2d ", MapOfMines[i][j]);
            else if(Status[i][j] == 0)
                printf(" # ");
            else if(MapOfMines[i][j] == MINE)
                printf(" x ");
            else if(MapOfMines[i][j] == 0)
                printf(" . ");
            else printf("%2d ", MapOfMines[i][j]);
        }
        printf("\n");
    }
}

void CountMines()
{
    int i,j;

    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(MapOfMines[i][j]==MINE)
            {
                Place_Numbers(i,j);
            }
        }
                
    }
}

void openAll()
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            Status[i][j] = 1;
        }
    }
}

int Count_remain()
{
    int cnt = 0;
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(Status[i][j] == 0)
                cnt++;
        }
    }
    return cnt;
}
int Open_check(int r, int c)
{
    if(Status[r][c] == 1)
       return 1;
    else return 0;
}

void Open_cell(int r, int c) {
     if(r<0 || r>=M || c<0 || c>=N)
         return;
     if(Status[r][c] == 1)
         return;
    Status[r][c] = 1;
     if(MapOfMines[r][c] > 0)
     {
         Status[r][c] = 1;
         return;
     }
     else if(MapOfMines[r][c] == 0)
     {
         Open_cell(r-1,c-1);
         Open_cell(r-1,c);
         Open_cell(r-1,c+1);
         Open_cell(r,c-1);
         Open_cell(r,c+1);
         Open_cell(r+1,c-1);
         Open_cell(r+1,c);
         Open_cell(r+1,c+1);
     }

}

void Init_mines(int k)
{
    srand(time(0));
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            MapOfMines[i][j]=0;
        }
    }
    int cnt=0;
    for(i=0;i<k;i++)
    {
        int r= rand()%M;
        int c =rand()%N;
        if(MapOfMines[r][c] == 0)
        {
            MapOfMines[r][c] = MINE;
            cnt++;
        }
    }
    return;
}

int Inside_MapOfMines_Check(int i,int j){
    if((0<=i && i<=M)&&(0<=j&&j<=N)) return 1;
    return 0;
}

void Place_Numbers(int i, int j){
    for(int iter1=i-1;iter1<=i+1;++iter1){
        for(int iter2=j-1;iter2<=j+1;++iter2){
            if(iter1==i&&iter2==j) continue;
                else if(Inside_MapOfMines_Check(iter1,iter2)){
                    MapOfMines[iter1][iter2]++;
            }
        }
    }
}