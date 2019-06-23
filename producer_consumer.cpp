#include<windows.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<curses.h>
void initial()
      {
        initscr();
        cbreak();
        nonl();
        noecho();
        intrflush(stdscr,FALSE);
        keypad(stdscr,TRUE);
        refresh();        
      }
using namespace std;
class game
{
	public:
		game(int a,int b);
		void ptest(int a,int b);    
		void ctest(int a,int b);
		void pmove();
		void cmove();
		int output(int a);        //螢幕顯示 
		void temp();              //暫存 
		int final();         	//檢查是否終止 
		void now(int a);    	//顯示目前數量 
		int help(int k);   		//使程式可以一直循環 
	private:
		int bio[24][80];           //0=無生物,123=生產者,-1-2-3=消費者 
		int tem[24][80];		 //暫存位置 
		int *seat[8]; 			 //指向 bio[24][80]中可能能移過去的 
		int n;    			 //有幾個位置可移動 
		int p,c;  			//help的次數 
		int pn,cn;			//生產者跟消費者數量 	
};
int main()
{
int p,c,k;
while(1){                 //while(1)表示永遠不斷執行直到break 
    cout<<"Producer:";
    cin>>p; 
    cout<<"Consumer:";
    cin>>c;
    if(p+c<=1920 && p+c>0)
    {break;} 
    else 
    cout << "error~ again" << endl;
}
game y(p,c);
initial();
start_color();
for(k=0;;k++){
     
	y.pmove();
	y.cmove();
	y.help(k);
	if(y.output(k)==1)
	{y.now(k);break;}	
}
}
game::game(int a,int b)
{int i,j,x,y;p=0,c=0;	
srand(time(0));
		for(i=0;i<24;i++){
	 		for(j=0;j<80;j++){
				bio[i][j]=0;
			}
	 	}								
		pn=a;cn=b;		
		for(i=0;i<a+b;i++){    
			y=rand()%24;
			x=rand()%80;
			if(i<a){
				if(bio[y][x]!=0){    //如果跟現存的生物重複到，重新rand 
					i=i-1;continue;
				}
				bio[y][x]=1; 	
			}
			else {
				if(bio[y][x]!=0){
				   i=i-1;continue;
				}
				bio[y][x]=-1;
			}			
		}	
}
int game::help(int k)
{
	int i;srand(time(0));int x,y;
	if(pn!=0&&cn!=0&&k%30>5&&k>20){    
	if(cn/pn>5)
	{
		for(i=0;i<pn;i++){
		if(pn==1920)
		{return(0);}    
			y=rand()%24;
			x=rand()%80;
			if(bio[y][x]!=0){
					i=i-1;continue;
		     }
				bio[y][x]=11; 	
     	}
	pn=pn*2;p++;	
	}
	else if(pn/cn>20)
	{if(cn==1920)
	{return(0);}   
	for(i=0;i<pn/20;i++){    
			y=rand()%24;
			x=rand()%80;
			if(bio[y][x]!=0){
					i=i-1;continue;
			}
				bio[y][x]=-11; 	
	}
	cn=cn+pn/20;c++;				
	}
	}	
	else if(pn==0&&k%30>0&&k>30){ 
		for(i=0;i<5;i++){    
			y=rand()%24;
			x=rand()%80;
			if(bio[y][x]!=0){
					i=i-1;continue;
			}
		bio[y][x]=11; 	
	}
	     pn=pn+5;p++;		
	}
	else if(cn==0&&k%30>0&&k>30){   
		for(i=0;i<5;i++){    
			y=rand()%24;
			x=rand()%80;
			if(bio[y][x]!=0){
					i=i-1;continue;
			}
		bio[y][x]=-11; 	
	}
	     cn=cn+5;c++;		
	}	
}
int game::final(){            
	int a=0,b=0,i,j;
	 	if(pn==1920)
	 	{return(1);}
	     else if(pn+cn==0)
	 	{return(1);}
	 	else
	 	return(0);		 
}
void game::now(int a){	
move(24,0);addstr("time:");refresh();cout<<a;
move(24,18);addstr("Producer:");refresh();cout<<pn;
move(24,36);addstr("Consumer:");refresh();cout<<cn;
move(24,52);addstr("Help-P:");refresh();cout<<p;
move(24,64);addstr("Help-C:");refresh();cout<<c;
}
int game::output(int a){          //生產者為O(white ->yellow ->green)，消費者為.(white ->cyan ->bule) ，help(red) 
int i,j;
now(a);
Sleep(400);
refresh(); 
erase();
for(i=0;i<24;i++){
		for(j=0;j<80;j++){
		     if(bio[i][j]==11){
			move(i,j);
               init_pair(1,COLOR_RED,COLOR_BLACK);
               attron(COLOR_PAIR(1));
		     addch('.');
		     attroff(COLOR_PAIR(1));
			bio[i][j]-=10;		
			}
			else if(bio[i][j]==-11){
			move(i,j);
               init_pair(1,COLOR_RED,COLOR_BLACK);
               attron(COLOR_PAIR(1));
		     addch('O');
		     attroff(COLOR_PAIR(1));	
		     bio[i][j]+=10;
			}
			else if(bio[i][j]==1){
			move(i,j);
               init_pair(2,COLOR_WHITE,COLOR_BLACK);
               attron(COLOR_PAIR(2));
		     addch('.');
		     attroff(COLOR_PAIR(2));	
			}
			else if(bio[i][j]==2){
			move(i,j);
               init_pair(3,COLOR_YELLOW,COLOR_BLACK);
               attron(COLOR_PAIR(3));
		     addch('.');
		     attroff(COLOR_PAIR(3));	
			}
			else if(bio[i][j]==3){
			move(i,j);
               init_pair(4,COLOR_GREEN,COLOR_BLACK);
               attron(COLOR_PAIR(4));
		     addch('.');
		     attroff(COLOR_PAIR(4));	
			}
			else if(bio[i][j]==-1){
			 init_pair(5,COLOR_WHITE ,COLOR_BLACK);
	      	attron(COLOR_PAIR(5));
		     move(i,j);
			addch('O');
			attroff(COLOR_PAIR(5));	
			}
			else if(bio[i][j]==-2){
			 init_pair(6,COLOR_CYAN ,COLOR_BLACK);
	      	attron(COLOR_PAIR(6));
		     move(i,j);
			addch('O');
			attroff(COLOR_PAIR(6));	
			}
			else if(bio[i][j]==-3){
			 init_pair(7,COLOR_BLUE ,COLOR_BLACK);
	      	attron(COLOR_PAIR(7));
		     move(i,j);
			addch('O');
			attroff(COLOR_PAIR(7));	
			}
			
		}	
	}
if(final()==1)
{
erase();
refresh(); 	
move(12,32);addstr("G A M E  O V E R");
move(13,36);addstr("平衡崩潰");
move(23,36);addstr("");
refresh(); 
return(1);
}			
}
void game::temp(){
	int i,j;
	for(i=0;i<24;i++){
	 		for(j=0;j<80;j++){
				tem[i][j]=bio[i][j];
			}
	 	}	
} 
void game::ptest(int a,int b){   
     n=0;
	int i,j;	
	     if(a==0||b==0)
	     {
	     	for(i=a;i<=a+1&&i>-1&&i<24;i++){
 			for(j=b;j<=b+1&&j>=0&&j<80;j++){
 				if(i==a&&j==b)                //i==a&&j==b 表示為p現在的位置，不列入考慮，continue到下一個 
	 	     	{continue;}
				if(bio[i][j]==0){
					seat[n]=&bio[i][j];
					n++;
				}		
			}
		}	
		}
		else {
		for(i=a-1;i<=a+1&&i>-1&&i<24;i++){
 			for(j=b-1;j<=b+1&&j>=0&&j<80;j++){
 				if(i==a&&j==b) 
	 	     	{continue;}
				if(bio[i][j]==0){
					seat[n]=&bio[i][j];
					n++;
				}		
			}
		}	
		}   
}
void game::ctest(int a,int b)
{    int m;
	n=0;
	int i,j;
	if(a==0||b==0){
		for(i=a;i<=a+1&&i>-1&&i<24;i++){
		for(j=b;j<=b+1&&j>=0&&j<80;j++){
			if(i==a&&j==b)
	 	     {continue;}
			if(bio[i][j]>0){
				seat[n]=&bio[i][j];
				n++;
			}		
		}
	}			
	}
	else{
	for(i=a-1;i<=a+1&&i>-1&&i<24;i++){
		for(j=b-1;j<=b+1&&j>=0&&j<80;j++){
			if(i==a&&j==b)
	 	     {continue;}
			if(bio[i][j]>0){
				seat[n]=&bio[i][j];
				n++;
			}		
		}
	}			
	}
	if(n==0){	
	if(a==0||b==0){
		for(i=a;i<=a+1&&i>-1&&i<24;i++){
		for(j=b;j<=b+1&&j>=0&&j<80;j++){
			if(i==a&&j==b)
	 	     {continue;}
			if(bio[i][j]==0){
				seat[n]=&bio[i][j];
				n++;
			}		
		}
	}			
	}
	else{
	for(i=a-1;i<=a+1&&i>-1&&i<24;i++){
		for(j=b-1;j<=b+1&&j>=0&&j<80;j++){
			if(i==a&&j==b)
	 	     {continue;}
			if(bio[i][j]==0){
				seat[n]=&bio[i][j];
				n++;
			}		
		}
	}			
	}
	}		
}
void game::pmove()
{    
	int i,j,k;
	temp();
	for(i=0;i<24;i++){
	 		for(j=0;j<80;j++){
			 	if(tem[i][j]>0){
			 	 ptest(i,j);
			 	 	if(n>0){
			 	 		k=rand()%n;           //rand出一個位置  
					  	if(bio[i][j]==3){     
			 				*seat[k]=1;
			 				bio[i][j]=1;
						 	pn++;
			 	      	}
						else{
							*seat[k]=bio[i][j]+1;
					 		bio[i][j]=0;
						} 
				  	}
					 else{
					 	if(bio[i][j]==3){
					 	 bio[i][j]=1;
						 }
						 else{
						 bio[i][j]+=1;
						 }
					 }	
			 	 }
			 }
	 	}	
}
void game::cmove()
{
	int i,j,k;
	temp();
	for(i=0;i<24;i++){
	 		for(j=0;j<80;j++){
			 	if(tem[i][j]<0){
				 	ctest(i,j);
					if(n>0){
						k=rand()%n;           //rand出一個位置 
			 	 		if(*seat[k]>0){      // 若是位置上有 p
							*seat[k]=-1;
			 				bio[i][j]=-1;
						 	cn++;pn--;
						 }
			 			else if(*seat[k]==0&&bio[i][j]!=-3){   // 若是空位
							*seat[k]=bio[i][j]-1;
					 	 	bio[i][j]=0;
					  	}
						else{
					 	     bio[i][j]=0;cn--;            
						} 
					}	
					else{
						if(bio[i][j]!=-3){
						bio[i][j]-=1;
						}
						else{
						bio[i][j]=0;cn--;
						}
					} 		 	
			 	 }
			 }
	}	
}
