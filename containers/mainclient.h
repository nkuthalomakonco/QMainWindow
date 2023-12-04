#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include <QMainWindow>

#include "containerlist.h"
#include "container.h"
#include "code.h"
#include "palletlist.h"
#include "containerlistmemento.h"

class QAction;
class QMenu;
class QToolBar;

class QSpinBox;
class QPushButton;
class QListWidget;
class QTextEdit;
class QTabWidget;
class QListView;
class QTcpSocket;
class QAbstractSocket;
class QStringListModel;

#include <QThread>

class MainClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainClient(QWidget *parent = nullptr);
    ~MainClient();
    void closeEvent(QCloseEvent *event);

public slots:

signals:
    void s_write(palletList *palletlist);

private slots:
    void showAbout();
    void showHelp();
    void restoreMethod();
    void xmlMethod();
    void backupMethod();
    void addBoxMethod();
    void addCylinder();
    void moveToPallet();
    void palletInfo();
    void writexmlfinished();
    void writexmlfinishedOut(const QString out);
    void threadQuit();
    void sendToServer(QString msg);
    //void displayError(QAbstractSocket::SocketError socketError);
    void displayError();
    void backUp();
    void restore();
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
    QListView *listView;
    QStringListModel *model;

private:
    QList<QObject*> paletList;//not using.
    palletList *palletlist;
    ContainerList *containerList;
    ContainerList *unallocatedContainers;
    Container *container;
    pallet *m_pallet;
    void addContainer();
    int pallenNo;
    QThread xmlThread;
    QTcpSocket* socket;
    containerListMemento *m_containerListMemento;
};

#endif // MAINCLIENT_H
