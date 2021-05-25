#include "tablesteam.h"

TablesTeam::TablesTeam(QWidget *parent) : QTableWidget(parent)
{
    setRowCount(15);
    setColumnCount(2);
    setGeometry(999,0,180,180);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    setDropIndicatorShown(true);
    addTeams();
    setIconSize(*sizeIcon);
}

void TablesTeam::addTeams()
{
  QVector<int> *equipe1 = new QVector<int>;
    for(int i=0;i<15;i++)
    {

        QTableWidgetItem *itemPlayer = new QTableWidgetItem();
        QPixmap *imagePlayer = new QPixmap();
        if(imagePlayer->load(QString(":/img/"+QString::number(i+1)+".png"),"PNG"))
        {
          QPixmap newImagePlayer =imagePlayer->scaled(QSize(500,500),Qt::KeepAspectRatio);
          QIcon icon(newImagePlayer);
          itemPlayer->setSizeHint(*sizeIcon);

          itemPlayer->setIcon(icon);


          itemPlayer->setData(Qt::UserRole, QVariant(*imagePlayer));
          itemPlayer->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
          setItem(i,0,itemPlayer);
          equipe1->append(i);
        }


    }
    numJoueur.append(*equipe1);
    equipe1->clear();
    for(int i=0;i<15;i++)
    {
        QTableWidgetItem *itemPlayer = new QTableWidgetItem();
        QPixmap *imagePlayer = new QPixmap();
        if(imagePlayer->load(QString(":/img/"+QString::number(i+1)+"_gris.png"),"PNG"))
        {
          QPixmap newImagePlayer =imagePlayer->scaled(QSize(500,500),Qt::KeepAspectRatio);
          QIcon icon(newImagePlayer);
          itemPlayer->setSizeHint(*sizeIcon);

          itemPlayer->setIcon(icon);


          itemPlayer->setData(Qt::UserRole, QVariant(*imagePlayer));
          itemPlayer->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
          setItem(i,1,itemPlayer);
          equipe1->append(i);

        }


    }
    numJoueur.append(*equipe1);
    showTable();



}
//Rendu graphique du tableau
void TablesTeam::showTable()
{
    //Redimisonne le tableau en fonction du nombre de lignes
    setHorizontalHeaderItem(0,new QTableWidgetItem(teamsName[0]));
    setHorizontalHeaderItem(1,new QTableWidgetItem(teamsName[1]));
    verticalHeader()->hide();
    setWindowTitle("Equipe ");



    resizeColumnsToContents();
    resizeRowsToContents();
    setGeometry(10,50,0,0);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    resizeColumnsToContents();
    int width =0, height=0;
    width = 250;
    height= 850;
    //Si limite atteint affichage des scroolbar
     setFixedSize(width,height);


}

void TablesTeam::resetTable()
{
  addTeams();
}

void TablesTeam::importTable(QList<joueur> joueurs)
{
  addTeams();
  for(int i=0;i<numJoueur.size();i++)
  {
    for(int j=0;j<numJoueur.value(i).size();j++)
    {
      if(numJoueur.value(i).contains(joueurs.value(j).numero_joueur))
      {
       delete takeItem(i,j);
      }
    }
  }

}




//Evenement déclencher quand objet prit pour glisser-déposer
void TablesTeam::startDrag(Qt::DropActions /*supportedAction*/)
{

    qDebug() << "startDrag";

    QTableWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPixmap resize = pixmap.scaled(QSize(71,71),Qt::KeepAspectRatio);
    dataStream << resize << teamsName[currentItem()->column()] << currentItem()->row()+1;
    QMimeData *mimeData = new QMimeData;
    mimeData->setData(TablePlayerMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(resize.width()/2, resize.height()/2));
    drag->setPixmap(resize);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item),column(item));

}


//Setter de la classe
void TablesTeam::setTeamName(QString equipe_1, QString equipe_2)
{
    teamsName[0] = equipe_1;
    teamsName[1] = equipe_2;

    setHorizontalHeaderItem(0,new QTableWidgetItem(teamsName[0]));
    setHorizontalHeaderItem(1,new QTableWidgetItem(teamsName[1]));

}






