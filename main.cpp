#include <iostream>//DAMIAN JÊDRYSIAK
#include <cstdlib>
#include <time.h>
#include <string>
#include <list>
#include <windows.h>
#include <conio.h>

using namespace std;
class pomieszczenie;


void menu()
{
    cout << "1. Ustaw temperature" << endl;
    cout << "2. Wlacz  system ogrzewania" << endl;
    cout << "3. Wylacz caly system" << endl;
    cout << "4. MENU" << endl;
}
class czujnik //OBSERWATOR
{
    public:
        virtual void mierz(pomieszczenie*) = 0;
};

class pomieszczenie //OBSERWOWANY
{
    private:
        list<czujnik*> czujniki;
    public:
        virtual ~pomieszczenie(){}
        virtual void dodaj(czujnik* m)
        {
            czujniki.push_back(m);
        }
        virtual void usun(czujnik* m)
        {
            czujniki.remove(m);
        }
        virtual void powiadom()
        {
            list<czujnik*>::iterator it = czujniki.begin();
            for( ; it != czujniki.end(); it++)
                {
                    (*it)->mierz(this);
                }

        }
};

class Pokoj : public pomieszczenie //OBSERWOWANY KONKRETNY
{
    public:
        float act_temp;
        float set_temp;
        int moc;

        Pokoj(){act_temp=14.0;set_temp=19.0;}//konstruktor domyœlne wartoœci poczatkowe

        void konfiguruj()
        {
            //
            cin >> set_temp;
            cout << "Optymalna temperatura zostala nastawiona"<<endl;
        }

        void ustaw_moc()
        {
            if(set_temp-act_temp>=10)
            {
                moc=100.0;
            }
            else
            {
                moc=(set_temp-act_temp)*10;
            }
        }

        void ustaw_temp(int moc)
        {
            act_temp+=(moc/50.0)-((rand()%20)-5)/10;
        }

};

class Wyswietlacz
{
     public:
        virtual void wyswietlaj(pomieszczenie* sypialnia)
        {
            Pokoj *m = dynamic_cast<Pokoj *>(sypialnia);
            cout << "Aktualna Temperatura w sypialni: " << m->act_temp<<"[*C]"<< endl;
            cout << "Nastawiona temperatura w sypialni: " << m-> set_temp<<"[*C]"<< endl;
            cout << "Moc grzania w sypialni: " << m-> moc <<"[%]"<< endl;
            Sleep(2000);
            system("cls");

        }
};

class Termometr: public czujnik //OBSERWATOR KONKRETNY
{
     public:
        virtual void mierz(pomieszczenie* sypialnia)
        {
            Pokoj *m = dynamic_cast<Pokoj *>(sypialnia);
            Wyswietlacz *e = new Wyswietlacz();
            if(m->set_temp - m->act_temp>1)
             {
                e->wyswietlaj(sypialnia);
                m->ustaw_moc();
                m->ustaw_temp(m->moc);
                this->mierz(sypialnia);
                Sleep(200);
             }

        }

};
/////////////
int main()
{
    Pokoj *sypialnia = new Pokoj();
    Pokoj *m = dynamic_cast<Pokoj *>(sypialnia);
    czujnik *temp = new Termometr();
    sypialnia->dodaj(temp);

    cout << "System ogrzewania" << endl;
    menu();

    int choose_menu = 0;

    while(choose_menu != 3)
        {
            cin >> choose_menu;
            switch(choose_menu)
            {
                case 1:
                    cout << "Podaj optmalna temperature w sypialni: " << endl;
                    m->konfiguruj();
                    system("cls");
                    menu();
                    break;
                case 2:
                    cout << "Wlaczono system ogrzewania!" << endl;
                   // e->wyswietlaj(sypialnia);
                    sypialnia->ustaw_moc();
                    sypialnia->powiadom();
                    //sypialnia->wyswietlaj();
                    Sleep(200);
                    system("cls");
                    cout << "Optymalna temperatura zostala osiagnieta!" << endl<<endl<<endl;
                    menu();
                    break;
                case 3:
                    cout << "System zostal wylaczony!"<< endl;
                    break;
                case 4:
                    system("cls");
                    menu();
                    break;
            }
        }
    delete sypialnia;//zwalnanie pamieci
    delete temp;
    return 0;

}


