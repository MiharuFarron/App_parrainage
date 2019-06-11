#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->boutonEgal,SIGNAL(clicked()),this, SLOT(calculerOperation()));


}

void Dialog::calculerOperation(){
//    int nbr1 = ui->nombre1->value();
    int nb = 5;
    QString nbretostring = QString(4);

    ui->resultat->setText(nbretostring);

}

Dialog::~Dialog()
{
    delete ui;
}
