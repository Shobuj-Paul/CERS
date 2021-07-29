#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
void gotoxy(int x, int y)//Move cursor to desired location
{
        printf("%c[%d;%df", 0x1B, y, x);
}
int getch(void)//get a character, does not wait for enter, does not echo
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
void borders()//Creates the borders for the program
{
	char ch='#';
        int i;
        for(i=0;i<150;i++)
        {
                gotoxy(i,1);
                printf("%c",ch);
        }
        for(i=0;i<150;i++)
        {
                gotoxy(i,50);
                printf("%c",ch);
        }
        for(i=0;i<50;i++)
        {
                gotoxy(1,i);
                printf("%c",ch);
        }
        for(i=0;i<50;i++)
        {
                gotoxy(150,i);
                printf("%c",ch);
        }
}
void password()//Puts the password
{
	int i;
label:	system("clear"); borders();
	char passwd[20]="2.718", temp[20];
	gotoxy(45,10);printf("Enter password: ");
	for(i=0;i<strlen(passwd);i++)
	{
		temp[i] = getch();
		printf("*");
	}
	if(strcmp(passwd,temp)==0)
	{
		gotoxy(45,11);
		printf("Access Granted");
	}
	else 
		goto label;
	getch();
	system("clear");
}
struct links
{
	char undertaking[5][100], ch_certificate[4][100], court_case[5][100], FIR[5][100], prescriptions[5][100];
};
union identification //only one required so saving space
{
	char PAN[10], adhr[30], v_id[30], DL[30];
};
typedef struct candidate//main structure
{
	char name[20], category[20], gender[10], edq[50], email[50], acc_no[20], mb[20], district[20];
	int  DOB[3], age, idtyp, symbol;
	union identification id;
	struct links l;
}candidate;
candidate input()//Input basic information of candidate
{
	candidate c; char g;
	c.symbol = 0;				//initialising the to be uploaded information
	strcpy(c.l.undertaking[0],"null");
        strcpy(c.l.ch_certificate[0],"null");
        strcpy(c.l.court_case[0],"null");
	strcpy(c.l.FIR[0],"null");
        strcpy(c.l.prescriptions[0],"null");
	system("clear"); borders();
        gotoxy(20,5);
        printf("Enter name: ");
       	scanf(" %[^\n]s",c.name);gotoxy(20,6);

        printf("Enter your date of birth(dd/mm/yyyy): ");
 	scanf("%d/%d/%d",&c.DOB[0],&c.DOB[1],&c.DOB[2]);gotoxy(20,7);
       	c.age = 2019-c.DOB[2];

      	printf("Enter Gender(F/M/O): ");
   	scanf(" %c",&g);gotoxy(20,8);
    	if(g=='M')				//Assigning gender based on entry
		strcpy(c.gender,"Male");
   	else if(g=='F')
                strcpy(c.gender,"Female");
    	else if(g=='O')
                strcpy(c.gender,"Other");

        printf("Enter Category: ");
        scanf(" %[^\n]s",c.category);gotoxy(20,9);

        printf("Enter e-mail ID: ");
        scanf(" %[^\n]s",c.email);gotoxy(20,10);
	
	printf("Enter mobile number: ");
	scanf(" %[^\n]s",c.mb);gotoxy(20,11);

	printf("Enter district: ");
	scanf(" %[^\n]s",c.district);gotoxy(20,12);

        printf("Enter Account Number: ");
        scanf(" %[^\n]s",c.acc_no);

        system("clear"); borders(); gotoxy(20,5);
        printf("Enter educational qualifications (highest degree and subject): ");gotoxy(20,6);
        scanf(" %[^\n]s",c.edq);gotoxy(20,7);

        printf("Enter identification type: ");gotoxy(20,8); 
        printf("1)PAN Card");gotoxy(20,9);
        printf("2)Aadhar Card");gotoxy(20,10);
        printf("3)Voter ID");gotoxy(20,11);
        printf("4)Driver's License");gotoxy(48,7);
	scanf("%d",&c.idtyp);gotoxy(20,14);
	if(c.idtyp==1)
	{
		printf("Enter PAN Card Number: ");
		scanf(" %[^\n]s",c.id.PAN);
	}
	else if(c.idtyp==2)
        {
                printf("Enter Aadhar Card Number: ");           
                scanf(" %[^\n]s",c.id.adhr);
        }	
	else if(c.idtyp==3)
        {
                printf("Enter Voter's Card Number: ");
                scanf(" %[^\n]s",c.id.v_id);
        }
	else if(c.idtyp==4)
        {
                printf("Enter Driver's License Number: ");
                scanf(" %[^\n]s",c.id.DL);
        }
	system("clear"); borders();
	return c;
}
void display(candidate c)//for displaying candidate info
{
	char a;
	system("clear"); borders();
	gotoxy(20,3);printf("Name: %s",c.name);
	gotoxy(20,4);printf("Date of Birth: %d/%d/%d",c.DOB[0],c.DOB[1],c.DOB[2]);
	gotoxy(20,5);printf("Age (As of January 2020): %d",c.age);
	gotoxy(20,6);printf("Gender: %s",c.gender);
	gotoxy(20,7);printf("Category: %s",c.category);
	gotoxy(20,8);printf("E-mail ID: %s",c.email);
	gotoxy(20,9);printf("Mobile Number: %s",c.mb);
	gotoxy(20,10);printf("District: %s",c.district);
	gotoxy(20,11);printf("Account Number: %s",c.acc_no);
	gotoxy(20,12);printf("Educational Qualifications: %s",c.edq);
	gotoxy(20,13);
	if(c.idtyp==1)
		printf("PAN Card Number: %s",c.id.PAN);
	else if(c.idtyp==2)
                printf("Aadhar Card Number: %s",c.id.adhr);
	else if(c.idtyp==3)
                printf("Voter's Card Number: %s",c.id.v_id);
	else if(c.idtyp==4)
		printf("Driver's License Number: %s",c.id.DL);
	scanf(" %c",&a);
	system("clear"); borders();
	if(c.symbol!=0) //displays symbol after upload
	{
		char t[4][10][20]; int i,ch;
		ch = c.symbol-1;
	        strcpy(t[0][0],"!!!!!!!!!!!");
	        strcpy(t[0][1],"!!");
	        strcpy(t[0][2],"!!!!!!!!!!!");
	        strcpy(t[0][3],"!!");
	        strcpy(t[0][4],"!!!!!!!!!!!");
	        strcpy(t[0][5],"!!");
	        strcpy(t[0][6],"!!!!!!!!!!!");

	        strcpy(t[1][0],"@@@@@@@@@@@@@");
	        strcpy(t[1][1],"@@@@@@ @@@@@@");
	        strcpy(t[1][2],"@@@@@   @@@@@");
	        strcpy(t[1][3],"@@@@     @@@@");
	        strcpy(t[1][4],"@@@       @@@");
	        strcpy(t[1][5],"@@         @@");
	        strcpy(t[1][6],"@@@@@@@@@@@@@");

	        strcpy(t[2][0],"*************");
	        strcpy(t[2][1]," *    *    *");
	        strcpy(t[2][2],"  *   *   *");
	        strcpy(t[2][3],"   *  *  *");
	        strcpy(t[2][4],"    * * *");
	        strcpy(t[2][5],"     ***");
	        strcpy(t[2][6],"      *");

	        strcpy(t[3][0],"~~~~~~~~~~~~~~~~~");
	        strcpy(t[3][1],"~  ~~~     ~~~  ~");
	        strcpy(t[3][2],"~               ~");
	        strcpy(t[3][3],"~      ~~       ~");
	        strcpy(t[3][4],"~               ~");
	        strcpy(t[3][5],"~   `````````   ~");
	        strcpy(t[3][6],"~~~~~~~~~~~~~~~~~");
			
		gotoxy(20,5);printf("%s",t[ch][0]);
		gotoxy(20,6);printf("%s",t[ch][1]);
		gotoxy(20,7);printf("%s",t[ch][2]);
		gotoxy(20,8);printf("%s",t[ch][3]);
 		gotoxy(20,9);printf("%s",t[ch][4]);
 		gotoxy(20,10);printf("%s",t[ch][5]);
 		gotoxy(20,11);printf("%s",t[ch][6]);
		scanf(" %c",&a);
		system("clear"); borders();
	}
	if(strcmp(c.l.ch_certificate[0],"null")!=0)//displays character certificate after upload
	{
		gotoxy(20,5);printf("Line 1: %s",c.l.ch_certificate[0]);
		gotoxy(20,6);printf("Line 2: %s",c.l.ch_certificate[1]);
		gotoxy(20,7);printf("Line 3: %s",c.l.ch_certificate[2]);
		gotoxy(20,8);printf("Line 4: %s",c.l.ch_certificate[3]);
		scanf(" %c",&a);
	}
	system("clear"); borders();
	if(strcmp(c.l.court_case[0],"null")!=0)//displays court documents after upload
        {
                gotoxy(20,5);printf("Nature of Case: %s",c.l.court_case[0]);
                gotoxy(20,6);printf("Fine Paid: %s",c.l.court_case[1]);
                gotoxy(20,7);printf("Jailtime: %s",c.l.court_case[2]);
                gotoxy(20,8);printf("%s",c.l.court_case[3]);
                scanf(" %c",&a);
        }
        system("clear"); borders();
	if(strcmp(c.l.FIR[0],"null")!=0)//displays FIR
        {
                gotoxy(20,5);printf("Conduct of Candidate: %s",c.l.FIR[0]);
                gotoxy(20,6);printf("Suspected Felonies: %s",c.l.FIR[1]);
                gotoxy(20,7);printf("%s",c.l.FIR[2]);
                scanf(" %c",&a);
        }
        system("clear"); borders(); 
	if(strcmp(c.l.prescriptions[0],"null")!=0)//displays prescriptions
        {
                gotoxy(20,5);printf("Name of Doctor: %s",c.l.prescriptions[0]);
                gotoxy(20,6);printf("Any existing mental conditions? : %s",c.l.prescriptions[1]);
                gotoxy(20,7);printf("Severity of Condition: %s",c.l.prescriptions[2]);
                gotoxy(20,8);printf("Comment: %s",c.l.prescriptions[3]);
                scanf(" %c",&a);
        }
	system("clear"); borders();
	if(strcmp(c.l.undertaking[0],"null")!=0)//displays undertaking
	{
		gotoxy(20,5);printf("Line 1: %s",c.l.undertaking[0]);
		gotoxy(20,6);printf("Line 2: %s",c.l.undertaking[1]);
		gotoxy(20,7);printf("Line 3: %s",c.l.undertaking[2]);
		scanf(" %c",&a);
	}		
        system("clear"); borders();
}
void writefile()//for writing into the file
{
	candidate c;
	char ch;
	FILE *fptr;
	char g;
	fptr = fopen("program.dat","ab");
	if(fptr==NULL)
		exit(1);
	fseek(fptr,0,SEEK_END);
	do
	{
		c = input();
		fwrite(&c,sizeof(c),1,fptr);
		gotoxy(20,5);printf("Enter another record(y/n)? ");
		scanf(" %c",&ch);
	}while(ch!='n');
	fclose(fptr);
}
void readfile()//for reading the file
{
	FILE *fptr;
	candidate c;
	fptr = fopen("program.dat","rb");
	if(fptr==NULL)
		exit(1);
	fseek(fptr,0,SEEK_SET);
	while(fread(&c,sizeof(c),1,fptr)==1)
		display(c);
}
candidate search() //for searching the file
{
	candidate c; int ch1, found=-1; char ch2, temp[50];
	FILE *fptr;
	system("clear");borders();
	gotoxy(20,5);printf("Search by:"); 
	gotoxy(20,6);printf("1)E-mail ID");
	gotoxy(20,7);printf("2)Mobile Number");
        gotoxy(31,5);scanf("%d",&ch1);
	gotoxy(20,8);
	switch(ch1)
	{
		case 1: printf("Enter Email ID to search: ");
                        scanf(" %[^\n]s",temp);
                        gotoxy(20,9);
                        fptr = fopen("program.dat","rb");
                        if(fptr==NULL)
                                exit(1);
                        fseek(fptr,0,SEEK_SET);
                        while(fread(&c,sizeof(c),1,fptr)==1)
                        {
                                if(strcmp(c.email,temp)==0)
                                {
                                        found=1;
                                        return c;
                                        break;
                                }
                        }
                        fflush(stdin);
                        if(found == -1)
                        {
                                gotoxy(20,5);printf("Not found");
                        }
                        fclose(fptr);
                        break;
		case 2: printf("Enter mobile number to search: ");
                        scanf(" %[^\n]s",temp);
	  		gotoxy(20,9);
                        fptr = fopen("program.dat","rb");
                        if(fptr==NULL)
                                exit(1);
                        fseek(fptr,0,SEEK_SET);
                        while(fread(&c,sizeof(c),1,fptr)==1)
                        {
                                if(strcmp(c.mb,temp)==0)
                                {
                                	found=1;
					return c;
					break;
                                }
                        }
			fflush(stdin);
			if(found == -1)
			{
				gotoxy(20,5);printf("Not found");
			}
			fclose(fptr);
                        break;
		default: break;
	}
	system("clear"); borders();
}
void update() //for changing any candidate's data
{
	candidate c,d;
	d = search();
	FILE *fptr;
	fptr = fopen("program.dat","rb+");
		while(fread(&c,sizeof(c),1,fptr)==1)
		{
			if(strcmp(d.mb,c.mb)==0)
			{
				c = input();
				fseek(fptr,-sizeof(c),SEEK_CUR);
				fwrite(&c,sizeof(c),1,fptr);
			}
		}
	fclose(fptr);
}
void upsymbol() //for uploading symbol
{
	candidate c,d;
        int ch; char a;
        FILE *fptr;
        d = search();
        fptr = fopen("program.dat","rb+");
        while(fread(&c,sizeof(c),1,fptr)==1)
        {
                display(d); system("clear"); borders();
		if(strcmp(d.mb,c.mb)==0)
                {

			system("clear"); borders();
			gotoxy(10,4);printf("Symbol 1: Party A");
			gotoxy(10,5); printf("!!!!!!!!!!!");
        		gotoxy(10,6); printf("!!");
        		gotoxy(10,7); printf("!!!!!!!!!!!");
        		gotoxy(10,8); printf("!!");
        		gotoxy(10,9); printf("!!!!!!!!!!!");
        		gotoxy(10,10);printf("!!");
        		gotoxy(10,11);printf("!!!!!!!!!!!");

			gotoxy(40,4);printf("Symbol 2: Party B");
			gotoxy(40,5); printf("@@@@@@@@@@@@@");
        		gotoxy(40,6); printf("@@@@@@ @@@@@@");
        		gotoxy(40,7); printf("@@@@@   @@@@@");
        		gotoxy(40,8); printf("@@@@     @@@@");
        		gotoxy(40,9); printf("@@@       @@@");
        		gotoxy(40,10);printf("@@         @@");
        		gotoxy(40,11);printf("@@@@@@@@@@@@@");
			
			gotoxy(10,14);printf("Symbol 3: Party C");
			gotoxy(10,15);printf("*************");
        		gotoxy(10,16);printf(" *    *    *");
        		gotoxy(10,17);printf("  *   *   *");
        		gotoxy(10,18);printf("   *  *  *");
        		gotoxy(10,19);printf("    * * *");
        		gotoxy(10,20);printf("     ***");
        		gotoxy(10,21);printf("      *");
		
			gotoxy(40,14);printf("Symbol 4: Others");
			gotoxy(40,15);printf("~~~~~~~~~~~~~~~~~");
        		gotoxy(40,16);printf("~  ~~~     ~~~  ~");
        		gotoxy(40,17);printf("~               ~");
        		gotoxy(40,18);printf("~      ~~       ~");
        		gotoxy(40,19);printf("~               ~");
        		gotoxy(40,20);printf("~   `````````   ~");
        		gotoxy(40,21);printf("~~~~~~~~~~~~~~~~~");
			scanf(" %c",&a);

			system("clear"); borders();
			gotoxy(20,5);printf("Enter symbol: ");
			scanf("%d",&c.symbol);
			fseek(fptr,-sizeof(c),SEEK_CUR);
                        fwrite(&c,sizeof(c),1,fptr);
		}
	}
	fclose(fptr);
	system("clear"); borders();
}
void updocuments()//for uploading documents
{
	candidate c,d;
	char a; int ch1; char ch2;
	d = search();
	display(d);
	FILE *fptr;
	fptr = fopen("program.dat","rb+");
		while(fread(&c,sizeof(c),1,fptr)==1)
		{
			if(strcmp(d.mb,c.mb)==0)
			{
				
				do
				{
					system("clear"); borders();
					gotoxy(20,5);printf("Enter document to upload: ");
					gotoxy(20,6);printf("1)Character Certificate");
					gotoxy(20,7);printf("2)Court Documents");
					gotoxy(20,8);printf("3)FIR Report");
					gotoxy(20,9);printf("4)Medical Report");
					gotoxy(20,10);printf("Press 0 to exit");
					gotoxy(47,5);scanf("%d",&ch1);
					switch(ch1)
					{
						case 1: system("clear"); borders(); //character certificate
							gotoxy(10,5);printf("Uploading character certificate...");
							gotoxy(10,7);printf("Line 1: ");
							scanf(" %[^\n]s",c.l.ch_certificate[0]);
							gotoxy(10,8);printf("Line 2: ");
                               				scanf(" %[^\n]s",c.l.ch_certificate[1]);
							gotoxy(10,9);printf("Line 3: ");
                                			scanf(" %[^\n]s",c.l.ch_certificate[2]);
							gotoxy(10,10);printf("Line 4: ");
                                			printf("Signed by the District Police.");
							strcpy(c.l.ch_certificate[3],"Signed by the District Police.");
							scanf(" %c",&a);
							fseek(fptr,-sizeof(c),SEEK_CUR);
							fwrite(&c,sizeof(c),1,fptr);
							break;
						case 2: system("clear"); borders(); //Court report
                                                        gotoxy(10,5);printf("Uploading court report...");
                                                        gotoxy(10,7);printf("Nature of case:  ");
                                                        scanf(" %[^\n]s",c.l.court_case[0]);
                                                        gotoxy(10,8);printf("Fine paid: ");
                                                        scanf(" %[^\n]s",c.l.court_case[1]);
                                                        gotoxy(10,9);printf("Jailtime: ");
                                                        scanf(" %[^\n]s",c.l.court_case[2]);
                                                        gotoxy(10,10);printf("Signed by the High Court.");
                                                        strcpy(c.l.ch_certificate[3],"Signed by the High Court.");
							scanf(" %c",&a);
                                                        fseek(fptr,-sizeof(c),SEEK_CUR);
                                                        fwrite(&c,sizeof(c),1,fptr);
							break;
						case 3: system("clear"); borders();  //FIR
                                                        gotoxy(10,5);printf("Uploading FIR...");
                                                        gotoxy(10,7);printf("Conduct of Candidate:  ");
                                                        scanf(" %[^\n]s",c.l.FIR[0]);
                                                        gotoxy(10,8);printf("Suspected Felonies: ");
                                                        scanf(" %[^\n]s",c.l.FIR[1]);
                                                        gotoxy(10,9);printf("Signed by the State Police.");
                                                        strcpy(c.l.FIR[2],"Signed by the State Police.");
                                                        scanf(" %c",&a);
                                                        fseek(fptr,-sizeof(c),SEEK_CUR);
                                                        fwrite(&c,sizeof(c),1,fptr);
                                                        break;
						case 4: system("clear"); borders(); //Medical Report
                                                        gotoxy(10,5);printf("Uploading Medical Report...");
                                                        gotoxy(10,7);printf("Name of Doctor: ");
                                                        scanf(" %[^\n]s",c.l.prescriptions[0]);
                                                        gotoxy(10,8);printf("Any existing mental conditions? : ");
                                                        scanf(" %[^\n]s",c.l.prescriptions[1]);
                              				gotoxy(10,9);
                                                    	printf("Severity of condition: ");
                                                        scanf("%[^\n]s",c.l.prescriptions[2]);
							gotoxy(10,10);
							printf("Comment: ");
							scanf(" %[^\n]s",
							c.l.prescriptions[3]);
                                                        scanf(" %c",&a);
                                                        fseek(fptr,-sizeof(c),SEEK_CUR);
                                                        fwrite(&c,sizeof(c),1,fptr);
                                                        break;
					}
				system("clear"); borders();
				gotoxy(20,5);printf("Enter more details(y/n)? ");
				scanf(" %c",&ch2);
				}while(ch2=='y');
			}
			system("clear"); borders();
		}
	fclose(fptr);
}
void upundertaking()//for uploading the undertaking
{
	candidate c,d;
	char a;
	d = search();
	FILE *fptr;
	fptr = fopen("program.dat","rb+");
	while(fread(&c,sizeof(c),1,fptr)==1)
	{

        	if((strcmp(d.mb,c.mb)==0)&&(strcmp(c.l.prescriptions[3],"Fit to contest")==0)&&(strcmp(c.l.FIR[1],"None")==0)&&(strcmp(c
        	.l.court_case[2],"More than 2 years")!=0)&&c.age>=25)
		{
			system("clear"); borders();
			display(d); system("clear"); borders();
			gotoxy(10,5);printf("Line 1:");
			scanf(" %[^\n]s",c.l.undertaking[0]);
			gotoxy(10,6);printf("Line 2:");
                        scanf(" %[^\n]s",c.l.undertaking[1]);
			gotoxy(10,7);printf("Line 3:");
                        scanf(" %[^\n]s",c.l.undertaking[2]);
			scanf(" %c",&a);
			fseek(fptr,-sizeof(c),SEEK_CUR);
			fwrite(&c,sizeof(c),1,fptr);
		}
		else if((strcmp(d.mb,c.mb)!=0)||(strcmp(c.l.prescriptions[3],"Fit to contest")!=0)||(strcmp(c.l.FIR[1],"None")!=0)||(strcmp(c.l.court_case[2],"More than 2 years")==0)||c.age>=25)
		{
			system("clear"); borders();
			gotoxy(20,5);printf("Unfit to contest elections");
			scanf(" %c",&a);
			system("clear"); borders();
		}
	}
	fclose(fptr);
}	
void delete()//for deleting a record
{
	candidate c,d; char a;
	d = search();
	display(d); system("clear"); borders();
	gotoxy(20,5);printf("Do you really want to delete the record(y/n)? ");
	scanf(" %c",&a);
	if(a=='y')
	{
	FILE *fptr,*temp;
	fptr = fopen("program.dat","rb");
	temp = fopen("temp.dat","wb");
	while(fread(&c,sizeof(c),1,fptr)==1)
	{
		if(strcmp(d.mb,c.mb)!=0)
			fwrite(&c,sizeof(c),1,temp);
	}
	fclose(fptr);
	fclose(temp);
	remove("program.dat");
	rename("temp.dat","program.dat");
	system("clear"); borders();
	gotoxy(20,5);printf("Record deleted successfully.");
	scanf(" %c",&a);
	}
}
void main()
{
	system("clear");
	candidate c;
	password();
	int choice;
	do
	{
		borders();
		gotoxy(62,2);
		printf("MENU"); gotoxy(60,3);		//Menu
		printf("________");gotoxy(40,6);
		printf("1) Enter new candidate");gotoxy(40,7);
		printf("2) Search candidate");gotoxy(40,8);
		printf("3) Upload party symbol");gotoxy(40,9);
	    	printf("4) Upload candidate documents");gotoxy(40,10);
		printf("5) Upload undertaking");gotoxy(40,11);
    		printf("6) Update candidate information");gotoxy(40,12);
		printf("7) Delete candidate");gotoxy(40,14);
    		printf("Press any one option or press 0 to exit...");
		scanf("%d",&choice);
		switch(choice)	//Choices in the Menu
		{
			case 1: writefile();
				break;
			case 2: c = search();
				display(c);
				break;
			case 3: upsymbol();
				break;
			case 4: updocuments();
				break;
			case 5: upundertaking();
				break;
			case 6: update();
				break;
			case 7: delete();
				system("clear"); 
				borders();
				break;
			case 8: readfile();
				break;

		}
		system("clear");
	}while(choice!=0);	
}

