#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "PScode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#ifdef __linux__
#define PATH "."
#endif


#ifdef __APPLE__
// to access bundle
#include "CoreFoundation/CoreFoundation.h"
// don't forget to add -framework CoreFoundation inside Makefile
#endif
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#endif


/******************************************************************************/

/*
 * getCodeAsList
 * export tabular as PS code
 */
void MainWindow::getCodeAsPS(){
/*
   * Clear code Tab
   */
  removeCode();
  if (ui->variationBox->checkState())
    PSVariation();
  else
    PSSigne();
}


void MainWindow::PSSigne(){

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
   * Create the PS code
   */

    // tableauPrd
  //assume last line is P(x) = 4 chars and max char is 4
    int maxFactorChar = 0;
    for(int i=hauteur-1; i>=0; i--){
        maxFactorChar = std::max(stringTable[i][0].length(),maxFactorChar);
    }
    QString tableauPrd = "[";
    for(int i=hauteur-1; i>=0; i--){
        tableauPrd = tableauPrd + "(";
        QString currentPrd = stringTable[i][0];
        int lack = maxFactorChar +1 - currentPrd.length();
        if (lack >= 0){
            currentPrd = " " + currentPrd;
            for(int l=0; l<lack-1; l++)
                currentPrd = currentPrd + " ";
        }
        else
            std::cout << "Attention Produit trop long : revoir à la main " <<
                         currentPrd.toStdString() << std::endl;
        tableauPrd = tableauPrd + currentPrd + ")";
    }
    tableauPrd = tableauPrd + "]";

    // tableauRac
    QString tableauRac = "[";
    QString tableauDep = "[";
    int maxRac=0;
    for(int i=2;i<longueur;i=i+2){
        tableauRac = tableauRac + "(" + stringTable[0][i] + ")";
        maxRac = std::max(maxRac, stringTable[0][i].length());
        tableauDep = tableauDep + "(" +
            QString::number(stringTable[0][i].length()) + ")";
        //+ stringTable[0][i].length()
    }
    tableauRac = tableauRac + "]";
    tableauDep = tableauDep + "]";


    // tableauSgn
    QString tableauSgn ="[";
    for(int i=hauteur-1; i>=0; i--){
        tableauSgn = tableauSgn + "[";
        for(int j=longueur-1; j>=0;j=j-2){
            QString car;
            if (stringTable[i][j] == ""){
                // cas vide donc ligne racine
                car = " ";
            }
            else{
                car = stringTable[i][j];
            }
            if (maxRac == 1)
              tableauSgn = tableauSgn + "( " + car + " )";
            else
              tableauSgn = tableauSgn + "(" + car + ")";
        }
        tableauSgn = tableauSgn + "]";
    }
    tableauSgn = tableauSgn + "]";


    // tableau0
    QString tableau0 = "[";
    for(int i=hauteur-1; i>0; i--){
        tableau0 = tableau0 + "[";
        for(int j=2;j<longueur; j=j+2){
            if (stringTable[i][j] == QString::fromStdString("|0"))
                    tableau0 = tableau0 + "(1)";
            else{
                    if (stringTable[i][j] == QString::fromStdString("||"))
                        tableau0 = tableau0 + "(2)";
                    else
                        tableau0 = tableau0 + "(0)";
            }
        }
        tableau0 = tableau0 + "(0)";
        tableau0 = tableau0 + "]";
    }
    tableau0 = tableau0 + "]";

    // ugly hack : ajoute 2 si racine de longueur 1
    QString nbCharLine;
    if (maxRac != 1)
        // + 6 because of infinity
      nbCharLine = QString::number(maxFactorChar+(maxRac+1)
                                           *longueur/2+1+6);
    else
        // + 6 because of infinity
      nbCharLine = QString::number(maxFactorChar+(maxRac+1+2)
                                           *longueur/2+1+6);

    ui->codeEdit->append("%!");
    ui->codeEdit->append("/tableauPrd" + tableauPrd + " def");
    ui->codeEdit->append("/tableauSgn" + tableauSgn + " def");
    ui->codeEdit->append("/tableauRac" + tableauRac + " def");
    ui->codeEdit->append("/tableau0" + tableau0 + " def");
    ui->codeEdit->append("/tableauDep" + tableauDep + " def");
    ui->codeEdit->append("/nbCharLine " + nbCharLine + " def");
    ui->codeEdit->append("/maxRac " + QString::number(maxRac) + " def");


    #ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path,
                                              PATH_MAX))
        {
            std::cout << "It's not normal !" << std::endl;
        }
        CFRelease(resourcesURL);
        chdir(path);
        std::string skelfile = "/skel.ps";
    #elif __linux__
        char path[PATH_MAX] = PATH;
        std::string skelfile = "/skel.ps";
    #elif _WIN32
         char path[2]=".";
         std::string skelfile = "\\skel.ps";
    #endif



    std::string stringPath;
    std::stringstream ss;
    ss << path;
    ss << skelfile;
    ss >> stringPath;

    // md5sum : 3f4889468acbd1a3d58a0ebff4244303  skel.ps
    std::ifstream skel(stringPath.c_str());
    std::string line;
    QString Qline;
    while (std::getline(skel, line)){
        Qline = Qline.fromStdString(line);
        ui->codeEdit->append(Qline);
    }

}





/*
 * PSVariation
 *  generate postscript code for var. tab
 *
 */

void MainWindow::PSVariation(){
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
   * Create the PS code
   */

  /*
   * Meme chose que pour le tableau de signe
   */

    // tableauPrd
  //assume last line is P(x) = 4 chars and max char is 4
    int maxFactorChar = 0;
    for(int i=hauteur-1; i>=0; i--){
        maxFactorChar = std::max(stringTable[i][0].length(),maxFactorChar);
    }
    QString tableauPrd = "[";
    for(int i=hauteur-1; i>=0; i--){
        tableauPrd = tableauPrd + "(";
        QString currentPrd = stringTable[i][0];
        int lack = maxFactorChar +1 - currentPrd.length();
        if (lack >= 0){
            currentPrd = " " + currentPrd;
            for(int l=0; l<lack-1; l++)
                currentPrd = currentPrd + " ";
        }
        else
            std::cout << "Attention Produit trop long : revoir à la main " <<
                         currentPrd.toStdString() << std::endl;
        tableauPrd = tableauPrd + currentPrd + ")";
    }
    tableauPrd = tableauPrd + "]";


    /*
     * On prend tout dans la premiere ligne
     */
    // tableauRac
    QString tableauRac = "[";
    QString tableauDep = "[";
    int maxRac=0;
    for(int i=1;i<longueur;i=i+2){
        tableauRac = tableauRac + "(" + stringTable[0][i] + ")";
        maxRac = std::max(maxRac, stringTable[0][i].length());
        tableauDep = tableauDep + "(" +
            QString::number(stringTable[0][i].length()) + ")";
        //+ stringTable[0][i].length()
    }
    tableauRac = tableauRac + "]";
    tableauDep = tableauDep + "]";


    // tableauVal
    // do tableauDiscont
    // use tableauVal to avoid useless work

    int max[longueur-1];
    for(int j=1; j<longueur;j++){
        max[j] = 0;
        for(int i=0; i<hauteur;i++){
            QString car = stringTable[i][j];
            if ((car == "+i") || (car == "-i") || (car == "||")){
                max[j] = 3;
                break;
            }
            else
                max[j] = std::max(max[j], stringTable[i][j].length());
          }
    }
    for(int j=1; j<longueur;j++){
        for(int i=0; i<hauteur;i++){
            QString car = stringTable[i][j];
            int n = max[j] - car.length();
            if ((car != "+i") && (car != "-i") && (car != "||")){
                if (n%2==1){
                    car = " "+car;
                    n--;
                }
                for(int k=0;k<n/2;k++)
                    car = " " + car + " ";
                stringTable[i][j] = car;

                }
        }
    }

    /*
     * should do the fucking stuff
     * with all column
     */
    QString tableauDiscont = "[";
    QString tableauVal ="[";
    for(int i=hauteur-1; i>=0; i--){
        tableauVal = tableauVal + "[";
        tableauDiscont = tableauDiscont + "[";
        for(int j=longueur-1; j>=0;j=j-2){
            QString car;
            if (stringTable[i][j] == ""){
                car = " ";
            }
            else{
                car = stringTable[i][j];
            }
            // tableauDiscont
            if (car=="||"){
                tableauDiscont = tableauDiscont + "(2)";
            }
            else{
                tableauDiscont = tableauDiscont + "(0)";
            }
            tableauVal = tableauVal + "(" + car + ")";
        }
        tableauVal = tableauVal + "]";
        tableauDiscont = tableauDiscont + "]";
    }
    tableauDiscont = tableauDiscont + "]";
    tableauVal = tableauVal + "]";

    // tableauVar
    QString tableauVar = "[";
    for(int j=2;j<longueur-1;j=j+2){
        QString car = stringTable[2][j];
        if (car == "/")
          tableauVar = tableauVar + "(c)";
        if (car == "\\")
          tableauVar = tableauVar + "(d)";
      }
    tableauVar = tableauVar + "]";


    // tableauDiscontVal
    QString tableauDiscontVal;
    QString tableauDiscontValZ;
    QString futurCar = "";
    for(int j=2;j<longueur-3;j=j+2){
        QString car = stringTable[2][j];
        if (j!=longueur-3){
            futurCar = stringTable[2][j+2];
        }
        if (car == "/")
          tableauDiscontVal = tableauDiscontVal + "(c";
        if (car == "\\")
          tableauDiscontVal = tableauDiscontVal + "(d";
        if (futurCar == "/")
          tableauDiscontVal = tableauDiscontVal + "c)";
        if (futurCar == "\\")
          tableauDiscontVal = tableauDiscontVal + "d)";
        tableauDiscontValZ = "(0)";
    }
    QString tableauTemp = tableauDiscontVal;
    tableauDiscontVal = "[";
    for (int i=0;i<hauteur;i++){
        if ((i==0) || (i==2)){
            tableauDiscontVal = tableauDiscontVal + "[(0)"+tableauTemp+"(0)]";
        }else{
            tableauDiscontVal = tableauDiscontVal + "[(0)"+tableauDiscontValZ+"(0)]";
        }
    }
    tableauDiscontVal = tableauDiscontVal + "]";

    // sgn
    QString sgn = QString::number(longueur/2);

    ui->codeEdit->append("%!");
    ui->codeEdit->append("/tableauPrd" + tableauPrd + " def");
    ui->codeEdit->append("/tableauVal" + tableauVal + " def");
    ui->codeEdit->append("/tableauDiscont" + tableauDiscont + " def");
    ui->codeEdit->append("/tableauDiscontVal" + tableauDiscontVal + " def");
    ui->codeEdit->append("/tableauVar" + tableauVar + " def");
    ui->codeEdit->append("/sgn " + sgn + " def");

    #ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path,
                                              PATH_MAX))
        {
            std::cout << "It's not normal !" << std::endl;
        }
        CFRelease(resourcesURL);
        chdir(path);
        std::string skelfile = "/skel-variation.ps";
    #elif __linux__
        char path[PATH_MAX] = PATH;
        std::string skelfile = "/skel-variation.ps";
    #elif _WIN32
     char path[2]=".";
     std::string skelfile = "\\skel-variation.ps";
    #endif

    std::string stringPath;
    std::stringstream ss;
    ss << path;
    ss << skelfile;
    ss >> stringPath;

    // md5sum : 3f4889468acbd1a3d58a0ebff4244303  skel.ps
    std::ifstream skel(stringPath.c_str());
    std::string line;
    QString Qline;
    while (std::getline(skel, line)){
        Qline = Qline.fromStdString(line);
        ui->codeEdit->append(Qline);
    }

}
