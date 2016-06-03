//
//  RandomWriter.cpp
//  
//
//  Created by Akshina on 5/23/16.
//
//

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string processLine(string line, int lineNum)
{
    string word = "";
    
    for(int i = 0; i < line.length(); i++)
    {
        char c =  line.at(i);
        c = toupper(c);
        word = word + c;
    }
    return word;
}

string findAllSeeds(string input, string seeds)
{
    int seedSize = seeds.length();
    string options = "";
    
    for(int i = 0; i<input.length() - seedSize ;i++)
    {
        if(input.substr(i,seedSize)==seeds) //check if we have a seed
        {
            if(i==input.length()-seedSize-1) //check if we are at the end of the input and will need to loop back
            {
                options += input.substr(0,1);
            }
            else
            {
                options += input.substr(i+seedSize+1,1);
            }
        }
    }
    return options;
}

string pickALetter(string choices)
{
    int ran = ( (rand() + time(0)) % (choices.length()) );
    return choices.substr(ran,1);
}

int main()
{
    int seedLength = 7;
    
    string line;
    int lineNum = 1;
    ifstream myfile ("words.txt");
    string inputText;
    string outputText;
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            inputText += processLine(line, lineNum);
            lineNum++;
        }
        myfile.close();
    }
    else{ cout << "Unable to open file";}
    
    int r = (int)( (rand() + time(0)) % (inputText.length() - seedLength - 1) );
    string seed = inputText.substr(r,seedLength);
    
    
    for(int i = 0; i<200; i++)
    {
        string all = findAllSeeds(inputText, seed);
        string temp = pickALetter(all);
        outputText += temp;
        seed = seed.substr(1,seed.length()-1) + pickALetter(all);
    }
    
    cout << outputText;
    
    return 0;
    
}
