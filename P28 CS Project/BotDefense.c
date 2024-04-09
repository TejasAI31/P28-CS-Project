#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
Enemy codes:
1->Small trooper
2->Giant trooper
3->Runners
4->Armored small trooper
5->Armored giant trooper
6->Armored goliaths
7->Armored runners
8->Speedster
*/

//enemy struct
typedef struct enemy { Rectangle hitbox; float health; float attack; float speed; float speedx; float speedy; int existence; Color color; int value; } enemystruct;


Rectangle p1 = { 480,480,40,40 };
Rectangle slots[8];


enemystruct enemy[100];

int newgame = 0;
int enemycount = 0;
int totalenemycount = 0;
int playermoney = 0;
int wavenumber = 0;
int slotweapons[8];

//weapon globals

//laserpulse
float laserpulseradius = 0;
float autopulseradius = 0;
int turnlaseron = 0;
int laserpulsevalues[100];
float totallaserpulse = 0;
float totalautopulse = 0;

//lightning bullets
typedef struct bullet { Vector2 currentpos; Vector2 endingpos; float speed; float speedx; float speedy; int existence; Rectangle hitbox; }bullet;
bullet bullets[200];
float totallightningbullets = 0;
float totalautobullets = 0;



//playerhealth
float playerhealth = 300;


//all enemy stats
void enemystats(int type,int t,int spawnx,int spawny)
{
	switch (type)
	{
		//small trooper
	case 1:
		enemy[t].health = 50;
		enemy[t].attack = 0.1;
		enemy[t].speed = 0.2;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,30,30 };
		enemy[t].color = YELLOW;
		enemy[t].value = 20;
		break;

		//giant trooper
	case 2:
		enemy[t].health = 300;
		enemy[t].attack = 0.3;
		enemy[t].speed = 0.15;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,80,80 };
		enemy[t].color = RED;
		enemy[t].value = 80;
		break;

		//runner
	case 3:
		enemy[t].health = 100;
		enemy[t].attack = 0.1;
		enemy[t].speed = 0.4;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,30,30 };
		enemy[t].color = PURPLE;
		enemy[t].value = 30;
		break;

		//armored small trooper
	case 4:
		enemy[t].health = 220;
		enemy[t].attack = 0.4;
		enemy[t].speed = 0.3;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,50,50 };
		enemy[t].color = ORANGE;
		enemy[t].value = 200;
		break;

		//armored giant trooper
	case 5:
		enemy[t].health = 550;
		enemy[t].attack = 0.5;
		enemy[t].speed = 0.2;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,100,100 };
		enemy[t].color = (Color){ 255,120,120,255 };
		enemy[t].value = 300;
		break;

		//armored goliath
	case 6:
		enemy[t].health = 3000;
		enemy[t].attack = 1;
		enemy[t].speed = 0.15;
		int q = rand() % 2;
		if(q==0)
			enemy[t].hitbox = (Rectangle){ spawnx,1000,300,300 };
		else if(q==1)
			enemy[t].hitbox = (Rectangle){ 1000,spawny,300,300 };
		enemy[t].color = (Color){ 187,190,120,255 };
		enemy[t].value = 5000;
		break;

		//armored runner
	case 7:
		enemy[t].health = 250;
		enemy[t].attack = 0.5;
		enemy[t].speed = 0.5;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,100,100 };
		enemy[t].color = (Color){ 80,220,100,255 };
		enemy[t].value = 300;
		break;

		//speedster
	case 8:
		enemy[t].health = 280;
		enemy[t].attack = 0.8;
		enemy[t].speed = 0.7;
		enemy[t].hitbox = (Rectangle){ spawnx,spawny,100,100 };
		enemy[t].color = (Color){ 50,100,200,255 };
		enemy[t].value = 400;
		break;
	}
}


void createenemy(int type)
{
	for (int t = 0; t < 100; t++)
	{
		if (enemy[t].existence!= 1)
		{

			//sets spawn location
			int spawnx=0;
			int spawny=0;
			int chance = (int)rand() % 4+1;

			switch (chance)
			{
			case 1:
				spawnx = rand() % 1000;
				spawny = -100;
				break;
			case 2:
				spawnx = rand() % 1000;
				spawny = 1000;
				break;
			case 3:
				spawnx = -100;
				spawny = rand() % 1000;
				break;
			case 4:
				spawnx = 1000;
				spawny = rand() % 1000;
			}
			
			
			
			enemystats(type, t,spawnx,spawny);





			//Circular path calculations
			if ( abs(enemy[t].hitbox.x - 500+enemy[t].hitbox.width)/2 >= abs(enemy[t].hitbox.y - 500 + enemy[t].hitbox.height)/2)
			{
				enemy[t].speedx =(enemy[t].hitbox.x<p1.x)? enemy[t].speed:-enemy[t].speed;
				float tempspeed= (abs(enemy[t].hitbox.y - 500 + enemy[t].hitbox.height / 2)) * enemy[t].speed / abs((enemy[t].hitbox.x - 500 + enemy[t].hitbox.width / 2));
				enemy[t].speedy = (enemy[t].hitbox.y < p1.y) ?tempspeed:-tempspeed;
			}
			else
			{
				enemy[t].speedy = (enemy[t].hitbox.y < p1.y)?enemy[t].speed: -enemy[t].speed;
				float tempspeed= (abs(enemy[t].hitbox.x - 500 + enemy[t].hitbox.width / 2)) * enemy[t].speed / abs((enemy[t].hitbox.y - 500 + enemy[t].hitbox.height / 2));
				enemy[t].speedx = (enemy[t].hitbox.x < p1.x) ? tempspeed : -tempspeed;
			}

			//creates existence
			enemy[t].existence = 1;
			enemycount++;
			break;

		}
	}
}


//autopulse attack
void autopulse(int q)
{
	float damage = 30;

	if (autopulseradius > 300 * totalautopulse)
	{
		DrawCircle(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, RED);
		DrawCircleLines(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, YELLOW);
	}
	else
	{
		DrawCircle(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, (Color) { 255, 105, 0, 255 });
		DrawCircleLines(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, YELLOW);
	}


	if(autopulseradius <= 400*totalautopulse)
	{
		if (autopulseradius < 30)
			DrawCircleLines(500, 500, (autopulseradius * 10)/totalautopulse, RED);

		if (autopulseradius * 10 >= 300*totalautopulse)
			DrawCircleLines(500, 500, 300, RED);

		if(autopulseradius<=300*totalautopulse)
		DrawCircleGradient(500, 500, autopulseradius/totalautopulse, (Color) { 255, 165, 0, 0 }, RED);

		autopulseradius += 1;
	}

	for (int t = 0; t < 100; t++)
	{
		if (enemy[t].existence == 1 && sqrt(pow(enemy[t].hitbox.x - 500 + enemy[t].hitbox.width / 2, 2) + pow(enemy[t].hitbox.y - 500 + enemy[t].hitbox.height / 2, 2)) - autopulseradius/totalautopulse <= 1 && laserpulsevalues[t] != totalautopulse&&autopulseradius<=300*totalautopulse)
		{
			enemy[t].health -= damage;
			laserpulsevalues[t] += 1;
		}
	}

	if (autopulseradius >= 400*totalautopulse)
	{
		for (int t = 0; t < 100; t++)
		{
			laserpulsevalues[t] = 0;
		}
		autopulseradius = 0;
	}

}




//Laserpulse
void laserpulse(int q)
{

	float damage = 40;

	if (turnlaseron == 0)
	{
		DrawCircle(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, RED);
		DrawCircleLines(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, YELLOW);
	}
	else
	{
		DrawCircle(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, (Color) { 255, 105, 0, 255 });
		DrawCircleLines(slots[q].x + slots[q].width / 2, slots[q].y + slots[q].height / 2, 10, YELLOW);
	}

	if (IsKeyPressed(KEY_W))
	{
		turnlaseron = 1;
	}


	if (turnlaseron == 1&&laserpulseradius<=300*totallaserpulse)
	{
		if(laserpulseradius<30)
		DrawCircleLines(500, 500, laserpulseradius*10/totallaserpulse, RED);

		if (laserpulseradius*10 >= 300*totallaserpulse)
			DrawCircleLines(500, 500, 300, RED);

		DrawCircleGradient(500, 500, laserpulseradius/totallaserpulse, (Color){255,165,0,0}, RED);
		laserpulseradius += 1;
	}


	for (int t = 0; t < 100; t++)
	{
		if (enemy[t].existence == 1 && sqrt(pow(enemy[t].hitbox.x - 500+enemy[t].hitbox.width/2, 2) + pow(enemy[t].hitbox.y - 500+enemy[t].hitbox.height/2, 2)) - laserpulseradius/totallaserpulse <= 1 && laserpulsevalues[t] != totallaserpulse)
		{
			enemy[t].health -= damage;
			laserpulsevalues[t] += 1;
		}
	}


	if (laserpulseradius >= 300*totallaserpulse)
	{
		for (int t = 0; t < 100; t++)
			laserpulsevalues[t] = 0;
		turnlaseron = 0;
		laserpulseradius = 0;
	}
}


//automatic lightning bullets
void autobullets(int q)
{
	float damage = 20;
	static int timer = 0;
	int closestenemy;
	for (int x = 0; x < 100; x++)
		if (enemy[x].existence == 1)
			closestenemy = x;
	float closestdistance = 1000;

	DrawCircle(slots[q].x + 20, slots[q].y + 20, 10, BLUE);
	DrawCircleLines(slots[q].x + 20, slots[q].y + 20, 10, SKYBLUE);
	if (timer > 10)
	{
		//finds closest enemy
		for (int t = 0; t < 100; t++)
		{
			if (enemy[t].existence == 1)
			{
				float distance = sqrt(pow(500 - enemy[t].hitbox.x, 2) + pow(500 - enemy[t].hitbox.y, 2));
				if (distance <= closestdistance)
				{
					closestenemy = t;
					closestdistance = distance;
				}
			}
		}


		for (int b = 0; b < 200; b++)
		{
			if (bullets[b].existence == 0)
			{
				bullets[b].currentpos = (Vector2){ slots[q].x + 10 ,slots[q].y + 10 };
				bullets[b].endingpos = (Vector2){ enemy[closestenemy].hitbox.x,enemy[closestenemy].hitbox.y };
				bullets[b].hitbox = (Rectangle){ bullets[b].currentpos.x,bullets[b].currentpos.y,20,20 };
				bullets[b].speed = 10;
				bullets[b].existence = 2;


				float xpos = bullets[b].currentpos.x;
				float ypos = bullets[b].currentpos.y;
				float fxpos = bullets[b].endingpos.x;
				float fypos = bullets[b].endingpos.y;

				if (abs(xpos - fxpos) >= abs(ypos - fypos))
				{
					bullets[b].speedx = (bullets[b].endingpos.x < bullets[b].currentpos.x) ? -bullets[b].speed : bullets[b].speed;
					float tempspeed = (abs(ypos - fypos)) * bullets[b].speed / abs((xpos - fxpos));
					bullets[b].speedy = (bullets[b].endingpos.y < bullets[b].currentpos.y) ? -tempspeed : tempspeed;
				}

				else
				{
					bullets[b].speedy = (bullets[b].endingpos.y < bullets[b].currentpos.y) ? -bullets[b].speed : bullets[b].speed;
					float tempspeed = (abs(xpos - fxpos)) * bullets[b].speed / abs((ypos - fypos));
					bullets[b].speedx = (bullets[b].endingpos.x < bullets[b].currentpos.x) ? -tempspeed : tempspeed;
				}
				timer = 0;
				break;
			}
		}
	}


	timer++;

	for (int b = 0; b < 200; b++)
	{
		float radius = sqrt(pow(bullets[b].hitbox.x - 500, 2) + pow(bullets[b].hitbox.y - 500, 2));
		if (bullets[b].existence == 2)
		{
			if (radius >= 1000)
			{
				bullets[b].existence = 0;
			}
		}
	}

	for (int b = 0; b < 20; b++)
	{
		if (bullets[b].existence == 2)
		{
			DrawRectangleRounded(bullets[b].hitbox,1,4, BLUE);
			DrawRectangleRoundedLines(bullets[b].hitbox, 1, 4, 3, SKYBLUE);
			for (int e = 0; e < 100; e++)
			{
				if (CheckCollisionRecs(bullets[b].hitbox, enemy[e].hitbox)&&enemy[e].existence==1)
				{
					enemy[e].health -= damage;
					DrawCircleGradient(bullets[b].hitbox.x + 10, bullets[b].hitbox.y + 10, 40, WHITE, BLUE);
					bullets[b].existence = 0;
				}
			}
			bullets[b].hitbox.x += bullets[b].speedx/totalautobullets;
			bullets[b].hitbox.y += bullets[b].speedy/totalautobullets;
		}
	}
}



//lightning bullets attacks
void lightningbullets(Vector2 mousepos,int t)
{
	float damage=40;
	static int timer = 0;

	DrawCircle(slots[t].x + 20, slots[t].y + 20, 10, BLUE);
	DrawCircleLines(slots[t].x + 20, slots[t].y + 20, 10, SKYBLUE);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)&&timer>10)
	{

		for (int b = 0; b <200; b++)
		{
			if (bullets[b].existence == 0)
			{
				bullets[b].currentpos = (Vector2){ slots[t].x+10 ,slots[t].y +10 };
				bullets[b].endingpos = mousepos;
				bullets[b].hitbox = (Rectangle){bullets[b].currentpos.x,bullets[b].currentpos.y,20,20};
				bullets[b].speed = 10;
				bullets[b].existence = 1;


				float xpos = slots[t].x + 10;
				float ypos = slots[t].y + 10;
				float fxpos = bullets[b].endingpos.x;
				float fypos = bullets[b].endingpos.y;

				if (abs(xpos - fxpos) >= abs(ypos - fypos))
				{
					bullets[b].speedx = (mousepos.x < 500) ? -bullets[b].speed : bullets[b].speed;
					float tempspeed = (abs(ypos - fypos)) * bullets[b].speed / abs((xpos - fxpos));
					bullets[b].speedy = (mousepos.y < 500) ? -tempspeed : tempspeed;
				}

				else
				{
					bullets[b].speedy = (mousepos.y < 500) ? -bullets[b].speed : bullets[b].speed;
					float tempspeed = (abs(xpos - fxpos)) * bullets[b].speed / abs((ypos - fypos));
					bullets[b].speedx = (mousepos.x < 500) ? -tempspeed : tempspeed;
				}
				timer = 0;
				break;
			}
		}
	}


	timer++;

	for (int b = 0; b < 200; b++)
	{
		float radius = sqrt(pow(bullets[b].hitbox.x - 500, 2) + pow(bullets[b].hitbox.y - 500, 2));
		if (bullets[b].existence == 1)
		{
			if (radius>=1000)
			{
				bullets[b].existence = 0;
			}
		}
	}

	for (int b = 0; b < 200; b++)
	{
		if (bullets[b].existence == 1)
		{
			DrawRectangleRounded(bullets[b].hitbox,1,4, BLUE);
			DrawRectangleRoundedLines(bullets[b].hitbox, 1, 4,3, SKYBLUE);
			for (int e = 0; e < 100; e++)
			{
				if (CheckCollisionRecs(bullets[b].hitbox, enemy[e].hitbox)&&enemy[e].existence==1)
				{
					enemy[e].health -= damage;
					DrawCircleGradient(bullets[b].hitbox.x+10,bullets[b].hitbox.y+10,40,WHITE,BLUE);
					bullets[b].existence = 0;
				}
			}
			bullets[b].hitbox.x += bullets[b].speedx/totallightningbullets;
			bullets[b].hitbox.y += bullets[b].speedy/totallightningbullets;
		}
	}

}





//autolaser
void autolaser(int t)
{
	float damage = 0.5;
	int closestenemy=0;
	float closestdistance = 1000;
	static float laserrot = 4;

	//finds closest enemy
	for (int t = 0; t < 100; t++)
	{
		if (enemy[t].existence == 1)
		{
			float distance = sqrt(pow(500 - enemy[t].hitbox.x, 2) + pow(500 - enemy[t].hitbox.y, 2));
			if (distance <= closestdistance)
			{
				closestenemy = t;
				closestdistance = distance;
			}
		}
	}

	if (laserrot < 10)
		laserrot += 0.1;
	else if (laserrot > 10)
		laserrot -= 2;

	DrawCircle(slots[t].x + 20, slots[t].y + 20, 10, GREEN);
	DrawCircle(slots[t].x + 20, slots[t].y + 20, 4, WHITE);
	DrawCircleLines(slots[t].x + 20, slots[t].y + 20, laserrot, WHITE);
	DrawLineEx((Vector2){slots[t].x+20, slots[t].y+20 }, (Vector2) { enemy[closestenemy].hitbox.x + enemy[closestenemy].hitbox.width / 2, enemy[closestenemy].hitbox.y + enemy[closestenemy].hitbox.height / 2 }, 10.0f, GREEN);
	DrawLineEx((Vector2) { slots[t].x + 20, slots[t].y + 20 }, (Vector2) { enemy[closestenemy].hitbox.x + enemy[closestenemy].hitbox.width / 2, enemy[closestenemy].hitbox.y + enemy[closestenemy].hitbox.height / 2 }, 5.0f, WHITE);
	DrawCircle(enemy[closestenemy].hitbox.x + enemy[closestenemy].hitbox.width / 2, enemy[closestenemy].hitbox.y + enemy[closestenemy].hitbox.height / 2, 10, GREEN);
	DrawCircle(enemy[closestenemy].hitbox.x + enemy[closestenemy].hitbox.width / 2, enemy[closestenemy].hitbox.y + enemy[closestenemy].hitbox.height / 2, 5, WHITE);
	enemy[closestenemy].health -= damage;
}

//laser attack
void laserattack(int posx, int posy, float* p1laserrot)
{
	float damage = 1;
	Vector2 mouseposition = { posx,posy };
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if (*p1laserrot < 10)
			*p1laserrot += 0.1;
		else if (*p1laserrot > 10)
			*p1laserrot -= 2;

		DrawLineEx((Vector2) { 500, 500 }, mouseposition, 10.0f, GREEN);
		DrawLineEx((Vector2) { 500, 500 }, mouseposition, 5.0f, WHITE);
		DrawCircle(posx, posy, 20, GREEN);
		DrawCircle(posx, posy, 15, WHITE);
		for (int t = 0; t < 100  ;t++)
		{
			if (CheckCollisionPointRec(mouseposition, enemy[t].hitbox))
			{
				enemy[t].health -= 1;
			}
		}
	}
	else if(*p1laserrot>4)
		*p1laserrot -=0.1;
}

void eraseslots(Vector2 mousepos)
{
	for(int x=0;x<8;x++)
		if (CheckCollisionPointRec(mousepos, slots[x]))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			{
				switch (slotweapons[x])
				{
				case 2:totallightningbullets -= 1;
					break;
				case 3:totalautobullets -= 1;
					break;
				case 4:totallaserpulse -= 1;
					break;
				case 5:totalautopulse -= 1;
					break;
				default:break;
				}
				slotweapons[x] = NULL;
			}
		}
}

//initiate unused slots
void initslots()
{
	int slotnumber = 0;
	for (int y = p1.y - 42; y <= p1.y + 42; y += 42)
	{
		for (int x = p1.x - 42; x <= p1.x + 42; x+=42)
		{
			if (x == p1.x && y ==p1.y)
				continue;
			slots[slotnumber] = (Rectangle){ x,y,40,40 };
			slotnumber++;
		}
	}
}

//draw unused slots
void drawslots()
{
	for (int x = 0; x <8; x++)
	{
		DrawRectangleRoundedLines(slots[x], 0.6,0,2 , BLACK);
		DrawRectangleRounded(slots[x], 0.5, 0, GRAY);
		//DrawRectangleRec(slots[x], GRAY);
		DrawCircle(slots[x].x + 20, slots[x].y + 20, 10, DARKGRAY);
	}
}

//initiate shop buttons
void initiatebuttons(Rectangle* button,int buttonnumber)
{
	switch (buttonnumber)
	{
	case 0:
		*button = (Rectangle){620,100,100,40};
		break;
	case 1:
		*button = (Rectangle){ 760,200,100,40 };
		break;
	case 2:
		*button = (Rectangle){ 860,300,100,40 };
		break;
	case 3:
		*button = (Rectangle){ 700,400,100,40 };
		break;
	case 4:
		*button = (Rectangle){ 660,500,100,40 };
		break;
	}
}


void enemycreator(int e, int c)
{
	for(int x=1;x<=c;x++)
	switch (e)
	{
	case 1:createenemy(1);
		break;
	case 2:createenemy(2);
		break;
	case 3:createenemy(3);
		break;
	case 4:createenemy(4);
		break;
	case 5:createenemy(5);
		break;
	case 6:createenemy(6);
		break;
	case 7:createenemy(7);
		break;
	case 8:createenemy(8);
		break;
	case 9:createenemy(9);
		break;
	case 10:createenemy(10);
		break;
	case 11:createenemy(11);
		break;
	}
}

//creates enemies
void wavecreator()
{

	if (enemycount <2&&wavenumber<=100)
	{
		wavenumber++;

		switch (wavenumber)
		{
		case 1:
			enemycreator(1, 20);
			break;
		case 2:
			enemycreator(1,25);
			enemycreator(2,5);
			break;
		case 3:
			enemycreator(1,25);
			enemycreator(2,15);
			break;
		case 4:
			enemycreator(1,10);
			enemycreator(2,10);
			enemycreator(3,20);
			break;
		case 5:
			enemycreator(1,5);
			enemycreator(2,20);
			enemycreator(3,20);
			break;
		case 6:
			enemycreator(2, 30);
			enemycreator(3, 20);
			break;
		case 7:
			enemycreator(4, 20);
			enemycreator(3, 30);
			break;
		case 8:
			enemycreator(4, 30);
			enemycreator(2, 10);
			enemycreator(3, 10);
			break;
		case 9:
			enemycreator(4, 40);
			enemycreator(2, 30);
			enemycreator(5, 10);
			break;
		case 10:
			enemycreator(6, 5);
			break;
		case 11:
			enemycreator(4, 40);
			enemycreator(5, 20);
			enemycreator(7, 10);
			break;
		case 12:
			enemycreator(7, 50);
			enemycreator(4, 30);
			break;
		case 13:
			enemycreator(6, 2);
			enemycreator(7, 30);
			enemycreator(5, 15);
			break;
		case 14:
			enemycreator(8, 50);
			enemycreator(6, 3);
			break;
		case 15:
			enemycreator(6, 5);
			break;
		default:
			for (int x = 1; x < 100; x++)
			{
				int et = rand() % 15;
				switch (et)
				{
				case 1:
				case 2:enemycreator(4,1);
					break;
				case 3:
				case 4:enemycreator(5, 1);
					break;
				case 5:
				case 6:
				case 7:
				case 8:enemycreator(7, 1);
					break;
				case 9:
				case 10:
				case 11:
					enemycreator(8, 1);
					break;
				case 12:
				case 13:enemycreator(4, 1);
					enemycreator(5, 1);
					break;
				case 14:
					enemycreator(6, 1);
					break;
				}
			}
		}
	}
}

void game2()
{
	Rectangle upgradebuttons[10];

	//initiates buttons
	for(int t=0;t<10;t++)
	initiatebuttons(&upgradebuttons[t],t);

	//switches screens
	int currentscreen = 3;

	//Weapon buys
	float p1laserrot=4;
	int autolaserbuy = 0;
	int laserpulsebuy = 0;
	int lightningbulletsbuy = 0;
	int autopulsebuy = 0;
	int autobulletsbuy = 0;

	//initiates game window
	InitWindow(1000,1000,"Bot Defender");

	Vector2 mousepos;

	SetTargetFPS(144);
	system("cls");
	


	while (!WindowShouldClose())
	{
		//sets mouse position
		mousepos = GetMousePosition();


		//Begin the drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);

		//switches to upgrade screen
		if (IsKeyPressed(KEY_E))
		{
			currentscreen = 1;
		}
		
		
		//upgrade screen
		if (currentscreen == 1)
		{
			//draws upgrade buttons
				DrawRectangleRec(upgradebuttons[0],RED);
			if(autolaserbuy==1)
				DrawRectangleRec(upgradebuttons[1], RED);
			if(lightningbulletsbuy==1||autobulletsbuy==1)
				DrawRectangleRec(upgradebuttons[2], RED);
			if(autobulletsbuy==1)
				DrawRectangleRec(upgradebuttons[3], RED);
			if(laserpulsebuy==1||autopulsebuy==1)
				DrawRectangleRec(upgradebuttons[4], RED);


			//checks if bought
			for (int t = 0; t < 10; t++)
			{
				if(CheckCollisionPointRec(mousepos,upgradebuttons[t]))
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						switch (t)
						{
						case 0:
							if (playermoney >= 500)
							{
								autolaserbuy = 1;
								for (int x = 0; x < 8; x++)
									if (slotweapons[x] ==NULL)
									{
										slotweapons[x] = 1;
										playermoney -= 500;
										break;
									}
							}
							break;
						case 1:
							if (playermoney >= 5000&&totallightningbullets<2)
							{
								lightningbulletsbuy = 1;
								for (int x = 0; x < 8; x++)
									if (slotweapons[x] ==NULL)
									{
										slotweapons[x] = 2;
										totallightningbullets += 1;
										playermoney -= 5000;
										break;
									}
							}
							break;
						case 2:
							if (playermoney >= 10000 &&totalautobullets<2)
							{
								autobulletsbuy = 1;
								for (int x = 0; x < 8; x++)
									if (slotweapons[x] == NULL)
									{
										slotweapons[x] = 3;
										totalautobullets += 1;
										playermoney -= 10000;
										break;
									}
							}
							break;
						case 3:
							if (playermoney >= 25000&&totallaserpulse<2)
							{
								laserpulsebuy = 1;
								for (int x = 0; x < 8; x++)
									if (slotweapons[x] == NULL)
									{
										slotweapons[x] = 4;
										totallaserpulse += 1;
										playermoney -= 25000;
										break;
									}
							}
							break;
						case 4:
							if (playermoney >= 50000 &&totalautopulse<2)
							{
								autopulsebuy = 1;
								for (int x = 0; x < 8; x++)
									if (slotweapons[x] == NULL)
									{
										slotweapons[x] = 5;
										totalautopulse += 1;
										playermoney -= 50000;
										break;
									}
							}
							break;
						}
					}
			}


			//Draws total money
			DrawText(TextFormat("Total Money: %d", playermoney), 800, 40,20, BLACK);

			//Upgrade text
			DrawText("Buy Auto Laser? ($500)", 100, 100, 40, BLACK);
			if (autolaserbuy == 1)
				DrawText("Buy Lightning Bullets? ($5000)", 100, 200, 40, BLACK);
			if (lightningbulletsbuy == 1 || autobulletsbuy == 1)
				DrawText("Buy Auto Lightning Turret ($10000)", 100, 300, 40, BLACK);
			if(autobulletsbuy==1)
				DrawText("Buy Laser Pulse? ($25000)", 100, 400, 40, BLACK);
			if (laserpulsebuy == 1||autopulsebuy==1)
				DrawText("Buy Auto Pulse? ($50000)", 100, 500, 40, BLACK);


			DrawText("Press 'R to Return",700,800,20,BLACK);
			
			if(IsKeyPressed(KEY_R))
				currentscreen = 0;
		}



		//main game
		else if(currentscreen==0)
		{

			//initiates and draws slots and player
			initslots();
			drawslots();
			DrawRectangleRoundedLines(p1, 0.6, 0,2, BLACK);
			DrawRectangleRounded(p1, 0.5, 0, BLUE);
			DrawCircle(p1.x + 20, p1.y + 20, 10, GREEN);
			DrawCircle(p1.x + 20, p1.y + 20, 4, WHITE);


			//creates enemies
			wavecreator();


			//draws enemy
			for (int t = 0; t < 100; t++)
			{
				if (enemy[t].health > 0)
				{
					DrawRectangleRoundedLines(enemy[t].hitbox, 0.2, 4,1.5, BLACK);
					DrawRectangleRounded(enemy[t].hitbox,0.2,4, enemy[t].color);
					DrawText(TextFormat("%.0f", enemy[t].health), enemy[t].hitbox.x + 10, enemy[t].hitbox.y + 10, 10, BLACK);
				}
				else if (enemy[t].health <= 0 && enemy[t].existence == 1)
				{
					playermoney += enemy[t].value;
					enemy[t].existence = 0;
					enemycount -= 1;
				}
			}


			//checks for contact with player
			for (int t = 0; t < 100; t++)
			{
				if (enemy[t].existence == 1)
				{
					if (!CheckCollisionRecs(enemy[t].hitbox, p1))
					{
						enemy[t].hitbox.x += enemy[t].speedx;
						enemy[t].hitbox.y += enemy[t].speedy;
					}
					else
					{
						if(playerhealth>0)
						playerhealth -= enemy[t].attack;
					}
				}
			}


			//attacks crosshair
			laserattack(mousepos.x, mousepos.y,&p1laserrot);

			for (int x = 0; x < 8; x++)
			{
				switch (slotweapons[x])
				{
				case 1:autolaser(x);
					break;
				case 2:lightningbullets(mousepos,x);
					break;
				case 3:autobullets(x);
					break;
				case 4:laserpulse(x);
					break;
				case 5:autopulse(x);
					break;
				}
			}

			// draws laser
			DrawCircleLines(p1.x + 20, p1.y + 20, p1laserrot, WHITE);

			eraseslots(mousepos);

			//shows total money
			DrawText(TextFormat("Total Money: %d", playermoney), 700, 100, 20, BLACK);

			DrawText(TextFormat("Wave Number: %d", wavenumber), 100, 100, 20, BLACK);

			DrawText("Press 'E' For Upgrade Shop",600,800,20,BLACK);

			DrawText(TextFormat("Player Health: %.0f", playerhealth), 400, 900, 20, BLACK);

			if (newgame == 1)
			{
				playermoney = 0;
				newgame = 0;
			}



			if (playerhealth <= 0)
				currentscreen = 2;
		}

		else if (currentscreen == 2)
		{
			DrawText("RESTART? (y/n)", 400, 400, 40, BLACK);

			wavenumber = 0;
			for (int t = 0; t < 100; t++)
			{
				enemy[t].health = 0;
			}
			for (int t = 0; t < 8; t++)
				slotweapons[t] = NULL;
			playerhealth = 300;
			newgame = 1;
			autolaserbuy = 0;
			lightningbulletsbuy = 0;
			autobulletsbuy = 0;
			laserpulsebuy = 0;
			autopulsebuy = 0;
			totalautobullets = 0;
			totalautopulse = 0;
			totallaserpulse = 0;
			totallightningbullets = 0;


			if (IsKeyPressed(KEY_Y))
			{
				currentscreen = 0;

			}
			else if (IsKeyPressed(KEY_N))
			{

				CloseWindow();
				mainscreen();
				break;
			}
		}

		else if (currentscreen == 3)
		{
			Rectangle startbutton = (Rectangle){430,590,130,50};
			DrawText("Geometry Defense", 270, 400, 50, RED);
			DrawRectangleRec(startbutton, RED);
			DrawText("Start", 450, 600, 30, BLACK);
			if (CheckCollisionPointRec(mousepos, startbutton))
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					currentscreen = 0;
		}


		//End the drawing
			EndDrawing();
	}
}