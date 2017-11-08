#include<cstring>
#include<string.h>
#include<fstream>
#include<iostream>
#include<cmath>
using namespace std;

fstream f;
char eno[4];
int n;
int fwptr[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},bkptr[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int flag[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
class Buffer{
	int next,p;
	public:char buf[29];
		Buffer(){
			next = -1;p=1;
			strcpy(buf,"");
		}
		void pack(char *s){
			if(p==1){
				strcpy(buf,"");
			}
			strcat(buf,s);
			strcat(buf,"|");
			p++;
		}
		void unpack(char s[15]){
			int p1=0;
			next++;
			while(buf[next]!='|'){
					s[p1]=buf[next];
					p1++;
					next++;
			}
			s[p1]='\0';
		}
};

struct record{
	char eno[4];
	char name[15];
	char mob[10];
};

char* fold(int roll){
	int nod = 0,n;
	char eno[4];
	n=roll;int i;
	while(n!=0){
		nod++;
		n=n/10;
	}i=nod-1;
	eno[nod]='\0';
	while(roll!=0){
		eno[i] = (char)(roll%10)+'0';
		roll=roll/10;
		i--;
	}
	return eno;
}

int unfold(char eno[4]){
	int nod = 0,n;
	int r=1;
	n=strlen(eno);int i;
	while(n!=1){
		nod += (int)((int)(eno[n-1])-'0')*r;
		r=r*10;
		n--;
	}
	nod += (int)((int)(eno[n-1])-'0')*r;
	return nod;
}

int hash(int k,int n){
	int r = k%n;
	return r;
}

void initialise(Buffer b[10]){
	int i;
	f.open("a.txt",ios::out);
	for(i=0;i<10;i++){
		b[i].pack("-1");
		for(int j=strlen(b[i].buf);j<28;j++){
			strcat(b[i].buf,"*");
		}
		strcat(b[i].buf,"#");
		f<<b[i].buf;
	}
	f.close();
}

void write(int i,Buffer b[10],int roll,fstream &f){
	int j;
	record r;
	strcpy(b[i].buf,"");
	char str[10];
	strcpy(str,fold(roll));
	b[i].pack(str);
	cout<<"Name : ";
	cin>>r.name;
	b[i].pack(r.name);
	cout<<"Mob No. : ";
	cin>>r.mob;
	b[i].pack(r.mob);
	for(j=strlen(b[i].buf);j<28;j++){
		strcat(b[i].buf,"*");
	}
	if(i!=0){
		f.seekp(i*29,ios::beg);
		f<<b[i].buf;
	}
	else{
		f<<b[i].buf;
	}
}

int read(Buffer b[10],int k,fstream &f){
	char str[15];
	cout<<k<<" is k"<<endl;
	char t;
	f.seekg(0,ios::beg);
	f.seekg(k*29,ios::beg);
	f>>t;
	if(t=='-'){
		f>>t;
		if(t=='1')
			return 1;
		else
			return 2;
	}
	else{
		return 0;
	}
}
int check(Buffer b[10],int r,int n){
	char eno[4];
	b[r].unpack(eno);
	int roll = unfold(eno);
	cout<<roll<<" am roll"<<endl;
	if(roll%n == r){
		return 1;
	}
	else{
		return 0;
	}
}
void add(Buffer b[10],int r,int roll,fstream &f,int n){
	int c=0;
	flag[r]++;
	int t;
	t=r;
	int bk=-1;
	char str[4];
	Buffer tb,tb1;
	strcpy(tb.buf,"");
	while(c!=n){
		int k = read(b,r,f);
		if(k==1 || k==2)	break;
		else{
			if(fwptr[r]==-1&&bk==-1){
				int c = check(b,r,n);
				cout<<"c is :"<<c<<endl;
				if(c==1){
					r=(r+1)%n;c++;continue;
				}
				else{
					b[r].unpack(str);
					strcat(tb.buf,str);
					f.getline(tb1.buf,29,'#');
					strcat(tb.buf,tb1.buf);
					write(r,b,roll,f);
					bk=bkptr[r];
					cout<<"hey bk "<<bk;
					fwptr[r]=-1;
					bkptr[r]=-1;
					cout<<"i am changing pos "<<tb.buf;
				}
				if(bkptr[r]!=-1){
					t=r;
				}
				r=(r+1)%n;c++;
			}
			else{
				t=r;
				r=fwptr[r];//c++;
				c+=abs(t-r);
			}
		}


		}
	if(c!=n){
		f.seekg(-2,ios::cur);
		if(flag[t]>0 && (strcmpi(tb.buf,"")==0)){
			fwptr[t]=r;cout<<fwptr[t]<<"@f";
			bkptr[r]=t;cout<<bkptr[r]<<"@b";
			write(r,b,roll,f);
		}
		else if(strcmpi(tb.buf,"")!=0){
			strcpy(b[r].buf,tb.buf);
			strcat(b[r].buf,"#");
			fwptr[bk]=r;cout<<fwptr[bk]<<"@f";
			bkptr[r]=bk;cout<<bkptr[r]<<"@b";
			f.seekg(r*29,ios::beg);
			f<<tb.buf;
		}
		else{
			write(r,b,roll,f);
		}
	}
}

void display(int i,Buffer b[100],char eno[4]){
	char str[15];
	f.getline(b[i].buf,29,'#');
	cout<<"\n Employee Details: - \n";
	cout<<"____________________________\n";
		cout<<"Eno : ";
		cout<<eno<<endl;
		cout<<"Name : ";b[i].unpack(str);
		cout<<str<<endl;
		cout<<"Mob No. : ";b[i].unpack(str);
		cout<<str<<endl;
	}



int search(char roll[4],int r,Buffer b[10],fstream &f,int n){
	int c = 0;
	f.seekp(0,ios::beg);
	char str[15];int t;
	while(c!=n){
		if(read(b,r,f)==0){
			b[r].unpack(str);
			if(strcmpi(str,roll)==0){
				cout<<b[r].buf;
				cout<<"Found !! ";
				//display(r,b,roll);
				return r;
			}
			else{
			if(fwptr[r]==-1){
				r=(r+1)%n;c++;
			}
			else{
				t=r;
				r=fwptr[r];c+=abs(t-r);
				}
			}
		}
		else{
			r=(r+1)%n;c++;
		}
	}
	return 0;
}

void delete_roll(char roll[4],int r,Buffer b[10],fstream &f,int n){
	int c = 0;
	char str[15];
	int p = search(roll,r,b,f,n);
	int k = strlen(roll);
	f.seekp(k*29,ios::beg);
	strcpy(roll,"-2");
	f<<roll;
	display(p,b,roll);
	}

int main(){
	Buffer b[10];
	initialise(b);
	fstream file;
	int r;
	file.open("a.txt",ios::in|ios::out);
	cout<<"Enter the no of records : - ";
	cin>>n;int roll ;
	for(int i=0;i<n;i++){
		cin>>roll;
		r = hash(roll,n);
		add(b,r,roll,file,n);
	}
	cout<<"Enter roll to be searched : - ";
	cin>>eno;
	int p = search(eno,r,b,f,n);
	cout<<"Enter roll to be deleted : - ";
	cin>>eno;
	//delete_roll(eno,r,b,f,n);
	file.close();
	return 0;
}
