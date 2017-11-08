#include<iostream>
#include<algorithm>
#include<cmath>
#include<fstream>
using namespace std;

void fill(fstream &f1,int a[4][100],int &s1){
	int i,j,a1[4]={0,0,0,0},k=0,m;
	while(k!=s1){
		if(a1[1] == s1/4 )	a1[1] = a1[1]-1;
		if(a1[0] == s1/4 )	a1[0] = a1[0]-1;
		if(a1[2] == s1/4 )	a1[2] = a1[2]-1;
		if(a1[3] == s1/4 )	a1[3] = a1[3]-1;
		int m1 = min(a[0][a1[0]],a[1][a1[1]]);
		int m2 = min(a[2][a1[2]],a[3][a1[3]]);
		int m3 = min(m1,m2);
		if(m3 == a[0][a1[0]]){
			a[0][a1[0]] = 999;
			a1[0]++;
		}
		else if(m3 == a[1][a1[1]]){
			a[1][a1[1]] = 999;
			a1[1]++;
		}
		else if(m3 == a[2][a1[2]]){
			a[2][a1[2]] = 999;
			a1[2]++;
		}
		else {
			a[3][a1[3]] = 999;
			a1[3]++;
		}
		k++;
		if(m3!=m && m3!=999){
			f1<<m3<<" ";
			m=m3;
		}

		//cout<<m3<<" "<<"::";
	}
}

void copy(fstream f[8],int s){
	int i,j,x;
	for(i=0;i<4;i++){
		f[i+4]>>x;
		if(x==-1){
			for(j=0;j<s;j++){
				f[i]<<999<<" ";
			}
		}
		else{
			f[i].seekp(ios::beg);
			f[i]<<x<<" ";
			for(j=1;j<s;j++){
				f[i+4]>>x;
				f[i]<<x<<" ";
			}
		}
	}
}

int main(){
	fstream f[8],fin;
	int i,j;
	fin.open("input.txt",ios::in|ios::out);
	char* str[8]={"a1.txt","a2.txt","a3.txt","a4.txt","a5.txt","a6.txt","a7.txt","a8.txt"};
	for(i=0;i<8;i++){
		f[i].open(str[i],ios::in|ios::out);
	}
	cout<<"enter the no of elements : ";
	int x,n,a[3];
	cin>>n;
	for(i=0;i<n;i++){
		cin>>x;
		fin<<x<<endl;
	}
	fin.close();
	fin.open("input.txt",ios::in|ios::out);
	int k=0;
	int a1[4][100];
	while(k!=n){
		for(i=0;i<4;i++){
			for(j=0;j<3;j++){
				fin>>a[j];k++;
			}
			sort(a,a+3);
			for(j=0;j<3;j++){
				f[i]<<a[j]<<" ";
			}
			f[i]<<endl;
			f[i+4]<<-1;
		}
		if(i==4){
			i=0;
		}
	}
	int p=4;
	k=0;
	int s = 3;
	while(s<n){
		s = s*4;p=4;k=0;
		for(i=0;i<8;i++){
				f[i].close();
			}
		for(i=0;i<8;i++){
				f[i].open(str[i],ios::in|ios::out);
				f[i].seekg(ios::beg);
			}
		while(k<n){
			for(i=0;i<4;i++){
				for(j=0;j<s/4;j++){
					f[i]>>a1[i][j];
					cout<<a1[i][j]<<" ";
					k++;
				}
				cout<<endl;
			}
			fill(f[p],a1,s);
			p++;
		}
		for(i=0;i<8;i++){
			f[i].close();
		}
		for(i=0;i<8;i++){
			f[i].open(str[i],ios::in|ios::out);
			f[i].seekg(ios::beg);
		}
		copy(f,s);
		//break;
	}
	fstream fout;
	fout.open("output.txt",ios::in|ios::out);
	k=0;
	f[0].close();
	f[0].open(str[i],ios::in|ios::out);
	//f[0].seekp(ios::beg);
	for(i=0;i<8;i++){
		f[i].close();
	}
	fout.close();
	return 0;
}

/*
24
24
4
8
19
12
7
2
20
18
6
17
9
16
10
11
21
22
1
23
3
13
15
14
45
*/
