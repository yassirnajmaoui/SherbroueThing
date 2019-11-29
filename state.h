#ifndef STATE_H
#define STATE_H
#include <headers.h>
#include <QString>

class State
{
public:
    State();
    void setVote(int pos, int vote);
    void setFond(int pos, double fond);
    int getVote(int pos);
    double getFond(int pos);
    QString getName(int pos);
    char getShortcut(int pos);
    void updateTotal();
private:
    int votes[NUMBER_OF_FACULTES];
    double fonds[NUMBER_OF_FACULTES];
    const QString names[NUMBER_OF_FACULTES] = {"Sciences","Génie","Musique","Éducation","Droit","Gestion","Médecine","Total"};
    const char shortcuts[NUMBER_OF_FACULTES-1] = {'S','G','U','E','D','A','M'};
};

#endif // STATE_H
