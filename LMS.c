
#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdlib.h>
#define RETURNTIME 15

void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);

int checkid(int);
int getdata();
void Password();
void mainmenu();

void fine();
FILE *fp,*ft,*fs;

char findbook;
char password[10]="admin";

struct date
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char author[20];
    int quantity;
    float price;
    int count;

    struct date issued;
    struct date duedate;

};
struct books b;


int main()
{       Password();
    getch();
    return 0;

}

void mainmenu()
{

    printf("\n\t\t\tMAIN MENU\n");
    printf("1.Add Books\n");
    printf("2.Delete Book\n");
    printf("3.Search Books\n");
    printf("4.Issue Book\n");
    printf("5.View Book List\n");
    printf("6.Edit Book List\n");
    printf("7.Fine Calculation\n");
    printf("8.Close Application\n");

    printf("Enter Your Choice:\n");
    switch(getch())
    {
    case '1':
        addbooks();
        break;
    case '2':
        deletebooks();
        break;
    case '3':
        searchbooks();
        break;
    case '4':
        issuebooks();
        break;
    case '5':
        viewbooks();
        break;
    case '6':
        editbooks();
        break;
    case '7':
        fine();
      break;
    case '8':
        printf("\n\tLibrary Management System Closed......\n\n\n");
        break;

    default:
        printf("wrong choice , try again\n");
        mainmenu();
        break;
    }
}

void addbooks()
{
    fp=fopen("data.txt","ab+");
    printf("To Add new book to data ");
    if(getdata()==1)
    {
        fseek(fp,0,SEEK_END);
        fwrite(&b,sizeof(b),1,fp);
        fclose(fp);
        printf("The record is saved successfully\n");

        mainmenu();
    }
}

void deletebooks()
{
    system("cls");
    int d;
    printf("Enter the book ID to delete\n");
    scanf("%d",&d);
    fp=fopen("data.txt","rb+");
    rewind(fp);
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        if(b.id==d)
        {
            printf("The book Record is availbale\n");
            printf("Book Name:%s\n",b.name);
            findbook='t';
        }
    }
    if(findbook!='t')
    {
        printf("NO record is found \n");
        if(getch())
            mainmenu();
    }
    if(findbook=='t')
    {
        printf("Do you want to delete it?(Y/N):");
        if(getch()=='y')
        {
            ft=fopen("temp.txt","wb+");
            rewind(fp);
            while(fread(&b,sizeof(b),1,fp)==1)
            {
                if(b.id!=d)
                {
                    fseek(ft,0,SEEK_CUR);
                    fwrite(&b,sizeof(b),1,ft);//write all in tempory file except that we want to delete
                }
            }
            fclose(ft);
            fclose(fp);
            remove("data.txt");
            rename("temp.txt","data.txt");
            fp=fopen("data.txt","rb+");
            //copy all item from temporary file to fp except that we want to delete
            if(findbook=='t')
            {
                printf("\nThe record is deleted sucessfully\n");

            }
            mainmenu();

        }


    }

}


void searchbooks()
{
    system("cls");
    int d;
    printf("********Search Books*******\n");
    printf("1.Search By ID\n");
    printf("2.Search By Name\n");
    printf("Enter your choice:\n");
    fp=fopen("data.txt","rb+");
    rewind(fp);
    switch(getch())
    {
    case '1':
    {
        printf("\n****Search Books by ID****\n");
        printf("Enter the book ID:");
        scanf("%d",&d);
        while(fread(&b,sizeof(b),1,fp)==1)
        {
            if(b.id==d)
            {
                fflush(stdin);
                printf("\nThe book is available\n");
                printf("ID:%d\n",b.id);
                printf("Name:%s\n",b.name);
                printf("Author:%s\n",b.author);
                printf("Quantity:%d\n",b.quantity);
                printf("Price:%f\n",b.price);

                findbook='t';
                mainmenu();
            }

        }
        if(findbook!='t')
        {
            printf("No Record found\n");
        }
    }
    case '2':
    {
        char s[15];
        system("cls");
        printf("\n****Search Book by name****\n");
        printf("Enter Book Name: ");
        scanf("%s",&s);
        int d=0;
        while(fread(&b,sizeof(b),1,fp)==1)
        {
            if(strcmp(b.name,(s))==0)
            {
                //checks whether a.name is equal to s or not
                printf("\nThis book is available\n");
                printf("ID:%d\n",b.id);
                printf("Name:%s\n",b.name);
                printf("Author:%s\n",b.author);
                printf("Quantity:%d\n",b.quantity);
                printf("Price:%d\n",b.price);
                d++;
            }
        }
        if(d==0)
        {
            printf("No Record Found\n");
        }
        fclose(fp);
    }
    mainmenu();
    }
}

void issuebooks()
{ int t=0; //t=book id
b.issued.dd=01;
b.issued.mm=01;
b.issued.yy=20;

    printf("\n**********ISSUE BOOKS*********\n");
    printf("1. Issue a Book\n");
    printf("2. View issued Books\n");
    printf("3. Search issued\n");
    printf("4. RETURN issued book\n");
    printf("Enter a choice:\n");
    switch(getch())
    {
    case '1':
    {
        system("cls");
        int c=0;
        printf("****Issue Book Section****\n");
        printf("Enter the book ID:");

        scanf("%d",&t);
        fp=fopen("data.txt","rb");
        fs=fopen("issue.txt","ab+");
        if(checkid(t)==0)    //issues those which are present in library
        {
            printf("The book record is available\n");
            printf("there are %d unissued books in library\n",b.quantity);
            printf("The name of Book is %s \n",b.name);
            printf("Enter Student name:");
            scanf("%s",b.stname);

            printf("\n\nIssued date=%d-%d-%d",b.issued.dd,b.issued.mm,b.issued.yy );

            printf("\nThe book of ID %d is issued\n",b.id );
            b.duedate.dd=b.issued.dd+RETURNTIME;   //for return date
            b.duedate.mm=b.issued.mm;
            b.duedate.yy=b.issued.yy;
            if(b.duedate.dd>30)
            {
                b.duedate.mm+=b.duedate.dd/30;
                b.duedate.dd-=30;

            }
            if(b.duedate.mm>12)
            {
                b.duedate.yy+=b.duedate.mm/12;
                b.duedate.mm-=12;
            }
            printf("\nTo be returned:%d-%d-%d\n",b.duedate.dd,b.duedate.mm,b.duedate.yy );
            fseek(fs,sizeof(b),SEEK_END);
            fwrite(&b,sizeof(b),1,fs);
            fclose(fs);
            c=1;
        }
        if(c==0)
        {
            printf("No record found\n");
        }
        fflush(stdin);
        fclose(fp);
        printf("The Book has taken by Mr. %s\n",b.stname);

    printf("Issued Date:%d-%d-%d\n",b.issued.dd,b.issued.mm,b.issued.yy);

    printf("Returning Date:%d-%d-%d\n",b.duedate.dd,b.duedate.mm,b.duedate.yy);

    }
    break;


    case '2':{
        int j=4;
        printf("******************Issued Book List******************\n");
        printf("STUDENT     NAME    ID  BOOK_NAME   ISSUE_DATE  RETURN_DATE \n");
        fs=fopen("issue.txt","rb");
        while(fread(&b,sizeof(b),1,fs)==1)
        {
            printf("%s \t",b.stname );
            printf("%d \t",b.id );
            printf("%s \t",b.name );
            printf("%d-%d-%d \t",b.issued.dd,b.issued.mm,b.issued.yy );
            printf("%d-%d-%d \t",b.duedate.dd,b.duedate.mm,b.duedate.yy );
            j++;
            printf("\n");
        }
        fclose(fs);
        getch();
        issuebooks();
        break;

    }
    case '3':   //search issuedbooks using id
    {
        system("cls");
        printf("Enter book id:");
        int p=0;
        int c=0;

        scanf("%d",&p);
        fs=fopen("issue.txt","rb");
        while(fread(&b,sizeof(b),1,fs)==1)
        {
            if(b.id==p)
            {
                printf("The Book has taken by Mr. %s\n",b.stname);

    printf("Issued Date:%d-%d-%d\n",b.issued.dd,b.issued.mm,b.issued.yy);

    printf("Returning Date:%d-%d-%d\n",b.duedate.dd,b.duedate.mm,b.duedate.yy);

                getch();
                c=1;
            }
        }
        fflush(stdin);
        fclose(fs);
        if(c==0)
        {
            printf("No record found\n");

        }
        mainmenu();
    }
    break;

    case '4':
    {
        int c;
        FILE *fg; //declaration of temporary file for delete

        printf("Enter book ID to return:");
        scanf("%d",&c);
        fs=fopen("issue.txt","rb+");		//checking for the id number with book record.
        while(fread(&b,sizeof(b),1,fs)==1)
        {
            if(b.id==c)
            {
                printf("The Book has taken by Mr. %s\n",b.stname);

    printf("Issued Date:%d-%d-%d\n",b.issued.dd,b.issued.mm,b.issued.yy);

    printf("Returning Date:%d-%d-%d\n",b.duedate.dd,b.duedate.mm,b.duedate.yy);
                findbook='t';
            }
            if(findbook=='t')
            {
                printf("Do you want to remove it?(Y/N) ");
                if(getch()=='y')
                {
                    fg=fopen("record.txt","wb+");
                    rewind(fs);
                    while(fread(&b,sizeof(b),1,fs)==1)
                    {
                        if(b.id!=c)
                        {
                            fseek(fs,0,SEEK_CUR);
                            fwrite(&b,sizeof(b),1,fg);
                        }
                    }
                    fclose(fs);
                    fclose(fg);
                    remove("issue.txt");
                    rename("record.txt","issue.txt");
                    printf("\n\nThe issued book is returned to library\n");



                }
            }
            if(findbook!='t')
            {
                printf("No record found\n");
            }
            mainmenu();
            break;
        }

        default:
            printf("\aWrong entry\n");
            issuebooks();
            break;
        }
    }
}
int getdata()
{
    int i=1;
    int t;
    printf("enter the information below..\n");
    printf("Books ID:\t");
    scanf("%d",&t);


    if(i==0)
    {
        printf("the book already exists\n");

        mainmenu();
        return 0;
    }
    b.id=t;
    printf("Book Name:");
    scanf("%s",&b.name);
    printf("Author:");
    scanf("%s",&b.author);
    printf("Quantity:");
    scanf("%d",&b.quantity);
    printf("Book Price:");
    scanf("%d",&b.price);
    return 1;

}

void viewbooks(void)
{
    int i=0,j;
    system("cls");

    printf("***************************Book List***********************\n");
    printf("ID   BOOK NAME   AUTHOR     QTY    PRICE\n");
    j=4;
    fs=fopen("data.txt","rb");
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        printf("%d \t",b.id);
        printf("%s \t",b.name);
        printf("%s \t",b.author );
        printf("%d \t",b.quantity );
        printf("%d \t",b.price );
        j++;
        i=i+b.quantity;
printf("\n");
    }
    printf("Total Books:%d",i);
    fclose(fp);
    mainmenu();

}

void editbooks()
{
    system("cls");
    int c=0;
    int d,e;
    printf("*****Edit Books Section*****\n");
    printf("Enter book id to be edited:");
    scanf("%d",&d);
    fp=fopen("data.txt","rb+");
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        if(checkid(d)==0)
        {
            printf("The book is availbale\n");
            printf("\nThe Book ID:%d",b.id);
            printf("\nEnter new Author:");
            scanf("%s",b.author);
            printf("\nEnter new quantity:");
            scanf("%d",&b.quantity);
            printf("\nEnter new price:");
            scanf("%f",&b.price);
            printf("\nThe record is modified");
            fseek(fp,ftell(fp)-sizeof(b),0);
            fwrite(&b,sizeof(b),1,fp);
            fclose(fp);
            c=1;
        }
        if(c==0)
        {
            printf("No record found\n");
        }
    }

}


int checkid(int t)
{
    rewind(fp);
    while(fread(&b,sizeof(b),1,fp)==1)
        if(b.id==t)
            return 0;


            return 1;

}

void Password()
{
    char ch;
    char pass[10];
    printf("****LIBRARY MANAGEMENT SYSTEM****\n");
    printf("Submitted by: UDIT SINGLA\n");
    printf("Submitted to: Dr. Shelly Sachdeva\n\n");
    printf("Enter password(admin):");
    gets(pass);

    if(strcmp(pass,password)==0)
    {
        printf("\nPassword match\n");
        printf("Press any key to continue..\n");
        getch();
        mainmenu();
    }
    else
    {
        printf("Warning, incoreect password\n");
        getch();
        Password();
    }
}

void fine()
{
    int days;
    float fine_per_day;
    float total;
    system("cls");
    printf("Enter the Number of days of fine(late return of book \n");
    scanf("%d",&days);
    printf("Fine amount per day: ");
    scanf("%f",&fine_per_day);
    total=days*fine_per_day;
    printf("The total amount of fine will be: %f",total);

    mainmenu();

}



main.c
Displaying main.c.
