#ifndef TABLESTEAM_H
#define TABLESTEAM_H

#include <QDebug>
#include <QAbstractItemModel>
#include "sql_request/sqlrequest.h"
#include <QtWidgets>



class TablesTeam : public QTableWidget
{
    Q_OBJECT
public:

    //Constructeur de la classe
    explicit TablesTeam(QWidget *parent = nullptr);
    //Ajoute les images qui corresponds aux joueurs de chaque équipes.
    void addTeams();




    //Methode pour les caractéristique du QTableWidget
    void showTable();
    void resetTable();
    void importTable(QList<joueur> joueurs);

    static QString TablePlayerMimeType() { return QStringLiteral("image/png"); }



//Setter de la classe
    void setTeamName(QString equipe_1 , QString equipe_2);
protected:
    void startDrag(Qt::DropActions) override;


private:
    QString teamsName[2] = {"equipe 1","equipe 2"};
    QVector<QVector<int>> numJoueur ;
    //QWidget *parent = new QWidget;
    QSize *sizeIcon = new QSize(100,100);


signals:

};

#endif // TABLESTEAM_H
