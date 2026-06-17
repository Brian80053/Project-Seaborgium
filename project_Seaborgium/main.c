#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "main.h"
// 0 밝혀진 빈 공간 1 밝혀진 지뢰 2 숨겨진 빈 공간 3 숨겨진 지뢰 9 플래그
int main(){
    int size_x=17,size_y=31,mine_num=99;
    printf("---- CLI Minesweeper ----\n");
    printf("Press Any Key to Continue\n");
    char temp;
    scanf("%c",&temp);
    while(getchar() != '\n');    
    printf("모드를 선택하세요.\n[1. 기본 모드]\n");
    int temp2;
    scanf("%d",&temp2);
    while(getchar() != '\n');
    if(temp2==1){
        int size_x = 17;
        int size_y = 31;
        int mine_num = 99;
    }
    int map[size_x][size_y];
    int mines[mine_num];
    int num[size_x][size_y];
    int flags[size_x][size_y];
    int visit[size_x][size_y];
    int i,j;
    int turn = 0;
    int x,y;
    bool flag=0;
    char checker;
    while(1){
        //출력 시작
        int seq=65;
        if(turn!=0){
            for(i=1; i<size_x; i++){
                if(i==1){
                    printf(" ABCDEFGHIJKLMNOPQRSTUVWXYZabcd\n");
                }
                printf("%c",seq);
                seq++;
                for(j=1; j<size_y; j++){
                    if(flags[i][j]==1){
                        printf("\u2691");
                    }
                    else if(map[i][j]>=2){
                        printf("\u25A0");
                    }
                    else if(map[i][j]==1){
                        printf("\u25A3");
                    }
                    else{
                        if(num[i][j]==0){
                            printf("\u25A1");
                        }
                        else{
                            printf("%d",num[i][j]);
                        }
                    }
                }
                printf("\n");
            }
        }
        //입력 확인
        printf("현재 플래그 모드: %s\n",flag ? "켜짐" : "꺼짐");
        printf("플래그 모드 설정 [F/N]\n");
        printf("좌표를 입력해 주세요. (맨 왼쪽 위가 (1 1)\n");
        scanf("%c",&checker);
        scanf("%d %d",&x,&y);
        printf("%d %d\n",x,y);
        if(checker=='F'){
            flag=1;                  
        }
        else{
            flag=0;
        }
        while (getchar() != '\n');
        if(x<1 || x >size_x-1 || y<1 || y>size_y-1){
            printf("유효하지 않는 좌표값입니다.\n");
            continue;
        }
        if(flag==false){
            //지뢰면 처음 빼고 터트리기
            if(turn==0){
                init(map,mines,size_x,size_y,mine_num,x,y);
                check_number(map,num,flags,size_x,size_y,mine_num,visit);
                search_out(x,y,visit,map,num,size_x,size_y);
                for(i=1; i<size_x; i++){
                    for(j=1; j<size_y; j++){
                        visit[i][j]=0;
                    }
                }
                turn++;
                continue;
            }
            else if(map[x][y]==3){
                game_over(size_x,size_y,flags,map,num);
                //지뢰 출력
                break;
            }
            //빈칸이면 DFS 탐색으로 꺼내기
            else if(map[x][y]==2){
                search_out(x,y,visit,map,num,size_x,size_y);
                for(i=1; i<size_x; i++){
                    for(j=1; j<size_y; j++){
                        visit[i][j]=0;
                    }
                }
            }
            //주변 밝히기 -> 필요한 부분이 플래그 처리 되어있으면 넘기고 아니면 버려라
            else if(map[x][y]==0){
                light_up(map,flags,num[x][y],x,y,size_x,size_y,num);
            }
            else{
                continue;
            }
            turn++;
        }
        else if(flag==true){
            if(flags[x][y]==1){
                flags[x][y]=0;
            }
            else if(map[x][y]>=2){
                flags[x][y]=1;
            }
            else{
                continue;
            }
        }
        else{
            continue;
        }
    }
}
//game_over
void game_over(int size_x,int size_y,int flags[][31],int map[][31],int num[][31]){
    int i,j;
    int seq=65;
    for(i=1; i<size_x; i++){
        if(i==1){
        printf(" ABCDEFGHIJKLMNOPQRSTUVWXYZabcd\n");
        }
        printf("%c",seq);
        seq++;
        for(j=1; j<size_y; j++){
            if(flags[i][j]==1){
                printf("\u2691");
            }
            else if(map[i][j]==1 || map[i][j]==3){
                printf("\u25A3");
            }
            else{
                if(num[i][j]==0){
                    printf("\u25A1");
                }
                else{
                    printf("%d",num[i][j]);
                }
            }
        }
        printf("\n");
    }
}
//Light Up
void light_up(int map[][31],int flag[][31],int num_v,int x,int y,int size_x,int size_y,int num[][31]){
    if(num_v==0){
        return;
    }
    int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    int nx,ny;
    int i;
    int cnt=0;
    for(i=0; i<8; i++){
        nx=x+dist[i][0];
        ny=y+dist[i][1];
        if(nx<1 || nx >size_x-1 || ny<1 || ny>size_y-1){
            continue;
        }
        if(flag[nx][ny]==0 && map[x][y]==3){
            //게임 오버
            game_over(size_x,size_y,flag,map,num);
            exit(0);
        }
        if(flag[nx][ny]==1){
            cnt++;
        }
    }
    if(cnt==num_v){
        for(i=0; i<8; i++){
            nx=x+dist[i][0];
            ny=y+dist[i][1];
            if(flag[nx][ny]==0){
                map[nx][ny]-=2;
            }
        }
    }
    else{
        return;
    }
}
//Search Out
void search_out(int x,int y,int visit[][31],int map[][31],int num[][31],int size_x,int size_y){
    int i,j;
    int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    int nx,ny;
    //일단 방문한 채로
    if(visit[x][y]==1){
        return;
    }
    visit[x][y]=1;
    if(map[x][y]==3){
        return;
    }
    if(map[x][y]==2 && num[x][y]!=0){
        map[x][y]-=2;
        return;
    }
    else{
        map[x][y]-=2;
        for(i=0; i<8; i++){
            nx = x+dist[i][0];
            ny = y+dist[i][1];
            if(nx<1 || nx >size_x-1 || ny<1 || ny>size_y-1){
                continue;
            }
            if(visit[nx][ny]==1){
                continue;
            }
            search_out(nx,ny,visit,map,num,size_x,size_y);
        }
    }
}
//Check Number
void check_number(int map[][31],int num[][31],int flags[][31],int size_x,int size_y,int mine_num,int visit[][31]){
    int i;
    int j;
    int k;
    int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    int nx,ny;
    for(i=1; i<size_x; i++){
        for(j=1; j<size_y; j++){
            flags[i][j]=0;
            num[i][j]=0;
            visit[i][j]=0; 
        }  
    }
    for(i=1; i<size_x; i++){
        for(j=1; j<size_y; j++){
            if(map[i][j]!=9 && map[i][j]%2==1){
                continue;
            }
            for(k=0; k<8; k++){
                nx=i+dist[k][0];
                ny=j+dist[k][1];
                if(nx<1 || nx >size_x-1 || ny<1 || ny>size_y-1){
                    continue;
                }
                if(map[nx][ny]!=9 && map[nx][ny]%2==1){
                    num[i][j]++;
                }
            }
        }
    }
}
//Init
void init(int map[][31],int mines[],int size_x,int size_y,int mine_num,int x,int y){
    int i,j,k;
    int avoids[9]={(x-2)*(size_y-1)+y-1,(x-2)*(size_y-1)+y,(x-2)*(size_y-1)+y+1,
                   x*(size_y-1)+y-1,x*(size_y-1)+y,x*(size_y-1)+y+1,
                   (x-1)*(size_y-1)+y-1,(x-1)*(size_y-1)+y,(x-1)*(size_y-1)+y+1};
    int dist[9][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1},{0,0}};
    for(i=1; i<size_x; i++){
        for(j=1; j<size_y; j++){
            map[i][j]=0;
        }
    }
    int mine;
    srand(time(NULL));
    for(i=0; i<mine_num; i++){
        mine = rand()%((size_x-1)*(size_y-1))+1;
        for(j=0; j<i; j++){
            if(mines[j]==mine){
                i--;
                break;
            }
        }
        if(j!=i){
            continue;
        }
        for(k=0; k<=8; k++){
            if(mine==avoids[k]){
                i--;
                break;
            }   
        }
        if(k!=9){
            continue;
        }
        mines[i]=mine;
    }
    int x_loc,y_loc;
    for(i=0; i<mine_num; i++){
        x_loc=mines[i]/(size_y-1)+1;
        y_loc=mines[i]%(size_y-1);
        if(y_loc==0){
            x_loc-=1;
            y_loc+=size_y;
        }
        map[x_loc][y_loc]=1;
    }
    for(i=1; i<size_x; i++){
        for(j=1; j<size_y; j++){
            map[i][j]+=2;
        }
    }
    int nx,ny;
    for(k=0; k<=8; k++){
        nx=x+dist[k][0];
        ny=y+dist[k][1];
        if(nx<1 || nx >size_x-1 || ny<1 || ny>size_y-1){
            continue;
        }
        else{
            map[nx][ny]-=2;
        }
    }
}