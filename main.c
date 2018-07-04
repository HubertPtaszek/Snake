#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <process.h>
#include <unistd.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int speed = 10000000;

struct list_node
{
    int data;
    int bonus;
    struct list_node *next;
} *list_pointer;

struct list_node *create_list(int data, int bonus)
{
    struct list_node *first = (struct list_node *) malloc(sizeof(struct list_node));
    if(first)
    {
        first->data = data;
        first->bonus = bonus;
        first->next = NULL;
    }
    return first;
}

struct list_node *add_at_front(struct list_node *list_pointer, struct list_node *new_node)
{
    new_node->next = list_pointer;
    return new_node;
}

struct list_node *find_spot(struct list_node *list_pointer, int data)
{
    struct list_node *previous = NULL;
    while(list_pointer && list_pointer->data<data)
    {
        previous = list_pointer;
        list_pointer = list_pointer->next;
    }
    return previous;
}

void add_in_middle_or_at_back(struct list_node *node, struct list_node *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

struct list_node *add_node(struct list_node *list_pointer, int data, int bonus)
{
    struct list_node *new_node = (struct list_node *) malloc(sizeof(struct list_node));
    if(list_pointer && new_node)
    {
        new_node->data = data;
        new_node->bonus = bonus;
        if(list_pointer->data>=data)
            return add_at_front(list_pointer, new_node);
        else
        {
            struct list_node *node= find_spot(list_pointer,data);
            add_in_middle_or_at_back(node,new_node);
        }
    }
    return list_pointer;
}

void print_list(struct list_node *list_pointer)
{
    while(list_pointer)
    {
        printf("%d ", list_pointer->bonus);
        list_pointer = list_pointer->next;
    }
    puts("");
}

int random_element(struct list_node *list_pointer)
{

    srand(time(0));
    int random = 1 + rand() % 9;
    int zzz;
    while(list_pointer)
    {
        if(random == list_pointer->data)
            zzz=list_pointer->bonus;
        list_pointer=list_pointer->next;
    }
    return zzz;
}

int length;
int bend_no;
int len;
char key;

void record();
void load();

int life;

void Delay();
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
void Display();
void Reshape(int width, int height);

struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500], food, body[30];

int main(int argc, char * argv[])
{
    char key;
    Print();
    system("cls");
    load();
    length = 5;
    head.x = 25;
    head.y = 20;
    head.direction = RIGHT;
    Boarder();
    Food();                                     //generuje wspolrzedne bonusow
    life = 3;                                   //ilosc "zyc" w grze
    bend[0] = head;
    Move();                                     //generuje poczatkowe wspolrzedne startu weza
    return 0;
}

void Move()
{
    int a;
    do
    {
        Food();
        fflush(stdin);
        len = 0;
        for(int i = 0; i < 30; i++)
        {
            body[i].x = 0;
            body[i].y = 0;
            if(i == length)
                break;
        }
        Delay(length);
        Boarder();
        if(head.direction == RIGHT)
            Right();
        else if(head.direction == LEFT)
            Left();
        else if(head.direction == DOWN)
            Down();
        else if(head.direction == UP)
            Up();
        ExitGame();
    }while(!kbhit());
    a = getch();
    if(a == 27)
    {
        system("cls");
        exit(0);
    }
    key = getch();
    if((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (key == LEFT && head.direction != RIGHT && head.direction != LEFT) || (key == UP && head.direction != DOWN && head.direction != UP) || (key == DOWN && head.direction != UP && head.direction != DOWN))
    {
        bend_no++;
        bend[bend_no] = head;
        head.direction = key;
        if(key == UP)
            head.y--;
        if(key == DOWN)
            head.y++;
        if(key == RIGHT)
            head.x++;
        if(key == LEFT)
            head.x--;
        Move();
    }
    else if(key == 27)
    {
        system("cls");
        exit(0);
    }
    else
    {
        printf("\a");
        Move();
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while(goal > clock());
}

void load()
{
    int row, col, c, q;
    gotoxy(36, 14);
    printf("loading...");
    gotoxy(30, 15);
    for(int i = 1; i <= 20; i++)
    {
        sleep(200); //symulowanie ladowania
        printf("%c", 219);
    }
}

void Delay(long double i)
{
    Score();
    for(i = 0; i <= speed; i++);
}

void ExitGame()
{
    int check = 0;
    for(int i = 4; i < length; i++) //zaczynamy z 4 bo potrzeba minimum 4 elementow
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
            check++;
        if(i==length||check!=0)
            break;
    }
    if(head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0)
    {
        life--;
        if(life > 0)
        {
            head.x = 25;
            head.y = 20;
            bend_no = 0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            puts("Utracono wsyztskie zycia...");
            puts("Nastepnym razem bedzie lepiej!!!");
            puts("\nNacisnij dowolny przycisk, aby kontynuowac...\n");
            record();
            exit(0);
        }
    }
}

void Food()
{
    if(head.x == food.x && head.y == food.y)
    {
        int bonus = random_element(list_pointer);
        if(bonus == 2)
        {
            length = length+2;
            speed = 10000000;
        }
        else if(bonus==3)
        {
            speed=1000000;
            length++;
        }
        else if(bonus==4)
        {
            speed=100000000;
            length++;
        }
        else
        {
            speed=10000000;
            length++;
        }
        time_t a;
        a = time(0);
        srand(a);
        food.x = rand() % 70;
        if(food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if(food.y <= 10)
            food.y += 11;
    }
    else if(food.x == 0) //tworzenie jedzenia na starcie
    {
        food.x = rand() % 70;
        if(food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if(food.y <= 10)
            food.y += 11;
    }
}

void Down()
{
    for(int i = 0; i <= (head.y - bend[bend_no].y) && len < length; i++)
    {
        GotoXY(head.x,head.y - i);
        puts("*");
        body[len].x = head.x;
        body[len].y = head.y - i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

void Up()
{
    for(int i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++)
    {
        GotoXY(head.x, head.y + i);
        puts("*");
        body[len].x = head.x;
        body[len].y = head.y + i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}

void Left()
{
    for(int i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++)
    {
        GotoXY((head.x+i), head.y);
        puts("*");
        body[len].x = head.x + i;
        body[len].y = head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
}

void Right()
{
    for(int i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++)
    {
        body[len].x = head.x - i;
        body[len].y = head.y;
        GotoXY(body[len].x, body[len].y);
        puts("*");
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}

void Bend()
{
    int diff;
    for(int i = bend_no; i >= 0 && len < length; i--)
    {
        if(bend[i].x == bend[i - 1].x)
        {
            diff = bend[i].y - bend[i - 1].y;
            if(diff < 0)
                for(int j = 1; j <= (-diff); j++)
                {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y + j;
                    GotoXY(body[len].x, body[len].y);
                    puts("*");
                    len++;
                    if(len == length)
                        break;
                }
            else if(diff > 0)
                for(int j = 1; j <= diff; j++)
                {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y - j;
                    GotoXY(body[len].x, body[len].y);
                    puts("*");
                    len++;
                    if(len == length)
                        break;
                }
        }
        else if(bend[i].y == bend[i - 1].y)
        {
            diff = bend[i].x - bend[i - 1].x;
            if(diff < 0)
                for(int j = 1; j <= (-diff) && len < length; j++)
                {
                    body[len].x = bend[i].x + j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    puts("*");
                    len++;
                    if(len == length)
                        break;
                }
        else if(diff > 0)
            for(int j = 1; j <= diff && len < length; j++)
            {
                body[len].x = bend[i].x - j;
                body[len].y = bend[i].y;
                GotoXY(body[len].x, body[len].y);
                puts("*");
                len++;
                if(len == length)
                    break;
            }
        }
   }
}

void Boarder()
{
    system("cls");
    GotoXY(food.x, food.y);
    printf("%c", 207);
    GotoXY(10,10);
    printf("%c", 218);
    GotoXY(70,10);
    printf("%c", 191);

    for(int i = 11; i < 70; i++) //poziom
    {
        GotoXY(i,10);
        printf("%c", 196);
        GotoXY(i,30);
        printf("%c",196);
    }

    GotoXY(10,30);
    printf("%c", 192);
    GotoXY(70,30);
    printf("%c", 217);

    for(int i = 11; i < 30; i++)  //pion
    {
        GotoXY(10,i);
        printf("%c", 179);
        GotoXY(70,i);
        printf("%c", 179);
   }
}

void Print()
{
    printf("\t\t\t\t\t    Witaj w grze 'Snake'\n");
    printf("\t\t\t\t\t        Wersja DEMO\n\n\n");
    printf("Jak grac:\n");
    printf("%c Uzywaj '->', aby poruszac sie wezem.\n", 254);
    printf("%c W grze zbieraj losowo generowane jedzenie, za kazdym razem gdy waz zje jedzenie rosnie.\n", 254);
    printf("%c W kazdej rozgrywce  posiadasz 3 ¿ycia. Zycie tracisz gdy uderzysz w sciane albo w cialo weza.\n", 254);
    printf("%c Mozesz wstrzymac gre nacisjkac dowolny przycisk. Aby kontyunowac to nacisnij ten sam przycisk jeszcze raz.\n", 254);
    printf("%c Jezeli chcesz wyjsc nacisnij 'esc'. \n", 254);
    list_pointer = create_list(1, 1);
    char c;
    puts("\nCzy chcesz bonusy? T/N");
    c = getch();
    if(c == 't' || c == 'T')
    {

        for(int i = 2; i < 4; i++)
            list_pointer=add_node(list_pointer, i, 2);
        for(int i = 4; i < 6; i++)
            list_pointer=add_node(list_pointer, i, 3);
        for(int i = 6; i < 8; i++)
            list_pointer=add_node(list_pointer, i, 4);
        for(int i = 8; i < 11; i++)
            list_pointer=add_node(list_pointer, i, 1);
    }
    else
    {
        for(int i = 2; i < 11; i++)
            list_pointer=add_node(list_pointer,i,1);
    }
   printf("\n\n\t\t\t     Nacisnij dowolny klawisz aby rozpoczac gre...");
   if(getch() == 27)
   exit(0);
}

void record()
{
    char plname[20], nplname[20], cha, c;
    int px, j;
    while(kbhit())   //czyszcenie bufforu
        getch();
    FILE *info;
    info = fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Podaj swoj nick\n");
    gets(plname);

    for(j = 0; plname[j] != '\0'; j++)
    {
        nplname[0] = toupper(plname[0]);
        if(plname[j-1] == ' ')
        {
            nplname[j] = toupper(plname[j]);
            nplname[j-1] = plname[j-1];
        }
        else
            nplname[j] = plname[j];
    }
    nplname[j] = '\0';
    fprintf(info,"Nick gracza: %s\n",nplname);
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Data rozgrywki: %s",ctime(&mytime));
    fprintf(info,"Punkty: %d\n",px=Scoreonly());
    for(int i = 0; i <= 50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    while(kbhit())      //czyszcenie bufforu
        getch();
    printf("Aby wyswietlic zapisane wyniki nacisnij 'y'\n \n");
    cha = getch();
    system("cls");
    if(cha == 'y')
    {
        info = fopen("record.txt","r");
        do
        {
           putchar(c = getc(info));
        }while(c != EOF);
    }
        fclose(info);
}

int Score()
{
    int score;
    GotoXY(20,8);
    score = length - 5;
    printf("PUNKTY: %d", (length - 5));
    score = length - 5;
    GotoXY(50,8);
    printf("Zycia: %d", life);
    return score;
}

int Scoreonly()
{
    int score = Score();
    system("cls");
    return score;
}
