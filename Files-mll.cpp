#include<iostream>
#include<fstream>
using namespace std;
int size=4;

struct pointer{
	int fptr;
	int bptr;
}sp[10],cp[10];

struct index{
	int list;
	int pos;
}s[10],c[10];

void ini(index s[]){
	int i;
	for(i=0;i<10;i++){
		s[i].list=s[i].pos = -1;
	}
}
void iniptr(pointer s[]){
	int i;
	for(i=0;i<10;i++){
		s[i].fptr=s[i].bptr = -1;
	}
}

int search(index s[],int l){
	int i;
		for(i=0;i<10;i++){
			if(s[i].list == l){
				return s[i].pos;
			}
		}
		return -1;
	}
	int count;
void put(index s[],int s1){
	int i;
	for(i=0;i<10;i++){
		if(s[i].list==-1){
			s[i].list = s1;
			s[i].pos = count;
			break;
		}
	}
}

void insert(int s1,int c1){
	int i;
	fstream f;
	f.open("multilist.txt");
	f.seekg((count)*4,ios::beg);
	int src = search(s,s1);
	if(src==-1){
		put(s,s1);
		f<<s1<<" "<<c1<<" ";
		int csrc = search(c,c1);
		if(csrc == -1){
			put(c,c1);
		}
		else{
			while(1){
				if(cp[csrc].fptr==-1){
					c[count].list = c1;
					c[count].pos = count;
					cp[csrc].fptr = count;
					cp[count].bptr = csrc;
					break;
				}
				else{
					csrc = cp[csrc].fptr;
				}
			}
		}
	}
	else{
		while(1){
			if(sp[src].fptr==-1){
				s[count].list = s1;
				s[count].pos = count;
				sp[src].fptr = count;
				sp[count].bptr = src;
				f<<s1<<" "<<c1<<" ";
				int csrc = search(c,c1);
				if(csrc == -1){
					put(c,c1);
				}
				else{
					while(1){
						if(cp[csrc].fptr==-1){
							c[count].list = c1;
							c[count].pos = count;
							cp[csrc].fptr = count;
							cp[count].bptr = csrc;
							break;
						}
						else{
							csrc = cp[csrc].fptr;
						}
					}
				}
				break;
			}
			else{
				src = sp[src].fptr;
			}
		}
	}
}

void searchfile(int s1,int c1){
	int src  = search(s,s1);
	if(src == -1){
		cout<<"Not found!! ";
	}
	else{
		while(1){
			if(c[src].list == c1){
				cout<<"Found ";
				break;
			}
			else{
				src = sp[src].fptr;
			}
			if(sp[src].fptr == -1){
				if(c[src].list == c1){
					cout<<"Found ";
					break;
				}
				else{
					cout<<"Not Found ";
					break;
				}
			}
		}
	}
}

void partcourse(int s1){
	int src = search(c,s1);
	int n=1;
	while(cp[src].fptr != -1){
		n++;
		src = cp[src].fptr;
	}
	cout<<n;
}

void partstu(int s1){
	int src = search(s,s1);
	int n=1;
	while(sp[src].fptr != -1){
		n++;
		src = sp[src].fptr;
	}
	cout<<n;
}

int main()
{
	ini(s);
	ini(c);
	iniptr(sp);
	iniptr(cp);
	ofstream fout;
	fout.open("multilist.txt",ios::trunc);
	int n,k,size;
	int ch;
	ifstream fin;
	for(int i=0;i<10;i++)
		fout<<" ** "<<endl;
	fout.close();
	while(1)
	{
		cout<<"enter roll:\n";
		cin>>n;
		cout<<"enter subject"<<endl;
		cout<<"1.maths"<<endl;
		cout<<"2.phy"<<endl;
		cout<<"3.chem"<<endl;
	    cout<<"4.soc"<<endl;
		cout<<"5.bio"<<endl;
		cin>>ch;
		if(n==-1)break;
		insert(n,ch);
		count++;
		cout<<"enter -1 to exit\n";
		cin>>k;
		if(k==-1)
		break;
	}
	cout<<"\t Stud \t Code \t SFPTR \t SBPTR \t CFPTR \t CBTR\n";
	for(int i=0;i<10;i++){
		cout<<"\t "<<s[i].list<<"\t "<<c[i].list<<"\t "<<sp[i].fptr<<"\t "<<sp[i].bptr<<"\t "<<cp[i].fptr<<"\t "<<cp[i].bptr<<endl;
	}
	cout<<"Search record : ";
	cin>>n>>ch;
	searchfile(n,ch);
	char ch1;
	cout<<" Wanna search for no of students taken a particular course ? (y/n) ";
	cin>>ch1;
	if(ch1=='y'){
		cout<<"Enter the course : ";
		cin>>ch;
		partcourse(ch);
	}
	cout<<" Wanna search for no of courses taken by particular student ? (y/n) ";
	cin>>ch1;
	if(ch1=='y'){
		cout<<"Enter the student roll : ";
		cin>>n;
		partstu(n);
	}
	fin.close();
}
/*
3
1
1
7
2
1
62
4
1
50
2
1
67
3
3
59
2
2
62
1
1
50
1
1
3
2
-1
*/
