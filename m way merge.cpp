#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int b[100];
int limit;
int convert(string s)
{
	int n=0;
	for(int i=0;i<s.length();i++)
		n=n*10+(int)s[i]-48;
	return n;
}
void read(int size, fstream &file)
{
	int count=0;
	string s;
	while(count<size)
	{
		getline(file,s,' ');
		b[count++]=convert(s);
	}
	limit=size;
}
void write(fstream &f)
{
	for(int i=0;i<limit;i++)
		f<<b[i]<<" ";
}
void writelast(fstream &f)
{
	for(int i=0;i<limit;i++)
		if(b[i])
		f<<b[i]<<" ";
}
void mergesort(int *x,int *y,int *z,int size)
{
	int i=0,j=0,k=0;
	while(i<size&&j<size)
	{
		if(*(x+i)<*(y+j))
		{
			*(z+k)=*(x+i);
			i++;
		}
		else
		{
			*(z+k)=*(y+j);
			j++;
		}
		k++;
	}
	while(i<size)
	{
		*(z+k)=*(x+i);
			i++;k++;
	}
	while(j<size)
	{
		*(z+k)=*(y+j);
			j++;k++;
	}
}
int main()
{
	fstream f[4],file;int store;
	cout<<"Enter the no of enteries::";
	int n;cin>>n;
	cout<<"enter the size of the sorted partition::";
	int p;cin>>p;
	f[0].open("101.txt",ios::in|ios::out|ios::trunc);
	f[1].open("102.txt",ios::in|ios::out|ios::trunc);
	f[2].open("103.txt",ios::in|ios::out|ios::trunc);
	f[3].open("104.txt",ios::in|ios::out|ios::trunc);
	file.open("105.txt",ios::in|ios::out|ios::trunc);
	cout<<"enter the data in form of sorted partitions::";
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
		file<<a[i]<<" ";
	while(n%p!=0)
		{file<<"0 ";n++;}
	for(int i=0;i<4;i++)
		f[i].clear();
	int change=0;
	file.seekg(0,ios::beg);
	for(int i=0;i<n;i=i+p)
	{
		read(p,file);
		if(change%2==0)
			{sort(b,b+p);write(f[0]);}
		else
			{sort(b,b+p);write(f[1]);}
		change++;
	}
	change =0;
	int size=p;
	int m=4;
	while(size<n)
	{
		if(change%2==0)
		{
			f[2].clear();
			f[3].clear();
			for(int i=0;i<m;i++)
			{
				if((i+1)<=(m/2))
					f[i].seekg(0,ios::beg);
				else
					f[i].seekp(0,ios::beg);
			}
			int r=0;
			while(!f[0].eof()&&!f[1].eof())
			{
				read(size,f[0]);
				int x[size];
				sort(b,b+limit);
				for(int i=0;i<size;i++)
					x[i]=b[i];
				read(size,f[1]);
				int y[size];
				sort(b,b+limit);
				for(int i=0;i<size;i++)
					y[i]=b[i];
				int z[2*size];
				mergesort(x,y,z,size);
				if(r%2==0)
				{
					for(int i=0;i<2*size;i++)
						f[2]<<z[i]<<" ";
						store=2;
				}
				else
				{
					for(int i=0;i<2*size;i++)
						f[3]<<z[i]<<" ";
						store=3;					
				}
				r++;
			}
		}
		else 
		{
			f[0].clear();
			f[1].clear();
			for(int i=0;i<m;i++)
			{
				if((i+1)<=(m/2))
					f[i].seekp(0,ios::beg);
				else
					f[i].seekg(0,ios::beg);
			}
			int r=0;
			while(!f[2].eof()&&!f[3].eof())
			{
				read(size,f[2]);
				int x[size];
				sort(b,b+limit);
				for(int i=0;i<size;i++)
					x[i]=b[i];
				read(size,f[3]);
				int y[size];
				sort(b,b+limit);
				for(int i=0;i<size;i++)
					y[i]=b[i];
				int z[2*size];
				mergesort(x,y,z,size);
				if(r%2==0)
				{
					for(int i=0;i<2*size;i++)
						f[0]<<z[i]<<" ";
						store=0;
				}
				else
				{
					for(int i=0;i<2*size;i++)
						f[1]<<z[i]<<" ";
						store=1;					
				}
				r++;
			}			
		}
		size=size*2;
		change++;
	}
	cout<<endl<<store;
	file.clear();
	f[store-1].seekg(0,ios::beg);
	file.seekp(0,ios::beg);
	while(!f[store-1].eof())
	{
		read(n,f[store-1]);
		writelast(file);
	}
	for(int i=0;i<4;i++)
	{
		f[i].close();
	}
	file.close();
	return 0;	
}

