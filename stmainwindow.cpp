#include "stmainwindow.h"

// Autre fenetre
// Signe de dollard
// Display: Pas de petites fleches

// Make a function that updates the values from what the counter gives you
StMainWindow::StMainWindow(QWidget* parent) : QMainWindow(parent)
{
    centreWidget = new QWidget(this);
    vbox = new QVBoxLayout();

    // Table
    v1 = new FaculteViewer(centreWidget, &mainState);

    vbox->addWidget(v1);
    centreWidget->setLayout(vbox);


    createActions();
    createMenus();

    centreWidget->setStyleSheet(".QWidget{background-color:black;} QInputDialog {background-color: white;color:black;}");
    this->setCentralWidget(centreWidget);

}
StMainWindow::~StMainWindow()
{

}

void StMainWindow::createActions()
{
    openAct = new QAction(tr("&Ouvrir"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Ouvrir un nouveau fichier"));
    connect(openAct, &QAction::triggered, this, &StMainWindow::openFile);

    saveAct = new QAction(tr("&Enregistrer"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Enregistrer les valeurs courantes"));
    connect(saveAct, &QAction::triggered, this, &StMainWindow::saveFile);

    exitAct = new QAction(tr("&Quitter"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Quitter l\'application"));
    connect(exitAct, &QAction::triggered, this, &StMainWindow::exitWin);

    signalMapperFonds = new QSignalMapper (this) ;
    signalMapperVotes = new QSignalMapper (this) ;
    for(int i=0;i<NUMBER_OF_FACULTES-1;i++)
    {
        addFondAct[i] = new QAction(tr("&Ajouter 1$ à ") + mainState.getName(i), this);
        addFondAct[i]->setShortcut(QKeySequence(mainState.getShortcut(i))); // Todo: have a real shortcut
        addVoteAct[i] = new QAction(tr("&Ajouter un vote à ") + mainState.getName(i), this);
        addVoteAct[i]->setShortcut(QKeySequence(QString("Shift+")+QString(mainState.getShortcut(i)))); // Todo: have a real shortcut
        connect(addFondAct[i], SIGNAL(triggered()), signalMapperFonds, SLOT(map()));
        connect(addVoteAct[i], SIGNAL(triggered()), signalMapperVotes, SLOT(map()));
        signalMapperFonds->setMapping(addFondAct[i],i);
        signalMapperVotes->setMapping(addVoteAct[i],i);
    }
    connect (signalMapperFonds, SIGNAL(mapped(int)), this, SLOT(addFond(int))) ;
    connect (signalMapperVotes, SIGNAL(mapped(int)), this, SLOT(addVote(int))) ;
}
void StMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("Fichier");
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);
    votesMenu = menuBar()->addMenu("Votes");
    fondsMenu = menuBar()->addMenu("Financement");

    for(int i=0;i<NUMBER_OF_FACULTES-1;i++)
    {
        fondsMenu->addAction(addFondAct[i]);
        votesMenu->addAction(addVoteAct[i]);
    }
}
void StMainWindow::openFile()
{
    qDebug() << "Open\n";

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Ouverture"), "",
        tr("All Files (*)"));
    if (fileName.isEmpty())
            return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Impossible d\'ouvrir ce fichier"),
                file.errorString());
            return;
        }
        QTextStream in(&file);
        int i=0;
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            qDebug() << line;
            bool correctFond,correctVote = true;
            mainState.setFond(i,(QString(fields.at(1))).toDouble(&correctFond));
            mainState.setVote(i,(QString(fields.at(2))).toInt(&correctFond));
            if(!correctFond || !correctVote)
            {
                QMessageBox::information(this, tr("Erreur de parsing"), tr("Le fichier specifié n'a pas pu être lu correctement"));
                return;
            }
            i++;
        }

        file.close();
    }

    v1->updateValues();
}
void StMainWindow::saveFile()
{
    qDebug() << "Save\n";

    QString strState = QString("");
    for(int i=0;i<NUMBER_OF_FACULTES-1;i++)
    {
        strState.append(mainState.getName(i));
        strState.append(",");
        strState.append(QString::number(mainState.getFond(i)));
        strState.append(",");
        strState.append(QString::number(mainState.getVote(i)));
        strState.append("\n");
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Enregistrement"), "",
        tr("All Files (*)"));
    if (fileName.isEmpty())
            return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Impossible d\'ouvrir ce fichier"),
                file.errorString());
            return;
        }
        QTextStream out(&file);
        out << strState;
    }
}


void StMainWindow::exitWin()
{
    qDebug() << "Exit\n";
    QApplication::exit();
}
void StMainWindow::editContent()
{
    qDebug() << "Edit\n";
}
void StMainWindow::addFond(int pos)
{
    qDebug() << "Adding financement: " << this->mainState.getName(pos);
    mainState.setFond(pos,mainState.getFond(pos)+1.00);
    v1->updateValues();
}
void StMainWindow::addVote(int pos)
{
    qDebug() << "Adding vote: " << this->mainState.getName(pos);
    mainState.setVote(pos,mainState.getVote(pos)+1);
    v1->updateValues();
}
