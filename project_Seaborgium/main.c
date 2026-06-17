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
    printf("모드를 선택하세요.\n[1. 기본 모드]\n");
    int temp2;
    scanf("%d",&temp2);
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
    init(map,mines,size_x,size_y,mine_num);
    check_number(map,num,flags,size_x,size_y,mine_num,visit);
    int i,j;
    int turn = 0;
    int x,y;
    bool flag=0;
    while(1){
        //출력 시작
        for(i=1; i<size_x; i++){
            for(j=1; j<size_y; j++){
                if(map[i][j]==9){
                    printf("\u2691"); //임시 값
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
        //입력 확인
        printf("현재 플래그 모드: %s\n플래그 모드 바꾸기 [F/N]\n",flag ? "켜짐" : "꺼짐");
        getchar();
        scanf("%c",&temp);
        getchar();
        printf("좌표를 입력해 주세요. (맨 왼쪽 위가 (1 1))\n");
        scanf("%d %d",&x,&y);
        if(temp=='N'){
            flag = false;
            //지뢰면 처음 빼고 터트리기
            if(turn==0 && map[x][y]==3){
                
                continue;
            }
            else if(map[x][y]==3){
                //지뢰 출력
                break;
            }
            //빈칸이면 DFS 탐색으로 꺼내기
            else if(map[x][y]==2){
                printf("test");
                search_out(x,y,visit,map,num,size_x,size_y);
                for(i=1; i<size_x; i++){
                    for(j=1; j<size_y; j++){
                        visit[i][j]=0;
                    }
                }
            }
            //주변 밝히기 -> 필요한 부분이 플래그 처리 되어있으면 넘기고 아니면 버려라
            else if(map[x][y]==0){
            
            }
            else{
                continue;
            }
        }
        else if(temp=='F'){
            flag = true;
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
        turn++;
    }
}
void search_out(int x,int y,int visit[][31],int map[][31],int num[][31],int size_x,int size_y){
    int i,j;
    int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    int nx,ny;
    //일단 방문한 채로
    if(visit[i][j]==1){
        return;
    }
    visit[i][j]=1;
    if(map[i][j]==3){
        return;
    }
    if(map[i][j]==2 && num[i][j]!=0){
        map[i][j]-=2;
        return;
    }
    else{
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
void init(int map[][31],int mines[],int size_x,int size_y,int mine_num){
    int i,j;
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
        mines[i]=mine;
    }
    int x,y;
    for(i=0; i<mine_num; i++){
        x=mines[i]/(size_y-1)+1;
        y=mines[i]%(size_y-1);
        if(y==0){
            x-=1;
            y+=size_y;
        }
        map[x][y]=1;
    }
    for(i=1; i<size_x; i++){
        for(j=1; j<size_y; j++){
            map[i][j]+=2;
        }
    }
}