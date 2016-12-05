#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MINBAL 1000

typedef struct inbox
{
	char box[6];
	int recieved;
}inbox;

typedef struct account
{
	char name[30];
	char VirtualAddress[6];
	char password[15];
	int balance;
	inbox msg[10];
	int msgCount;
	struct account *next;
}account;

account *start=NULL;

void clear()
{
	int i;
	
	for(i=0;i<50;i++)
		putchar('\n');
}

void pause()
{
	while(getchar()!='\n');
	printf("Press any key to continue......\n");
	getchar();
	clear();
}

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
	char pass1[15],pass2[15];
	
	printf("[NEW ACCOUNT SIGNUP]\n\n");
	
	account *p=(account *)malloc(sizeof(account));
	printf("Enter name: ");
	scanf("%s",p->name);
	while(getchar()!='\n');
	
	while(1)
	{
		printf("Enter a password: ");
		scanf("%s",pass1);
		printf("Enter the password again: ");
		scanf("%s",pass2);
		
		if(strcmp(pass1,pass2)==0)
		{
			strcpy(p->password,pass1);
			break;
		}
		printf("Passwords donot match!\n\n\a\a");
	}
	
	reinitializeVirtualAddress:
		for(i=0;i<2;i++)
			p->VirtualAddress[i]=rand()%26+'A';
		for(i=2;i<5;i++)
			p->VirtualAddress[i]=rand()%10+'0';
		p->VirtualAddress[i]='\0';
		
		if(searchByVirtualAdd(p->VirtualAddress)!=NULL)
			goto reinitializeVirtualAddress;
	
	p->balance=0;
	p->next=NULL;
	p->msgCount=0;
	
	printf("\n\n*******************************\n");
	printf("Account Successfully created! Please note down your PASSWORD and VIRTUAL ADDRESS\n");
	printf("Your Virtual Address = %s\n",p->VirtualAddress);
	printf("Your Password = %s\n",p->password);
	printf("Your Balance = %d\n",p->balance);
	printf("*******************************\n");	
	
	pause();
	
	if(start==NULL)
	{
		start = p;
		return;
	}
	
	account *q=start;
	while(q->next!=NULL)
		q=q->next;
		
	q->next=p;
	
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
	printf("{{{%s}}} {{{%s}}}\n",VA,q->name);getchar();
	if(q==NULL)
	{
		printf("Account does not exist\n\a");
		return;
	}
	printf("Enter amount to be transfered: ");
	scanf("%d",&savings);
	savings=withdraw(p,savings);
	
	if(savings==-1)
	{
		printf("Insufficient funds [Transfer terminated]\n\a");
		return;
	}
	if(q->msgCount>9)
	{
		printf("Receiver's account acception has expired\n\a");
		return;
	}
	
	deposit(q,savings);
	strcpy(q->msg[q->msgCount].box,VA);
	q->msgCount++;
	q->msg[q->msgCount].recieved=savings;
}

void balance(account *p)
{
	printf("Balance = %d\n",p->balance);
}

void Inbox(account *q)
{
	int i;
	char res;
	
	if(q->msgCount==0)
	{
		printf("No messages\n");
		return;
	}
	
	for(i=0;i<q->msgCount;i++);
		printf("\t[%d] %s sent INR%d to you\n",i+1,q->msg[i].box,q->msg[i].recieved);
	
	printf("Clear inbox (Y/N): ");
	scanf("%c",&res);
	if(res=='Y'||res=='y')
		q->msgCount=0;
}

void signIn()
{
	char VA[6],pass[15];
	int savings;
	int res;
	
	printf("Enter Virtual Adress: ");
	scanf("%s",VA);
	account *q=searchByVirtualAdd(VA);
	
	if(q==NULL)
	{
		printf("Account not found\n\a\a");
		clear();
		return;
	}
	
	printf("Enter password: ");
	scanf("%s",pass);
	
	if(strcmp(pass,q->password)!=0)
	{
		printf("Wrong password\n\a");
		clear();
		return;
	}
	
	printf("\n\n**********************************\n");
	printf("Welcome, %s\n",q->name);
	pause();
	
	while(1)
	{
		printf("1:Check balance\n2:Withdraw money\n3:Deposit money\n4:Send money\n5:Inbox(%d)\n6:Sign out\n",q->msgCount);
		printf("======> ");
		scanf("%d",&res);
		if(res==6){pause();break;}
		
		switch(res)
		{
			case 1: balance(q);
				break;
			case 2: printf("Enter amount to withdraw: ");
				scanf("%d",&savings);
				withdraw(q,savings);
				balance(q);
				break;
			case 3: printf("Enter amount to deposit: ");
				scanf("%d",&savings);
				deposit(q,savings);
				balance(q);
				break;
			case 4: transfer(q);
				break;
			case 5: Inbox(q);
				break;
			default: printf("Invalid response\n\a");			 
		}
		
		pause();
	}
}

void main()
{
	int res;
	
	while(1)
	{
		printf("[[WELCOME TO BANK OF DALMIA]]\n\n");
		
		printf("1:New Account Sign Up\n2:Sign In\n3:Exit\n\n");
		printf("======> ");
		scanf("%d",&res);
		if(res==3)break;
		
		clear();
		
		switch(res)
		{
			case 1: newSignUp();
				break;
			case 2: signIn();
				break;
		}
	}
	getchar();
}
