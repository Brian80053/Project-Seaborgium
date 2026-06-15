#include<stdio.h>
#include "main.h"
int main(){
    printf("---- CLI Chess ----\n");
    printf("Press Any Key to Continue\na");
    char temp;
    scanf("%c",&temp);
    st map[9][501];
    int i,j;
    char map_init[9][501]={"  a b c d e f g h","8 R N B Q K B N R", "7 P P P P P P P P", "6 _ _ _ _ _ _ _ _", "5 _ _ _ _ _ _ _ _","4 _ _ _ _ _ _ _ _","3 _ _ _ _ _ _ _ _","2 P P P P P P P P","1 R N B Q K B N R"};
    for(i=0; i<9; i++){
        for(j=0; map_init[i][j]!='\0'; j++){
            if(map[i][j].piece!=' ' && j!=0 && (i==1 || i==2)){
                map[i][j].color = 1;
            }
            else if(map[i][j].piece!=' ' && j!=0 && (i==8 || i==7)){
                map[i][j].color = 2;
            }
            else{
                map[i][j].color = 0;
            }
            map[i][j].piece=map_init[i][j];
        }
    }
    while(1){
        output(map);
        break;
    }
}
void output(st map[][501]){
    int i,j;
    for(i=0; i<9; i++){
        for(j=0; map[i][j].piece!='\0'; j++){
            if(map[i][j].piece=='P' && map[i][j].color == 1){
                printf("\u265F");
            }
            else if(map[i][j].piece=='P' && map[i][j].color == 2){
                printf("\u2659");
            }
            else if(map[i][j].piece=='N' && map[i][j].color == 1){
                printf("\u265E");
            }
            else if(map[i][j].piece=='N' && map[i][j].color == 2){
                printf("\u2658");
            }
            else if(map[i][j].piece=='B' && map[i][j].color == 1){
                printf("\u265D");
            }
            else if(map[i][j].piece=='B' && map[i][j].color == 2){
                printf("\u2657");
            }
            else if(map[i][j].piece=='R' && map[i][j].color == 1){
                printf("\u265C");
            }
            else if(map[i][j].piece=='R' && map[i][j].color == 2){
                printf("\u2656");
            }
            else if(map[i][j].piece=='Q' && map[i][j].color == 1){
                printf("\u265B");
            }
            else if(map[i][j].piece=='Q' && map[i][j].color == 2){
                printf("\u2655");
            }
            else if(map[i][j].piece=='K' && map[i][j].color == 1){
                printf("\u265A");
            }
            else if(map[i][j].piece=='K' && map[i][j].color == 2){
                printf("\u2654");
            }
            else{
                printf("%c",map[i][j].piece);
            }
        }
        printf("\n");
    }
}