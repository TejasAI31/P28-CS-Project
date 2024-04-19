#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



const float ballgravity = 4;
const float playergravity = 8;
const float restitution = 0.8f;

float uball = 0;
float vball = 0;
float uplayer1 = 0;
float vplayer1 = 0;
float uplayer2 = 0;
float vplayer2 = 0;
float x = 0;

int player1points=0;
int player2points = 0;
int chain = 0;
int p1jumps = 2;
int p2jumps = 2;
int playertexture = 0;
int ballhitforcex=4;
int ballhitforcey = 3;
int isgloveworking = 0;

Vector2 mousepos = { 0.0f,0.0f };

Rectangle ball = { 200,100,20,20 };
Rectangle player = { 100,400,20,50 };
Rectangle player2 = { 1500,400,20,50 };
Rectangle grass = { 0,620,1600,200 };
Rectangle net = { 790,320,20,300 };
Rectangle closebutton = { 1500,50,18,18 };



Texture2D volleyballtexture;
Texture2D volleyballnettexture;
Texture2D tree2texture;
Texture2D treetexture;
Texture2D platformtexture;
Texture2D outertexture;
Texture2D innertexture;
Texture2D glovetexture;
Texture2D suntexture;
Texture2D moontexture;
Texture2D bigcloudtexture;
Texture2D smallcloudtexture;
Texture2D emptybartexture;
Texture2D fullbartexture;
Texture2D closetexture;


Color sky = { 0,0,0,0 };





void checkpowerupactivation()
{
	if (chain >= 3)
	{
		ballhitforcex = 5.5;
		ballhitforcey = 2;
		isgloveworking = 1;
	}
}

void showpoints()
{
	DrawText(TextFormat("%d",player1points), 710,695 , 80, GREEN);
	DrawText(TextFormat("%d", player2points), 1480, 695, 80, GREEN);
	if (chain >= 1)
		DrawText(TextFormat("Chain: %d", chain), 750, 100, 30, RED);
}

void checknetball()
{
	if (ball.x >= 790 && ball.x <= 810 && ball.y >= 320)
	{
		if (ball.x >= 800)
		{
			player1points++;
			ball.x = 1200;
		}
		else
		{
			player2points++;
			ball.x = 200;
		}
		ball.y = 100;
		uball = 0;
		vball = 0;
		x = 0;
		chain = 0;
		ballhitforcex = 4;
		ballhitforcey = 3;
		isgloveworking = 0;
	}
}


void player2hit()
{

	if (IsKeyPressed(KEY_END) && (player2.x + 10) - ball.x <= 40 && ball.x - (player2.x + 10) <= 40 && player2.y - ball.y <= 40 && ball.y - player2.y <= 55)
	{
		if (player2.y <= 500)
		{
			vball = -ballhitforcey;
			x = -ballhitforcex-2;
		}
		else if (player2.y >= 500)
		{
			vball = -ballhitforcey*2;
			x = -ballhitforcex;
		}
		chain++;
	}
}


void playerhit()
{
	if (IsKeyPressed(KEY_ENTER) && (player.x + 10) - ball.x <= 40 && ball.x - (player.x + 10) <= 40 && player.y - ball.y <= 40&&ball.y-player.y<=55)
	{
		if (player.y <= 500)
		{
			vball = -ballhitforcey;
			x = ballhitforcex+2;
		}
		else if (player.y >= 500)
		{
			vball = -ballhitforcey*2;
			x = ballhitforcex;
		}
		chain++;
	}
}

void player2movement()
{
	if (IsKeyDown(KEY_RIGHT) && IsKeyPressed(KEY_RIGHT_CONTROL)&&player2.x<=1580&&p2jumps>=1)
	{
		vplayer2 -= 6;
		player2.x += 2;
		p2jumps--;
	}
	else if (IsKeyDown(KEY_LEFT) && IsKeyPressed(KEY_RIGHT_CONTROL)&&player2.x>=810&&p2jumps>=1)
	{
		vplayer2 -= 6;
		player2.x -= 2;
		p2jumps--;
	}
	else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_RIGHT_SHIFT) && player2.x <= 1580)player2.x += 4;
	else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT_SHIFT)&&player2.x >= 810)player2.x -= 4;
	else if (IsKeyDown(KEY_RIGHT) && player2.x <= 1580)player2.x += 2;
	else if (IsKeyDown(KEY_LEFT)&&player2.x >= 810)player2.x -= 2;
	else if (IsKeyPressed(KEY_RIGHT_CONTROL)&&p2jumps>=1)
	{
		if (vplayer2 > 2)
			vplayer2 = -4;
		else if (vplayer2 < 0)
			vplayer2 = -4;
		else if (vplayer2 <= 2 && vplayer2 > 0)
			vplayer2 -= 4;
		else
			vplayer2 -= 6;
		p2jumps--;
	}
}


/*void player2movement(char inp)
{
	printf("%c\n", inp);
	if (IsKeyDown(KEY_RIGHT) && IsKeyPressed(KEY_RIGHT_CONTROL) && player2.x <= 1580 && p2jumps >= 1)
	{
		vplayer2 -= 6;
		player2.x += 2;
		p2jumps--;
	}
	else if (IsKeyDown(KEY_LEFT) && IsKeyPressed(KEY_RIGHT_CONTROL) && player2.x >= 810 && p2jumps >= 1)
	{
		vplayer2 -= 6;
		player2.x -= 2;
		p2jumps--;
	}
	else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_RIGHT_SHIFT) && player2.x <= 1580)player2.x += 4;
	else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT_SHIFT) && player2.x >= 810)player2.x -= 4;
	else if (inp=='d' && player2.x <= 1580)player2.x += 2;
	if (inp=='a'&& player2.x >= 810)player2.x -= 2;
	else if (IsKeyPressed(KEY_RIGHT_CONTROL) && p2jumps >= 1)
	{
		if (vplayer2 > 2)
			vplayer2 = -4;
		else if (vplayer2 < 0)
			vplayer2 = -4;
		else if (vplayer2 <= 2 && vplayer2 > 0)
			vplayer2 -= 4;
		else
			vplayer2 -= 6;
		p2jumps--;
	}
	
}*/

//movement check
void playermovement()
{
	if (IsKeyDown(KEY_D) && IsKeyPressed(KEY_SPACE)&&player.x<=770&&p1jumps>=1)
	{
			vplayer1 -= 6;
			player.x += 2;
			p1jumps--;
	}
	else if (IsKeyDown(KEY_A) && IsKeyPressed(KEY_SPACE)&&player.x>=0&&p1jumps>=1)
	{
			vplayer1 -= 6;
			player.x -= 2;
			p1jumps--;
	}
	else if (IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) && player.x <= 770)player.x += 4;
	else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) && player.x >= 0)player.x -= 4;
	else if (IsKeyDown(KEY_D) && player.x <= 770)player.x += 2;
	else if (IsKeyDown(KEY_A) && player.x >= 0)player.x -= 2;
	else if (IsKeyPressed(KEY_SPACE)&&p1jumps>=1)
	{
		if (vplayer1 > 2)
			vplayer1 = -4;
		else if (vplayer1 < 0)
			vplayer1 = -4;
		else if (vplayer1 <= 2&&vplayer1>0)
			vplayer1 -= 4;
		else
			vplayer1 -= 6;
		p1jumps--;
	}
}



void player2bounce()
{
	if (player2.y >= 570 && vplayer2 >= 0)
	{
		vplayer2 = 0;
		p2jumps = 2;
	}
	if(player2.y>10)
	player2.y += vplayer2;
}


void playerybounce()
{
	if (player.y >= 570 && vplayer1 >= 0)
	{
		vplayer1 = 0;
		p1jumps = 2;
	}
	if (player.y < 10)
		vplayer1=1;
	player.y += vplayer1;
}




void groundfriction()
{
	if (ball.y >= 600&&x!=0)
	{
		if (x >= 0)
			x -= 0.2f;
		else
			x += 0.2f;
	}
	if (x <= 0.2f && x >= -0.2f)x = 0;
}

void ballxmovement()
{
	ball.x += x;
}

void addbounce(int extrabounce)
{
	if (IsKeyPressed(KEY_W)&&(player.x+10)-ball.x<=40&&ball.x-(player.x+10)<=40&&player.y-ball.y<=40&&ball.y-player.y<=55)
	{
		x = 0;
		if (ball.y<=400)
			vball = -extrabounce;
		else
		{
			vball = -4; 
		}
		x = 1;
	}
	if (IsKeyPressed(KEY_UP) && (player2.x + 10) - ball.x <= 40 && ball.x - (player2.x + 10) <= 40 && player2.y - ball.y <= 40 && ball.y - player2.y <= 55)
	{
		x = 0;
		if (ball.y <= 400)
			vball = -extrabounce;
		else
		{
			vball = -4;
		}
		x = -1;
	}
}


void checkboundary()
{
	if (ball.y <= 0 && vball <= 0)
	{
		vball = -(restitution * vball);
		return;
	}
	else if (ball.x <= 0 && x <= 0)
	{
		x = -(restitution)*x;
		return;
	}
	else if (ball.x >= 1580 && x >= 0)
	{
		x = -(restitution)*x;
		return;
	}
}


//y bounce
void ballybounce()
{
	if (ball.y >= 600 && vball >= 0)
	{
		if (vball <= 0.2 && vball >= -0.2)
			vball = 0;
		else
		vball = -(restitution * vball);
	}
	ball.y += vball;
}

void settexture()
{
	Image volleyball = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//ballart.png");
	volleyballtexture = LoadTextureFromImage(volleyball);
	UnloadImage(volleyball);

	Image volleyballnet = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//volleyballpole.png");
	volleyballnettexture = LoadTextureFromImage(volleyballnet);
	UnloadImage(volleyballnet);

	Image tree2 = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//tree2.png");
	tree2texture = LoadTextureFromImage(tree2);
	UnloadImage(tree2);

	Image tree = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//tree.png");
	treetexture = LoadTextureFromImage(tree);
	UnloadImage(tree);

	Image platform = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//platform.png");
	platformtexture = LoadTextureFromImage(platform);
	UnloadImage(platform);

	Image outer = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//outer.png");
	outertexture = LoadTextureFromImage(outer);
	UnloadImage(outer);

	Image inner = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//inner.png");
	innertexture = LoadTextureFromImage(inner);
	UnloadImage(inner);

	Image glove = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//gloves.png");
	glovetexture = LoadTextureFromImage(glove);
	UnloadImage(glove);

	Image sun = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//sun.png");
	suntexture = LoadTextureFromImage(sun);
	UnloadImage(sun);

	Image moon = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//moon.png");
	moontexture = LoadTextureFromImage(moon);
	UnloadImage(moon);

	Image bigcloud = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//bigcloud.png");
	bigcloudtexture = LoadTextureFromImage(bigcloud);
	UnloadImage(bigcloud);

	Image smallcloud = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//smallcloud.png");
	smallcloudtexture = LoadTextureFromImage(smallcloud);
	UnloadImage(smallcloud);

	Image emptybar = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//emptybar.png");
	emptybartexture = LoadTextureFromImage(emptybar);
	UnloadImage(emptybar);

	Image fullbar = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//fullbar.png");
	fullbartexture = LoadTextureFromImage(fullbar);
	UnloadImage(fullbar);
	
	Image close = LoadImage("C://Users//tsm69//Desktop//Coding//c++//P28 CS Project//Sprites//close.png");
	closetexture = LoadTextureFromImage(close);
	UnloadImage(close);
}


//main game
void game()
{
	float sunx;
	float suny;
	float theta = -4;
	float bigcloudx;
	float bigcloudy = 100;
	float bigcloud2x;
	float bigcloud2y = 100;
	float smallcloudx;
	float smallcloudy = 250;
	float smallcloud2x;
	float smallcloud2y = 150;
	float smallcloud3x;
	float smallcloud3y = 100;


	InitWindow(1600, 800, "Volleyball");
	SetTargetFPS(144);
	settexture();
	aitrain();


	//initiates cloud x positions
	bigcloudx = rand() % 1600;
	bigcloud2x = rand() % 1600;
	smallcloudx = rand() % 1600;
	smallcloud2x = rand() % 1600;
	smallcloud3x = rand() % 1600;

	while (!WindowShouldClose())
	{
		//initiates mouse position
		mousepos = GetMousePosition();

		if (CheckCollisionPointRec(mousepos, closebutton))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				CloseWindow();
				break;
			}
		}

		//initiates sun position
		sunx = 800 * cos(theta);
		suny = 800 * sin(theta);


		//Initiates ball and player y speed
		vball = uball + 0.006944444f * ballgravity;
		vplayer1 = uplayer1 + 0.006944444f * playergravity;
		vplayer2 = uplayer2 + 0.006944444f * playergravity;

		BeginDrawing();
		ClearBackground(sky);
		
		//checks activation of gloves
		checkpowerupactivation();


		//manages y direction of ball and player
		ballybounce();
		playerybounce();
		player2bounce();

		//checks if player hit
		playerhit();
		player2hit();

		//manages ball x movement
		ballxmovement();

		//manages w,a,s,d, movements
		playermovement();
		
		player2movement();

		//additional bounce
		addbounce(2);

		//checks boundary condition
		checkboundary();

		//checks ground friction
		groundfriction();

		//checks if ball hit the net
		checknetball();


		//draws ball,player and floor
		DrawTexture(suntexture, 600+sunx, 800+suny, WHITE);
		DrawTexture(moontexture, 600-sunx, 800 - suny, WHITE);


		//draws clouds
		DrawTexture(smallcloudtexture, smallcloudx, smallcloudy, WHITE);
		if (smallcloudx >= -440)
			smallcloudx -= 0.3;
		else
		{
			smallcloudy = 100 + rand() % 200;
			smallcloudx = 1600;
		}

		DrawTexture(smallcloudtexture, smallcloud2x, smallcloud2y, WHITE);
		if (smallcloud2x >= -440)
			smallcloud2x -= 0.3;
		else
		{
			smallcloud2y = 100 + rand() % 200;
			smallcloud2x = 1600;
		}


		DrawTexture(smallcloudtexture, smallcloud3x, smallcloud3y, WHITE);
		if (smallcloud3x >= -440)
			smallcloud3x -= 0.3;
		else
		{
			smallcloud3y = 100 + rand() % 200;
			smallcloud3x = 1600;
		}

		DrawTexture(bigcloudtexture, bigcloudx, bigcloudy, WHITE);
		if (bigcloudx >= -440)
			bigcloudx-=0.2;
		else
		{
			bigcloudy =100+rand() % 200;
			bigcloudx = 1600;
		}

		DrawTexture(bigcloudtexture, bigcloud2x, bigcloud2y, WHITE);
		if (bigcloud2x >= -440)
			bigcloud2x -= 0.2;
		else
		{
			bigcloud2y = 100 + rand() % 200;
			bigcloud2x = 1600;
		}

		//draws textures
		DrawTexture(treetexture, 450, 300, WHITE);
		DrawTexture(tree2texture, 100, 200, WHITE);
		DrawTexture(treetexture, 1200, 300, WHITE);
		DrawRectangleRec(player, BLUE);
		DrawRectangleRec(player2, RED);
		DrawCircleLines(player.x + 10, player.y + 20, 40, YELLOW);
		DrawCircleLines(player2.x + 10, player2.y + 20, 40, YELLOW);
		DrawRectangleLinesEx(ball,0, WHITE);
		DrawTexture(volleyballtexture, ball.x, ball.y,WHITE);
		DrawRectangleRec(grass, DARKBLUE);
		DrawRectangleRec(net, BLACK);
		DrawTexture(volleyballnettexture, net.x, net.y, WHITE);

		//draws blue tiles
		int pos = 650;
		for (int y = 1; y <= 2; y++)
		{
			for (int x = 0; x <= 1600; x += 32)
			{
				DrawTexture(outertexture, x, pos, WHITE);
			}
			pos = 778;
		}
		pos = 682;
		for (int y = 1; y <= 3; y++)
		{
			for (int x = 0; x <= 1568; x += 32)
			{
				if(x<64||(x>=768&&x<832)||x>=1536)
				DrawTexture(innertexture, x, pos, WHITE);
			}
			pos += 32;
		}

		//draws platform and powerups
		if (isgloveworking == 0)
		{
			DrawTexture(emptybartexture, 170, 714, WHITE);
			DrawTexture(emptybartexture, 938, 714, WHITE);
		}
		else
		{
			DrawTexture(fullbartexture, 170, 714, WHITE);
			DrawTexture(fullbartexture, 938, 714, WHITE);
		}
		DrawTexture(glovetexture, 64, 682, WHITE);
		DrawTexture(glovetexture, 832, 682, WHITE);
		DrawTexture(platformtexture, 0, 613, WHITE);
		DrawTexture(platformtexture, 520, 613, WHITE);
		DrawTexture(platformtexture, 1040, 613, WHITE);
		DrawTexture(platformtexture, 1560, 613, WHITE);
		
		
		//shows points
		showpoints();

		//changes theta for sun position
		theta -= 0.0002;


		//changes sky color
		if ((int)suny % 10 == 0&&(int)suny>=-50 && (int)sunx >= 0&&(int)suny<=0)
		{
			sky.r += 2;
			sky.g += 1;
		}
		if((int)suny%30==0&&sky.b!=255&&(int)sunx>=0&&(int)suny<=0)
		{
			sky.b += 1;
		}
		if ((int)suny % 30 == 0 && sky.b != 0 && (int)sunx <= 0)
		{
			sky.b -= 1;
		}
		if ((int)suny % 10 == 0 && (int)suny >= -50 && (int)sunx <= 0&&sky.r!=0&&sky.g!=0)
		{
			sky.r -= 2;
			sky.g -= 1;
		}

		DrawRectangleRec(closebutton, BLACK);
		DrawTexture(closetexture, 1500, 50, WHITE);
		EndDrawing();

		//establishes 'u' for next calculation
		uball = vball;
		uplayer1 = vplayer1;
		uplayer2 = vplayer2;
	}
	mainscreen();
}