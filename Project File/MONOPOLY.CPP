#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int n; //number of players
int owner; //owner of property
int ComCard=0,ChanceCard=0; //card indexes of community chest and chance cards
int cards[13]; //Array shuffled with random order of 13 cards before the game starts
int bankrupts=0; //Number of Bankrupt Players.

struct player
{	
	int num;
	float cash;
	char name[30];
	int position;
	int id;
	int properties[40];
	float networth;
	int bankrupt;
}id[4];

struct Places
{
	int id;
	int cost;
	int bought;
};

Places place[40] = { {0,0,0},
	                 {1,60,0},
		{2,0,0},
		{3,60,0},
		{4,0,0},
		{5,200,0},
		{6,100,0},
		{7,0,0},
		{8,100,0},
		{9,120,0},
		{10,0,0},
		{11,140,0},
		{12,150,0},
		{13,140,0},
		{14,160,0},
		{15,200,0},
		{16,200,0},
		{17,0,0},
		{18,180,0},
		{19,200,0},
		{20,0,0},
		{21,220,0},
		{22,0,0},
		{23,220,0},
		{24,240,0},
		{25,200,0},
		{26,260,0},
		{27,260,0},
		{28,150,0},
		{29,280,0},
		{30,0,0},
		{31,300,0},
		{32,300,0},
		{33,0,0},
		{34,320,0},
		{35,200,0},
		{36,0,0},
		{37,350,0},
		{38,0,0},
		{39,400,0}
	            };

void placeName(int a)
{
	switch(a)
	{
		case 0: cout<<"GO";
		break;

		case 1: cout<<"OLD KENT ROAD";
		break;

		case 2: cout<<"COMMUNITY CHEST";
		break;

		case 3: cout<<"WHITECHAPEL ROAD";	
		break;

		case 4: cout<<"INCOME TAX";
		break;

		case 5: cout<<"KINGS CROSS STATION";
		break;

		case 6: cout<<"THE ANGEL ISLINGTON";
		break;

		case 7: cout<<"CHANCE";
		break;

		case 8: cout<<"EUSTON ROAD";
		break;

		case 9: cout<<"PENTONVILLE ROAD";
		break;

		case 10: cout<<"JAIL";
		break;

		case 11: cout<<"PALL MALL";
		break;

		case 12: cout<<"ELECTRIC COMPANY";
		break;

		case 13: cout<<"WHITEHALL";
		break;

		case 14: cout<<"NORTHUMRL'D AVENUE";
		break;

		case 15: cout<<"MARYLEBONE STATION";
		break;

		case 16: cout<<"BOW STREET";
		break;

		case 17: cout<<"COMMUNITY CHEST";
		break;

		case 18: cout<<"MARLBOROUGH STREET";
		break;

		case 19: cout<<"VINE STREET";
		break;

		case 20: cout<<"FREE PARKING";
		break;

		case 21: cout<<"STRAND";
		break;

		case 22: cout<<"CHANCE";
		break;

		case 23: cout<<"FLEET STREET";
		break;

		case 24: cout<<"TRAFALGAR SQUARE";
		break;

		case 25: cout<<"FENCHURCH ST. STATION";
		break;

		case 26: cout<<"LEICESTER SQUARE";
		break;

		case 27: cout<<"CONVENTRY STREET";
		break;

		case 28: cout<<"WATER WORKS";
		break;

		case 29: cout<<"PICCADILLY";
		break;

		case 30: cout<<"GO TO JAIL";
		break;

		case 31: cout<<"REGENT STREET";
		break;

		case 32: cout<<"OXFORD STREET";
		break;

		case 33: cout<<"COMMUNITY CHEST";
		break;

		case 34: cout<<"BOND STREET";
		break;

		case 35: cout<<"LIVERPOOL ST. STATION";
		break;

		case 36: cout<<"CHANCE";
		break;

		case 37: cout<<"PARK LANE";
		break;

		case 38: cout<<"SUPER TAX";
		break;

		case 39: cout<<"MAYFAIR";
		break;

	    }
}

void CommunityChest(int crp);
void Chance(int crp);
void Station(int crp);
void Utility(int crp);
void Place(int crp);
void Tax(int crp);
void Jail(int crp);
void RollDice(int &dice);
void Bankrupt(int crp);
void EndGame();

void Bankrupt(int crp)
{
	for (int pos=0;pos<40;pos++)
	if (id[crp].properties[pos]==1)
	{
		id[crp].properties[pos]=0; //Removing property from user
		place[pos].bought=0; //Place is now available for buying again
	}
	id[crp].cash=0;
	id[crp].networth=0;
	bankrupts++;
}

void EndGame()
{
	int p;
	clrscr();
	cout<<"The Game has Ended!";
	cout<<"\n\nResult\n";
	cout<<"--------------";
	int first=0,second,third,fourth;
	for (p=0;p<n;p++) //loop to find player with most networth
	if (id[p].networth>first&&id[p].bankrupt!=1)
	first=id[p].networth;
	for (p=0;p<n;p++)
	if(id[p].networth!=first&&id[p].networth>second&&id[p].bankrupt!=1)
	second=id[p].networth;
	for (p=0;p<n;p++)
	if(id[p].networth!=first&&id[p].networth!=second && id[p].networth>third&&id[p].bankrupt!=1)
	third=id[p].networth;
	for (p=0;p<n;p++)
	if (id[p].networth!=first && id[p].networth != second && id[p].networth != third && id[p].bankrupt!=1)
	fourth=id[p].networth;
	for (p=0;p<n;p++)
	{
		if (id[p].networth==first)
		cout<<"\nFirst: "<<id[p].name<<"(Networth: $"<<id[p].networth<<")";
		if (id[p].networth==second)
		cout<<"\nSecond: "<<id[p].name<<"(Networth: $"<<id[p].networth<<")";
		if (id[p].networth==third)
		cout<<"\nThird: "<<id[p].name<<"(Networth: $"<<id[p].networth<<")";
		if (id[p].networth==fourth)
		cout<<"\nFourth: "<<id[p].name<<"(Networth: $"<<id[p].networth<<")";
		if (id[p].bankrupt==1)
		cout<<"\nBankrupt: "<<id[p].name<<"(Networth: $"<<id[p].networth<<")";
	}
getch();
exit(0);
}

void findType(int crp) //crp for getting Current Player ID and function to find what kind of place it is, then goes to the respective functions.
{
	int &pos=id[crp].position; //storing position of current player in reference variable
	if (pos==0)
	{
		cout<<"\nCollected $200";
		id[crp].cash+=200;
		id[crp].networth+=200;
		cout<<"\nYou now have $"<<id[crp].cash;
	}
	else if (pos==2||pos==17||pos==33)
	CommunityChest(crp);
	else if (pos==7||pos==22||pos==36)
	Chance(crp);
	else if (pos==5||pos==15||pos==25||pos==35)
	Station(crp);
	else if (pos==12||pos==28)
	Utility(crp);
	else if (pos==10)
	cout<<"\nJust Visiting!";
	else if (pos==20); //position 20 is FREE PARKING which is practically nothing.
	else if (pos==30)
	{
		id[crp].position=10;
		Jail(crp);
	}
	else if (pos==4||pos==38)
	Tax(crp);
	else
	Place(crp);
}

void CommunityChest(int crp)
{
	int &pos=id[crp].position;
	switch(cards[ComCard])
	{
		case 0:    cout<<"Advance to GO ";
			id[crp].position=0;
			id[crp].cash+=200;
			id[crp].networth+=200;
			cout<<"\n\nYou now have $"<<id[crp].cash;
			break;

		case 1:     cout<<"Go to Jail";
			pos=10;
			Jail(crp);
			break;

		case 2:     cout<<"Doctor's fee. Pay $50";
			id[crp].cash-=50;
			id[crp].networth-=50;
			cout<<"\n\nYou now have $"<<id[crp].cash;
			break;

		case 3:    cout<<"Bank error in your favour. Collect $200";
			id[crp].cash+=200;
			id[crp].networth+=200;
			cout<<"\n\nYou now have $"<<id[crp].cash;
			break;

		case 4: cout<<"Income Tax Refund. Collect $20";
		              id[crp].cash+=20;
		              id[crp].networth+=20;
		              cout<<"\n\nYou now have $"<<id[crp].cash;
		              break;

		case 5: cout<<"You have won second prize in a beauty contest.Collect $10";
		              id[crp].cash+=10;
		              id[crp].networth+=10;
		              cout<<"\n\nYou now have $"<<id[crp].cash;
		              break;

		case 6: cout<<"From sale of stock you collect $50";
		              id[crp].cash+=50;
		              id[crp].networth+=50;
		              cout<<"\n\nYou now have $"<<id[crp].cash;
		               break;

		case 7: cout<<"Go back to Old Kent Road\n";
		              pos=1;
		              Place(crp);
		              break;

		case 8:cout<<"Pay your Insurance Premium $50";
		             id[crp].cash-=50;
		             id[crp].networth-=50;
		             cout<<"\n\nYou now have $"<<id[crp].cash;
		             break;

		case 9:cout<<"It's your birthday. Collect $10 from each player";
			     for(int i=0;i<n;++i)
			    {
				if (i!=crp) //player cannot collect Money from himself/herself
				{
					id[i].cash-=10;
					id[i].networth-=10;
					id[crp].cash+=10;
					id[crp].networth+=10;
				}
			   }
			  cout<<"\n\nYou now have $"<<id[crp].cash;
			  break;

		case 10:cout<<"Pay Hospital $100";
		               id[crp].cash-=100;
		               id[crp].networth-=100;
		               cout<<"\n\nYou now have $"<<id[crp].cash;
		                break;

		case 11:cout<<"You inherit $100";
		               id[crp].cash+=100;
		                id[crp].networth+=100;
		               cout<<"\n\nYou now have $"<<id[crp].cash;
		               break;

		case 12: cout<<"Annuity matures. Collect $100";
		                id[crp].cash+=100;
		                id[crp].networth+=100;
		               cout<<"\n\nYou now have $"<<id[crp].cash;
		               break;
	}
	if (ComCard==12)
	ComCard=0;
	else	
	ComCard++;
}

void Chance(int crp)
{
	int &pos=id[crp].position;
	switch(cards[ChanceCard])
	{
		case 0:cout<<"Bank pays you dividend of $50";
		             id[crp].cash+=50;
		             id[crp].networth+=50;
		            cout<<"\nYou now have $"<<id[crp].cash;
		            break;

		case 1:cout<<"Advance to Mayfair";
		             pos=39;
		            Place(crp);
		            break;

		case 2:cout<<"Drunk in Charge fine $20";
		             id[crp].cash-=20;
		             id[crp].networth-=20;
		             cout<<"\nYou now have $"<<id[crp].cash;
		             break;

		case 3:cout<<"Speeding fine $15";
		             id[crp].cash-=15;
		             id[crp].networth-=15;
		             cout<<"\nYou now have $"<<id[crp].cash;
		             break;

		case 4:cout<<"Advance to Trafalgar Square";
		              if (pos<24)
		             {
			pos=24;
			Place(crp);
		             }
		             else
		             {
			pos=24;
			cout<<"\n\nYou crossed GO";
			cout<<"\nCollected $200";
			id[crp].cash+=200;
			id[crp].networth+=200;
		            }
		            break;

		case 5:cout<<"Go back three spaces";
		             pos-=3;
		             Place(crp);
		             break;

		case 6:cout<<"Take a trip to Marylebone Station";
		             if (pos<15)
		             {
			pos=15;
			Station(crp);
		             }
		            else
		            {
			pos=15;
			cout<<"\n\nYou crossed GO";
			cout<<"\nCollected $200";
			id[crp].cash+=200;
			id[crp].networth+=200;
		            }	
		            break;

		case 7:cout<<"You are assessed for street repairs: Pay $25 for each property";
		             int totalproperties=0;
		            for (int i=0;i<40;i++)
                                                {
		                 if (id[crp].properties[i]==1) //1 means the Player has bought the property
		                totalproperties++;
                                               }
		           id[crp].cash-=(25*totalproperties);
		           id[crp].networth-=(25*totalproperties);
			   cout<<"\nYouhave"<<totalproperties<<"properties";
			   cout<<"\nPaid $"<<(totalproperties*25);
			   cout<<"\nYou now have $"<<id[crp].cash;
		           break;

		case 8:cout<<"Pay school fees of $150";
		             id[crp].cash-=150;
		             id[crp].networth-=150;
		             cout<<"\nYou now have $"<<id[crp].cash;
		             break;

		case 9: cout<<"Go to Jail!";
		              id[crp].position=10;
		             Jail(crp);
		             break;

		case 10:cout<<"Advance to GO";
		               id[crp].cash+=200;
		               id[crp].networth+=200;
		               cout<<"\n\nYou now have $"<<id[crp].cash;
		               break;

		case 11:cout<<"Your building loan matures. Receive $150";
		                id[crp].cash+=150;
		                id[crp].networth+=150;
		                cout<<"\nYou now have $"<<id[crp].cash;
		                break;

		case 12:cout<<"You have won a crossword competition.Collect $100";
		               id[crp].cash+=100;
		               id[crp].networth+=100;
		              cout<<"\nYou now have $"<<id[crp].cash;
		              break;

	}
	if (ChanceCard==12)
	  ChanceCard=0;
	else
                   ChanceCard++;
}

void Station(int crp)
{
	int &pos=id[crp].position;
	if (place[pos].bought==0)
	{
		int ch;
		cout<<"\n\nWould you like to";
		cout<<"\n1.Buy this Station (Cost: $"<<place[pos].cost<<")";
		cout<<"\n2.Do Nothing";
		cout<<"\n\nYou have $"<<id[crp].cash;
		cout<<"\n\nEnter your Choice: ";
		while (!(cin>>ch))
		{
			clrscr();
			cout << "Incorrect input\n\n";
			cout<<"\n\nWould you like to";
			cout<<"\n1.Buy this Station (Cost: $"<<place[pos].cost<<")";
			cout<<"\n2.Do Nothing";
			cout<<"\n\nYou have $"<<id[crp].cash;
			cout<<"\n\nEnter your Choice: ";
			cin.clear();
			cin.ignore();
	               }
		switch(ch)
		{
			case 1:cout<<"\nYou bought ";
			             placeName(pos);
			             id[crp].cash-=place[pos].cost; //reducing player cash after buying property
			             id[crp].networth+=place[pos].cost;
			            cout<<"\nYou now have $"<<id[crp].cash;
			            place[pos].bought=1;
			            id[crp].properties[pos]=1; //player bought the property
			            break;

			case 2: break;

			default: break;
		}
	}
	else
	{
		for (int p=0;p<4;p++) //loop to find the player who bought the current property
		if (id[p].properties[pos]==1) //Checking if player bought the property by counter 1
		   owner=p;
		if (owner!=crp)
		{
		    cout<<"\n\nThe owner is "<<id[owner].name;
		    cout<<"\nPaid Rent of $"<<50<<" to " <<id[owner].name;
		     id[owner].cash+=50;
		     id[owner].networth+=50;
		     id[crp].cash-=50;
		     id[crp].networth-=50;
		     cout<<"\n\nYou now have $"<<id[crp].cash;
		}
	else
		cout<<"You have already bought this station";
	}
}

void Utility(int crp)
{
	int &pos=id[crp].position;
	if (place[pos].bought==0)
	{
		int ch;	
		cout<<"\n\nWould you like to";
		cout<<"\n1.Buy this Utility (Cost: $"<<place[pos].cost<<")";
		cout<<"\n2.Do Nothing";
		cout<<"\n\nYou have $"<<id[crp].cash;
		cout<<"\n\nEnter your Choice: ";
		while (!(cin>>ch))
		{
		      clrscr();
		      cout << "Incorrect input\n\n";
		      cout<<"\n\nWould you like to";
		      cout<<"\n1.Buy this Utility (Cost: $"<<place[pos].cost<<")";
		      cout<<"\n2.Do Nothing";
		      cout<<"\n\nYou have $"<<id[crp].cash;
		      cout<<"\n\nEnter your Choice: ";
		      cin.clear();
		      cin.ignore();
		}
		switch(ch)
		{
			case 1:cout<<"\nYou bought ";
			             placeName(pos);
			             id[crp].cash-=place[pos].cost; //reducing player cash after buying property
			             id[crp].networth+=place[pos].cost;
			             cout<<"\nYou now have $"<<id[crp].cash;
			             place[pos].bought=1;
			             id[crp].properties[pos]=1; //player bought the property
			             break;	

			case 2: break;

			default:   break;
		}
	}
	else
	{
		for (int p=0;p<4;p++) //loop to find the player who bought the current property
		if (id[p].properties[pos]==1) //Checking if player bought property by the counter 1
		owner=p;
		if (owner!=crp)
		{
			cout<<"\n\nThe owner is "<<id[owner].name;
			cout<<"\nPaid Rent of $"<<50<<" to "<<id[owner].name;
			id[owner].cash+=70;
			id[owner].networth+=70;
			id[crp].cash-=70;
			id[crp].networth-=70;
			cout<<"\n\nYou now have $"<<id[crp].cash;
		}
		else
		     cout<<"You have already bought this station";
	}
}

void Place(int crp)
{
		int &pos=id[crp].position;
		if (place[pos].bought==0)
		{
			int ch;
			cout<<"\n\nWould you like to";
			cout<<"\n1.Buy this Property (Cost: $"<<place[pos].cost<<")";
			cout<<"\n2.Do Nothing";
			cout<<"\n\nYou have $"<<id[crp].cash;
			cout<<"\n\nEnter your Choice: ";
			while (!(cin>>ch))
			{
				clrscr();
				cout << "Incorrect input\n\n";
				cout<<"\n\nWould you like to";
				cout<<"\n1.Buy this Property (Cost:$"<<place[pos].cost<<")";
				cout<<"\n2.Do Nothing";
				cout<<"\n\nYou have $"<<id[crp].cash;
				cout<<"\n\nEnter your Choice: ";
				cin.clear();
				cin.ignore();
			}
			switch(ch)
			{
				case 1:cout<<"\nYou bought ";
				             placeName(pos);
				             id[crp].cash-=place[pos].cost; //reducing player cash after buying property
				             cout<<"\nYou now have $"<<id[crp].cash;
				             place[pos].bought=1;
				             id[crp].properties[pos]=1;
				             break;

				case 2: break;

				default:break;
			}
		}
		else
		{
			for (int p=0;p<4;p++) //loop to find the player who bought the current property
			if (id[p].properties[pos]==1)
			owner=p;
			if (owner!=crp)
			{
				cout<<"\n\nThe owner is "<<id[owner].name;
				cout<<"\nPaid Rent of $"<<place[pos].cost/2<<"to "<<id[owner].name;
				id[owner].cash+=place[pos].cost/2;
				id[owner].networth+=place[pos].cost/2;
				id[crp].cash-=place[pos].cost/2;
				id[crp].networth-=place[pos].cost/2;
				cout<<"\n\nYou now have $"<<id[crp].cash;
			}
			else
			    cout<<"You have already bought this property";
		}
}

void Tax(int crp)
{
	int ch;
	if (id[crp].position==4) //INCOME TAX
	{
		cout<<"\n1. Pay $200";
		cout<<"\n2. Pay 10% of your net worth($"<<id[crp].networth/10<<")";
		cout<<"\nEnter your choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:id[crp].cash-=200;
			             id[crp].networth-=200;
			             cout<<"\n\nYou now have $"<<id[crp].cash;	
			             break;

			case 2:cin.clear();
			             cin.ignore();
			             id[crp].cash-=(id[crp].networth/10);
			             id[crp].networth=id[crp].cash;
			             cout<<"\n\nYou now have $"<<id[crp].cash;
			             break;

			default:id[crp].cash-=200;
			            id[crp].networth-=200;
			            cout<<"\n\nYou now have $"<<id[crp].cash;
			            break;
		}
	}
	else //SUPER TAX
	{
		cout<<"\nPaid $100 as tax";
		id[crp].cash-=100;
		id[crp].networth-=100;
		cout<<"\nYou now have $"<<id[crp].cash;
	}
}

void Jail(int crp)
{
	cout<<"\nYou have to pay $50 to get out";
	cout<<"\nPaid $50";
	id[crp].cash-=50;
	id[crp].networth-=50;
	cout<<"\nYou now have $"<<id[crp].cash;
}

void Rolldice(int &dice) //calculates the total number when the dice is rolled
{
	dice=0;	
	unsigned int seedval;
	time_t t; //t is time type variable now
	seedval=(unsigned)time(&t); //time(&t) function will initialize time variable t with system time.
	srand(seedval); // seed the random no. generator
	dice=(rand()%6)+1; //Roll a dice with numbers 1-6
}

void main()
{
	clrscr();
	int i,j,dice,totaldice,a,p,ch,flag;
	names:
		cout<<"Enter number of players(max 4): ";
		cin>>n;
		if (n>0&&n<=4)
		{
			for(int i=0;i<n;++i)
			{
				cout<<"\nEnter the name of player "<<i+1<<": ";
				gets(id[i].name);
			}
		}
		else
		{
			clrscr();
			cout<<"Incorrect input. Please Enter a number from 1 to 4.\n\n";
			cin.clear();
			cin.ignore();
			goto names;
		}
		clrscr();
		for(p=0;p<n;++p) //initializing all players
		{		
			cout<<"\nName: "<<id[p].name;
			id[p].id=p;
			cout<<"\nPlayer ID: "<<id[p].id+1;
			id[p].cash=1500;
			id[p].networth=1500;
			cout<<"\nCash: "<<id[p].cash;
			cout<<"\n\n";
			id[p].position=0;
			id[p].bankrupt=0;
			for (int i=0;i<40;i++)
			id[p].properties[i]=0;
		}
		getch();
		int crp;
		p=0; //p=0 for while loop to work.
		for (i=0;i<13;i++) //shuffling of CARDS takes place here and put into cards[]
		{
			int card;
			flag=0;
			randomize();
			random(13);
			for (j=0;j<13;j++)
			{
				if (cards[j]==card) //checking if the random card has already been put into card[]
				flag=1;
			}
			if (flag!=1)
			cards[i]=card;
		}
		while(p<n) //Main While loop that switches the player turns
		{
			clrscr();
			while(id[p].bankrupt==1) //while loop to skip to next player who is not bankrupt.
			{
				if (p==n-1)
				p=0;
				else
				p++;
				if (bankrupts==n-1) //if number of bankrupt players is one less than total players (i.e. only one player remaining)
				{
					cout<<"ONLY ONE PLAYER REMAINING";
					cout<<"\n\nPress a key to End Game";
					getch();
					EndGame();
				}
			}
			crp=p;//storing value of p in crp (current player)
			cout<<"\n1.Roll Dice";
			cout<<"\n2.End Game\n";
			cout<<id[crp].name<<" enter your choice: ";
			while (!(cin>>ch))
			{
				cout << "Incorrect input. Please try again.\n";
				cin.clear();
				cin.ignore();
			}
			if (ch==1)
			{
				clrscr();
				for (int c=1,totaldice=0;c<=2;c++)
			{	
				Rolldice(dice);
				totaldice+=dice;
			}
				id[crp].position+=totaldice;
				cout<<id[crp].name<<" rolled "<<totaldice<<"!\n";
				if (id[crp].position>39) //since the monopoly board is a loop, we need to make the position IDs a loop.
				{
					id[crp].position-=40;
					if (id[crp].position!=0) //adds $200 if player crosses GO (not if he/she lands on GO itself - this is handled by the Go function.
					{
						cout<<"\nYou crossed GO!";
						id[crp].cash+=200;
						id[crp].networth+=200;
						cout<<"\nYou now have $ " <<id[crp].cash <<endl;
					}
				}
			cout<<"\nYou reached ";
			placeName(id[crp].position);
			cout<<endl;
			findType(crp);
			if (id[crp].cash<=0)
			{
				id[crp].bankrupt=1;
				cout<<"\n\nYou are bankrupt!\nYou have lost all of your proeprties!\n\nYou are now out of the game.";
				Bankrupt(crp);
			}
			if (id[crp].cash<0)
			{
				id[crp].bankrupt=1;
			}
			getch();
			if (p==n-1)
			p=0;
			else	
			p++;
	}
	else if (ch==2)
	{
		EndGame();
	}
      }
}