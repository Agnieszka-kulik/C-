#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string temat,nick;
    string tresc[5];
    string odpA[5],odpB[5],odpC[5],odpD[5];
    string poprawna[5];
    string odpowiedz;
    int pt=0;

    int nr_lini=1;
    string linia;
    int nr_pytania=0;


    fstream plik;
    plik.open("quiz.txt", ios::in);
    if (plik.good()==false)
    {
        cout << "Plik nie istnieje";
        exit(0);
    }
    while(getline(plik,linia))
    {
      switch(nr_lini)
      {
          case 1:temat=linia;       break;
          case 2:nick=linia;        break;
          case 3:tresc[nr_pytania]=linia;    break;
          case 4:odpA[nr_pytania]=linia;     break;
          case 5:odpB[nr_pytania]=linia;     break;
          case 6:odpC[nr_pytania]=linia;     break;
          case 7:odpD[nr_pytania]=linia;     break;
          case 8:poprawna[nr_pytania]=linia; break;

      }
        if(nr_lini==8){nr_lini=2; nr_pytania++;}
        nr_lini++;
    }
        plik.close();

        cout << temat << endl << nick << endl;

       for (int i=0;i<=4; i++)
       {
        cout << endl << tresc[i]<< endl;
        cout << "A."<< odpA[i]<<endl;
        cout << "B."<< odpB[i]<<endl;
        cout << "C."<< odpC[i]<<endl;
        cout << "D."<< odpD[i]<<endl;

        cout << "Twoja odpowiedz: ";
        cin >> odpowiedz;

        transform(odpowiedz.begin(),odpowiedz.end(),odpowiedz.begin(),::tolower);

        if (odpowiedz==poprawna[i])
        {
            cout <<"Zdobywasz punkt!!!"<< endl;
            pt++;
        }
        else cout << "Nieporawny wynik: Poprawna odpowiedz: "<< poprawna[i] <<endl;

       }
       cout <<endl<< "Wynik koncowy: "<< pt <<" punktow";
    return 0;
}
