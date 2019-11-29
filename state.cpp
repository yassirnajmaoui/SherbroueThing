#include "state.h"

State::State()
{
    for(int i=0;i<NUMBER_OF_FACULTES;i++)
    {
        this->fonds[i]=0;
        this->votes[i]=0;
    }
}
int State::getVote(int pos)
{
    if(pos<0||pos>=NUMBER_OF_FACULTES)
        return 0;
    return this->votes[pos];
}
QString State::getName(int pos)
{
    if(pos<0||pos>=NUMBER_OF_FACULTES)
        return 0;
    return this->names[pos];
}
double State::getFond(int pos)
{
    if(pos<0||pos>=NUMBER_OF_FACULTES)
        return 0;
    return this->fonds[pos];
}
void State::setVote(int pos, int vote)
{
    if(pos<0||pos>=NUMBER_OF_FACULTES)
        return;
    this->votes[pos] = vote;
}
void State::setFond(int pos, double fond)
{
    if(pos<0||pos>=NUMBER_OF_FACULTES)
        return;
    this->fonds[pos] = fond;
}
void State::updateTotal()
{
    int     totalVotes=0;
    double  totalFonds=0;
    for(int i=0;i<NUMBER_OF_FACULTES-1;i++)
    {
        totalFonds += this->fonds[i];
        totalVotes += this->votes[i];
    }
    this->fonds[NUMBER_OF_FACULTES-1] = totalFonds;
    this->votes[NUMBER_OF_FACULTES-1] = totalVotes;
}
char State::getShortcut(int pos)
{
    if(pos<0||pos>=NUMBER_OF_FACULTES-1)
        return 0;
    return this->shortcuts[pos];
}

