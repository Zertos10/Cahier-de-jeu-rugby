#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>
#include <QCursor>
#include <QPainter>
#include <QtMath>
#include <QPainterPath>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <graphicscene.h>
#include "form.h"
#include "calcul_courbe_bezier.h"

struct ligne
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;
  float distance =0;

};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void mousePressEvent ( QMouseEvent * event )  override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
  void paintEvent(QPaintEvent*)  override;
  void animationStart();

 // void paint(QPainter *painter);
  void on_start_clicked();

  void on_create_Trajectory_clicked();

  void on_modify_trajectory_clicked();

  void on_pushButton_clicked();

  void on_Vitesserouge_clicked();

  void on_Vitesse_orange_clicked();

  void on_vitesse_vert_clicked();

  void on_testButton_clicked();

private:
  Ui::MainWindow *ui;
  QTimer *timer;
  int mouvement = 0;
  bool switchPoint=1;
  QPen pen;
  QBrush brush;
  QPoint lastPoint;
  QPoint firstPoint;
  QList<QPoint> interPoint;
  QPainter *pencilPainter = new QPainter(this);
  ligne *tempLigne = new ligne();
  bool mousePressed;
  bool isDrawing , isMoving = false ;
  unsigned index = 0 ;
  unsigned pt = 0;

  QPoint coord;
  float x = 0;
  int index_2=0;
  QList<ligne> mesLignes ;
  int avance;
  bool isCreateTrajectory = false;
  bool isModifyTrajectory = false;
  int selecteur =0;
  bool isModif = false;
  bool enregistPos = true;
  QPoint pointTempTrajectoire ;
  QList<int> pointModif;
  int pointModifSelect =0;
  QList<QPoint> *pointProvisoire = new QList<QPoint>;
  QPropertyAnimation *animation =new QPropertyAnimation();

};
#endif // MAINWINDOW_H
