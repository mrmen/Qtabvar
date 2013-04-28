#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableView>
#include <QStandardItem>
#include <QTextEdit>
#include <QShortcut>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
//   connect widgets
  connect(ui->updateTabular,SIGNAL(clicked()), this, SLOT(updateTabular()));
  connect(ui->getCode, SIGNAL(clicked()), this, SLOT(getCodeAsList()));
  connect(ui->effacerButton, SIGNAL(clicked()), this, SLOT(removeCode()));
  connect(ui->actionAdapter_le_tableau, SIGNAL(triggered()), this, SLOT(updateTabular()));
  connect(ui->actionG_n_rer_le_tableau, SIGNAL(triggered()), this, SLOT(getCodeAsList()));
  connect(ui->hauteurSpinbox, SIGNAL(valueChanged(int)), this, SLOT(updateTabular()));
  ui->hauteurSpinbox->setMinimum(1);
  connect(ui->longueurSpinbox, SIGNAL(valueChanged(int)), this, SLOT(updateTabular()));
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
  QString stringTable[oldHauteur][oldLongueur]; // create string tabular to get current printed values
  for(int i=0; i<oldHauteur; i++){
    for(int j=0; j<oldLongueur; j++){
      // do the stuff tu get 
      // you must use mode to acces data
      stringTable[i][j] = ui->tableau->model()->data(ui->tableau->model()->index(i,j)).toString();
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
      ui->tableau->model()->setData(ui->tableau->model()->index(i,j),stringTable[i][j]);
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


/*
 * getCodeAsList
 * export tabular as LaTeX code
 */
void MainWindow::getCodeAsList(){
//  int variations = ui->variationBox->checkState();
  /*
   * Clear code Tab
   */
  removeCode();

  /*
   * get the current dimension of the tabular
   */
  int hauteur = ui->hauteurSpinbox->value();
  int longueur = ui->longueurSpinbox->value();

  
  /*
   * get the whole code
   */
  QString stringTable[hauteur][longueur]; // create string table to get code 
  for(int i=0; i<hauteur; i++){
    for(int j=0; j<longueur; j++){
      // use model to access data
      stringTable[i][j] = ui->tableau->model()->data(ui->tableau->model()->index(i,j)).toString();
    }
  }
  
  /*
   * Create the LaTeX code
   */
  QString line = "\\begin{array}{|c|";
  // how many column are needed
  for(int j=0; j<longueur-1; j++){
    line = line+"c";
  }
  line+="|}"; 
  // add commented LaTeX preamble
  ui->codeEdit->append("% \\usepackage{tikz, tikzrput}"); // tikzrput can be grab at
  // http://altermundus.com/pages/tkz/tikzrput/index.html
  // 0 scratch LaTeX code
  ui->codeEdit->append("% \\newcommand{\\zr}{\\vline");
  ui->codeEdit->append("%     \\begin{tikzpicture}%");
  ui->codeEdit->append("%     \\rput[B](-0.5\\arrayrulewidth,0){$0$};%");
  ui->codeEdit->append("% \\end{tikzpicture}}");
  // increase arrow LaTeX code
  ui->codeEdit->append("% \\newcommand{\\cr}{");
  ui->codeEdit->append("%     \\begin{tikzpicture}%");
  ui->codeEdit->append("%     \\draw[->] (-0.5,-0.5) -- (0.5,0.5)%");
  ui->codeEdit->append("% \\end{tikzpicture}}");
  // decrease arrow LaTeX code
  ui->codeEdit->append("% \\newcommand{\\de}{");
  ui->codeEdit->append("%     \\begin{tikzpicture}%");
  ui->codeEdit->append("%     \\draw[->] (-0.5,0.5) -- (0.5,-0.5)%");
  ui->codeEdit->append("% \\end{tikzpicture}}");
  // add empty line
  ui->codeEdit->append("");
  
  // fill the code widget
  ui->codeEdit->append(line);
  ui->codeEdit->append("\\hline"); // add hline at the end of line
  for(int i=0; i<hauteur; i++){
    QString line = "";
    for(int j=0; j<longueur; j++){
      // call doReplaceStuff to obtain nice LaTeX code
      line = line+doReplaceStuff(stringTable[i][j]);
      // test if it's last column and add & or 
      if (j!=longueur-1){
        line = line + " & ";
      }
      else{
        line = line + " \\\\";
      }
    }
    // paste it
    ui->codeEdit->append(line);
    // paste \hline
    ui->codeEdit->append("\\hline");
  }
  //close array and paste
  line = "\\end{array}";
  ui->codeEdit->append(line);
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



MainWindow::~MainWindow()
{
  delete ui;
}
