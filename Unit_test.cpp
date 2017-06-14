#include <iostream>//DAMIAN JÊDRYSIAK
#include <cstdlib>
#include <time.h>
#include <string>
#include <list>
#include <windows.h>
#include <conio.h>
using namespace std;

class Pokoj
{
    public:
        float act_temp;
        float set_temp;
        int moc;

        Pokoj(){act_temp=14.0;}//konstruktor domyœlne wartoœci poczatkowe
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
int main()
{
    cout << "Test ma za zadanie sprawdzenie czy ustawianie mocy grzania, " << endl;
    cout << "w zaleznosci od temperatury aktualnej oraz  temperatury nastawionej dziala, prawidlowo." << endl;

    cout << "Podaj optmalna temperature w sypialni: " << endl;
    Pokoj Sypialnia;
    cin >> Sypialnia.set_temp;

    while(1)
    {
        Sypialnia.ustaw_moc();
        Sypialnia.ustaw_temp(Sypialnia.moc);
        Sleep(2000);
        cout << "Aktualna Temperatura w sypialni: " << Sypialnia.act_temp<<"[*C]"<< endl;
        cout << "Nastawiona temperatura w sypialni: " <<Sypialnia.set_temp<<"[*C]"<< endl;
        cout << "Moc grzania w sypialni: " << Sypialnia.moc <<"[%]"<< endl<<endl;


    }
}
