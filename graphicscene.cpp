#include "graphicscene.h"



 GraphicScene::GraphicScene()
{



}
 QGraphicsScene& GraphicScene::addScene()
{
  QPushButton *bouton = new QPushButton("Mon bouton entre en scène !");
  QTextEdit *textedit = new QTextEdit("test");
      QGraphicsScene *scene = new QGraphicsScene;
      QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
      textedit->setGeometry(100,100,100,100);
      bouton->setGeometry(0,0,10,20);

      proxy->setWidget(bouton);
      proxy->setWidget(textedit);
      scene->addItem(proxy);

      return  *scene;
}

