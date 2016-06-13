#include<bits/stdc++.h>
#include<windows.h>
#define Sameer_Gupta

using namespace std;

class mine_create
{
	private:
		int mat[100][100];
		char front[100][100];
		int rand_no,size,mine,turn,win;
	public:
		void get_data();
		void set_all();
		void fetch_rand_num();
		void place_mine();
		int randomize();
		void mark_surround(int y,int x);
		int check_lim(int a,int b);		
		void show_map();
		
		
		void show_front();
		void play();
		int check_box(int row,int col);
		int check_around_bfs(int row,int col);
		int check_more(int a,int b);
		int check_finish();	

		mine_create(){
			size=9;
			mine=9;
			
			win=0;
			turn=1;
			for(int i=0;i<100;i++)
				for(int j=0;j<100;j++){
					mat[i][j]=0;
					front[i][j]='#';
				}
		}		
};
	
	
int main()
{
	
	mine_create first;
	first.set_all();
//	first.show_map();
//	cout<<endl<<endl;
	first.play();
	
	
	system("pause");
	

	return 0;	
}

void mine_create:: play()
{
	int row,col;	
	do{
	//	show_map();
		cout<<endl<<endl;
		show_front();
		cout<<"\n enter the row    : ";
		cin>>row;
		cout<<"\n enter the column : ";
		cin>>col;
		if(row<=size && col <=size){
			turn=check_box(row,col);
			system("cls");
		}
		else{
			cout<<"wrong choice\n";
		}
		
	}while(turn);
	
	if(win){
		show_map();
		show_front();
		cout<<"\n\nCongratulation you win !!! \n\n";
	} 
	else{
		show_map();
		show_front();
		cout<<"\nBitch please...\n";
	}		
}

int mine_create :: check_finish()
{
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(front[i][j]=='#' && mat[i][j]!=9)	return 0;
		}
	}
	
	return 1;	
}


int mine_create:: check_box(int row,int col)
{
	int x;
	
	if(mat[row-1][col-1]==9){
		front[row-1][col-1]='*';
		win=0;
		return 0;
	}
	else if(mat[row-1][col-1]==0){
		front[row-1][col-1]='.';
		check_around_bfs(row-1,col-1);
		if(check_finish()){
			win=1;
			return 0;
		} 
		else{
			return 1;
		}		
	}
	else{
		front[row-1][col-1]=mat[row-1][col-1]+48;
		
		if(check_finish()){
			win=1;
			return 0;
		} 
		else{
			return 1;
		}
	}
}


int mine_create :: check_around_bfs(int y,int x)
{
	if(y>=0 && x>=0 && y<size && x<size){
			
		if(mat[y][x]>0 && mat[y][x]<=8){
			front[y][x]=mat[y][x]+48;
			return 0;
		}
		else if(mat[y][x]==0){
			front[y][x]='.';
			
			if(check_more(y-1,x-1))		check_around_bfs(y-1,x-1);
			if(check_more(y-1,x)) 		check_around_bfs(y-1,x);
			if(check_more(y-1,x+1)) 	check_around_bfs(y-1,x+1);
			if(check_more(y,x-1)) 		check_around_bfs(y,x-1);
			if(check_more(y,x+1)) 		check_around_bfs(y,x+1);
			if(check_more(y+1,x-1)) 	check_around_bfs(y+1,x-1);
			if(check_more(y+1,x)) 		check_around_bfs(y+1,x);
			if(check_more(y+1,x+1)) 	check_around_bfs(y+1,x+1);									
		}
		else cout<<"\n you are fucked \n";		
	}
	else return 0;	
}


int mine_create:: check_more(int y,int x)
{
	if(x<0 || y<0 || x>=size || y>=size) return 0;
	else if(mat[y][x]>0 && mat[y][x]<=8){
			front[y][x]=mat[y][x]+48;
			return 0;
	}
	else if(mat[y][x]==0){
		if(front[y][x]=='#') return 1;
		else return 0;
	}
	else{
		cout<<"\n you are fucked even bigger\n";
		return 0;
	}
}


void mine_create:: show_front()
{
	int i,j;	
	cout<<"   ";
		for(i=0;i<size;i++) cout<<" "<<i+1<<" ";
		cout<<endl<<endl;
		for(i=0;i<size;i++){
			cout<<" "<<i+1<<" ";
			for(j=0;j<size;j++){
				cout<<" "<<front[i][j]<<" ";				
			}
			cout<<endl;
		}	
}


void mine_create :: set_all()
{
//	get_data();
	fetch_rand_num();
	place_mine();
//	cout<<"all set \n";	
}


void mine_create:: get_data()
{
	cout<<"Enter the size of area : ";
	cin>>size;
	cout<<"Enter number of mines : ";
	cin>>mine;	
}


int mine_create:: check_lim(int a,int b)
{
	if(a<0 || b<0 || mat[a][b]==9) return 0;
	if(a>=size || b>=size || mat[a][b]==9) return 0;
	else return 1;
}


void mine_create:: mark_surround(int y,int x)
{
	int a,b,c,d,e,f;		
	a=y-1;
	b=y;
	c=y+1;
	d=x-1;
	e=x;
	f=x+1;
		
	if(check_lim(a,d)) mat[a][d]++;
	if(check_lim(a,e)) mat[a][e]++;
	if(check_lim(a,f)) mat[a][f]++;
	if(check_lim(b,d)) mat[b][d]++;
	if(check_lim(b,f)) mat[b][f]++;
	if(check_lim(c,d)) mat[c][d]++;
	if(check_lim(c,e)) mat[c][e]++;
	if(check_lim(c,f)) mat[c][f]++;	
}


void mine_create:: show_map()
{
	int i,j;	
	cout<<"   ";
		for(i=0;i<size;i++) cout<<" "<<i+1<<" ";
		cout<<endl<<endl;
		for(i=0;i<size;i++){
			cout<<" "<<i+1<<" ";
			for(j=0;j<size;j++){
				if(mat[i][j]==0) cout<<" . ";
				else if(mat[i][j]==9) cout<<" * ";
				else cout<<" "<<mat[i][j]<<" ";
			}
			cout<<endl;
		}	
}

void mine_create:: place_mine()
{
	int i,x,y;	
	for(i=0;i<mine;i++)
	{
		x=(randomize()%(size+1))%size;	
		for(int k;k<randomize()%50;k++)	Sleep(randomize()%3);
		y=(randomize()%(size+1))%size;
		if(mat[y][x]==9){
			i--;
		}
		else{
			mat[y][x]=9;
			mark_surround(y,x);		
		}		
	//	cout<<i<<" "<<y<<" "<<x<<endl;						
	}	
}


void mine_create:: fetch_rand_num()
{
	char ch, data[25];
	FILE *fp;
	rand_no=0;
	fp = fopen("unicode.sfx","rb");
	while( ( ch = fgetc(fp) ) != EOF ){
		rand_no=(rand_no*10) + (ch-48);
	} 
//	cout<<rand_no<<endl;
	fclose(fp);
   
   fp=fopen("unicode.sfx","wb");
   fprintf(fp,"%d",rand_no+1);
   fclose(fp); 	
}


int mine_create:: randomize()
{
	int c;
	c=(rand()*rand_no)%1000007;
	rand_no=rand_no+3;
//	cout<<c<<endl;
    return c;	
}
