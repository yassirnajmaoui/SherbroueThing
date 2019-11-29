#include "headers.h"
#include "faculteviewer.h"

FaculteViewer::FaculteViewer(QWidget *parent, State* st) : QTabWidget(parent)
{
    stateRef = st;

    fondsTab = new QWidget();
    votesTab = new QWidget();

    QFont myFont = QFont();
    myFont.setPointSize(72);

    QPalette myPalette;
    myPalette.setColor(QPalette::Window, Qt::white);
    myPalette.setColor(QPalette::WindowText, Qt::white);

    QString txtStyle = QString("background-color:black;color:rgb(160,170,71);font-size:50pt");

    // Display layout here
    for(int i=0;i<NUMBER_OF_FACULTES;++i)
    {
        txtAssocFonds[i] = new QPushButton(st->getName(i),this);
        txtAssocFonds[i]->setStyleSheet(txtStyle);
        txtAssocVotes[i] = new QPushButton(st->getName(i),this);
        txtAssocVotes[i]->setStyleSheet(txtStyle);
        fondsFaculte[i] = new QLabel(this);
        fondsFaculte[i]->setFont(myFont);
        fondsFaculte[i]->setPalette(myPalette);
        fondsFaculte[i]->setAlignment(Qt::AlignCenter);
        votesFaculte[i] = new QLabel(this);
        votesFaculte[i]->setFont(myFont);
        votesFaculte[i]->setPalette(myPalette);
        votesFaculte[i]->setAlignment(Qt::AlignCenter);
    }


    this->initGrid1();
    this->initGrid2();


    fondsTab->setLayout(grid1);
    votesTab->setLayout(grid2);

    updateValues();


    signalMapperFonds = new QSignalMapper (this) ;
    signalMapperVotes = new QSignalMapper (this) ;
    for(int i=0;i<NUMBER_OF_FACULTES-1;i++)
    {
        connect(txtAssocFonds[i], SIGNAL(clicked()), signalMapperFonds, SLOT(map()));
        connect(txtAssocVotes[i], SIGNAL(clicked()), signalMapperVotes, SLOT(map()));
        signalMapperFonds->setMapping(txtAssocFonds[i],i);
        signalMapperVotes->setMapping(txtAssocVotes[i],i);
    }
    connect (signalMapperFonds, SIGNAL(mapped(int)), this, SLOT(changeValueFond(int))) ;
    connect (signalMapperVotes, SIGNAL(mapped(int)), this, SLOT(changeValueVote(int))) ;


    this->addTab(fondsTab, "Financement");
    this->addTab(votesTab, "Votes");
    this->setDocumentMode(true);
}
void FaculteViewer::initGrid1()
{
    grid1 = new QGridLayout();
    grid1->addWidget(txtAssocFonds[0], 0, 0);
    grid1->addWidget(txtAssocFonds[1], 0, 1);
    grid1->addWidget(txtAssocFonds[2], 0, 2);
    grid1->addWidget(txtAssocFonds[3], 0, 3);
    grid1->addWidget(fondsFaculte[0], 1, 0);
    grid1->addWidget(fondsFaculte[1], 1, 1);
    grid1->addWidget(fondsFaculte[2], 1, 2);
    grid1->addWidget(fondsFaculte[3], 1, 3);
    grid1->addWidget(txtAssocFonds[4], 2, 0);
    grid1->addWidget(txtAssocFonds[5], 2, 1);
    grid1->addWidget(txtAssocFonds[6], 2, 2);
    grid1->addWidget(txtAssocFonds[7], 2, 3);
    grid1->addWidget(fondsFaculte[4], 3, 0);
    grid1->addWidget(fondsFaculte[5], 3, 1);
    grid1->addWidget(fondsFaculte[6], 3, 2);
    grid1->addWidget(fondsFaculte[7], 3, 3);
}
void FaculteViewer::initGrid2()
{
    grid2 = new QGridLayout();
    grid2->addWidget(txtAssocVotes[0], 0, 0);
    grid2->addWidget(txtAssocVotes[1], 0, 1);
    grid2->addWidget(txtAssocVotes[2], 0, 2);
    grid2->addWidget(txtAssocVotes[3], 0, 3);
    grid2->addWidget(votesFaculte[0], 1, 0);
    grid2->addWidget(votesFaculte[1], 1, 1);
    grid2->addWidget(votesFaculte[2], 1, 2);
    grid2->addWidget(votesFaculte[3], 1, 3);
    grid2->addWidget(txtAssocVotes[4], 2, 0);
    grid2->addWidget(txtAssocVotes[5], 2, 1);
    grid2->addWidget(txtAssocVotes[6], 2, 2);
    grid2->addWidget(txtAssocVotes[7], 2, 3);
    grid2->addWidget(votesFaculte[4], 3, 0);
    grid2->addWidget(votesFaculte[5], 3, 1);
    grid2->addWidget(votesFaculte[6], 3, 2);
    grid2->addWidget(votesFaculte[7], 3, 3);
}
void FaculteViewer::updateValues()
{
    stateRef->updateTotal();
    for(int i=0;i<NUMBER_OF_FACULTES-1;i++)
    {
        QString myFond = QString::number(stateRef->getFond(i)) + QString('$');
        QString myVote = QString::number(stateRef->getVote(i));
        votesFaculte[i]->setText(myVote);
        fondsFaculte[i]->setText(myFond);
    }
    fondsFaculte[7]->setText(QString::number(stateRef->getFond(7))+ QString('$'));
    votesFaculte[7]->setText(QString::number(stateRef->getVote(7)));
}
void FaculteViewer::changeValueFond(int pos)
{
    stateRef->setFond(pos,QInputDialog::getDouble(this, QString("Valeur à mettre pour le financement de ") + stateRef->getName(pos), QString("Argent"),stateRef->getFond(pos),0,2147483647,2));
    updateValues();
}
void FaculteViewer::changeValueVote(int pos)
{
    stateRef->setVote(pos,QInputDialog::getInt(this, QString("Valeur à mettre pour les votes de ") + stateRef->getName(pos), QString("Votes"),stateRef->getVote(pos),0,2147483647,2));
    updateValues();
}
