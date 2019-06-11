#include "fenprincipale.h"
#include "dialog.h"
#include <iostream>
#include <fstream>
#include "fenqcm.h"


FenPrincipale::FenPrincipale() : QWidget()
{
    // Ouverture de la fenêtre de sélection du question.json
    fichier = QFileDialog::getOpenFileName(this,"Sélectionner le questionnaire (.json)", "", ".json (*.json)");

    QVBoxLayout *layoutPrincipale = new QVBoxLayout;
    QHBoxLayout *layoutFenetre = new QHBoxLayout;

    //Formulaire de base
    m_nom = new QLineEdit;
    m_prenom = new QLineEdit;
    m_nom->setMinimumSize(300,20) ;
    QFormLayout *info_etudiant = new QFormLayout;
    info_etudiant->addRow("Nom : ",m_nom);
    info_etudiant->addRow("Prenom : ",m_prenom);

    // Position de l'affiche à droite
    label_affiche = new QLabel;
    QPixmap affiche("affiche_neon.png") ;

    // taille image = 1748*2480
    QPixmap  affiche_scale = affiche.scaled(438,620);
    label_affiche->setPixmap(affiche_scale);;

        //Combobox
    type_etudiant = new QComboBox;
    type_etudiant->addItem("Choisir un parcours :");
    type_etudiant->addItem("M1");
    type_etudiant->addItem("M2");

    QPushButton *demarrer = new QPushButton("Démarrer", this);
    demarrer->setStyleSheet("padding-left: 5px; padding-right: 5px;"
                            "padding-top: 100px; padding-bottom: 100px;");


    //Remplissage du layout principale

    layoutPrincipale->setSpacing(20);
    layoutPrincipale->setContentsMargins(50, 50, 50, 50);
    layoutPrincipale -> addLayout(info_etudiant);
    layoutPrincipale -> addWidget(type_etudiant);
    layoutPrincipale -> addWidget(demarrer);

    layoutFenetre->addLayout(layoutPrincipale);
    layoutFenetre->addWidget(label_affiche);

    // Paramètres de la page
    this->setLayout(layoutFenetre);
    this->setWindowTitle("AMBB Application Parrainage");
    this->setWindowIcon(QIcon("biologo.png"));

    connect(demarrer,SIGNAL(clicked(bool)),this, SLOT(Debut_QCM()));

}

void FenPrincipale::Debut_QCM()
{
    if(m_nom->text().isEmpty() || m_prenom->text().isEmpty() || type_etudiant->currentIndex() == 0){
        QMessageBox::critical(this,"Erreur formulaire", "Vous devez remplire le formulaire en entier");
    }
    else{
        FenQCM *fen_qcm = new FenQCM(fichier,this);
        nom = m_nom->text().toStdString();
        prenom = m_prenom->text().toStdString();
        niveau = type_etudiant->currentText().toStdString();
        //fen_qcm->qcm_fichier = "marssouss";
        fen_qcm->exec();
        fen_qcm->score["prenom"]=prenom;
        fen_qcm->score["nom"]=nom;
        fen_qcm->score["niveau"]=niveau;
        writeCSV(fen_qcm,fen_qcm->score);
        m_nom->clear();
        m_prenom->clear();
    }
}

int FenPrincipale::writeCSV(FenQCM *fen_qcm, json json_object){
    string niveau_fichier;
    if(json_object["niveau"]=="M1"){
        niveau_fichier="M1.csv";
    }
    else{
        niveau_fichier="M2.csv";
    }

    ofstream file;
    file.open (niveau_fichier, std::ofstream::out | std::ofstream::app);
    file << json_object["prenom"] << ";";
    file << json_object["nom"] << ";";
    /*for (json::iterator it = fen_qcm->score["note"].begin(); it != fen_qcm->score["note"].end(); it++) {
      //std::cout << it.key() << " : " << it.value() << "\n";
        if(it != fen_qcm->score["note"].end()){
            file << it.value() << ";";
        }

    }*/
    vector<int> sequence = fen_qcm->score["sequence"];

    for(std::size_t i=0; i<sequence.size(); ++i){
        file<< sequence[i] <<";";
    }

    file << "\n";
    file.close();

    return 0;
}
