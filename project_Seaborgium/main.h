void init(int map[][31],int mines[],int size_x,int size_y,int mine_num);
void check_number(int map[][31],int num[][31],int flags[][31],int size_x,int size_y,int mine_num,int visit[][31]);
void search_out(int x,int y,int visit[][31],int map[][31],int num[][31],int size_x,int size_y);