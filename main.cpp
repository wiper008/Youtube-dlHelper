#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <ctype.h>

using namespace std;

//Funckija za posodobitev youtube-dl
void posodobitev()
{
    stringstream posodobitev_string;
    posodobitev_string << "youtube-dl.exe -U"; //String za posodobitev
    system(posodobitev_string.str().c_str());
}

//Funkcija za pretvorbo prenesenega videa
void pretvorba_prenesenega() //Trenutno v testni fazi
{
    system("cls");
    system("cd output & dir /b *.mp4"); //Prikaže vse .mp4 datoteke v mapi output.
    cout << "\n" << endl;
    cout << "Vnesite naslov videa:" << endl;
    cout << "OPOMBA: Naslov vnesi v narekovajih drugace ne bo delovalo!" << endl;
    cout << "Naslov: ";
    string naslov_videa ="";
    cin.ignore();
    getline(cin, naslov_videa); //Uporaba getline namesto navadnega cin da zazna celoten vnos z narekovaji.
    izbris_prompt:
    int izbris;
    cout << "\nZelite obdrzati .mp4 datoteko? (1[da]/0[ne]): ";
    cin >> izbris;
    stringstream premakni_mp4, konvertiraj, premakni_mp3, zbris_mp4, obdrzi_mp4;
    cout << naslov_videa;
    premakni_mp4 << "cd output & move " << naslov_videa << " .."; //Premakne .mp4 datoteko iz output mape v mapo kjer se nahaja program
    konvertiraj << "ffmpeg -i " << naslov_videa << " -c:v lib264 " << naslov_videa << ".mp3"; //Pretvori premaknjeno .mp4 datoteko
    premakni_mp3  << "move " << naslov_videa << ".mp3 output"; //Premakne novo .mp3 datoteko katera je bila pretvorjena v mapo output
    zbris_mp4 << "del /q /f " << naslov_videa; //Zbrise .mp4 datoteko po pretvorbi
    obdrzi_mp4 << "move " << naslov_videa << " output"; //Premakne .mp4 datoteko v primeru da je ne zelimo izbrisati

    if(izbris == 1)
    {
        system(premakni_mp4.str().c_str());
        system(konvertiraj.str().c_str());
        system(premakni_mp3.str().c_str());
        system(obdrzi_mp4.str().c_str());
    }
    else if (izbris == 0)
    {
        system(premakni_mp4.str().c_str());
        system(konvertiraj.str().c_str());
        system(premakni_mp3.str().c_str());
        system(zbris_mp4.str().c_str());
    }
    else
        goto izbris_prompt;

}

//Funkcija poslje informacije za formate
void format_info()
{
    cout << "\"Hitri\" formati:" << endl;
    cout << "1. mp3" << endl;
    cout << "2. aac" << endl;
    cout << "3. wav" << endl;
    cout << "4. vorbis" << endl;
    cout << "5. opus" << endl;
    cout << "6. m4a" << endl;
    cout << "Vpisi stevilko za hitri format ali vpisi ime formata v katerega zelis pretvoriti" << endl;
}

//Funkcija za pretvorbo stevilk hitrih formatov(int) v string
string formati(string vhodni_format)
{
    //Program preveri ce je uporabnik uporabil številko za hitri format, ce ne uporabi vpisan format
    if(vhodni_format == "1")
    {
        vhodni_format = "mp3";
    }
    else if(vhodni_format == "2")
    {
        vhodni_format = "aac";
    }
    else if(vhodni_format == "3")
    {
        vhodni_format = "wav";
    }
    else if(vhodni_format == "4")
    {
        vhodni_format = "vorbis";
    }
    else if(vhodni_format == "5")
    {
        vhodni_format = "opus";
    }
    else if(vhodni_format == "6")
    {
        vhodni_format = "m4a";
    }
    return vhodni_format;
}

//Funkcija samo za prenos videa
void prenos_videa()
{
    string url;
    system("cls");
    cout << "URL Naslov videa: ";
    cin >> url;
    stringstream vnos_podatkov;
    vnos_podatkov << "youtube-dl.exe --output /output/%(title)s.%(ext)s --console-title --keep-video --ignore-errors -f best " << url; //String za prenos videa v mp4 formatu
    system(vnos_podatkov.str().c_str());
}

//Funkcija za prenos in pretvorbo videa
void prenos_in_pretvorba()
{
    pip_vnos:  //Zaèetek za vnosa; V primeru da uporanbik ne vpiše èesar pravilno ga vrne na zaèetek vpisa za prenos in pretvorbo
    string url, format;
    int obdrzi;
    stringstream obdrzi_datoteko_string, zbrisi_datoteko_string;
    system("cls");
    cout << "Vnesi URL videa: ";
    cin >> url;
    format_info();
    cout << "Vnesi format: ";
    cin >> format;
    format=formati(format); //Poklice funkcijo s formati in vrne string v primeru da smo vnesli stevilko.
    cout << "Zelite obdrzati izvorno datoteko? (DA [1]/NE [0]) " << endl;
    cout << "Vasa izbira: ";
    cin >> obdrzi;

    switch(obdrzi)
    {
        //Pretvori izvorno datoteko in jo obdrzi
        case 1:
        obdrzi_datoteko_string << "youtube-dl.exe --output /output/%(title)s.%(ext)s --console-title --keep-video --ignore-errors --extract-audio --audio-quality 0 --audio-format " << format << " " << url;
        system(obdrzi_datoteko_string.str().c_str());
        break;

        //Izbris izvorne datoteke po pretvorbi
        case 0:
        zbrisi_datoteko_string << "youtube-dl.exe --output /output/%(title)s.%(ext)s --console-title --ignore-errors --extract-audio --audio-quality 0 --audio-format " << format << " " << url;
        system(zbrisi_datoteko_string.str().c_str());
        break;

        //Povrne uporabnika nazaj na vpis v primeru, da ni vpisal 1(da) ali 0 (ne).
        default:
            goto pip_vnos;
    }


}

int main()
{
    int zacetna_izbira;
    //Program nastavi pisavo na zeleno  barvo in prikaze zagonsko sporocilo
    system("color A");
    cout << "Dobrodosli v uporabniskem vmesniku za Youtube-dl \n" << endl;
    cout << "Program Youtube-dl in ffmpeg sta tuja programa in pripadata svojim lastnikom" << endl;
    cout << "Ta program je samo uporabniski vmesnik kateri je namenjen lazji uporabi teh programov" << endl;

    //Program pocaka uporabnika, da pritisne tipko za nadaljevanje, pobirse sporocilo in nastavi pisavo nazaj na belo
    system("pause");
    system("cls");
    system("color F");

    //Zacetna izbira
    zacetek:
    cout << "1. Posodobitev" << endl;
    cout << "2. Prenos videa" << endl;
    cout << "3. Prenos in pretvorba videa" << endl;
    cout << "4. Pretvorba prenesenega videa v mp3" << endl;
    cout << "0. Izhod iz programa" << endl;
    cout << "Vasa izbira: ";
    cin >> zacetna_izbira;

    //Switch za zacetno izbiro glede na uporabnikov vnos
    switch(zacetna_izbira)
    {

    //Izhod iz programa
    case 0:
        return 0;
        break;

    //Program gre na funkcijo za posodobitev
    case 1:
        posodobitev();
        break;

    //Funkcija za samo prenos videa
    case 2:
        prenos_videa();
        break;

    //Funkcija za prenos in pretvorbo videa
    case 3:
        prenos_in_pretvorba();
        break;

    //Funkcija za pretvorbo prenesenih videev
    case 4:
        pretvorba_prenesenega();
        break;

    //Vrne uporabnika na zacetek ce je vnesel napacno stevilko
    default:
        goto zacetek;
        cout << "Napacna izbira! Poskusi znova." << endl;
        system("pause");
        system("cls");
        break;
    }

    //Se izvede po pretvorbi, prenosu ali kater koli drugi funkciji
    nadaljevanje:
    int nadaljuj;
    system("cls");
    cout << "Zelite nadaljevati? (DA [1]/NE [0]): " ;
    cin >> nadaljuj;

    switch(nadaljuj)
    {
        //Vrne se na zacetek za izbiro funkcij
        case 1:
            goto zacetek;
            break;

        //Konca program
        case 0:
            return 0;
            break;

        //Pozove uporabnika za ponoven vnos v primeru napacnega vnosa.
        default:
            cout << "Napacen vnos! Poskusi znova.";
            break;
    }

}
