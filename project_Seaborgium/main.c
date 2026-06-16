#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "main.h"
// 0 밝혀진 빈 공간 1 밝혀진 지뢰 2 숨겨진 빈 공간 3 숨겨진 지뢰 9 플래그
int main(){
    printf("---- CLI Minesweeper ----\n");
    printf("Press Any Key to Continue\n");
    int temp;
    scanf("%d",&temp);
    int map[17][31]={};
    int mines[99]={};
    int num[17][31]={};
    init(map,mines);
    check_number(map,num);
}
void check_number(int map[][31],int num[][31]){
    int i;
    int j;
    int k;
    int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    int nx,ny;
    for(i=1; i<=16; i++){
        for(j=1; j<=30; j++){
            if(map[i][j]!=9 && map[i][j]%2==1){
                continue;
            }
            for(k=0; k<8; k++){
                nx=i+dist[k][0];
                ny=j+dist[k][1];
                if(nx<1 || nx >16 || ny<1 || ny>30){
                    continue;
                }
                if(map[nx][ny]!=9 && map[nx][ny]%2==1){
                    num[i][j]++;
                }
            }
        }
    }
}
void init(int map[][31],int mines[]){
    int i,j;
    int mine;
    srand(time(NULL));
    for(i=0; i<99; i++){
        mine = rand()%480+1;
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
    for(i=0; i<99; i++){
        x=mines[i]/30+1;
        y=mines[i]%30;
        if(y==0){
            x-=1;
            y+=30;
        }
        map[x][y]=1;
    }
    int temp=0;
    for(i=1; i<=16; i++){
        for(j=1; j<=30; j++){
            map[i][j]+=2;
            if(map[i][j]==3){
                temp++;
            }
        }
    }
    printf("%d",temp);
}