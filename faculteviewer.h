#ifndef FACULTEVIEWER_H
#define FACULTEVIEWER_H

#include "state.h"
#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include <QColor>
#include <QInputDialog>
#include <QDebug>
#include <QTabBar>

class FaculteViewer : public QTabWidget
{
    Q_OBJECT
public:
    explicit FaculteViewer(QWidget *parent = nullptr, State* st=nullptr);
    void updateValues();
signals:

public slots:
    void changeValueFond(int pos);
    void changeValueVote(int pos);
private:
    State* stateRef;
    QGridLayout* grid1;
    QGridLayout* grid2;
    QPushButton* txtAssocFonds[8];
    QPushButton* txtAssocVotes[8];
    QLabel* fondsFaculte[8];
    QLabel* votesFaculte[8];
    QWidget* fondsTab;
    QWidget* votesTab;
    QSignalMapper* signalMapperFonds;
    QSignalMapper* signalMapperVotes;
private:
    void initGrid1();
    void initGrid2();
};

#endif // FACULTEVIEWER_H
