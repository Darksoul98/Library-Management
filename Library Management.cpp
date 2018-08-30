#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<iomanip.h>
void box(int x1,int y1,int x2,int y2);
void title(int r,char s[30],int k=38);
void nocursor(int r,char s[20],int k=30,int p=45)
{
	window(k,r,p,r);
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	cout<<s;
}
void cursor(int r,char s[20],int k=30,int p=45)
{
	window(k,r,p,r);
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	cout<<s;
}
void subtitle(int r,char s[20],int k,int k2)
{
	window(k,r,k2,r);
	textbackground(RED);
	textcolor(BLUE);
	clrscr();
	cout<<s;
}
void box(int x1,int y1,int x2,int y2)
{
	int i;
	window(1,1,80,25);
	clrscr();
	clrscr();
	window(1,1,79,24);
	char horz='Í';
	char rttop = '»';
	char lttop ='É';
	char rtbott ='¼';
	char ltbott='È';
	char vert='º';
		gotoxy(x1,y1);	//for positioning
		cout<<lttop;
		gotoxy(x2,y1);
		cout<<rttop;
		gotoxy(x1,y2);
		cout<<ltbott;
		gotoxy(x2,y2);
		cout<<rtbott;
		for(i=y1+1;i<=y2-1;i++)
		{
			gotoxy(x1,i);
			cout<<vert;
		}
		for(i=y1+1;i<=y2-1;i++)
		{
			gotoxy(x2,i);
			cout<<vert;
		}
		for(i=x1+1;i<=x2-1;i++)
		{
			gotoxy(i,y1);
			cout<<horz;
		}
		for(i=x1+1;i<=x2-1;i++)
		{
			gotoxy(i,y2);
			cout<<horz;
		}
}
class book
{
		int bno;
		char bname[50];
		char aname[20];
		int bprice;
		
	public:
		void create();
		void display(int k,int j);
		void searchdisp();
		void modify();
		int retbno()
		{
			return bno;
		}
		int retbprice()
		{
			return bprice;
		}
		char* retbname()
		{
			return bname;
		}
		
};
void book::create()
{

	gotoxy(2,2);
	cout<<"Enter the Book No."<<endl;
	gotoxy(2,3);
	cout<<"Enter Book Name"<<endl;
	gotoxy(2,4);
	cout<<"Enter Author Name"<<endl;
	gotoxy(2,5);
	cout<<"Enter the Book Price."<<endl;

	gotoxy(51,2);
	cin>>bno;
	gotoxy(51,3);
	gets(bname);
	gotoxy(51,4);
	gets(aname);
	gotoxy(51,5);
	cin>>bprice;

}
void book::display(int k,int j)
{
	cout<<bno;
	gotoxy(k+10,j);
	cout<<bname;
	gotoxy(k+30,j);
	cout<<aname;
	gotoxy(k+50,j);
	cout<<bprice;
}
void book::searchdisp()
{
	gotoxy(2,3);
	cout<<"BookNo."<<endl;
	gotoxy(51,3);
	cout<<bno;

	gotoxy(2,4);
	cout<<"BookName"<<endl;
	gotoxy(51,4);
	puts(bname);

	gotoxy(2,5);
	cout<<"AuthorName"<<endl;
	gotoxy(51,5);
	puts(aname);

	gotoxy(2,6);
	cout<<"BookPrice."<<endl;
	gotoxy(51,6);
	cout<<bprice;
}
void book::modify()
{
	gotoxy(2,8);
	cout<<"Book no.";
	gotoxy(51,8);
	cin>>bno;

	gotoxy(2,9);
	cout<<"Modify Book Name:";
	gotoxy(51,9);
	gets(bname);

	gotoxy(2,10);
	cout<<"Modify Authors Name:";
	gotoxy(51,10);
	gets(aname);

	gotoxy(2,11);
	cout<<"Enter the Book Price."<<endl;
	gotoxy(51,11);
	cin>>bprice;
}

fstream fp;
book bk;

void write_book()
{
	clrscr();
	box(1,1,79,24);
	window(2,2,78,23);

	char ch;
	fp.open("book.txt",ios::out|ios::app);
	do
	{
		clrscr();
		gotoxy(35,1);
		cout<<"ADD BOOK";
		bk.create();
		fp.write((char*)&bk,sizeof(book));
		gotoxy(10,6);
		cout<<"Do You Want To Add Another Book	(Y/N)";
		gotoxy(51,6);
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
	getch();

}
void search_book()
{
	int n;
	clrscr();
	box(1,1,79,24);
	window(2,2,78,23);
	gotoxy(35,1);
	cout<<"SEARCH BOOK";
	gotoxy(2,2);
	cout<<"Enter Book No.";
	gotoxy(51,2);
	cin>>n;
	int flag=0;
	fp.open("book.txt",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(bk.retbno()==n)
		{
			bk.searchdisp();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		gotoxy(25,4);
		cout<<"Book Does Not Exist";
	}
	getch();
}
void displayall_book()
{
	int i=0,k,j;
	clrscr();
	box(1,1,79,24);
	window(2,2,78,23);
	fp.open("book.txt",ios::in);
	if(!fp)
	{
		gotoxy(35,12);
		cout<<"No Data Found";
		getch();
	}

	gotoxy(35,2);
	cout<<"Book List";
	gotoxy(2,3);
	cout<<"BookNo.";
	gotoxy(12,3);
	cout<<"BookName";
	gotoxy(32,3);
	cout<<"Author";
	gotoxy(52,3);
	cout<<"Book Price";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		gotoxy(k=2,j=4+i);
		bk.display(k,j);
		i++;

	}
	fp.close();
	getch();
}
void modify_book()
{
	int n,flag=0;
	clrscr();
	box(1,1,79,24);
	window(2,2,78,23);
	gotoxy(30,2);
	cout<<"MODIFY BOOK RECORD";
	gotoxy(2,3);
	cout<<"Enter Book No.";
	gotoxy(51,3);
	cin>>n;
	fp.open("book.txt",ios::in|ios::out);
	while((fp.read((char*)&bk,sizeof(book)))||(flag==0))
	{
		if(bk.retbno()==n)
		{
			bk.searchdisp();
			gotoxy(25,7);
			cout<<"Enter New Details of Book"<<endl;
			bk.modify();
			int pos=-1*sizeof(book);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			gotoxy(51,12);
			cout<<"Record Updated";
			flag=1;
		}


	}
	fp.close();
	if(flag==0)
	{
		gotoxy(38,4);
		cout<<"No Record Found";
		getch();
	}
}
void delete_book()
{
	int n,flag=0;
	clrscr();
	box(1,1,79,24);
	window(2,2,78,23);
	gotoxy(35,1);
	cout<<"DELETE BOOK"<<endl;
	gotoxy(2,2);
	cout<<"Enter The Book No. You Want To Delete";
	gotoxy(51,2);
	cin>>n;
	fstream fp2;
	fp.open("book.txt",ios::in|ios::out);
	fp2.open("temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(bk.retbno()==n)
		{
			bk.searchdisp();
			flag++;
		}
			if(bk.retbno()!=n)
		{
			fp2.write((char*)&bk,sizeof(book));
			flag++;
		}
	}
	fp2.close();
	fp.close();
	remove("book.txt");
	rename("temp.txt","book.txt");
	if(flag==0)
	{
		gotoxy(38,7);
		cout<<"No Record Found";

	}
	else
	{
		gotoxy(38,10);
		cout<<"Record Deleted"<<endl;
	}
	getch();
}


void screen1()
{
	clrscr();
	int ch;
	int cr=0;

	do{
		box(1,1,79,24);
		char option[5][20]={"Add Book","Display","Search","Modify","Delete"};
		gotoxy(30,2);
		cout<<"MAIN MENU";
		subtitle(20,"press esc to exit",10,27);

		for(int i=0;i<5;i++)
			nocursor(6+i*2,option[i]);
		cursor(6+cr*2,option[cr]);
		ch=getch();
		if(ch==0)ch=getch();
			switch(ch)
			{
				case 72:nocursor(6+cr*2,option[cr]);
					if(cr==0)
						cr=4;
					else
						cr--;
					cursor(6+cr*2,option[cr]);
					break;
				case 80:nocursor(6+cr*2,option[cr]);
					if (cr==4)
						cr=0;
					else
						cr++;
					cursor(6+cr*2,option[cr]);
					break;
				case 13:
					switch(cr)
					{
						case 0:write_book();break;
						case 1:displayall_book();break;
						case 2:search_book();break;
						case 3:modify_book();break;
						case 4:delete_book();break;
					}
			}
	}while(ch!=27);

}

void screen2()
{
	clrscr();
	int order_arr[50],quan[50],c=0;
	float amt=0,amtf=0;
	char ch='Y';
	displayall_book();
	cout<<endl;

	cout<<"º PLACE YOUR ORDER"<<endl;

	do{
		cout<<"º Enter The Book No. Of The Book:\t";
		cin>>order_arr[c];
		fp.open("book.txt",ios::in);
		fp.read((char*)&bk,sizeof(book));
		int book_available=0;
		while(!fp.eof())
		{
			if(bk.retbno()==order_arr[c])
			{
				book_available=1;
				break;
			}
		    fp.read((char*)&bk,sizeof(book));
		}
		fp.close();
		if(book_available==0){
			cout<<"º\tEntered book no is not available";
		}
		else{
			cout<<"\nº Quantity in number: \t";
			cin>>quan[c];
			c++;
		}
		cout<<"\nº\tDo You Want To Order Another Product ? (y/n)\t";
		cin>>ch;
	}while(ch=='y' ||ch=='Y');
	cout<<"\nº\tThank You For Placing The Order";
	getch();
	clrscr();

	cout<<"********************************INVOICE**************************************\n"<<endl;
	cout<<"º BookNo.\tBookName\tQuantity \tPrice \tAmount "<<endl;
	for(int x=0;x<c;x++)
	{
		fp.open("book.txt",ios::in);
		fp.read((char*)&bk,sizeof(book));
		while(!fp.eof())
		{
			if(bk.retbno()==order_arr[x])
			{
				amtf=amt+bk.retbprice()*quan[x];
				amt=bk.retbprice()*quan[x];
				cout<<"º "<<order_arr[x]<<"\t\t"<<bk.retbname()<<"\t"<<quan[x]<<"\t"<<bk.retbprice()<<"\t"<<amt<<endl;
				break;
			}
		fp.read((char*)&bk,sizeof(book));
		}
	fp.close();
	}
	cout<<"\n\nº\t\t\t\tTOTAL = Rs."<<amtf;
	getch();
}

void screen0()
{

	window(1,1,80,25);
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	int ch;
	int cr=0;
	do{
		box(1,1,79,24);
		char option[2][20]={"ADMINISTRATOR","CUSTOMER"};
		subtitle(20,"press esc to exit",10,27);
		for(int i=0;i<2;i++)
			nocursor(6+i*2,option[i]);
		cursor(6+cr*2,option[cr]);
		ch=getch();
		switch(ch)
		{
			case 72:nocursor(6+cr*2,option[cr]);
				if(cr==0)
					cr=1;
				else
					cr=0;
				cursor(6+cr*2,option[cr]);
				break;
			case 80:nocursor(6+cr*2,option[cr]);
				if(cr==2)
					cr=0;
				else
					cr=1;
				cursor(6+cr*2,option[cr]);
				break;
			case 13:
				switch(cr)
				{
					case 0:screen1();break;
					case 1:screen2();break;
				}
				break;
		}
	}while(ch!=27);
}
void main()
{
screen0();
getch();
}

