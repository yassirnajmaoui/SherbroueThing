#ifndef StMainWindow_H
#define StMainWindow_H
#include "faculteviewer.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLayout>
#include <QDebug>
#include <QSignalMapper>
#include "state.h"


class StMainWindow : public QMainWindow
{
Q_OBJECT
public:
    StMainWindow(QWidget* parent = nullptr);
    ~StMainWindow();
public slots:
    void addFond(int pos);
    void addVote(int pos);
private:
    State mainState;
    QWidget* centreWidget;
    QVBoxLayout* vbox;
    FaculteViewer* v1;
    QPushButton* cliqueIci;
    QMenu* fileMenu;
    QMenu* votesMenu;
    QMenu* fondsMenu;
    QAction* openAct;
    QAction* saveAct;
    QAction* exitAct;
    QAction* addFondAct[NUMBER_OF_FACULTES-1];
    QAction* addVoteAct[NUMBER_OF_FACULTES-1];
    QSignalMapper* signalMapperFonds;
    QSignalMapper* signalMapperVotes;
private:
    void createMenus();
    void createActions();
    void openFile();
    void saveFile();
    void exitWin();
    void editContent();
};



#endif
