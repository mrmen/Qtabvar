#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PScode.h"
#include "LaTeXcode.h"

#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <QTableView>
#include <QStandardItem>
#include <QTextEdit>
#include <QShortcut>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <QTextCodec>

#ifdef __APPLE__
// to access bundle
#include "CoreFoundation/CoreFoundation.h"
// don't forget to add -framework CoreFoundation inside Makefile
#endif


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
//   connect widgets
// from an old version
//  connect(ui->updateTabular,SIGNAL(clicked()), this, SLOT(updateTabular()));
  connect(ui->getCode, SIGNAL(clicked()), this, SLOT(getCodeAsList()));
  connect(ui->getPS, SIGNAL(clicked()), this, SLOT(getCodeAsPS()));
  connect(ui->effacerButton, SIGNAL(clicked()), this, SLOT(removeCode()));
  connect(ui->exporterButton, SIGNAL(clicked()), this, SLOT(exportPS()));
  connect(ui->actionAdapter_le_tableau, SIGNAL(triggered()), this,
          SLOT(updateTabular()));
  connect(ui->actionG_n_rer_le_tableau, SIGNAL(triggered()), this,
          SLOT(getCodeAsList()));
  connect(ui->actionCr_dits, SIGNAL(triggered()), this, SLOT(showCredits()));
  connect(ui->hauteurSpinbox, SIGNAL(valueChanged(int)), this,
          SLOT(updateTabular()));
  ui->hauteurSpinbox->setMinimum(1);
  connect(ui->longueurSpinbox, SIGNAL(valueChanged(int)), this,
          SLOT(updateTabular()));
  ui->longueurSpinbox->setMinimum(1);

  // create one-one tabular
  ui->hauteurSpinbox->setValue(1);
  ui->longueurSpinbox->setValue(1);
  // update ui to have the value
  updateTabular();
}


/*
 * updateTabular
 * To update current tabular on the screen
 */
void MainWindow::updateTabular(){

  /*
   * Get the old value used in your tabular
   */
  int oldLongueur = ui->tableau->horizontalHeader()->count();// get lengtgh
  int oldHauteur = ui->tableau->verticalHeader()->count(); // get height

  /*
   * store old value into string tabular
   */
  QString stringTable[oldHauteur][oldLongueur]; // create string tabular to get
                                                // current printed values
  for(int i=0; i<oldHauteur; i++){
    for(int j=0; j<oldLongueur; j++){
      // do the stuff tu get 
      // you must use mode to acces data
      stringTable[i][j] = ui->tableau->model()->data(
            ui->tableau->model()->index(i,j)).toString();
    }
  }

  /*
   * Get the current value update into the spinbox
   */
  int hauteur = ui->hauteurSpinbox->value();
  int longueur = ui->longueurSpinbox->value();

  /*
   * Fill a new table with a model
   */
  QStandardItemModel* tableModel = new QStandardItemModel();
  for(int i=0; i<hauteur; i++){
    for(int j=0; j<longueur; j++){
      tableModel->setItem(i, j, new QStandardItem(""));
    }
  }
  ui->tableau->setModel(tableModel); // add model to tableau item

  /*
   * Fill you new tabular with old value if posible
   */
  for(int i=0; i<std::min(oldHauteur, hauteur); i++){
    for(int j=0; j<std::min(oldLongueur, longueur); j++){
      // use model to setData
      ui->tableau->model()->setData(
            ui->tableau->model()->index(i,j),stringTable[i][j]);
    }
  }

}


/*
 * removeCode
 * Clear all code printed in code tab
 */
void MainWindow::removeCode(){
  // remove the code
  ui->codeEdit->clear();
}




/******************************************************************************/

/*
 * exportPS
 * export ps code into a file on Desktop
 */

void MainWindow::exportPS(){
    QString fichier = QFileDialog::getSaveFileName(this,
                                                   "Exporter PostScript",
                                                   QString(),
                                                   "Fichier PostScript (*.ps)");
    QFile file(fichier);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    file.write(ui->codeEdit->toPlainText().toAscii());
    file.close();
    // wait for file close
    // this works for unix and linux
#ifdef __APPLE__
    while(file.handle()!=-1)
        1;
    // add nice PATH for ps2eps works
    // should be done differently...
    execl("export", "PATH=$PATH:/usr/local/bin:/usr/texbin","ps2eps", "-f", fichier.toStdString().c_str(), "&", NULL);
#elif __linux__
    while(file.handle()!=-1)
        1;
    // add nice PATH for ps2eps works
    // should be done differently...
    QString cmd = "/usr/bin/ps2eps -f " + fichier + " &";
    //    execl("/usr/bin/ps2eps", "-f", fichier.toStdString().c_str(), "&", NULL);
    system(cmd.toStdString().c_str());
#endif
}

/*
 * doReplaceStuff
 * convert visual code to LaTeX code
 */
QString MainWindow::doReplaceStuff(QString line){
  QString temp = line;
  // adde what you want here
  temp = temp.replace("\\", "\\de");
  temp = temp.replace("/","\\cr");
  temp = temp.replace("|0","\\zr");
  temp = temp.replace("||", "\\vline\\:\\vline");
  temp = temp.replace("|","\\vline");
  temp = temp.replace("inf","\\infty");
  // return new string converted
  return temp;
}


/*
 * showCredits
 * show some infos and changelog (TODO)
 */
void MainWindow::showCredits(){
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QMessageBox::about(this,
  "À Propos",
  "QTabvar Version 0.99\n"\
  "Application permettant de réaliser des tableaux de signes/variations.\n"\
  "\n"\
  "Documentation disponible sur http://qtabvar.mrmen.fr (TODO)\n"\
		       );
}

MainWindow::~MainWindow()
{
  delete ui;
}
