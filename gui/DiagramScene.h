#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "MainWindow.h"
#include "DiagramBlock.h"
#include "DiagramOperation.h"
#include "DiagramConstructor.h"
#include "BlockIn.h"
#include "BlockOut.h"
#include "ModulesPanelModel.h"
#include "DataflowModel.h"
#include "ModelManipulator.h"

#include <QGraphicsScene>
#include <QTreeView>
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QBrush>

#include <memory>
#include <iostream>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QColor;
class QTreeView;
QT_END_NAMESPACE

class MainWindow;

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, MoveItem };
    explicit DiagramScene(ModulesPanelModel * panelModel, QTreeView * panelView, QMenu * itemMenu, QObject * parent = 0);
    void setSceneSizeAndGradient(QSize size);
    QSize getSizeHint();

    void setModels(ModulesPanelModel * panelModel, ProjectModel * projectModel, ModelManipulator * modelManipulator)
    { this->panelModel = panelModel; this->projectModel = projectModel; this->manipulator = modelManipulator; }

    DiagramBlock * findBlockById(int id);
    BlockIn * findInput(DiagramOperation * block, int index);
    BlockOut * findOutput(DiagramBlock * block, int id);
    bool paintConnectionWhenLoadingProject(int inputBlockId, int inputBlockInput, int outputBlockId, int outputBlockOutputId);

public slots:
    void setMode(Mode mode);

signals:
    void itemInserted();
    void itemSelected(QGraphicsItem * item);

protected:
    void keyPressEvent(QKeyEvent * keyEvent);
    void keyReleaseEvent(QKeyEvent * keyEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
    //qreal minWidth, minHeight, width, height;

    MainWindow * mainWindow;
    QMenu * myItemMenu;
    QTreeView * panelView;
    ModulesPanelModel * panelModel;

    ProjectModel * projectModel;
    ModelManipulator * manipulator;

    Mode myMode;
    QPointF startPoint;
    QGraphicsLineItem * line;
    QColor myTextColor;
    QColor myLineColor;

    bool shiftIsDown;
};
#endif // DIAGRAMSCENE_H
