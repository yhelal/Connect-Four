/*Youssef Helal
900142332
Assignment 7
Recursion and SFML 
Connect 4 Game*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
#define rows 7
#define cols 7
#define wincount 4
#define r 50
void drawBoard(sf::RectangleShape &);
void drawcircles(sf::CircleShape[][cols]);
void drawPlayers(sf::CircleShape &p1, sf::CircleShape &p2);
void update(sf::CircleShape, sf::CircleShape, sf::CircleShape[][cols], bool &, bool &);
bool check_win(sf::CircleShape, sf::CircleShape[][cols]);
bool checker(sf::CircleShape, sf::CircleShape [][cols], int , int , int,int);
void initialize_restart(bool &, bool &, bool &, bool &, bool &, bool &);
bool game_finished( bool, bool,sf::CircleShape[][cols]);
void main()
{
	int v = 0;
	sf::Vector2f A[rows][cols];
	sf::RenderWindow win;                                         //window
	win.create(sf::VideoMode(1920, 1080), "Connect 4");            //window size and name
	sf::RectangleShape board;
	drawBoard(board);


	sf::CircleShape circles[rows][cols];
	drawcircles(circles);

	sf::CircleShape p1;
	sf::CircleShape p2;


	sf::Music music;                           //music
	if (!music.openFromFile("music.ogg"))
	{
		cout << "Error loading music";
	}


	
	music.setVolume(10);   // music volume control
	music.setLoop(true);  //music loops


	sf::Font MyFont;
	if (!MyFont.loadFromFile("font.ttf"))
		cout << "Error";
	

	sf::Text Instructions("Press left or right to move. Press down to drop the coin. Press Space to Start the Game.", MyFont);
	Instructions.setCharacterSize(15);
	Instructions.setPosition(0, 0);

	sf::Text p1wins("Player 1 wins!. Press space to restart or ESC to quit.", MyFont);      //text for win and tie
	p1wins.setCharacterSize(15);
	p1wins.setPosition(500, 850);
	sf::Text p2wins("Player 2 wins!. Press space to restart or ESC to quit.", MyFont);
	p2wins.setCharacterSize(15);
	p2wins.setPosition(500, 850);
	sf::Text nowinner("It's a tie!. Press space to restart or ESC to quit.", MyFont);
	nowinner.setCharacterSize(15);
	nowinner.setPosition(500, 850); 

	sf::Text playerone("Player 1", MyFont);
	playerone.setCharacterSize(25);
	playerone.setPosition(100, 100);
	sf::Text playertwo("Player 2", MyFont);
	playertwo.setCharacterSize(25);
	playertwo.setPosition(100, 100);



	bool isRunning = false;
	bool player1 = false;
	bool player2 = false;
	bool p1win = false;
	bool p2win = false;
	bool tie = false;

	while (win.isOpen())         //game loop
	{
		sf::Event myevent;
		while (win.pollEvent(myevent))     //event handling
		{

			if (myevent.type == sf::Event::Closed)         //close game if x is clicked
				win.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))           //close game if ESC keys is pressed
				win.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  //to restart
			{
				if (!isRunning)
				{
					initialize_restart(isRunning, player1, player2, p1win, p2win, tie);
					drawcircles(circles);
					drawBoard(board);
					drawPlayers(p1, p2);
					music.play();
				}
			}

			if (isRunning)
			{
				

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //moves coin right
				{
					if (player1 && p1.getPosition().x < 1180)

						p1.move(110, 0);



					if (player2 && p2.getPosition().x<1180)
						p2.move(110, 0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  //moves coin left
				{
					if (player1 && p1.getPosition().x>520)
						p1.move(-110, 0);
					if (player2 && p2.getPosition().x > 520)
						p2.move(-110, 0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					
					update(p1, p2, circles, player1, player2);
					if (check_win(p1, circles))
					{
						isRunning = false;
						p1win = true;
					}
						if (check_win(p2, circles))
					{
						isRunning = false;
						p2win = true;
					}
					if (game_finished(p1win, p2win,circles))
					{
						isRunning = false;
						tie = true;
					}
				}
			}

			win.clear(sf::Color::Black);
		
			{

				win.draw(board);


				for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
				{

					win.draw(circles[i][j]);
				}
				if (player1)
				{
					win.draw(p1);
					win.draw(playerone);
				}
				if (player2)
				{
					win.draw(p2);
					win.draw(playertwo);
				}
				win.draw(Instructions);
			}

		
			if (p1win)
			{
				win.draw(p1wins);
			}
			if (p2win)
			{
				win.draw(p2wins);
			}
			if (tie)
				win.draw(nowinner);
			win.display();

		}
	}
}


void drawBoard(sf::RectangleShape & board)     //funtion to set board
{
	board.setFillColor(sf::Color::Blue);
	board.setSize(sf::Vector2f(800, 680));
	board.setPosition(sf::Vector2f(500, 150));
}

void drawcircles(sf::CircleShape circles[][cols])         //function to set circles
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			circles[i][j].setRadius(r);
			circles[i][j].setFillColor(sf::Color::White);
			circles[i][j].setPosition((i*r*2.2 + 10.0f)+510 , (j*r*2.2 + 10.0f)+40 );
			//circles[i][j].setOutlineColor(sf::Color::Red);                //testing to see if tiles exist and to help with positioning and movement
		//	circles[i][j].setOutlineThickness(1);
		}
	}
	
		for (int j = 0; j < cols; j++)
		{
			
			circles[j][0].setFillColor(sf::Color::Black);
			
		}
	


}


void drawPlayers(sf::CircleShape &p1, sf::CircleShape &p2)   //function to set players
{
	p1.setFillColor(sf::Color::Green);
	p1.setRadius(r);
	p1.setPosition(sf::Vector2f(520,50));

	p2.setFillColor(sf::Color::Red);
	p2.setRadius(r);
	p2.setPosition(sf::Vector2f(520,50));
}

void update(sf::CircleShape p1, sf::CircleShape p2, sf::CircleShape circles[][cols],bool &player1,bool &player2)  //update function. Called when down is pressed
{


	if (player1)
	{
		if (p1.getPosition().x == circles[0][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[0][i].getFillColor() == sf::Color::White)
			{
				circles[0][i].setFillColor(p1.getFillColor());
				break;
			}
		}
		else	if (p1.getPosition().x == circles[1][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[1][i].getFillColor() == sf::Color::White)
			{
				circles[1][i].setFillColor(p1.getFillColor());
				break;
			}
		}
		else	if (p1.getPosition().x == circles[2][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[2][i].getFillColor() == sf::Color::White)
			{
				circles[2][i].setFillColor(p1.getFillColor());
				break;
			}
		}
		else	if (p1.getPosition().x == circles[3][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[3][i].getFillColor() == sf::Color::White)
			{
				circles[3][i].setFillColor(p1.getFillColor());
				break;
			}
		}
		else	if (p1.getPosition().x == circles[4][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[4][i].getFillColor() == sf::Color::White)
			{
				circles[4][i].setFillColor(p1.getFillColor());
				break;
			}
		}
		else if (p1.getPosition().x == circles[5][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[5][i].getFillColor() == sf::Color::White)
			{
				circles[5][i].setFillColor(p1.getFillColor());
				break;
			}
		}

		else		if (p1.getPosition().x == circles[6][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[6][i].getFillColor() == sf::Color::White)
			{
				circles[6][i].setFillColor(p1.getFillColor());
				break;
			}
		}
		
	}
	else if (player2)
	{
		if (p2.getPosition().x == circles[0][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[0][i].getFillColor() == sf::Color::White)
			{
				circles[0][i].setFillColor(p2.getFillColor());
				break;
			}
		}
		else	if (p2.getPosition().x == circles[1][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[1][i].getFillColor() == sf::Color::White)
			{
				circles[1][i].setFillColor(p2.getFillColor());
				break;
			}
		}
		else	if (p2.getPosition().x == circles[2][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[2][i].getFillColor() == sf::Color::White)
			{
				circles[2][i].setFillColor(p2.getFillColor());
				break;
			}
		}
		else	if (p2.getPosition().x == circles[3][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[3][i].getFillColor() == sf::Color::White)
			{
				circles[3][i].setFillColor(p2.getFillColor());
				break;
			}
		}
		else	if (p2.getPosition().x == circles[4][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[4][i].getFillColor() == sf::Color::White)
			{
				circles[4][i].setFillColor(p2.getFillColor());
				break;
			}
		}
		else	if (p2.getPosition().x == circles[5][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[5][i].getFillColor() == sf::Color::White)
			{
				circles[5][i].setFillColor(p2.getFillColor());
				break;
			}
		}

		else	if (p2.getPosition().x == circles[6][0].getPosition().x)
		{
			for (int i = cols; i >0; i--)
			if (circles[6][i].getFillColor() == sf::Color::White)
			{
				circles[6][i].setFillColor(p2.getFillColor());
				break;
			}
		}
	}

	


	if (player1)
	{

		player1 = false;
		player2 = true;
	}
	else if (player2)
	{

		player2 = false;
		player1 = true;
	}
}


bool check_win(sf::CircleShape x,sf::CircleShape circles[][cols])        //checks who won or not
{
	int direction = 1;
	bool f=false;
	int i = 0, j = 0;
	sf::Vector2f pos = x.getPosition();

	for (int a = 0; a < rows;a++)
	
	if (circles[a][0].getPosition() == pos)
	{
		i = a;
		
	}
	int c = 0;
	int q=0 ;
	
	for (q = 0; q < cols;q++)
	{
		
		if (circles[i][q].getFillColor() == x.getFillColor())
		{
			j = q;
			break;
		}
		
	}
	
	if (checker(x, circles, i, j, direction, c))     //directions: 1 horizontal, 2 vertical, 3 diagonal, 4 reverse diagonal
		return true;
	else return false;
}






bool checker(sf::CircleShape x, sf::CircleShape circles[][cols], int i, int j, int direction, int c)  //checks around position 
{
	c = 0;
	int n, m;
	if (direction == 1)
	{
		for (n=j; x.getFillColor() == circles[i][n].getFillColor(); n++)
			c++;
		for (n=j; x.getFillColor() == circles[i][n].getFillColor(); n--)
			c++;
		if (c > wincount)
			return true;
		else return checker(x, circles, i, j, direction + 1, c);
	
	}
	
	
	if (direction == 2)
	{
		for (m=i; x.getFillColor() == circles[m][j].getFillColor(); m++)
			c++;
		for (m=i; x.getFillColor() == circles[m][j].getFillColor(); m--)
			c++;
		if (c > wincount)
			return true;
		else return checker(x, circles, i, j, direction + 1, c);
	}
	

	
	if (direction == 3)
	{
		for (n=i,m=j; x.getFillColor() == circles[n][m].getFillColor(); n++,m++)
			c++;
		for (n=i,m=j; x.getFillColor() == circles[n][m].getFillColor(); n--,m--)
			c++;
		if (c > wincount)
			return true;
		else return checker(x, circles, i, j, direction + 1, c);
	}
	
	if (direction == 4)
	{
		for (n=i, m=j; x.getFillColor() == circles[n][m].getFillColor(); n++, m--)
			c++;
		for (n=i,m=j; x.getFillColor() == circles[n][m].getFillColor(); n--, m++)
			c++;
		if (c > wincount)
			return true;
		else return false;
	}
	
}




bool game_finished(bool p1, bool p2,sf::CircleShape circles[][cols])    //checks to see if no one won
{
	bool f = false;
	for (int i = 0; i < rows;i++)
	for (int j = 0; j < cols; j++)
	{
		if (circles[i][j].getFillColor() == sf::Color::White)
			f = true;
	}
	if (f==false && p1 == false && p2 == false)
	{
		return true;
	}
	else return false;
}

void initialize_restart(bool &isRunning,bool &player1,bool &player2,bool &p1win,bool &p2win, bool &tie)  //initializes restart
{
	isRunning = true;
	player1 = true;
	player2 = false;
	p1win = false;
	p2win = false;
	tie = false;
}