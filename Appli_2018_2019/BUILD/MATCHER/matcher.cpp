#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "json.hpp"
#include "parser.hpp"

//https://github.com/AriaFallah/csv-parser
using namespace std;
using namespace aria::csv;
using json = nlohmann::json;

json M2;
json M1;

void extract_in_dic()
{
    std::ifstream m2("../M2.csv");
    CsvParser parserm2 = CsvParser(m2).delimiter(';').quote('\"').terminator('\n');
    int rownum = 0;
    for (auto &row : parserm2) //read each line of M2
    {
        int fieldnum = 0;
        M2[rownum]["valeurs"] = {};
        for (auto &field : row) //read each field of the line
        {
            if (fieldnum == 0)
            {
                M2[rownum]["nom"] = field;
            }
            if (fieldnum == 1)
            {
                M2[rownum]["prenom"] = field;
            }
            if (fieldnum > 1)
            {
                M2[rownum]["valeurs"].push_back(stoi(field));
            }
            fieldnum++;
        }
        rownum++;
    }

    //Duplicated code: We could compact the code below with the previous one but at first i wanted to separate this two procedure (one for M1 & M2)
    std::ifstream m1("../M1.csv");
    CsvParser parserm1 = CsvParser(m1).delimiter(';').quote('\"').terminator('\n');
    rownum = 0;
    for (auto &row : parserm1) //read each line of M2
    {
        int fieldnum = 0;
        M1[rownum]["valeurs"] = {};
        for (auto &field : row) //read each field of the line
        {
            if (fieldnum == 0)
            {
                M1[rownum]["nom"] = field;
            }
            if (fieldnum == 1)
            {
                M1[rownum]["prenom"] = field;
            }
            if (fieldnum > 1)
            {
                M1[rownum]["valeurs"].push_back(stoi(field));
            }
            fieldnum++;
        }
        rownum++;
    }
    //cout << M2 << endl;
    //cout << M1 << endl;
}

void match_classes()
{
    ofstream file;
    file.open("result.csv");

    for (unsigned idM2 = 0; idM2 < M2.size(); idM2++) //Take one M2
    {
        for (unsigned idM1 = 0; idM1 < M1.size(); idM1++) //And for each M1...
        {
            file << M2[idM2]["nom"] << ";";
            file << M1[idM1]["nom"] << ";";

            int personnality_ressemblance = 0;
            for (unsigned id = 0; id < M1[idM1]["valeurs"].size(); id++) //Calcul difference on each categorie
            {
                if ((int)M2[idM2]["valeurs"][id] == (int)M1[idM1]["valeurs"][id]){
                personnality_ressemblance = personnality_ressemblance + 1;
                }
            }
            file << personnality_ressemblance << ";\n"; //Write the score in the file
        }
    }

    file.close();
}

int main()
{
    extract_in_dic();
    match_classes();
    return 0;
}
