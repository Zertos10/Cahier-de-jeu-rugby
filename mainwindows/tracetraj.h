#ifndef TRACETRAJ_H
#define TRACETRAJ_H

#include <QWidget>
#include "trajectoire_entite.h"
#include <QPainter>
#include <mainwindow.h>
#include <QList>



class TraceTraj
{
public:
    TraceTraj();
    static void tempTraj(QPainter *painter,trajectoire_entite trajTemp);
    static void tracerTraj(QPainter *painter,QList<trajectoire_entite> listTraj,int colors= Marche);
    static QPen colorTraj(int colors);
    static void paintPoints(QPainter *painterPoint,QPoint dep, QPoint arrv);

private:


};

#endif // TRACETRAJ_H
