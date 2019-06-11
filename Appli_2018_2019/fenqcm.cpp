#include "fenqcm.h"
#include "json.hpp"
#include "fenprincipale.h"


using json = nlohmann::json;
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

static string path_questions_json = QDir::currentPath().toStdString()+"/questions.json";

static std::ifstream ifs(path_questions_json);
static json j = json::parse(ifs);
static json score;

FenQCM::FenQCM(QString qcm_fichier, QWidget *parent = 0) : QDialog(parent)
{
    std::cout << "marssouss lol" << qcm_fichier.toStdString() << std::endl;

    categoryCreator();
    // Initialisation du layout principale
    QVBoxLayout *layout_principal = new QVBoxLayout;
    QGridLayout *layout_bouton = new QGridLayout;

    // Initialisatiopn des Widgets
    string numero_question_str = std::to_string(numero_question);
    string question = j[numero_question_str]["question"];
    QString q_question = QString::fromStdString(question);
    QString q_rep1 = QString::fromStdString(j[numero_question_str]["1"]["text"]);
    QString q_rep2 = QString::fromStdString(j[numero_question_str]["2"]["text"]);
    QString q_rep3 = QString::fromStdString(j[numero_question_str]["3"]["text"]);
    QString q_rep4 = QString::fromStdString(j[numero_question_str]["4"]["text"]);

    // La progress bar qui indique le numero de la question
    laprogressbar = new QProgressBar(this);
    laprogressbar->setMaximum(j.size());
    laprogressbar->setValue(numero_question);

    la_question = new QLabel(q_question);
    rep1 = new QPushButton();
    rep2 = new QPushButton();
    rep3 = new QPushButton();
    rep4 = new QPushButton();

    rep1lbl = new QLabel(q_rep1,rep1);
    rep2lbl = new QLabel(q_rep2,rep2);
    rep3lbl = new QLabel(q_rep3,rep3);
    rep4lbl = new QLabel(q_rep4,rep4);

    // Customisation des boutons :

    la_question->setFixedHeight(400);
    la_question->setAlignment(Qt::AlignVCenter);
    la_question->setStyleSheet("padding-left: 5px; padding-right: 5px;"
                               "padding-top: 100px; padding-bottom: 100px;");

    rep1->setFixedSize(400,200);
    rep2->setFixedSize(400,200);
    rep3->setFixedSize(400,200);
    rep4->setFixedSize(400,200);

    la_question->setWordWrap(true);
    rep1lbl->setWordWrap(true);
    rep2lbl->setWordWrap(true);
    rep3lbl->setWordWrap(true);
    rep4lbl->setWordWrap(true);
    rep1lbl->setAlignment(Qt::AlignCenter);
    rep2lbl->setAlignment(Qt::AlignCenter);
    rep3lbl->setAlignment(Qt::AlignCenter);
    rep4lbl->setAlignment(Qt::AlignCenter);

    //Font-size
    QFont font = la_question->font();
    font.setPointSize(40);
    font.setBold(true);
    la_question->setFont(font);

    auto layoutbtn1 = new QHBoxLayout(rep1);
    auto layoutbtn2 = new QHBoxLayout(rep2);
    auto layoutbtn3 = new QHBoxLayout(rep3);
    auto layoutbtn4 = new QHBoxLayout(rep4);
    layoutbtn1->addWidget(rep1lbl,0,Qt::AlignCenter);
    layoutbtn2->addWidget(rep2lbl,0,Qt::AlignCenter);
    layoutbtn3->addWidget(rep3lbl,0,Qt::AlignCenter);
    layoutbtn4->addWidget(rep4lbl,0,Qt::AlignCenter);

    // Remplissage du Layout principale



    layout_bouton->addWidget(rep1,0,0);
    layout_bouton->addWidget(rep2,0,1);
    layout_bouton->addWidget(rep3,1,0);
    layout_bouton->addWidget(rep4,1,1);


    // Dernières étape : ajout du Layout dans la fenêtre
    layout_principal->addWidget(laprogressbar, 0, Qt::AlignRight);
    layout_principal->addWidget(la_question);
    layout_principal->addLayout(layout_bouton);
    this->setLayout(layout_principal);


    // Paramètres de la page
    //this->setFixedSize(500,250); // Changer les dimensions de la page
    this->setWindowTitle("AMBB QCM");

    connect(rep1, SIGNAL(clicked()),this,SLOT(actionReponse1()));
    connect(rep2, SIGNAL(clicked()),this,SLOT(actionReponse2()));
    connect(rep3, SIGNAL(clicked()),this,SLOT(actionReponse3()));
    connect(rep4, SIGNAL(clicked()),this,SLOT(actionReponse4()));

}

void FenQCM::categoryCreator(){    
    for (int index= 1; index < j.size(); index++)
    {
        for (int Questindex=1; Questindex < j[std::to_string(index)].size(); Questindex++)
        {
        std::string category = j[std::to_string(index)][std::to_string(Questindex)]["category"];
        if (score["note"][category].is_null())
        {
            score["note"][category] = 0;
        }
      }
   }
    score["sequence"]={0};
}

void FenQCM::actionReponse1(){
    answer =1 ;
    calculScore();
    questionSuivante();
}

void FenQCM::actionReponse2(){
    answer =2 ;
    calculScore();
    questionSuivante();
}

void FenQCM::actionReponse3(){
    answer =3 ;
    calculScore();
    questionSuivante();
}

void FenQCM::actionReponse4(){
    answer =4 ;
    calculScore();
    questionSuivante();
}

void FenQCM::calculScore(){
    std::string category = j[std::to_string(numero_question)][std::to_string(answer)]["category"];
    std::string valuetext = j[std::to_string(numero_question)][std::to_string(answer)]["value"];
    int currentscore = score["note"][category];
    score["note"][category]= currentscore + stoi(valuetext);
    vector<int> tempvector = score["sequence"].get<std::vector<int>>();
    tempvector.push_back(answer);
    score["sequence"]=tempvector;
}


void FenQCM::questionSuivante(){
    numero_question++;

    if(numero_question > j.size()){
        la_question->setText("Fin des questions !");
        rep1lbl->setText("");
        rep2lbl->setText("");
        rep3lbl->setText("");
        rep4lbl->setText("");
        la_question->repaint();
        rep1->setEnabled(false);
        rep2->setEnabled(false);
        rep3->setEnabled(false);
        rep4->setEnabled(false);
        sleep_for(seconds(3));
       close();
    }
    else{
        laprogressbar->setValue(numero_question);
        la_question->setText(QString::fromStdString(j[std::to_string(numero_question)]["question"]));
        rep1lbl->setText(QString::fromStdString(j[std::to_string(numero_question)]["1"]["text"]));
        rep2lbl->setText(QString::fromStdString(j[std::to_string(numero_question)]["2"]["text"]));
        rep3lbl->setText(QString::fromStdString(j[std::to_string(numero_question)]["3"]["text"]));
        rep4lbl->setText(QString::fromStdString(j[std::to_string(numero_question)]["4"]["text"]));
    }

}


