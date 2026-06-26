#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "main.h"
// 0 밝혀진 빈 공간 1 밝혀진 지뢰 2 숨겨진 빈 공간 3 숨겨진 지뢰 5 숨겨진 대전차 지뢰 7 밝혀진 대전차 지뢰 9 플래그
int main(){
    LABEL_ONE:
    int ward_num = 9999;
    int size_x,size_y,mine_num;
    printf("---- CLI Minesweeper ----\n");
    printf("Press Any Key to Continue\n");
    char temp;
    scanf("%c",&temp);
    while(getchar() != '\n');
    printf("모드를 선택하세요.\n[1. 기본 모드] [2. 랜덤 모드] [3. 노플래그 모드] [4.와드 모드] [5.대전차 지뢰 모드] [6.타임어택 모드]\n");
    int temp2;
    scanf("%d",&temp2);
    while(getchar() != '\n');
    if(temp2==1){
        printf("…진짜 설명이 필요할까요? 기본 모드입니다!\n");
    }
    else if(temp2==2){
        printf("당신의 운을 시험해보세요.\n");
    }
    else if(temp2==3){
        printf("지뢰위에 깃발을 꽃으면 터지는 건 상식이죠! flag를 쓸 수 없습니다.\n");
    }
    else if(temp2==4){
        printf("직장인의 설움은 야근이죠.. 깃발 대신 와드를 박아서 시야를 넓혀보세요!\n");
    }
    else if(temp2==5){
        printf("지구를 위해 지뢰는 제거합시다! 일부 지뢰가 flag대신 dig해야만 안전해집니다.\n");
    }
    else if(temp2==6){
        printf("더 빨리! 더 빨리! 더 빨리! (Plus vite! Plus vite! Plus vite!)\n");
    }
    if(temp2==1 || temp2 == 3 || temp2==4 || temp2==5 || temp2 == 6){
        size_x = 17;
        size_y = 31;
        mine_num = 99;
        printf("세로 축: %d개, 가로 축: %d개, 지뢰 개수: %d개\n",size_x,size_y,mine_num);
    }
    else if(temp2==2){
        srand(time(NULL));
        size_x = rand()%50+1;
        size_y = 31;
        mine_num = rand()%(size_x*size_y/2)+1;
        printf("세로 축: %d개, 가로 축: %d개, 지뢰 개수: %d개\n",size_x,size_y,mine_num);
    }
    else{
        printf("종료\n");
        return 0;
    }
    if(temp2==4){
        ward_num=10;
    }
    int map[size_x][size_y];
    int mines[mine_num];
    int num[size_x][size_y];
    int flags[size_x][size_y];
    int visit[size_x][size_y];
    int anti_tank_num[size_x][size_y];
    int i,j;
    int turn = 0;
    int x,y;
    bool flag=0;
    char checker;
    bool win_checker;
    clock_t start,end;
    while(1){
        win_checker=0;
        if(turn!=0){
            system("cls");
        }
        // 성공 체크
        for(i=1; i<size_x; i++){
            for(j=1; j<size_y; j++){
                if(map[i][j]==2){
                    win_checker=1;
                    break;
                }
            }
            if(map[i][j]==2){
                continue;
            }
        }
        if(win_checker==0){
            char mode[11][101]={"기본","랜덤","노플래그","와드","대전차지뢰","타임 어택"};
            printf("축하합니다. %s모드에서 모든 지뢰를 발견하는데 성공했습니다.\n",mode[temp2-1]);
            printf("[다시 플레이하기]\n");
            int temp3;
            scanf("%d",temp3);
            goto LABEL_ONE;
        }
        //출력 시작
        if(turn!=0){
            output(size_x,size_y,flags,map,num,ward_num,anti_tank_num);
        }
        //입력 확인
        if(temp2!=3 && temp2!=4){
            printf("현재 플래그 모드: %s\n",flag ? "켜짐" : "꺼짐");
            printf("플래그 모드 설정 [F/N]\n");
        }
        if(temp2==4){
            printf("현재 와드 모드: %s\n",flag ? "켜짐" : "꺼짐");
            printf("와드 모드 설정 [W/N]\n");            
        }
        printf("좌표를 입력해 주세요. (맨 왼쪽 위가 (1 1))\n");
        if(temp2!=3 && temp2!=4){
            printf("F/N X Y 식으로 입력\n");
        }
        if(temp2==3){
            printf("\033[31m깃발을 사용 할 수 없습니다!\033[0m C X Y 식으로 입력\n");
        }
        if(temp2==4){
            printf("\033[31m와드를 사용할 수 있습니다!\033[0m W/N X Y 식으로 입력\n");            
        }
        end=clock();
        if(turn!=0 && (double)(end-start)/ CLOCKS_PER_SEC>10 && temp2==6){
            game_over(size_x,size_y,flags,map,num);
            //지뢰 출력
            char mode[11][101]={"기본","랜덤","노플래그","와드","대전차지뢰","타임 어택"};
            printf("%s모드에서 시간이 초과되었습니다..\n",mode[temp2-1]);
            printf("[다시 플레이하기]\n");
            int temp3;
            scanf("%d",temp3);
            goto LABEL_ONE;       
        }
        start = clock();
        scanf("%c ",&checker);
        char temp_y,temp_x;
        scanf("%c %c",&temp_y,&temp_x);
        while(getchar() != '\n');
        if(temp_y>='a' && temp_y<='d'){
            temp_y-=6;
        }
        int y=(int)temp_y-64;
        int x=(int)temp_x-64;
        if(checker=='F' && temp2!=3 && temp2!=4){
            flag=1;          
        }
        else if(checker=='F' && temp2==3){
            printf("\033[31m\033[1m깃발을 사용 할 수 없습니다!\033[0m");
            return 0;
        }
        if(checker =='W' && temp2==4){
            flag=1;
        }
        if(checker=='N'){
            flag=0;
        }
        if(x<1 || x >size_x-1 || y<1 || y>size_y-1){
            printf("유효하지 않는 좌표값입니다.\n");
            continue;
        }
        if(flag==false){
            //지뢰면 처음 빼고 터트리기
            if(turn==0){
                init(map,mines,size_x,size_y,mine_num,x,y,temp2);
                check_number(map,num,flags,size_x,size_y,mine_num,visit,anti_tank_num,temp2);
                search_out(x,y,visit,map,num,size_x,size_y);
                for(i=1; i<size_x; i++){
                    for(j=1; j<size_y; j++){
                        visit[i][j]=0;
                    }
                }
                turn++;
                continue;
            }
            else if(map[x][y]==5){
                map[x][y]+=2;
            }
            else if(map[x][y]==3){
                game_over(size_x,size_y,flags,map,num);
                //지뢰 출력
                char mode[11][101]={"기본","랜덤","노플래그","와드","대전차지뢰","타임 어택"};
                printf("%s모드에서 지뢰를 밟으셨습니다..\n",mode[temp2-1]);
                printf("[다시 플레이하기]\n");
                int temp3;
                scanf("%d",temp3);
                goto LABEL_ONE;
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
            if(ward_num != 9999){
                if(flags[x][y]==1){
                    if(ward_num<=10){
                        ward_num++;
                        flags[x][y]=0;
                    }
                    continue;
                }
                if(ward_num<=0){
                    printf("설치할 수 없습니다.\n");
                    continue;
                }
                ward_num--;
                flags[x][y]=1;
                continue;
            }
            if(flags[x][y]==1){
                flags[x][y]=0;
                continue;
            }
            if(map[x][y]==5){
                game_over(size_x,size_y,flags,map,num);
                //지뢰 출력
                char mode[11][101]={"기본","랜덤","노플래그","와드","대전차지뢰","타임 어택"};
                printf("%s모드에서 지뢰를 밟으셨습니다..\n",mode[temp2-1]);
                printf("[다시 플레이하기]\n");
                int temp3;
                scanf("%d",temp3);
                goto LABEL_ONE;
                break;
                break;
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
//output 현재 지뢰 상태 출력
void output(int size_x,int size_y,int flags[][31],int map[][31],int num[][31],int ward_num,int anti_tank_num[][31]){
    if(ward_num==9999){
        int seq=65;
        int i,j;
        for(i=1; i<size_x; i++){
            if(i==1){
                printf(" ABCDEFGHIJKLMNOPQRSTUVWXYZabcd\n");
            }
            printf("%c",seq);
            if(seq=='Z'){
                seq='a';
            }
            else{
                seq++;
            }
            for(j=1; j<size_y; j++){
                int color[9]={37,31,32,33,34,35,36,3,1};
                if(flags[i][j]==1){
                    printf("\033[%dm\u2691\033[0m",color[anti_tank_num[i][j]]); //플래그
                }
                else if(map[i][j]>=2 && map[i][j]<=5){
                    printf("\u25A0"); //미발견된 타일
                }
                else if(map[i][j]==7){
                    printf("\u25C9"); // 대전차 지뢰
                }
                else if(map[i][j]==1){
                    printf("\u25A3"); // 공개된 지뢰
                }
                else{
                    if(num[i][j]==0){
                        printf("\033[%dm\u25A1\033[0m",color[anti_tank_num[i][j]]);  //공개된 타일
                    }
                    else{
                        //색깔 출력 필요
                        printf("\033[%dm%d\033[0m",color[anti_tank_num[i][j]],num[i][j]);
                    }          
                }
            }
            printf("\n");
        }
        return;
    }
    else{
        int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
        int seq=65;
        int i,j,k;
        int nx=0,ny=0;
        bool ward_exists = 0;
        for(i=1; i<size_x; i++){
            if(i==1){
                printf(" ABCDEFGHIJKLMNOPQRSTUVWXYZabcd\n");
            }
            printf("%c",seq);
            if(seq=='Z'){
                seq='a';
            }
            else{
                seq++;
            }
            for(j=1; j<size_y; j++){
                ward_exists=0;
                if(flags[i][j]==1){
                    printf("\u25B2");
                    continue;
                }
                for(k=0; k<8; k++){
                    nx=i+dist[k][0];
                    ny=j+dist[k][1];
                    if(nx<1 || nx >size_x-1 || ny<1 || ny>size_y-1){
                       continue;
                    }
                    if(flags[nx][ny]==1){
                        if(num[i][j]==0){
                            printf("\u25A1");
                        }
                        else{
                            printf("%d",num[i][j]);
                        }
                        ward_exists=1;
                        break;
                    }
                }
                if(ward_exists==0){
                    printf("\u25A0");                    
                }
            }
            printf("\n");
        }      
        return;  
    }
}
//game_over 게임이 끝났을 때 지뢰가 모두 밝혀진 채로 출력
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
            else if(map[i][j]==5 || map[i][j]==7){
                printf("\u25C9");
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
//Light Up 이미 밝혀진 칸을 지정했을 때 주변 아홉 칸에 이미 정확한 곳에 지뢰를 배치했을 경우 밝혀주는 편의 기능
void light_up(int map[][31],int flag[][31],int num_v,int x,int y,int size_x,int size_y,int num[][31]){
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
        if(flag[nx][ny]==0 && map[nx][ny]==3){
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
            if(nx<1 || nx >size_x-1 || ny<1 || ny>size_y-1){
                continue;
            }
            if(map[nx][ny]==2 || map[nx][ny]==3){
                map[nx][ny]-=2;
            }
        }
    }
    else{
        return;
    }
}
//Search Out DFS를 통해 탐색을 실시하며 인접한 빈칸을 밝히는 기능
void search_out(int x,int y,int visit[][31],int map[][31],int num[][31],int size_x,int size_y){
    int i,j;
    int dist[8][2]={{1,0},{1,-1},{1,1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    int nx,ny;
    //일단 방문한 채로
    if(visit[x][y]==1){
        return;
    }
    visit[x][y]=1;
    if(map[x][y]==3 || map[x][y]==5){
        return;
    }
    if((map[x][y]==2 || map[x][y]==0) && num[x][y]!=0){
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
//Check Number 주변 8칸에 지뢰가 몇개 있는지 계산하는 기능
void check_number(int map[][31],int num[][31],int flags[][31],int size_x,int size_y,int mine_num,int visit[][31],int anti_tank_num[][31],int temp2){
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
            anti_tank_num[i][j]=0;
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
                if(map[nx][ny]!=9 && map[nx][ny]==3){
                    num[i][j]++;
                }
                if(map[nx][ny]!=9 && (map[nx][ny]==5 || map[nx][ny]==7)){
                    anti_tank_num[i][j]++;
                }
            }
        }
    }
}
//Init 초기 설정 (지뢰 랜덤 배치 (클릭 주변 9개는 지뢰 X), 배열 초기화)
void init(int map[][31],int mines[],int size_x,int size_y,int mine_num,int x,int y,int temp2){
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
        if(temp2==5 && i<=(mine_num)/5){
            map[x_loc][y_loc]+=2;
        }
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