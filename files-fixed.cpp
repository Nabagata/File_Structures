#include<bits/stdc++.h>
using namespace std;

class Buffer{
	int next,p;
	public:char *buf;
		Buffer(){
			next = -1;p=1;
			buf = new (char);
		}
		void pack(char *s){
			if(p==1){
				strcpy(buf,"");
			}
			if(p<5){
				strcat(buf,s);
				strcat(buf,"|");
				p++;
			}
			else{
				strcat(buf,s);
				strcat(buf,"|#");
				p=1;
			}
		}
		void unpack(char *s){
			int p1=0;
			next++;
			while(*(buf+next)!='|'){
				*(s+p1)=*(buf+next);
				next++;
				p1++;
			}
			*(s+p1)='\0';
		}
};

union rec{
	char adr[4];
	char mob[10];
};

struct record{
	char roll[4];
	char *name;
	char marks[2];
	char tag[1];
	union rec u;
};

int main(){
	record r[100];	Buffer b[100];
	cout<<"Enter the no of records: - ";
	int n,i,flag=0,k=0;
	cin>>n;char str[25];
	fstream f;
	f.open("a.txt",ios::in|ios::out);
	for(i=0;i<n;i++){
		cout<<"Roll : ";
		cin>>r[i].roll;b[i].pack(r[i].roll);
		cout<<"Name : ";
		cin>>str;
		b[i].pack(str);
		cout<<"Marks : ";
		cin>>r[i].marks;b[i].pack(r[i].marks);
		cout<<"Enter 1 for adress 2 for mobile no. : ";
		cin>>r[i].tag;b[i].pack(r[i].tag);
		if(strcmp(r[i].tag,"1")){
			cin>>r[i].u.adr;b[i].pack(r[i].u.adr);
		}
		else{
			cin>>r[i].u.mob;b[i].pack(r[i].u.mob);
		}
		f<<b[i].buf;
	}
	int l=i;
	i=0;
	f.close();
	f.open("a.txt",ios::in|ios::out);
	while(i<l){
		f.getline(b[i].buf,50,'#');
		cout<<"Roll : ";b[i].unpack(str);
		cout<<str<<endl;
		cout<<"Name : ";b[i].unpack(str);
		cout<<str<<endl;
		cout<<"Marks : ";b[i].unpack(str);
		cout<<str<<endl;
		if(strcmp(r[i].tag,"1")){
			cout<<"Address : ";b[i].unpack(str);b[i].unpack(str);
			cout<<str<<endl;
		}
		else{
			cout<<"Mobile No. : ";b[i].unpack(str);b[i].unpack(str);
			cout<<str<<endl;
		}
		cout<<endl;
		i++;
		}
		f.close();
	return 0;
}
