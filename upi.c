#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MINBAL 1000

typedef struct node
{
	char name[30];
	char VirtualAddress[6];
	char password[15];
	int balance;
	struct node *next;
}account;

account *start=NULL;

account *searchByVirtualAdd(char *VA)
{
	account* q=start;
	while(q!=NULL)
		if(strcmp(q->VirtualAddress,VA)==0)
			break;
		else q=q->next;	
			
	return q;
}

void newSignUp()
{
	srand((unsigned)time(NULL));
	int i;
	
	account *p=(account *)malloc(sizeof(account));
	printf("Enter name: ");
	scanf("%s",p->name);
	while(getchar()!='\n');
	printf("Enter a password: ");
	scanf("%s",p->password);
	
	reinitializeVirtualAddress:
		for(i=0;i<2;i++)
			p->VirtualAddress[i]=rand()%26+'A';
		for(i=2;i<5;i++)
			p->VirtualAddress[i]=rand()%10+'0';
		p->VirtualAddress[i]='\0';
		
		if(searchByVirtualAdd(p->VirtualAddress)!=NULL)
			goto reinitializeVirtualAddress;
	
	p->balance=0;
	
	printf("\n\n*******************************\n");
	printf("Account Successfully created!\n");
	printf("Your Virtual Address = %s\n",p->VirtualAddress);
	printf("Your balance = %d\n",p->balance);
	printf("*******************************\n");	
	
	printf("\n\nPress any key to continue.......\n");
	while(getchar()!='\n');
	getchar();
	
	if(start==NULL)
	{
		start = p;
		return;
	}
	
	account *q=start;
	while(q->next!=NULL)
		q=q->next;
		
	q=p;
	
	return;	
}

int withdraw(account *p,int savings)
{
	if(p->balance-savings<MINBAL)
	{
		printf("Minimum balance error\n\a\aWithdrawl terminated\n");
		return -1;
	}
	p->balance-=savings;
	return savings;
}

void deposit(account *p,int savings)
{
	p->balance+=savings;
}

void transfer(account *p)
{
	char VA[6];
	int savings;
	printf("Enter Virtual address of the reciever: ");
	scanf("%s",VA);
	account *q=searchByVirtualAdd(VA);
	if(q==NULL)
	{
		printf("Account does not exist\n\a");
		return;
	}
	printf("Enter amount to be transfered: ");
	scanf("%d",&savings);
	savings=withdraw(p,savings);
	if(savings==-1)
		return;
	deposit(q,savings);
}

void balance(account *p)
{
	printf("Balance = %d\n",p->balance);
}

void signIn()
{
	char VA[6],pass[15];
	int savings;
	int res;
	
	printf("Enter Virtual Adress: ");
	scanf("%s",VA);
	account *q=searchByVirtualAdd(VA);
	printf("Enter password: ");
	scanf("%s",pass);
	
	if(q==NULL)
	{
		printf("Account not found\n\a\a");
		return;
	}
	
	if(strcmp(pass,q->password)!=0)
	{
		printf("Wrong password\n\a");
		return;
	}
	
	printf("Welcome, %s\n",q->name);
	while(getchar()!='\n');
	printf("Press any key to continue......\n");
	getchar();
	
	while(1)
	{
		printf("1:Check balance\n2:Withdraw money\n3:Deposit money\n4:Send money\n5:Sign out\n");
		scanf("%d",&res);
		if(res==5)break;
		switch(res)
		{
			case 1: balance(q);
				break;
			case 2: printf("Enter amount to withdraw: ");
				scanf("%d",&savings);
				withdraw(q,savings);
				balance(q);
				while(getchar()!='\n');
				printf("Press any key to continue......\n");
				getchar();
				break;
			case 3: printf("Enter amount to deposit: ");
				scanf("%d",&savings);
				deposit(q,savings);
				balance(q);
				while(getchar()!='\n');
				printf("Press any key to continue......\n");
				getchar();
				break;
			case 4: transfer(q);		 
		}
	}	
}

void main()
{
	int res;
	
	printf("Welcome to UPI\n");
	while(1)
	{
		printf("1:New Account Sign Up\n2:Sign In\n3:Exit\n\n");
		printf("======> ");
		scanf("%d",&res);
		if(res==3)break;
		
		switch(res)
		{
			case 1: newSignUp();
				break;
			case 2: signIn();
				break;
		}
	}		
}
