#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while(goal > clock());
}
void menu();
void main_menu();
void customer_menu();
void customer_login();
void customer_startup();
void employee_login();
void employee_startup();
void employee_menu();
void emty();
void make_fly();
void fly_det();
void seat_booking();
void availability();
void total_transaction();
void cancel();
void deta();
void transfile();


struct time
{
	int Hrs,Min;
};

struct bus
{
	int     bn;
	char    bc[100];
	char    seat[9][4][20];
	struct  time dt,at;
	char    to[50];
	char    from[50];
	float   fare;
	int     sr;
}b[100];

FILE *p,*q;
char        EmptySeat[]="Empty";
static int  n=1;
char        i=':';

#define MAX_CUSTOMERS 10
#define MAX_EMPLOYEES 10

struct Customer {
    char name[100];
    char phoneNumber[12];
    char password[20];
};

struct Employee {
    char name[100];
    char phoneNumber[12];
    char identificationNumber[10];
    char code[5];
};

int main(void)
{
    int a;
    printf("\n\n\n\t\t\t\t\t Loading");
    for(a = 1; a<=2; a++)
    {
        printf(".");
        delay(1000);
    }

    int choice;
    char c;
    def:
    system("COLOR 47");
    system("cls");
    printf("Menu-Driven with Bus Booking Ticketing System");
    printf("\nSubmitted by: Levy Kibet||\n\n");
    printf("\n                                + + + + + + + + + + WELCOME + + + + + + + + + + ");
	printf("\n                                +              ADRIELAS BUS                       +");
	printf("\n                                +              BOOKING TICKET SYSTEM          +  ");
	printf("\n                                +                                             +  ");
	printf("\n                                +                                             +  ");
	printf("\n                                +                                             +  ");
	printf("\n                                +                                             +  ");
	menu();
}
/* For the CRUD simulation guidelines, it will be: PRESS 1 -- CREATE, PRESS 3,4,6 -- READ, PRESS 2 -- UPDATE, PRESS 5 -- DELETE*/
void menu()
{
	int ch;
	printf("\n\t                              +                    MAIN MENU                    +");
	printf("\n\t                              +              PRESS 1 Customer                   +");
	printf("\n\t                              +              PRESS 2 Employee                   +");
	printf("\n\t                              +              PRESS 3 Exit                       +");
	printf("\n\n\t                                    Please enter your preferred operation:     ");
	fflush(stdin);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:customer_startup();break;
		case 2:employee_startup();break;
		case 3:
    printf("\n\nMenu-Driven with File Handling Bus Booking System");
    printf("\nSubmitted by: Levy Kibet");
			exit(0);
		default:
		    getch();
		    main_menu();
	}
}

void saveCustomers(struct Customer customers[], int numCustomers) {
    FILE *file = fopen("customers.txt", "w");
    if (file) {
    	int i;
        for (i = 0; i < numCustomers; i++) {
            fprintf(file, "%s %s %s\n", customers[i].name, customers[i].phoneNumber, customers[i].password);
        }
        fclose(file);
    }
}

void saveEmployees(struct Employee employees[], int numEmployees) {
    FILE *file = fopen("employees.txt", "w");
    if (file) {
    	int i;
        for (i = 0; i < numEmployees; i++) {
            fprintf(file, "%s %s %s %s\n", employees[i].name, employees[i].phoneNumber, employees[i].identificationNumber, employees[i].code);
        }
        fclose(file);
    }
}

void loadEmployees(struct Employee employees[], int *numEmployees) {
    FILE *file = fopen("employees.txt", "r");
    if (file) {
        while (*numEmployees < MAX_EMPLOYEES && fscanf(file, "%s %s %s %s", employees[*numEmployees].name, employees[*numEmployees].phoneNumber, employees[*numEmployees].identificationNumber, employees[*numEmployees].code) == 4) {
            (*numEmployees)++;
        }
        fclose(file);
    }
}

void loadCustomers(struct Customer customers[], int *numCustomers) {
    FILE *file = fopen("customers.txt", "r");
    if (file) {
        while (*numCustomers < MAX_CUSTOMERS && fscanf(file, "%s %s %s", customers[*numCustomers].name, customers[*numCustomers].phoneNumber, customers[*numCustomers].password) == 3) {
            (*numCustomers)++;
        }
        fclose(file);
    }
}

void customer_login()
{
int isValid = 0;
    struct Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;

    loadCustomers(customers, &numCustomers);

    int choice;
    int loggedInCustomer = -1;
    char phoneNumber[15];
    char password[20];
    char identificationNumber[10];
    char code[5];

    do {
        printf("\n1. Customer Registration\n2. Customer Login\n3. Quit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (numCustomers < MAX_CUSTOMERS) {
                    printf("Enter your name: ");
                    scanf("%s", customers[numCustomers].name);
                    printf("Enter your phone number: ");
                    fgets(phoneNumber, sizeof(phoneNumber), stdin);
                    phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // Remove the newline character
                    if ((strlen(phoneNumber) == 10) && (strncmp(phoneNumber, "01", 2) == 0 || strncmp(phoneNumber, "07", 2) == 0)) {
                    isValid = 1;
                    printf("Phone number is valid: %s\n", phoneNumber);
                    } else {
                    printf("Invalid phone number. Please enter a 10-digit number starting with '01' or '07'.\n");
                    }
                    scanf("%s", customers[numCustomers].phoneNumber);
                    printf("Create a password: ");
                    scanf("%s", customers[numCustomers].password);
                    numCustomers++;
                    printf("Customer registration successful.\n");
                    saveCustomers(customers, numCustomers);
                    customer_menu();
                } else {
                    printf("Customer registration is full.\n");
                }
                break;
            case 2:
                printf("Enter your phone number: ");
                scanf("%s", phoneNumber);
                printf("Enter your password: ");
                scanf("%s", password);
                int i;
                for (i = 0; i < numCustomers; i++) {
                    if (strcmp(customers[i].phoneNumber, phoneNumber) == 0 && strcmp(customers[i].password, password) == 0) {
                        loggedInCustomer = i;
                        break;
                    }
                }
                if (loggedInCustomer != -1) {
                    printf("Customer login successful. Welcome, %s!\n", customers[loggedInCustomer].name);
                    customer_menu();
                } else {
                    printf("Customer login failed. Please check your phone number and password.\n");
                }
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

void employee_login()
{
int isValid = 0;
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    loadEmployees(employees, &numEmployees);

    int choice;
    int loggedInEmployee = -1;
    char phoneNumber[15];
    char password[20];
    char identificationNumber[10];
    char code[5];

    do {
        printf("\n1. Employee Registration\n2. Employee Login\n3. Quit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (numEmployees < MAX_EMPLOYEES) {
                    printf("Enter your name: ");
                    scanf("%s", employees[numEmployees].name);
                    printf("Enter your phone number: ");
                    fgets(phoneNumber, sizeof(phoneNumber), stdin);
                    phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // Remove the newline character
                    if ((strlen(phoneNumber) == 10) && (strncmp(phoneNumber, "01", 2) == 0 || strncmp(phoneNumber, "07", 2) == 0)) {
                    isValid = 1;
                    printf("Phone number is valid: %s\n", phoneNumber);
                    } else {
                    printf("Invalid phone number. Please enter a 10-digit number starting with '01' or '07'.\n");
                    }
                    scanf("%s", employees[numEmployees].phoneNumber);
                    printf("Enter your identification number: ");
                    fgets(identificationNumber, sizeof(identificationNumber), stdin);
                    identificationNumber[strcspn(identificationNumber, "\n")] = '\0'; // Remove the newline character
                    if (strlen(identificationNumber) == 8) {
                    isValid = 1;
                    printf("Identification number is valid: %s\n", identificationNumber);
                    } else {
                    printf("Invalid identification number. Please enter 8 digits.\n");
                    }
                    scanf("%s", employees[numEmployees].identificationNumber);
                    printf("Enter the registration code (): ");
                    scanf("%s", employees[numEmployees].code);
                    if (strcmp(employees[numEmployees].code, "2004") == 0) {
                        numEmployees++;
                        printf("Employee registration successful.\n");
                        saveEmployees(employees, numEmployees);
                        employee_menu();
                    } else {
                        printf("Employee registration code is incorrect. Registration failed.\n");
                    }
                } else {
                    printf("Employee registration is full.\n");
                }
                break;
            case 2:
                printf("Enter your phone number: ");
                scanf("%s", phoneNumber);
                printf("Enter your identification number: ");
                scanf("%s", identificationNumber);
                for (i = 0; i < numEmployees; i++) {
                    if (strcmp(employees[i].phoneNumber, phoneNumber) == 0 && strcmp(employees[i].identificationNumber, identificationNumber) == 0) {
                        loggedInEmployee = i;
                        break;
                    }
                }
                if (loggedInEmployee != -1) {
                    printf("Employee login successful. Welcome, %s!\n", employees[loggedInEmployee].name);
                    employee_menu();
                } else {
                    printf("Employee login failed. Please check your phone number and identification number.\n");
                }
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;

}
void employee_startup()
{
	int ch;
	printf("\n\t                        +                    EMPLOYEE MENU                     +");
	printf("\n\t                        +              PRESS 1 Registration                    +");
	printf("\n\t                        +              PRESS 2 Login                           +");
	printf("\n\t                        +              PRESS 3 Exit                            +");
	printf("\n\n\t                              Please enter your preferred operation:          ");
	fflush(stdin);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:employee_login();break;
		case 2:employee_login();break;
		case 3:menu();break;
	}
}

void customer_startup()
{
    int ch;
	printf("\n\t                        +                    CUSTOMER MENU                     +");
	printf("\n\t                        +              PRESS 1 Registration                    +");
	printf("\n\t                        +              PRESS 2 Login                           +");
	printf("\n\t                        +              PRESS 3 Exit                            +");
	printf("\n\n\t                              Please enter your preferred operation:          ");
	fflush(stdin);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:customer_login();break;
		case 2:customer_login();break;
		case 3:menu();break;
	}
}

void employee_menu()
{
	int ch;
	printf("\n\t                             +                    MENU                        +");
	printf("\n\t                             +              PRESS 1 Make a Flight             +");
	printf("\n\t                             +              PRESS 2 Information               +");
	printf("\n\t                             +              PRESS 3 Exit                      +");
	printf("\n\n\t                              Please enter your preferred operation:         ");
	fflush(stdin);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:make_fly();break;
		case 2:total_transaction();break;
		case 3:menu();break;
	}
}

void customer_menu()
{
	int ch;
	printf("\n\t                        +                    MENU                     +");
	printf("\n\t                        +              PRESS 1 Reserve a Seat         +");
	printf("\n\t                        +              PRESS 2 Bus Details            +");
	printf("\n\t                        +              PRESS 3 Available Seat         +");
	printf("\n\t                        +              PRESS 4 Cancel a Reservation   +");
	printf("\n\t                        +              PRESS 5 Exit                   +");
	printf("\n\n\t                              Please enter your preferred operation: ");
	fflush(stdin);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:seat_booking();break;
		case 2:fly_in();break;
		case 3:availability();break;
		case 4:cancel();break;
		case 5:menu();break;
	}
}

void main_menu()
{
	int ch;
	printf("\n\t                        +                    MENU                     +");
	printf("\n\t                        +              PRESS 1 Make a Schedule        +");
	printf("\n\t                        +              PRESS 2 Reserve a Seat         +");
	printf("\n\t                        +              PRESS 3 Bus Details            +");
	printf("\n\t                        +              PRESS 4 Available Seat         +");
	printf("\n\t                        +              PRESS 5 Cancel a Reservation   +");
	printf("\n\t                        +              PRESS 6 Information            +");
	printf("\n\t                        +              PRESS 7 Exit                   +");
	printf("\n\n\t                              Please enter your preferred operation: ");
	fflush(stdin);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:make_fly();break;
		case 2:seat_booking();break;
		case 3:fly_in();break;
		case 4:availability();break;
		case 5:cancel();break;
		case 6:total_transaction();break;
		case 7:
    printf("\n\nMenu-Driven with File Handling Bus Booking System");
    printf("\nSubmitted by: Levy Kibet||");
			exit(0);
		default:
		    getch();
		    menu();
	}
}

void make_fly()
{
	char ch;
	do
	{
	    system("COLOR 90");
	    system("cls");
	    printf("\n\t+ + + Make a Schedule for your passengers + + +\n");
		printf("\n\tFlight Number:  %d",n);
        b[n].bn=n;

		buscode:
			printf("\n\n\tPlease enter the Bus Code:\t");
			fflush(stdin);
			scanf("%s",&b[n].bc);

		from:
			printf("\n\tComing from:\t");
			fflush(stdin);
			scanf("%s",&b[n].from);

        to:
		    printf("\n\tToward:\t");
		    fflush(stdin);
            gets(b[n].to);

        printf("\n\t!!!Please enter the time in hh:mm (24hrs) manner. Example: 06:30 to 10:45!!!");
		arrivaltime:
			printf("\n\n\tArrival time:\t");
			fflush(stdin);
			scanf("%d%c%d",&b[n].at.Hrs,&i,&b[n].at.Min);
			if(b[n].at.Hrs==0)
			{
				printf("\n\tError");
				goto arrivaltime;
			}
		    if((i!=':')||(b[n].at.Hrs>=24)||(b[n].at.Hrs<0)||(b[n].at.Min>=60)||(b[n].at.Min<0))
		    {
		    	printf("\n\tError.....Please enter the time in hh:mm (24hrs) manner");
                goto arrivaltime;
		    }

		departuretime:
		    printf("\n\tDeparture time:\t");
		    fflush(stdin);
		    scanf("%d%c%d",&b[n].dt.Hrs,&i,&b[n].dt.Min);
		    if(b[n].dt.Hrs==0)
			{
				printf("\n\tError");
				goto departuretime;
			}
		    if((i!=':')||(b[n].dt.Hrs>=24)||(b[n].dt.Hrs<0)||(b[n].dt.Min>=60)||(b[n].dt.Min<0))
		    {
		        printf("\n\tError.....Please enter the time in hh:mm (24hrs) manner");
                goto departuretime;
		    }

		if(b[n].at.Hrs>b[n].dt.Hrs)
		{
		    printf("\n\t\tDeparture time should be greater than Arrival time");
		    goto arrivaltime;
		}

        printf("\n\tFare:\t");
		fflush(stdin);
		scanf("%f",&b[n].fare);
		emty();
		b[n].sr=0;
	    printf("\n\tDo you want to use this operation again?:");
	    printf("\n\t\tPress [Y] if Yes, [N] if no:");
		fflush(stdin);
		scanf("%c",&ch);
		n++;
	}while(ch=='y'||ch=='Y');
	employee_menu();
}

void fly_in()
{
    system("COLOR 64");
    system("cls");
	int a;
	char ch;
    printf("\n\n\t\t+ + + BUS DETAILS + + + \n");
    for(a=1;a<n;a++)
    {
    	printf("\n\n\t\tBUS NUMBER:\t\t%d",b[a].bn);
        printf("\n\t\tBUS CODE:\t\t%s",b[a].bc);
        printf("\n\t\tCOMING FROM:\t\t%s",b[a].from);
        printf("\n\t\tTOWARD:\t\t\t%s",b[a].to);
        printf("\n\t\tARRIVAL TIME:\t\t%d%c%d",b[a].at.Hrs,i,b[a].at.Min);
        printf("\n\t\tDEPARTURE TIME:\t\t%d%c%d",b[a].dt.Hrs,i,b[a].dt.Min);
        printf("\n\t\tFARE:\t\t\t%.4f",b[a].fare);
        printf("\n\t\tSEATS RESERVED:\t\t%d",b[a].sr);
        printf("\n\t\tAVAILABLE SEATS:\t%d",20-(b[a].sr));
    }
    printf("\n\n\t\tDO YOU WANT TO STORE IT IN A FILE?(Y/N):\t");
    fflush(stdin);
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
   		deta();
    else
        customer_menu();
}

void seat_booking()
{
    system("COLOR 90");
    system("cls");
	char pn[50];
    int fbn;
    int fs;
    char ch;
    printf("\n\t\t\t+ + + Book a Seat + + + \t\t");
    printf("\n\n\tFlight Number:\t");
    fflush(stdin);
    scanf("%d",&fbn);
    if(fbn>=n)
	{
    	printf("\n\tError.. THERE'S NO BUS WITH THAT NUMBER...!");
    	seat_booking();
    }
    seat:
    	printf("\n\tPlease choose a seat number from [1-20]:\t");
    	fflush(stdin);
    	scanf("%d",&fs);
    	if(fs>20)
    	{
    		printf("\n\tError.. THERE'S ONLY 20 SEAT FOR THIS BUS NUMBER...!\t");
    		goto seat;
    	}
    	else if(strcmp(b[fbn].seat[fs/4][(fs%4)-1],"Empty")!=0)
    	{
    		printf("\n\tThis seat is already reserved!");
    		printf("\n\t\tDo u want to try again(y/n)\n");
    		fflush(stdin);
    		ch=getchar();
    		if(ch=='y'||ch=='Y')
            seat_booking();
            else
            menu();
    	}
    	else
    	{
    		name:
    		    printf("\n\tPlease enter your Name:");
    			fflush(stdin);
    			gets(pn);
    			strcpy(b[fbn].seat[fs/4][fs%4-1],pn);
    			printf("\n\tSeat Number %d is Reserved for %s at Bus Number %d",fs,pn,fbn);
    			printf("\n\tThank you for choosing ADRIELAS BUS!!!");
    			b[fbn].sr++;
    			printf("\n\n\tDo u want to continue with reservation(y/n)\t");
    			scanf("%c",&ch);
   				if(ch=='y'||ch=='Y')
   				seat_booking();
                else
                customer_menu();
    	}
}

void total_transaction()
{
    system("COLOR 64");
    system("cls");
	char ch;
	int i;
	long unsigned int fdt=0;
	long unsigned int fbt=0;
	printf("\n\n\t\t Total Transactions");
	for(i=1;i<n;i++)
	{
		fbt=b[i].sr*b[i].fare;
		printf("\n\n\tBus Number:\t%d",i);
		printf("\n\tTotal Seats Booked:\t%d",b[i].sr);
		printf("\n\tMoney Transacted for Bus Number %d:\t%lu\n",i,fbt);
		fdt+=fbt;
	}
	printf("\n\n\t\t\tTotal:\t%lu\n",fdt);
	printf("\n\n\t\tDo you want to store this information in a File?(Y/N):\t");
    fflush(stdin);
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
   		transfile();
    else
        employee_menu();
}

void emty()
{
    system("COLOR 30");
    system("cls");
	int i,j;
	for( i=0;i<9;i++)
	{
		for( j=0;j<4;j++)
		{
			strcpy(b[n].seat[i][j],EmptySeat);
		}
	}
}

void availability()
{
    system("COLOR 64");
    system("cls");
	int fbn;
	int sn=0,j,k;
	char ch;
	printf("\n\n\t\tPlease Enter the Bus Number:\t");
	fflush(stdin);
	scanf("%d",&fbn);
	if(fbn>=n||fbn<1)
	{
		printf("\n\t\tERROR!! THAT BUS DOESNT EXIST!!");
		availability();
	}
	else
	{
		printf("\nBUS CODE\t%s",b[fbn].bc);
	    printf("\nCOMING FROM:\t%s",b[fbn].from);
	    printf("\nTOWARD:\t\t%s",b[fbn].to);
	    printf("\nARRIVAL TIME:\t%d%c%d",b[fbn].at.Hrs,i,b[fbn].at.Min);
	    printf("\nDEPARTURE TIME\t%d%c%d",b[fbn].dt.Hrs,i,b[fbn].dt.Min);
	    printf("\nFARE:\t\t%f",b[fbn].fare);
	    printf("\nSEATS RESERVED:\t%d",b[fbn].sr);
	    printf("\nAVAILABLE SEATS:%d",20-b[fbn].sr);
	    for(j=0;j<5;j++)
	    {
	    	printf("\n");
	    	for(k=0;k<4;k++)
	    	{
	    		sn++;
	    		printf("%d .%s\t",sn,b[fbn].seat[j][k]);
	    	}
	    }
	}
	getch();
	printf("\n\n\t\tDO YOU WANT TO CHECK THE OTHER SCHEDULES(y/n)??");
	fflush(stdin);
	scanf("%c",&ch);
	if(ch=='y'||ch=='Y')
	availability();
	else
	customer_menu();
}

void cancel()
{
    system("COLOR 90");
    system("cls");
	int bnc;
	int stc;
	char ch;
	printf("\n\t\t+ + + Cancel a Reservation + + +");
	printf("\n\tFlight Number:");
	scanf("%d",&bnc);
	if(bnc>=n||bnc<1)
	{
    	printf("\n\t\tError.. THERE'S NO BUS WITH THAT NUMBER...!");
    	getch();
    	cancel();
    }
    cancel_seat:
    	printf("\n\tSeat Number:");
    	fflush(stdin);
    	scanf("%d",&stc);
    	if(stc>36)
    	{
    		printf("\n\t\t Error.. THERE'S ONLY 20 SEATS ON THAT BUS NUMBER...!");
    		goto cancel_seat;
    	}
    	else if(strcmp(b[bnc].seat[stc/4][(stc%4)-1],"Empty")==0)
    	{
            printf("\n\tTHIS SEAT IS AVAILABLE!\n\tCANCEL ONLY RESERVED SEATS!");
    		printf("\n\tDo u want to try again(y/n)");
    		fflush(stdin);
    		ch=getchar();
    		if(ch=='y'||ch=='Y')
            goto cancel_seat;
            else
            customer_menu();
    	}
    	else
    	{
    		strcpy(b[bnc].seat[stc/4][stc%4-1],"Empty");
    		b[bnc].sr--;
    		printf("\n\t\tSeat Number %d has been Cancelled Successfully at Bus Number %d",stc,bnc);
    		printf("\n\n\t Do you want to continue the cancellation(Y/N)\t");
    		fflush(stdin);
    		scanf("%c",&ch);
    		if(ch=='y'||ch=='Y')
    		cancel();
            else
            customer_menu();
    	}
}

void deta()
{
    system("COLOR 30");
    system("cls");
	int a;
	int sn=0,j,k;
	p=fopen("FlightFile.txt","w");
    fprintf(p,"\n\n\t\t + + + + + Bus Information + + + + + \n");
    fprintf(p,"\n\t\t---------------------------------");
    for(a=1;a<n;a++)
    {
    	fprintf(p,"\n\n\t\t	Bus NUMBER:\t\t\t%d",b[a].bn);
        fprintf(p,"\n\t\tBus CODE:\t\t%s",b[a].bc);
        fprintf(p,"\n\t\tCOMING FROM:\t\t\t%s",b[a].from);
        fprintf(p,"\n\t\tTOWARD:\t\t\t%s",b[a].to);
        fprintf(p,"\n\t\tARRIVAL TIME:\t\t%d%c%d",b[a].at.Hrs,i,b[a].at.Min);
        fprintf(p,"\n\t\tDEPARTURE TIME:\t\t%d%c%d",b[a].dt.Hrs,i,b[a].dt.Min);
        fprintf(p,"\n\t\tFARE:\t\t\t%.4f",b[a].fare);
        fprintf(p,"\n\t\tRESERVED SEATS:\t\t%d\n",b[a].sr);
        fprintf(p,"\n\t\t AVAILABLE SEATS:\t\t%d\n",36-(b[a].sr));
        for(j=0;j<5;j++)
	    {
	    	fprintf(p,"\n");
	    	for(k=0;k<4;k++)
	    	{
	    		sn++;
	    		fprintf(p,"%d .%s\t",sn,b[a].seat[j][k]);
	    	}
	    }
    }
    fclose(p);
    printf("\tDATA HAS BEEN SAVED IN BUS FILE.txt");
    getch();
    employee_menu();
}

void transfile()
{
    system("COLOR 70");
    system("cls");
	int i;
	long unsigned int fdt=0;
	long unsigned int fbt=0;
	q=fopen("flight details.txt","w");
	for(i=1;i<n;i++)
	{
		fbt=b[i].sr*b[i].fare;
		fprintf(q,"\n\tBus number:\t%d",i);
		fprintf(q,"\n\tTotal Seats booked:\t%d",b[i].sr);
		fprintf(q,"\n\tMoney transacted for Bus number%d:\t%lu\n",i,fbt);
		fdt+=fbt;
	}
	fprintf(q,"\n\n\t\t\tTotal:\t%lu\n",fdt);
	fclose(q);
    printf("\tDATA HAS BEEN SAVED IN BUS FILE.txt");
	getch();
	employee_menu();
}

