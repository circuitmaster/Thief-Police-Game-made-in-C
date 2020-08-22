#include <stdio.h> 
#include <time.h> //in order to generate random numbers with cpu clock
#include <stdlib.h> //in order to call srand function
#include <math.h> //in order to use absolute function

//This function prints array which is given by parameter. I use it to print game map.
void PrintArray(const char array[17][34]){
	//it prints game map matrix represented by 2-D array, row by row.  
	for (int i=0;i<17;++i)
	{
		printf("%s\n",array[i]);
	}
}
//game runs in StartGame function. It gets game map from parameter and process it to run game.
void StartGame(char mapp[17][34]){
	//I declared another array to store map since original map should not be changed. Player can play several times. 
	char map[17][34];
	//Loop sets all elements of map same as original map.
	for (int i=0;i<17;++i)
	{
		for (int j=0;j<34;++j)
		{
			map[i][j]=mapp[i][j];
		}
	}
	srand(time(NULL)); //Random seeding and some necessary variables. 
	int thiefPosX; //X axis position of police with origin of upper left corner of matrix. 
	int policePosX; //X axis position of police. 
	int thiefPosY; //Y axis position of thief.
	int policePosY; //Y axis position of police. 
	int distancePtoT; //absolute distance between police and thief.
	int distancePtoE; //absolute distance between police and exit. 
	int distanceTtoE; //absolute distance between thief and exit.
	char ignore; //ignore character for scanf function because when we enter char it gets twice input with enter char. 
	char move; //User movement input which is W,A,S,D.
	char gameMode; //User gamemode input which is E,H.
	//scans for game difficulty. 
	while(1){
		printf("Enter difficulty level. (Easy:E, Hard:H)\n");
		scanf("%c%c",&gameMode,&ignore);
		if (gameMode=='E'||gameMode=='H')
		{
			system("clear");
			break;
		}
		printf("Invalid choose. Enter again!\n");
	}
	//generating random poritions for thief and police than checking if the positions are suitable for conditions. 
	do
	{
		thiefPosX = rand() % 16;
		policePosX = rand() % 16;
		thiefPosY = rand() % 16;
		policePosY = rand() % 16;
		distancePtoT = abs(thiefPosY-policePosY) + abs(thiefPosX-policePosX);
		distancePtoE = abs(policePosY-7) + abs(policePosX-15);
		distanceTtoE = abs(thiefPosY-7) + abs(thiefPosX-15);
	}
	while(distanceTtoE<16 || distancePtoT<16 || distancePtoE<16 || map[thiefPosY+1][2*thiefPosX+1] == 'W' || map[policePosY+1][2*policePosX+1] == 'W');
	//After determining right positions i put characters. 
	map[thiefPosY+1][2*thiefPosX+1] = 'T';
	map[policePosY+1][2*policePosX+1] = 'P';

	PrintArray(map);
	//Moves player to valid positon set by player. If movement is invalid it asks again. 
	while(1){
		printf("Which way do you want to go? (Left:A, Right:D, Up:W, Down:S)\n");
		scanf("%c%c",&move,&ignore);
		//While checking X position it calculates 2*x+1 because in matris there is seperator character between every 2 neighbour x position and first x posiions are occupied with matrix borders. 
		//While checking Y position it calculates y+1 because first y positions are borders of matrix.   
		if ((move=='A'&&thiefPosX!=0&&map[thiefPosY+1][2*(thiefPosX-1)+1]!='W')||(move=='D'&&thiefPosX!=15&&map[thiefPosY+1][2*(thiefPosX+1)+1]!='W')||(move=='W'&&thiefPosY!=0&&map[thiefPosY][2*thiefPosX+1]!='W')||(move=='S'&&thiefPosY!=15&&map[thiefPosY+2][2*thiefPosX+1]!='W'))
		{
			//switch statements checks movement input. Correspondingly if there is not police at movement position player moves. If there is exit game ends with winning. 
			switch(move){
				case 'A':
					if (map[thiefPosY+1][2*(thiefPosX-1)+1]=='P')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						map[thiefPosY+1][2*(thiefPosX-1)+1]='T';
						thiefPosX--;
					}
					break;
				case 'D':
					if (map[thiefPosY+1][2*(thiefPosX+1)+1]=='P')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else if (map[thiefPosY+1][2*(thiefPosX+1)+1]=='E')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You won!\n");
						return;
					}else{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						map[thiefPosY+1][2*(thiefPosX+1)+1]='T';
						thiefPosX++;
					}
					break;
				case 'W':
					if (map[thiefPosY][2*thiefPosX+1]=='P')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else if (map[thiefPosY][2*thiefPosX+1]=='E')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You won!\n");
						return;
					}
					else{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						map[thiefPosY][2*thiefPosX+1]='T';
						thiefPosY--;
					}
					break;
				case 'S':
					if (map[thiefPosY+2][2*thiefPosX+1]=='P')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else if (map[thiefPosY+2][2*thiefPosX+1]=='E')
					{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						system("clear");
						PrintArray(map);
						printf("You won!\n");
						return;
					}
					else{
						map[thiefPosY+1][2*thiefPosX+1]='_';
						map[thiefPosY+2][2*thiefPosX+1]='T';
						thiefPosY++;
					}
					break;
				default:
					break;
			}
		}else{
			printf("Invalid move. Enter again!\n");
			continue;
		}

		//if difficulty is chosen as easy i generated random variable to represent 4 situations of movement of police until they satisfy conditions. 
		if (gameMode=='E')
		{
			while(1){
				int way;
				way = rand() % 4; //generation of random number between 0 and 3. When it is 0 police goes left, when 1 police goes right, when 2 police goes up and when 3 police goes down.
				//if thief stays at where police go, police catches the thief and game ends with failure.
				if ((way==0&&policePosX!=0&&map[policePosY+1][2*(policePosX-1)+1]!='W')||(way==1&&policePosX!=15&&map[policePosY+1][2*(policePosX+1)+1]!='W')||(way==2&&policePosY!=0&&map[policePosY][2*policePosX+1]!='W')||(way==3&&policePosY!=15&&map[policePosY+2][2*policePosX+1]!='W'))
				{
					//Check random way value in switch statement. Then moves correspondingly.
					switch(way){
						case 0:
							if (map[policePosY+1][2*(policePosX-1)+1]=='T')
							{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY+1][2*(policePosX-1)+1]='P';
								system("clear");
								PrintArray(map);
								printf("You lost!\n");
								return;
							}
							else{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY+1][2*(policePosX-1)+1]='P';
								policePosX--;
							}
							break;
						case 1:
							if (map[policePosY+1][2*(policePosX+1)+1]=='T')
							{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY+1][2*(policePosX+1)+1]='P';
								system("clear");
								PrintArray(map);
								printf("You lost!\n");
								return;
							}
							else{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY+1][2*(policePosX+1)+1]='P';
								policePosX++;
							}
							break;
						case 2:
							if (map[policePosY][2*policePosX+1]=='T')
							{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY][2*policePosX+1]='P';
								system("clear");
								PrintArray(map);
								printf("You lost!\n");
								return;
							}
							else{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY][2*policePosX+1]='P';
								policePosY--;
							}
							break;
						case 3:
							if (map[policePosY+2][2*policePosX+1]=='T')
							{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY+2][2*policePosX+1]='P';
								system("clear");
								PrintArray(map);
								printf("You lost!\n");
								return;
							}
							else{
								map[policePosY+1][2*policePosX+1]='_';
								map[policePosY+2][2*policePosX+1]='P';
								policePosY++;
							}
							break;
						default:
							break;
					}
					break;
				}
				else{
					continue;
				}
			}

		}
		/*if difficulty is chosen as hard it checks feasible squares to move and it sets indexes of movePos array which represents
		feasible squares to 1. After in for loop i choose random feasible square to move.  
		*/
		else if(gameMode=='H'){
			int movePos[4]={0};
			int moveWay=100;
			//if thief gets more close when police goes right and there is no wall at right, movepos0 is set to 1 which means right place is feasible.  
			if (abs((thiefPosX)-(policePosX+1))<abs(thiefPosX-(policePosX-1)))
			{
				if (map[policePosY+1][2*(policePosX+1)+1]=='W'&&map[policePosY+1][2*(policePosX-1)+1]!='W')
				{
					movePos[1]=2;
				}else if (map[policePosY+1][2*(policePosX+1)+1]!='W')
				{
					movePos[0]=1;
				}
			}else if(abs((thiefPosX)-(policePosX+1))>abs(thiefPosX-(policePosX-1))){
				//if thief gets more close when police goes left and there is no wall at left, movepos1 is set to 1 which means left place is feasible.
				if (map[policePosY+1][2*(policePosX+1)+1]!='W'&&map[policePosY+1][2*(policePosX-1)+1]=='W')
				{
					movePos[0]=2;
				}else if (map[policePosY+1][2*(policePosX-1)+1]!='W')
				{
					movePos[1]=1;
				}
			}else if (abs((thiefPosX)-(policePosX+1))==abs(thiefPosX-(policePosX-1)))
			{
				/*if distance do not change police moves either left or right, if right place is wall(and left place is empty) then left place is feasible
				and movepos2 becomes 2, if left place is wall(and right place is empty) then right place is feasible and movepos2 becomes 2. 
				If both of these spaces are empty both of them becomes feasible and both of movepos values become 1. I set values to 2 in other situations 
				since there should be difference between absoulute distance inequality comparison statements and equation comparisons. */   
				if (map[policePosY+1][2*(policePosX-1)+1]!='W'&&map[policePosY+1][2*(policePosX+1)+1]=='W')
				{
					movePos[1]=2;
				}else if (map[policePosY+1][2*(policePosX+1)+1]!='W'&&map[policePosY+1][2*(policePosX-1)+1]=='W')
				{
					movePos[0]=2;
				}else if (map[policePosY+1][2*(policePosX-1)+1]!='W'&&map[policePosY+1][2*(policePosX+1)+1]!='W')
				{
					movePos[0]=1;
					movePos[1]=1;
				}
			}
			/* I applied the same procedure to Y positions but if both x positions do not change distance and y decreases 
			distance and there is no wall, movepos of other X positions becomes 0 */
			if (abs(thiefPosY-(policePosY+1))<abs(thiefPosY-(policePosY-1)))
			{
				if (map[policePosY+2][2*(policePosX)+1]=='W'&&map[policePosY][2*(policePosX)+1]!='W'&&((movePos[0]==1&&movePos[1]==1)||movePos[0]==2||movePos[1]==2))
				{
					movePos[3]=1;
				}else if (map[policePosY+2][2*(policePosX)+1]!='W')
				{
					if ((movePos[0]==1&&movePos[1]==1)||movePos[0]==2||movePos[1]==2)
					{
						movePos[0]=0;
						movePos[1]=0;
					}
					movePos[2]=1;
				}
			}else if(abs(thiefPosY-(policePosY+1))>abs(thiefPosY-(policePosY-1))){
				if (map[policePosY][2*(policePosX)+1]=='W'&&map[policePosY+2][2*(policePosX)+1]=='W'&&((movePos[0]==1&&movePos[1]==1)||movePos[0]==2||movePos[1]==2))
				{
					movePos[2]=1;
				}else if (map[policePosY][2*(policePosX)+1]!='W')
				{
					if ((movePos[0]==1&&movePos[1]==1)||movePos[0]==2||movePos[1]==2)
					{
						movePos[0]=0;
						movePos[1]=0;
					}	
					movePos[3]=1;
				}	
			}else if (abs(thiefPosY-(policePosY+1))==abs(thiefPosY-(policePosY-1)))
			{
				if ((movePos[0]==0&&movePos[1]==0)||movePos[0]==2||movePos[1]==2)
				{
					if (map[policePosY][2*(policePosX)+1]!='W'&&map[policePosY+2][2*(policePosX)+1]=='W')
					{
						movePos[3]=1;
					}else if (map[policePosY][2*(policePosX)+1]=='W'&&map[policePosY+2][2*(policePosX)+1]!='W')
					{
						movePos[2]=1;
					}else if (map[policePosY][2*(policePosX)+1]!='W'&&map[policePosY+2][2*(policePosX)+1]!='W')
					{
						movePos[2]=1;
						movePos[3]=1;
					}
				}
			}
			//if there is no feasible positions, empty places become feasible. 
			if (movePos[0]==0&&movePos[1]==0&&movePos[2]==0&&movePos[3]==0)
			{
				if (map[policePosY+1][2*(policePosX+1)+1]!='W')
					movePos[0]=1;
				if (map[policePosY+1][2*(policePosX-1)+1]!='W')
					movePos[1]=1;
				if (map[policePosY+2][2*(policePosX)+1]!='W')
					movePos[2]=1;
				if (map[policePosY][2*(policePosX)+1]!='W')
					movePos[3]=1;
			}
			//Choose random feasible square if there is more than one feasible squares. There can be maximum 3 feasible squares. 
			for (int i=0;i<4;++i)
			{
				if (movePos[i]==1||movePos[i]==2)
				{
					moveWay=i;
					for (int j=0;j<4;++j)
					{
						int random=rand()%2;
						if (i!=j&&(movePos[j]==1||movePos[j]==2))
						{
							moveWay=(random==0)?i:j;
							for (int k=0;k<4;++k)
							{
								int random2=rand()%3;
								if (i!=k&&(movePos[k]==1||movePos[k]==2)&&j!=k)
								{
									if (random2==0)
										moveWay=i;
									else if (random2==1)
										moveWay=j;
									else
										moveWay=k;
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}	
			//Moves police with predetermined moveWay variable. 
			switch(moveWay){
				case 0:
					if (map[policePosY+1][2*(policePosX+1)+1]=='T')
					{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY+1][2*(policePosX+1)+1]='P';
						system("clear");	
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY+1][2*(policePosX+1)+1]='P';
						policePosX++;
					}
					break;
				case 1:
					if (map[policePosY+1][2*(policePosX-1)+1]=='T')
					{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY+1][2*(policePosX-1)+1]='P';
						system("clear");	
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY+1][2*(policePosX-1)+1]='P';
						policePosX--;
					}
					break;
				case 2:
					if (map[policePosY+2][2*policePosX+1]=='T')
					{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY+2][2*policePosX+1]='P';
						system("clear");	
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY+2][2*policePosX+1]='P';
						policePosY++;
					}
					break;
				case 3:
					if (map[policePosY][2*policePosX+1]=='T')
					{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY][2*policePosX+1]='P';
						system("clear");	
						PrintArray(map);
						printf("You lost!\n");
						return;
					}else{
						map[policePosY+1][2*policePosX+1]='_';
						map[policePosY][2*policePosX+1]='P';
						policePosY--;
					}
					break;
				default:
					break;
			}
		}	
		system("clear");	
		PrintArray(map);

	}
}

int main(){
	//variable declarations 
	char answer='X'; // answer of the play more question.
	char ignore; //character to handle enter char from scanf.
	char background[17][34] = {
		" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \0",
		"|_|_|_|_|_|_|_|_|W|_|_|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|_|_|W|_|_|_|_|_|_|_|\0",
		"|_|_|W|_|_|_|_|_|_|_|_|_|_|W|_|_|\0",
		"|_|_|W|_|_|_|_|_|_|_|_|_|_|W|_|_|\0",
		"|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|W|W|W|_|_|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|W|_|_|_|_|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|E|\0",
		"|_|_|_|_|_|_|_|_|_|_|W|_|_|_|_|_|\0",
		"|_|_|_|W|W|W|_|_|_|_|W|_|_|_|_|_|\0",
		"|_|_|_|_|_|W|_|_|_|_|W|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|_|_|_|_|W|W|_|_|_|_|\0",
		"|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\0",
		"|_|_|W|W|W|_|_|_|_|_|_|_|_|_|_|_|\0",
		"|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\0",
	}; //Game background. 
	//First starts game by calling funtion and after the game ends if user wants to play again it continues loop and calls StartGame again.
	while(1){
		StartGame(background); 
		do{
			printf("Do you want to play more? (Yes:Y,No:N)");
			scanf("%c%c",&answer,&ignore);
		}while(answer!='Y'&&answer!='N');
		if (answer=='Y')
		{
			system("clear");
			continue;
		}else if (answer=='N')
		{
			system("clear");
			break;
		}
	}
	return 0;
}
