#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Arrow.h"
#include "DiagramScene.h"
#include "DiagramBlock.h"
#include "DiagramConstructor.h"
#include "DiagramOperation.h"
#include "ModulesPanelModel.h"
#include "DataflowModel.h"
#include "ModelManipulator.h"
#include "XMLParser.h"
#include "Interpreter.h"

#include <QMainWindow>
#include <QAction>
#include <QScopedPointer>
#include <QtWidgets>
#include <QVector>
#include <QTextStream>

#include <iostream>
#include <typeinfo>

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QStringListModel;
class QTreeView;
class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    QSize getSceneViewSize();

private slots:
    void splitterMovedEvent(int pos, int index);
    void resizeEvent(QResizeEvent* event);
    void panelViewClicked();
    void panelViewCollapsedExpanded();
    void newProject();
    void openFile();
    void deleteItem();
    void pointerGroupClicked(int id);
    void itemInserted();
    void about();
    void execute();
    void saveFile();
    void saveAs();
    void toggleEntryPoint();
    void openPanelMenu(const QPoint &);

private:
    void createModulesList();
    void createActions();
    void createMenus();
    void createToolbars();

    void saveModelAs(const QString & filename);
    void updateInterfaceState();
    void updateExecute();

    void addLibrary(const QString & name);

    DiagramScene * scene;
    QGraphicsView * sceneView;

    QAction * openFileAction;
    QAction * exitAction;
    QAction * deleteAction;
    QAction * aboutAction;
    QScopedPointer<QAction> executeAction;
    QScopedPointer<QAction> saveAction;
    QScopedPointer<QAction> saveAsAction;
    QScopedPointer<QAction> entryPointAction;

    QMenu * fileMenu;
    QMenu * itemMenu;
    QMenu * aboutMenu;
    QToolBar * editToolBar;
    QToolBar * pointerToolbar;
    QToolBar * fileToolbar;

    QButtonGroup * pointerTypeGroup;
    QAction * lineAction;

    QString openedFileName;
    QScopedPointer<ProjectModel> projectModel;
    QScopedPointer<ModelManipulator> manipulator;

    QScopedPointer<ModulesPanelModel> panelModel;
    QTreeView * panelView;
};
#endif // MAINWINDOW_H
