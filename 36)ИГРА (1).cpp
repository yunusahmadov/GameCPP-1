#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<time.h>
#include<iostream>
using namespace std;
struct Cat
{
	int x;
	int y;
	bool alive;
};

void main()
{
	srand(time(0));
	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	ALLEGRO_BITMAP*player=	al_load_bitmap("images/catsmall.png");
	ALLEGRO_BITMAP* cat = al_load_bitmap("images/catbombs.png");
	ALLEGRO_BITMAP* rip = al_load_bitmap("images/ripp.png");
	ALLEGRO_COLOR background = al_map_rgb(0, 100, 100);

	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();//очередь событий
	al_register_event_source(event_queue, al_get_keyboard_event_source());//отлавливает нажатые кнопки
	al_register_event_source(event_queue, al_get_mouse_event_source());//отлавливает нажатые кнопки
	ALLEGRO_DISPLAY*display= al_create_display(1000, 1000);
	/*al_hide_mouse_cursor(display);*///скрываем курсор
	
	int playerX = 0, playerY=0;

	int catsCount = 5;
	Cat * cats = new Cat[catsCount];
	for (int i = 0; i < catsCount; i++)
	{
		cats[i].x=rand()%900;
		cats[i].y=rand()%900;
		cats[i].alive=true;
	}
	while (true)
	{
		//отрисовка
		al_clear_to_color(background);
		for (int i = 0; i < catsCount; i++)
		{
			if (cats[i].alive)
			{
				al_draw_bitmap(cat, cats[i].x, cats[i].y, 0);
			}
			else
				al_draw_bitmap(rip, cats[i].x, cats[i].y, 0);
		}
		al_draw_bitmap(player, playerX, playerY, 0);
		al_flip_display();
		//ввод пользователя
		al_wait_for_event_timed(event_queue, &event,0.01);//если через 0.01 не будет движения будет выполнятьяс логика
		/*cout<<"X:" << event.mouse.x<< "Y:"<< event.mouse.y<< endl;*/ 
		////логика
		playerX = event.mouse.x;
		playerY = event.mouse.y;
		//движение
		for (int i = 0; i < catsCount; i++)
		{
			if (cats[i].alive)
			{
				int newX = cats[i].x + rand() % 11 - 5;
				int newY = cats[i].y + rand() % 11 - 5;
				if (newX > 0 && newX < 900 && newY>0 && newY < 900)
				{
					cats[i].x = newX;
					cats[i].y = newY;
				}
			}
			
		}
		//уничтожение 
		for (int i = 0; i < catsCount; i++)
		{
			if (abs(cats[i].x - playerX)<50&&abs(cats[i].y-playerY)<50)//abs-нахождение модуля
				cats[i].alive = false;
		}
		
	}
}