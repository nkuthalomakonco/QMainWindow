#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include <QMainWindow>

#include "containerlist.h"
#include "container.h"
#include "code.h"

class QAction;
class QMenu;
class QToolBar;

class QSpinBox;
class QPushButton;
class QListWidget;
class QTextEdit;
class QTabWidget;

class MainClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainClient(QWidget *parent = nullptr);
    ~MainClient();
    void closeEvent(QCloseEvent *event);

public slots:

private slots:
    void showAbout();
    void showHelp();
    void restoreMethod();
    void xmlMethod();
    void backupMethod();
    void addBoxMethod();
    void addCylinder();
    void moveToPallet();
private:
    void setupActions();
    void setupMenus();
    void setupToolbar();
    void setupContainerWidget();

    // Add QAction items as required
    QAction *actAbout;
    QAction *actHelp;
    QAction *actExit;

    QAction *restoreAct;
    QAction *backupAct;
    QAction *xmlAct;

    // Add QMenu items as required
    QMenu *mnuFile;
    QMenu *mnuBackup;
    QMenu *mnuPost;
    QMenu *mnuHelp;

    QToolBar *toolbar;

    //ContainerWidget
private:
    QSpinBox *box_breadth, *box_length, *box_height, *box_weight;
    QSpinBox *cylinder_diameter, *cylinder_height, *cylinder_weight;
    QPushButton *buttonAddBox, *buttonAddCylinder;
    QListWidget *displayUnallocated;
    QSpinBox *palletNumber;
    QPushButton *buttonMoveToPallet, *buttonBackupRestore;
    QPushButton *buttonPostXML;
    QTextEdit *displayPalletXML;
    QTabWidget *tabWidget;

private:
    QList<QObject*> paletList;
    ContainerList *containerList;
    ContainerList *unallocatedContainers;
    Container *container;
    void addContainer();
    QStringList cList;

};

#endif // MAINCLIENT_H
