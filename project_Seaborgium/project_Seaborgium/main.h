void init(int map[][31],int mines[],int size_x,int size_y,int mine_num,int x,int y,int temp2);
void check_number(int map[][31],int num[][31],int flags[][31],int size_x,int size_y,int mine_num,int visit[][31],int anti_tank_num[][31],int temp2);
void search_out(int x,int y,int visit[][31],int map[][31],int num[][31],int size_x,int size_y);
void light_up(int map[][31],int flag[][31],int num_v,int x,int y,int size_x,int size_y,int num[][31]);
void game_over(int size_x,int size_y,int flags[][31],int map[][31],int num[][31]);
void output(int size_x,int size_y,int flags[][31],int map[][31],int num[][31],int ward_num,int anti_tank_num[][31]);