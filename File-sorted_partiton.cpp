#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;

char str[100],str1[100];

int fold(char str[100],int arr[3],int &p){
	int i,s=0,r=1,k=0;
	for(i=p;i>=0;i--){
		if(str[i]!=' '){
			s = s + (int)(str[i]-'0')*r;
			r=r*10;
		}
		else{
			if(s!=0)
				arr[k++] = s;
			s=0;r=1;
		}
		if(k==3)
			break;
	}
	p=i;
	if(s!=0 && k!=3)
		arr[k++] = s;
	return k;
}
void merge(int a[3],int b[3],int c[6],int A,int B){
	int i,k=0,k1=0;
	for(i=0;k<A && k1<B;i++){
		if(a[k]>b[k1]){
			c[i] = a[k++];
		}
		else{
			c[i] = b[k1++];
		}
	}
	while(k<A){
		c[i++] = a[k++];
	}
	while(k1<B){
		c[i++] = b[k1++];
	}
}
void merge1(int a[3],int b[3],int c[6],int A,int B){
	int i,k=0,k1=0;
	for(i=0;k<A && k1<B;i++){
		if(a[k]<b[k1]){
			c[i] = a[k++];
		}
		else{
			c[i] = b[k1++];
		}
	}
	while(k<A){
		c[i++] = a[k++];
	}
	while(k1<B){
		c[i++] = b[k1++];
	}
}

int main(){
	int a[3],b[3],c[6],i;
	fstream f1,f2;
	f1.open("f1.txt");
	f2.open("f2.txt");
	fstream f3;
	f3.open("f3.txt");
	int k=0,A,B;
	int p,p1;
	while(!f1.eof() && !f2.eof()){
		f1.getline(str,100);
		p = strlen(str)-1;
		f2.getline(str1,100);
		p1 = strlen(str1)-1;
		while(p>=0 || p1>=0){
			A = fold(str,a,p);
			for(i=0;i<A;i++){
				cout<<a[i]<<" ";
			}
			B = fold(str1,b,p1);
			for(i=0;i<B;i++){
				cout<<b[i]<<" ";
			}
			merge(a,b,c,A,B);
			cout<<endl;
			for(i=0;i<(A+B);i++){
				cout<<c[i]<<" ";
			}
			cin>>i;
			for(i=0;i<(A+B);i++){
				f3<<c[i]<<" ";
			}
		}
		f3<<endl;
	}
	f3.close();
	fstream f4;
	f3.open("f3.txt",ios::out|ios::in);
	f4.open("f4.txt",ios::out|ios::in);
	while(!f3.eof()){
		f3.getline(str,100);
		p = strlen(str)-1;
		f3.getline(str1,100);
		p1 = strlen(str1)-1;
		while(p>=0 || p1>=0){
			A = fold(str,a,p);
			for(i=0;i<A;i++){
				cout<<a[i]<<" ";
			}
			B = fold(str1,b,p1);
			for(i=0;i<B;i++){
				cout<<b[i]<<" ";
			}
			merge1(a,b,c,A,B);
			cout<<endl;
			for(i=0;i<(A+B);i++){
				f4<<c[i]<<" ";
			}
		}
	}
	f3.close();
	f4.close();
	f1.close();
	f2.close();
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
5
*/
