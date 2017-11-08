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
			strcat(buf,s);
			strcat(buf,"|");
			p++;
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
struct child{
	char *cname;
	char age[2];
};
struct record{
	char eno[4];
	char *name;
	char noc[2];
	struct child c;

};

int main(){
	record r[100];	Buffer b[100];
	cout<<"Enter the no of records: - ";
	int n,i,flag=0,k=0,noc,j;
	cin>>n;char str[25],str1[25];
	fstream f;
	f.open("a.txt",ios::in|ios::out);
	for(i=0;i<n;i++){
		cout<<"Eno : ";
		cin>>r[i].eno;b[i].pack(r[i].eno);
		cout<<"Name : ";
		cin>>str;
		b[i].pack(str);
		cout<<"No of children : ";
		cin>>r[i].noc;b[i].pack(r[i].noc);
		noc=(int)(r[i].noc[0]-'0');
		for(j=0;j<noc;j++){
			cout<<"Enter age : ";
			cin>>r[i].c.age;b[i].pack(r[i].c.age);
			cout<<"Enter name : ";
			cin>>str1;b[i].pack(str1);
		}
		strcat(b[i].buf,"#");
		f<<b[i].buf;
	}
	int l=i;
	i=0;
	f.close();
	f.open("a.txt",ios::in|ios::out);
	while(i<l){
		f.getline(b[i].buf,50,'#');
		cout<<"Eno : ";b[i].unpack(str);
		cout<<str<<endl;
		cout<<"Name : ";b[i].unpack(str);
		cout<<str<<endl;
		cout<<"No. of children : ";b[i].unpack(str);
		cout<<str<<endl;
		for(j=0;j<noc;j++){
			cout<<"Age : ";b[i].unpack(str);
			cout<<str<<endl;
			cout<<"Name : ";b[i].unpack(str);
			cout<<str<<endl;
		}
		i++;
		}
		f.close();
	return 0;
}
