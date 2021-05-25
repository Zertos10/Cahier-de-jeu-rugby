#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  mousePressed = false;


  ui->setupUi(this);
  // curseur: croix
  this->setCursor(QCursor(Qt::CrossCursor));
  ui->pos_souris->setText(QString(QString::number(hasMouseTracking())));
 /* centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
  setMouseTracking(true);*/


}

MainWindow::~MainWindow()
{
  delete ui;
}




void MainWindow::paintEvent(QPaintEvent*)
   {

  //Tracer actuelle


if(tempLigne->ptint.empty() != true && isDrawing)
{
  QPoint *intl  = new QPoint[tempLigne->ptint.size()];

  QPainter actualDraw(this);
  for(int i =0;i<tempLigne->ptint.size();i++)
  {

      intl[i] = tempLigne->ptint[i];
  }

  actualDraw.drawPolyline(intl,tempLigne->ptint.size());
  delete[] intl;



}



if(mesLignes.empty() != true)
 {
QPainter *oldDraw = new QPainter(this);
for(int i =0;i<mesLignes.size();i++)
{
QPoint *oldDrawPoint  = new QPoint[mesLignes[i].ptint.size()];


  for(int j = 0;j<mesLignes[i].ptint.size();j++)
  {

    oldDrawPoint[j] = mesLignes[i].ptint[j];

  }

    oldDraw->drawPolyline(oldDrawPoint,mesLignes[i].ptint.size());
    oldDraw->setPen(QPen(Qt::red,15));
    oldDraw->drawPoint(mesLignes[i].pta);
    oldDraw->drawPoint(mesLignes[i].ptb);
    oldDraw->setPen(QPen(Qt::black,1));
  delete[] oldDrawPoint;

}
delete oldDraw;


}
if(isModifyTrajectory)
{
  QPainter modif(this);
  modif.setPen(QPen(Qt::green,15));


    for(int i=1;i< pointModif.size();i++)
     {
    modif.drawPoint(*new QPoint(mesLignes[selecteur].ptint[pointModif[i]].rx(),mesLignes[selecteur].ptint[pointModif[i]].ry()));

    }






}








}



void MainWindow::animationStart()
{
  qDebug() << animation->currentTime();
  if(animation->currentTime() == animation->duration()) timer->stop();


/*  qDebug() << "animationStart()";
  qDebug() << "Selecteur :"<< selecteur;






  if(index == 0)
  {
    qDebug() << "Lancement de l'animation";
//QRect coord = ui->label->geometry();

  //  ui->label->move(mesLignes[selecteur].pta);

  }
  else
   {
    if(index == mesLignes[selecteur].ptint.size())
    {
      qDebug() << "Arrêt";
      index =0;
      qDebug() <<"Index :" <<index;
      timer->stop();


      return;
    }
    else
    {
      qDebug() << "Animation au point :" <<index;
     // ui->label->move(mesLignes[selecteur].ptint[index]);
    }



  }


  index++;

*/

}




void  MainWindow::mousePressEvent( QMouseEvent * event ){
    // position de la souris



  if(!mesLignes.empty())
  {
  for( int i =0;i<mesLignes.size();i++)
  {

    if(mesLignes[i].pta.rx()+20 >= event->pos().rx() && mesLignes[i].pta.rx()-20 <= event->pos().rx() && mesLignes[i].pta.ry()+20 >= event->pos().ry() && mesLignes[i].pta.ry()-20 <= event->pos().ry())
  {
    qDebug() << "point de la figure n° "<< i <<",sélectionner a";
    selecteur = i;
     qDebug() <<i;
    break;
  }
    if(mesLignes[i].ptb.rx()+20 >= event->pos().rx() && mesLignes[i].ptb.rx()-20 <= event->pos().rx() && mesLignes[i].ptb.ry()+20 >= event->pos().ry() && mesLignes[i].ptb.ry()-20 <= event->pos().ry())
  {
    qDebug() << "point de la figure n° "<< i <<",sélectionner point b";
    selecteur = i;
    break;
  }


  }
}
 qDebug() << "Nombre de figure : "<< mesLignes.size();
 if (event->button() == Qt::LeftButton)
 {
   if(isModifyTrajectory)
   {


       int size_select =mesLignes[selecteur].ptint.size();
       pointModif.clear();
       pointModif.append(0);
       for(int i=2;i<4;i++)
        {

      int result_size  = (size_select-1)/i;

         qDebug()<< "Résultat de result_size : " << result_size ;
         if(mesLignes[selecteur].ptint[result_size].rx()+20 >= event->pos().rx() && mesLignes[selecteur].ptint[result_size].rx()-20 <= event->pos().rx() && mesLignes[selecteur].ptint[result_size].ry()+20 >= event->pos().ry() && mesLignes[selecteur].ptint[result_size].ry()-20 <= event->pos().ry())
         {

           //    qDebug() <<i <<" : Point x="<<mesLignes[selecteur].ptint[result_size].x() <<" y=" <<mesLignes[selecteur].ptint[result_size].x();
               qDebug() << "Résultat de result_size" << result_size;
               isModif = true;
                 pointModifSelect = result_size;
                 pointProvisoire = new QList<QPoint>;




        }
         pointModif.append(result_size);
       }
       pointModif.append(mesLignes[selecteur].ptint.indexOf(mesLignes[selecteur].ptint.last()));

       //Sélectionne le dernier point de la trajectoire
       qDebug() << pointModif;

       //trie des résultat par  ordre croissant
       for(int i=0;i<pointModif.size();i++)
       {

                 //mémoriser T[i] dans x
                 int x = pointModif[i];
                 int j = i;
                     while(j>0 && pointModif[j-1] >x)
                 {
                   pointModif[j] = pointModif[j-1];
                   j = j-1;
                 }

                 pointModif[j] = x;
       }
        qDebug() << pointModif;
       qDebug() << "Max nombre point " << size_select;

       update();



   }
   else
   {
     if(!ui->Vitesserouge->isEnabled() || !ui->Vitesse_orange->isEnabled() ||!ui->vitesse_vert->isEnabled() )
        {
       if(!tempLigne->ptint.empty())
       {
       tempLigne->ptint.clear();
       qDebug() << "Taille : "<< tempLigne->ptint.size();
        }
       if(isCreateTrajectory != true )
       {

         qDebug() << "x="<< pointTempTrajectoire.x() <<"\n y=" << pointTempTrajectoire.y();
          tempLigne->pta = pointTempTrajectoire;
          tempLigne->ptint.append(pointTempTrajectoire);
       }
       else
       {
         tempLigne->ptint.append(event->pos());
           tempLigne->pta = event->pos();
       }
         qDebug() << "Ajout point de départ : " << event->pos();
         isDrawing = true;
         mousePressed = true;
       update();
     }

   }

  }




}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

      if(!isMoving)
      {
        ui->pos_souris->setText(QString("Pos X:"+QString::number(event->pos().rx())+"\nPosY:"+QString::number(event->pos().ry())));
        if ((event->buttons() & Qt::LeftButton) && isDrawing)
        {

          qDebug() << "Detect 1:" << tempLigne->ptint.size();
          if(enregistPos == true)
          {
            tempLigne->ptint.append(event->pos());
            enregistPos= false;
          }
          else
          {
            enregistPos = true;
          }




          qDebug() << "Ajout point intermediaire : "<< event->pos()  ;
        }
        update();

      }
      if(isModifyTrajectory && isModif)
      {

        mesLignes[selecteur].ptint[pointModifSelect] = event->pos();
        int limitePoint = pointModif.indexOf(pointModifSelect);

        int intLimitePoint = pointModif[limitePoint] ;
        int intLimiteplus = pointModif[limitePoint+1];
        int intLimitemoins = pointModif[limitePoint-1];
        qDebug() << "limite point" << limitePoint;
        qDebug() << pointModif[limitePoint-1];
        qDebug() << pointModif[limitePoint];
        qDebug() << pointModif[limitePoint+1];
       QPoint P0 = mesLignes[selecteur].ptint[intLimiteplus];
        QPoint P1 = mesLignes[selecteur].ptint[intLimitePoint] ,P2 = mesLignes[selecteur].ptint[intLimitePoint];
        QPoint P3 = mesLignes[selecteur].ptint[intLimitemoins];
       double epsilon = 5e-3;
        QList<QPoint> points;
        points.append(P0);
        points.append(P1);
        points.append(P2);
        points.append(P3);
        calcul_courbe_Bezier courbeBezier ;


       points =  courbeBezier.coube_bezier_init(points,epsilon);

       qDebug() << points;

        if(pointProvisoire->isEmpty())
        {
          for(int i=0;i<mesLignes[selecteur].ptint.size();i++)
          {
            //qDebug() <<"Ajout du point" << mesLignes[selecteur].ptint.indexOf(mesLignes[selecteur].ptint[i]) ;

              pointProvisoire->insert(i,mesLignes[selecteur].ptint[i]);
          }
        }
        if(!(limitePoint == pointModif.last())|| !(limitePoint == pointModif.first()))
        {
         // qDebug()<<"Limite point:" << intLimitePoint;
          //qDebug()<<"Limite point+1:" << intLimiteplus;

         // int i = intLimitePoint;
         // float j=0.1/intLimitePoint;

          /*
           while(i < intLimiteplus)
           {

           //  qDebug() <<"Limite point vers"<<pointModif[limitePoint] <<" : " <<i;
             QPoint point = pointProvisoire->value(i);

             float x =point.x()/j;
            // float equation = intLimitemoins*pow(3,1-x)+3*intLimitePoint*x*pow(2,1-x)+3*intLimitePoint*pow(2,x)*(1-x)+intLimiteplus*pow(3,x);

             if(j>=0 && j<=1)
             {

               qDebug() << "j = " << j;
           //    qDebug() << "resultat équation" << equation;
               //point.setY(equation);
               mesLignes[selecteur].ptint[i]= point;
             }

             i++;
          j=j+0.1;

           }
        //   qDebug()<<"Limite point:" << intLimitePoint;
          // qDebug()<<"Limite point+1:" << intLimitemoins;
            i = intLimitePoint;
            j =0;
            while(i > intLimitemoins)
            {
             //  qDebug() <<"Limite point vers"<<pointModif[limitePoint] <<" : " <<i;

              QPoint point = pointProvisoire->value(i);

             // point.setX(event->pos().x()+point.x());
              //point.setY(event->pos().y()+point.y());



              mesLignes[selecteur].ptint[i]= point;
              i--;
              j++;

            }*/



        }
        update();
    }


}



void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  isMoving = false;
  if(isModifyTrajectory)
  {
    isModif = false;
    delete pointProvisoire;

  }
  if (event->button() == Qt::LeftButton && isDrawing )
    {

      ligne *nouvelleligne = new ligne;
      nouvelleligne->pta = tempLigne->pta;
      nouvelleligne->ptb = event->pos();
      nouvelleligne->ptint = tempLigne->ptint;
      if(!isCreateTrajectory)
      {
        if(mesLignes.isEmpty()) mesLignes.append(*nouvelleligne);
     pointTempTrajectoire =  nouvelleligne->ptb;
        qDebug() << "x="<< pointTempTrajectoire.x() <<"\n y=" << pointTempTrajectoire.y();
        mesLignes.last().ptb = event->pos();
        for(int i=0; i<tempLigne->ptint.size();i++)
        {
          mesLignes.last().ptint.append(tempLigne->ptint[i]);
        }
      }
      else
      {
        mesLignes.append(*nouvelleligne);

      }
      //calcule de la distance
      float calcDistance = 0;
      for(int i=0;i<mesLignes.last().ptint.size();i++)
      {

        if(!(i == mesLignes.last().ptint.size()-1))
        {
            QPoint pointA = mesLignes.last().ptint[i];
            QPoint pointB = mesLignes.last().ptint[i+1];

            calcDistance = sqrt(pow(2,pointB.x()-pow(2,pointA.x()))+pow(2,pointB.y()-pointA.y()));
            mesLignes.last().distance = mesLignes.last().distance + calcDistance;
        }
        else
        {

        }

      }
      qDebug() << "Résultat" << mesLignes.last().distance;

      delete nouvelleligne;
      isDrawing = false;
      mousePressed = false;


      index_2 =0;
      update();

    }

}


void MainWindow::on_start_clicked()
{
if(!mesLignes.empty())
{
    animation = new QPropertyAnimation(ui->label, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(mesLignes[selecteur].pta.x(), mesLignes[selecteur].pta.y(), ui->label->geometry().width(),ui->label->geometry().height()));
    qDebug() << "carré" << sqrt(2);
    int divi = mesLignes[selecteur].ptint.size();

   for(int i=1;i<mesLignes[selecteur].ptint.size();i++)
   {
     float qTimeLine = 1/i;

     // qTimeLine = 0.01*i;

       qDebug() << "resultat:" << qTimeLine;
      animation->setKeyValueAt(qTimeLine,QRect(mesLignes[selecteur].ptint[i].x(),mesLignes[selecteur].ptint[i].y(), ui->label->geometry().width(),ui->label->geometry().height()));


   }
  animation->setStartValue(QRect(mesLignes[selecteur].pta.x(), mesLignes[selecteur].pta.y(), ui->label->geometry().width(),ui->label->geometry().height()));
  animation->setEndValue(QRect(mesLignes[selecteur].ptb.x(), mesLignes[selecteur].ptb.y(), ui->label->geometry().width(),ui->label->geometry().height()));

  animation->start();
  timer = new QTimer;
  timer->setInterval(50);
  connect(timer, SIGNAL(timeout()),this, SLOT(animationStart()));
  timer->start();
}

}

void MainWindow::on_create_Trajectory_clicked()
{

  if(isCreateTrajectory != true)
  {

    ui->create_Trajectory->setText("Désactiver !");
    isCreateTrajectory = true;
    qDebug() << "Mode création activé !";
  }
  else
  {
    isCreateTrajectory = false;
    ui->create_Trajectory->setText("Créer trajectoire !");
    qDebug() << "Mode création désactivé  !";

  }

}

void MainWindow::on_modify_trajectory_clicked()
{
    if(isModifyTrajectory != true)
    {
      isModifyTrajectory = true;
      ui->modify_trajectory->setText("Désactiver !");

    }
    else
    {
      isModifyTrajectory = false;
      ui->modify_trajectory->setText("Modifier trajectoire !");

    }

}

void MainWindow::on_pushButton_clicked()
{
  GraphicScene graph ;
  ui->graphicsView->setScene(&graph.addScene());



}



void MainWindow::on_Vitesserouge_clicked()
{
ui->Vitesserouge->setDisabled(true);
ui->Vitesse_orange->setDisabled(false);
ui->vitesse_vert->setDisabled(false);
}

void MainWindow::on_Vitesse_orange_clicked()
{
  ui->Vitesse_orange->setDisabled(true);
  ui->Vitesserouge->setDisabled(false);
  ui->vitesse_vert->setDisabled(false);

}

void MainWindow::on_vitesse_vert_clicked()
{
  ui->Vitesserouge->setDisabled(false);
  ui->Vitesse_orange->setDisabled(false);
  ui->vitesse_vert->setDisabled(true);

}

void MainWindow::on_testButton_clicked()
{
  //ConversionBin().setConversion(100512320.411);
/*  int i =0;
 if(!pointProvisoire->isEmpty())
 {
   for(QPoint point : *pointProvisoire)
   {
     mesLignes[selecteur].ptint.replace(i,point);
     i++;
   }
   update();
  }*/


}
