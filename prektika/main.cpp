#include <iostream>
#include <vector>
using namespace std;
struct Cart
{
    int nCart;
    int nBook;
};
class Human
{
protected:
    int number;
public:
    Human(int number);
    void virtual creatCart(int nViewer) = 0;
    bool virtual transferBook(int nBook) = 0;
};
class Viewer:public Human
{
private:
    int nBook;
public:
    Viewer(int nViewer);
    void creatCart(int nViewer);
    bool transferBook(int nBook);
};
class Admin:public Human
{
private:
    static vector<Cart> carts;
public:
    Admin(int number);
    void creatCart(int nViewer);
    bool transferBook(int nBook);
    Cart returnCart(int nViewer);
    void putCart(Cart cart);
};

class Librian:public Human
{
private:
    Cart cart;
    static vector<int> book;
public:
    Librian(int number);
    void creatCart(int nViewer);
    void getCart(int nViewer);
    bool transferBook(int nBook);
    friend bool Admin::transferBook(int nBoo);
};
vector<int> Librian::book;
vector<Cart> Admin::carts;
vector <Viewer> view;
vector <Librian> libr;
vector <Admin> admins;
int main()
{
    for (int i = 0; i<5;i++)//5  читателей
        view.push_back(Viewer(rand()%100));
    for (int i = 0; i<3; i++)// 3 bibliotekar
        libr.push_back(Librian(rand()%100));
    for (int i = 0; i<2; i++)
        admins.push_back(Admin(rand()%100));
    for (int i = 0; i<view.size();i++)//5  новых карточек
        view[i].creatCart(1);
    for (int i = 0; i<12; i++)//BOOK
        admins[rand()%admins.size()].transferBook(10+rand()%90);
    for (int i=0; i<5; i++) //Берут книги
        view[i].transferBook(10+rand()%90);
    for (int i=0; i<5; i++) //Забирают книги
        view[i].transferBook(0);
    for (int i = 0; i<12; i++)//попытка списать книги
        admins[rand()%admins.size()].transferBook(10+rand()%90);
    
};
Human::Human(int number)
{
    this->number = number;
}
//Viewer
Viewer::Viewer(int number):Human(number)
{
    nBook = 0;
};
void Viewer::creatCart(int nViewer)
{
    cout<<"Читатель №"<<number<<" хочу зарегистрироваться"<<endl;
    libr[rand()%libr.size()].creatCart(number);
    
};
bool Viewer::transferBook(int Book)
{
    int randlibr =rand()%libr.size();
    cout<<"Читатель №"<<number<<" Я пришел к Вам"<<endl;
    libr[randlibr].getCart(number);
    if (nBook == 0)
    {
        cout<<"Читатель №"<<number<<" хочу получить новую книгу "<<Book<<endl;
        if (libr[randlibr].transferBook(Book) == false)
        {
            cout<<"Читатель №"<<number<<"  Я огорчен"<<endl;
        };
        
    } else
    {
        libr[randlibr].transferBook(nBook);
        cout<<"Читатель №"<<number<<" Хочу сдать книгу "<<nBook<<endl;
    }
    return true;
}
//Librian
Librian::Librian(int number):Human(number)
{
};
void Librian::creatCart(int nViewer)
{
    cout<<"Библиотекарь № "<<number<<" Нужно завести карточку №"<<nViewer<<endl;
    admins[rand()%admins.size()].creatCart(nViewer);
    
}
bool Librian::transferBook(int nBook)
{
    if (cart.nBook == 0)
    {
        cout<<"Библиотекарь № "<<number<<" Ищу нужную книгу"<<endl;
        for (int i = 0; i < book.size(); i++ )
        {
            if (book[i] == nBook)
            {
                book.erase(book.begin()+i);
                cart.nBook = nBook;
                admins[rand()%admins.size()].putCart(cart);
                cout<<"Библиотекарь № "<<number<<" Книгу выдала"<<endl;
                return true;
            }
        }
        cout<<"Библиотекарь № "<<number<<" Книги нет"<<endl;
        return false;
    } else
    {
        cout<<"Библиотекарь № "<<number<<" Книгу забрала"<<endl;
        book.push_back(nBook);
        cart.nBook = 0;
        admins[rand()%admins.size()].putCart(cart);
        return true;
    }
}
void Librian::getCart(int nViewer)
{
    cout<<"Библиотекарь № "<<number<<" Нужна крточка"<<endl;
    cart = admins[rand()%admins.size()].returnCart(nViewer);
    cout<<"Библиотекарь № "<<number<<" Карточку получила № карты "<<cart.nCart<<endl;
}
//Admin
Admin::Admin(int number):Human(number){};
void Admin::creatCart(int nViewer)
{
    carts.push_back(Cart());
    carts.back().nBook = 0;
    carts.back().nCart = nViewer;
    cout<<"Администратор №"<<number<<" Карточку создал"<<endl;
};
bool Admin::transferBook(int nBook)
{
    for(int i =0; i<Librian::book.size(); i++)
    {
        if (nBook == Librian::book[i])
        {
            Librian::book.erase(Librian::book.begin()+i);
            cout<<"Администратор №"<<number<<" Книгу №"<<nBook<<" списал"<<endl;
            return false;
        }
    }
    Librian::book.push_back(nBook);
    cout<<"Администратор №"<<number<<" Книгу №"<<nBook<<" получил"<<endl;
    return true;
};
Cart Admin::returnCart(int nViewer)
{
    Cart cart;
    for (int i =0; i<carts.size(); i++)
    {
        if (carts[i].nCart == nViewer)
        {
            cart = carts[i];
            carts.erase(carts.begin()+i);
            cout<<"Администратор №"<<number<<" Держи"<<endl;
            return cart;
        }
    }
    return cart;
};
void Admin::putCart(Cart cart)
{
    carts.push_back(cart);
};
