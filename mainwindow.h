#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void updateTabular();
    void getCodeAsList();
    void getCodeAsPS();
    void PSSigne();
    void PSVariation();
    void exportPS();
    void removeCode();
    void showCredits();
    QString doReplaceStuff(QString);
};

#endif // MAINWINDOW_H
