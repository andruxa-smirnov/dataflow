#include "Arrow.h"
#include <cmath>
#include <QPen>
#include <QPainter>
#include "BlockIn.h"
#include "BlockOut.h"
#include <iostream>

using namespace std;

const qreal Pi = 3.14;
Arrow::Arrow(BlockIn * startItem, BlockOut * endItem, QGraphicsItem * parent)
    : QGraphicsLineItem(parent)
{
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
           .normalized()
           .adjusted(-extra, -extra, extra, extra);
}
QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}
void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}
void Arrow::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //if (myStartItem->collidesWithItem(myEndItem))
    //return;


    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 10;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    setLine(QLineF(myStartItem->pos(), myEndItem->pos()));
    double angle = ::acos(line().dx() / line().length());

    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());

    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0, -8.0);
        painter->drawLine(myLine);
    }
}
