#include "GraphWidget.h"

GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	QGraphicsScene *scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(-200, -200, 400, 400);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	scale(qreal(0.8), qreal(0.8));
	setMinimumSize(400, 400);
	setWindowTitle(tr("Elastic Nodes"));
}