#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <ctype.h>


using namespace std;

int main()
{
    string url, cont, format, selection;
    stringstream update;

    //Welcome message
    system("color A");
    cout << "Welcome to Youtube-dl helper\n\n " << endl;
    cout << "This little 'tool' was written by Aljaz Gros" << endl;
    cout << "Youtube-dl and FFmpeg belong to their respective owners and are not owned by me" << endl;
    cout << "I wrote this just to make downloading/conversion easier for windows users" << endl << endl;
    cout << "If you haven't got youtube-dl and/or FFMpeg get them now as they are required for this 'tool' to work properly" << endl;
    cout << "If you experiance any ffprobe errors please read README.txt\n\n" << endl;
    system("pause");
    system("cls");
    system("color F"); //Clears text and sets color to bright white after user presses any key


    //Selection menu
    select:
    cout << "What would you like to do?" << endl;
    cout << "1) Update" << endl;
    cout << "2) Download (no convertion)" << endl;
    cout << "2) Download & convert video" << endl;
    cout << "Your input: ";
    cin >> selection;
    string keep_file="";

    //If for selection
    if(selection == "1")
    {
        update << "youtube-dl -U";
        system(update.str().c_str());
        system("pause");
        goto select;
    }
    else if (selection == "2")
    {
        goto input_noformat;
    }
    else if (selection == "3")
    {
        goto input_format;
    }
    else
    {
        goto select;
        cout << "Wrong input!" << endl;
    }

    //URL input /w.o converting
    input_noformat:
    cout << "Input video URL: ";
    cin >> url;
    system("cls");
    goto no_format_skip;

    //URL Input /w converting
    input_format:
    cout << "Input video URL: ";
    cin >> url;
    system("cls");

    //Formats
    cout << "Here are recommended formats:"<<endl;
    cout << "best (1)" << endl;
    cout << "aac (2)" << endl;
    cout << "vorbis (3)" << endl;
    cout << "mp3 (4)" << endl;
    cout << "m4a (5)" << endl;
    cout << "opus (6)" << endl;
    cout << "wav (7)" << endl;
    cout << "Either write in number or input format name on your own" << endl;
    cout << "Input format: ";
    cin >> format;

    //Formats by number
    if(format == "1")
    {
        format="best";
    }
    else if(format == "2")
    {
        format="aac";
    }
    else if(format == "3")
    {
        format="vorbis";
    }
    else if(format == "4")
    {
        format="mp3";
    }
    else if(format == "5")
    {
        format="m4a";
    }
    else if(format == "6")
    {
        format="opus";
    }
    else if(format == "7")
    {
        format="wav";
    }

    //Keeping original file Y/N
    keepfile:
    cout << "Would you like to keep original file?(Y/N) ";
    cin >> keep_file;
    Sleep(1000);
    system("cls");

    //String for system()
    no_format_skip:
    stringstream call_line;
    if (keep_file == "Y" || keep_file == "y" )
    {
    call_line << "youtube-dl --output /output/%(title)s.%(ext)s --console-title --k --ignore-errors --extract-audio --audio-quality 0 --audio-format " << format << " " << url;
    }
    else if (keep_file == "N" || keep_file == "n")
    {
    call_line << "youtube-dl --output /output/%(title)s.%(ext)s --console-title --ignore-errors --extract-audio --audio-quality 0 --audio-format " << format << " " << url;
    }
    else if (selection == "2")
    {
    call_line << "youtube-dl --output /output/%(title)s.%(ext)s --console-title --ignore-errors --audio-quality 0 " << url;
    }
    else //If input is not Y/y or N/n
    {
    cout<<"Wrong input";
    goto keepfile;
    }
    system(call_line.str().c_str());
    contini:
    cout << endl << "To continue write Y to end write N." << endl;

    //Returns to start if User inputs Y
    cin >> cont;
    if(cont=="Y" || cont=="y")
    {
        goto select;
        system("cls");
    }
    else if(cont=="N" || cont=="n")
    {

    //Ends program if anything else is input by User than Y or y.
    cout << endl << "Ending program" << endl;
    Sleep(1000);
    return 0;
    }
    else
    {
        cout << "Invalid input." <<endl;
        goto contini;
    }
}
