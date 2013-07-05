#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "LaTeXcode.h"

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
      stringTable[i][j] = ui->tableau->model()->data(
            ui->tableau->model()->index(i,j)).toString();
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
  ui->codeEdit->append("% \\usepackage{tikz, tikzrput}"); // tikzrput can be
                                                          // grab at
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

