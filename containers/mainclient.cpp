#include "mainclient.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>

#include <QSpinBox>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QTabWidget>
#include <QListView>
#include <QStringListModel>
#include <QStandardItem>
#include <QApplication>
#include <QMainWindow>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>

//#include "box.h"
//#include "cylinder.h"
#include "containerfactory.h"

#include "writexml.h"

#include <QDebug>

MainClient::MainClient(QWidget *parent)
    : QMainWindow(parent),
      box_breadth(new QSpinBox()),
      box_length(new QSpinBox()),
      box_height(new QSpinBox()),
      box_weight(new QSpinBox()),
      cylinder_diameter(new QSpinBox()),
      cylinder_height(new QSpinBox()),
      cylinder_weight(new QSpinBox()),
      buttonAddBox(new QPushButton("Add box")),
      buttonAddCylinder(new QPushButton("Add cylinder")),
      displayUnallocated (new QListWidget),
      palletNumber(new QSpinBox()),
      buttonMoveToPallet(new QPushButton("Move to pallet")),
      buttonBackupRestore(new QPushButton("Backup")),
      buttonPostXML(new QPushButton("Post XML to network")),
      displayPalletXML(new QTextEdit),
      tabWidget(new QTabWidget()),
      listView(new QListView()),
      model(new QStringListModel),
      socket(0),
      m_containerListMemento()

{
    // Setup actions
    setupActions();

    // Setup menu
    setupMenus();

    // Setup tool bar
    setupToolbar();

    // Connect Signals and Slots
    // Connect Signals and Slots as required
    connect(actAbout, &QAction::triggered, this, &MainClient::showAbout);
    connect(actHelp, &QAction::triggered, this, &MainClient::showHelp);
    connect(actExit, &QAction::triggered, this, &QWidget::close);
    /*

*/
    connect(buttonAddBox, SIGNAL(clicked()), this, SLOT(addBoxMethod()));
    connect(buttonAddCylinder, SIGNAL(clicked()), this, SLOT(addCylinder()));
    /*

*/
    connect(buttonMoveToPallet, SIGNAL(clicked()), this, SLOT(moveToPallet()));
    /*

*/
    connect(buttonPostXML, &QPushButton::clicked, this, &MainClient::xmlMethod);
 /*

*/
    connect(buttonBackupRestore, &QPushButton::clicked, this, &MainClient::backUp);

    // Initialize window
    //setCentralWidget(???);
    setupContainerWidget();
    setWindowTitle("Main window");
    //setMaximumSize();
   // setWindowState(Qt::WindowMaximized);
    statusBar()->showMessage("Ready");

    containerList = ContainerList::getInstance();
    container = 0;
    palletlist = new palletList();
    pallenNo = 0;

    listView->setModel(model);
}

MainClient::~MainClient()
{
    // Tidy up pointers, if required
    //container->deleteLater();
    //delete container;
//    delete m_pallet;
    threadQuit();
    if(socket->isOpen())
        socket->close();
}
void MainClient::addBoxMethod()
{
    addContainer();
}
void MainClient::addCylinder()
{
    addContainer();
}
void MainClient::moveToPallet()
{
    if (containerList->size() == 0)return;

    const int pos = listView->currentIndex().row();
    if(pos<0)return;
    QModelIndex index = model->index(pos);
    const QVariant val = model->data(index);
    const QString ContainerCode = val.toString();

    const int pN = palletNumber->value();

    //check pallet in pallet list.

    m_pallet = new pallet(pN);

    m_pallet = palletlist->getPallet(m_pallet);

    if(m_pallet == 0)//pallet does not exist in the pallet list.
    {
        //Create a new pallet.
        m_pallet = new pallet(pN);
        //Add container to the new pallet.
        m_pallet->addContainer(containerList->getContainer(ContainerCode));
        //Add pallet pallet list.
        palletlist->addPallet(m_pallet);
    }
    else //pallet exist in the pallet list.
    {
        //Add a container to the pallet.
        m_pallet->addContainer(containerList->getContainer(ContainerCode));
        //Update pallet in the pallet list.
        palletlist->updatePallet(m_pallet);
    }

    containerList->deleteContainer(ContainerCode);

    model->removeRows(listView->currentIndex().row(),1);

}

void MainClient::palletInfo()
{

}
/*
The user should be able to backup this list of unallocated containers (remembering that you
cannot simply back up the pointers to the container objects as they may be deleted before the
restore is done); when restoring the unallocated container list, the container objects should
be recreated and added to the list, and the model/view convenience object appropriately updated.
*/
void MainClient::backUp()
{//save list state here [m_containerListMemento]
    m_containerListMemento = containerList->createMemento();
}
void MainClient::restore()
{//get saved list state here [m_containerListMemento]
    containerList->setMemento(m_containerListMemento);
    QStringList list;
    for (int i = 0; i < containerList->size(); ++i)
        list << containerList->getContainer(i)->getCode();
    model->setStringList(list);//update ui listview.
}
void MainClient::addContainer()
{

    QString typ;
    QString obj = QObject::sender()->objectName();

    if (obj == "BoxButton") typ = "box";
    if (obj == "CylinderButton") typ = "cylinder"; 

    int count = containerList->size();
    int lenght = 1;
    int breath = 2;
    int height = 3;
    int diameter = 1;
    int weight = 2;

    code *cde = new code(typ,count);
    QString cd = cde->getCode();

    containerFactory *cf = new containerFactory();
    container = cf->createContainer(typ,cd,lenght,breath,height,diameter,weight);
    if (container!= 0)
    {
        containerList->addContainer(container);

        if(model->insertRow(model->rowCount())) {
            QModelIndex index = model->index(model->rowCount() - 1, 0);
            model->setData(index, container->getCode(),Qt::DisplayRole);
        }

    }

    delete cf;
    delete cde;
}
void MainClient::showAbout()
{
    // Display 'About' information here
    QApplication::aboutQt();
}

void MainClient::showHelp()
{
    // Display 'Help' information here
    QString message("<b>Transporting</b> cargo around the world is essential in "
              "ensuring that customers have access to the goods they need and want.");

    QMessageBox::about(this, tr("About Application"),
             tr("<b>Transporting</b> cargo around the world is essential in "
                "ensuring that customers have access to the goods they need and want."
                ""));
}

void MainClient::setupActions()
{
    // Set up QActions as required
    // Create resource file for images in sub-directory 'images'.

    actAbout = new QAction(QIcon(":/images/info.png"), "About");
    actHelp = new QAction(QIcon(":/images/help.png"), "Help");
    actExit = new QAction(QIcon(":/images/exit.png"), "Exit");
}

void MainClient::setupMenus()
{
    // Set up QMenus as required

    mnuFile = menuBar()->addMenu("File");
    mnuFile->addSeparator();
    mnuFile->addAction(actExit);

    mnuBackup = menuBar()->addMenu("Backup");
    // Add items to Save and Restore containers
    //mnuBackup->addAction(backupAct);
    //mnuBackup->addAction(restoreAct);

    mnuPost = menuBar()->addMenu("Post XML");
    // Add item to post XML to server
    //mnuPost->addAction(xmlAct);

    mnuHelp = menuBar()->addMenu("Help");
    mnuHelp->addAction(actAbout);
    mnuHelp->addAction(actHelp);
}
void MainClient::backupMethod()
{
    QMessageBox::information(this, tr(""),
                tr(""
                   ""));
    statusBar()->showMessage(tr("backupMethod"), 2000);
}
void MainClient::restoreMethod()
{
    restore();
}
void MainClient::writexmlfinished()
{
    //update user.
    statusBar()->showMessage("xml thread done.");
}
void MainClient::displayError()
{
    //update user.
    statusBar()->showMessage(socket->errorString());
}
void MainClient::sendToServer(QString msg)
{
    socket = new QTcpSocket(this);

    connect(socket, &QAbstractSocket::errorOccurred, this, &MainClient::displayError);
//    connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
//            this, &MainClient::displayError);
    socket->connectToHost(QHostAddress::LocalHost,6164);

    if(socket->waitForConnected())
    {
        statusBar()->showMessage("Connected to Server.");
        QDataStream socketStream(socket);
        socketStream.setVersion(QDataStream::Qt_5_9);

        QByteArray byteArray = msg.toUtf8();

        socketStream << byteArray;
        socket->close();
        socket->deleteLater();
    }
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }

}

void MainClient::writexmlfinishedOut(const QString out)
{
    displayPalletXML->setPlainText(out);//QString toHtml() const
    threadQuit();
    if(out.length()==0)return;

    //send to server.
    sendToServer(out);

    QMessageBox::information(this, tr(""),
                             tr("Pallet list writen to xml file and sent to server."),QMessageBox::Ok);

}
void MainClient::threadQuit()
{
    if(xmlThread.isRunning())
    {xmlThread.quit();
        xmlThread.wait();}
}
void MainClient::xmlMethod()
{
    auto *threadWritexml = new writeXml(palletlist);

    connect(&xmlThread, &QThread::finished, threadWritexml, &QObject::deleteLater);
    connect(&xmlThread, &QThread::finished, this, &MainClient::writexmlfinished);
    connect(&xmlThread, &QThread::started, threadWritexml, &writeXml::write);
    //connect(threadWritexml, &writeXml::done, this, &MainClient::writexmlfinishedOut);
    connect(threadWritexml, SIGNAL(done()), this, SLOT(threadQuit()));
    connect(threadWritexml, SIGNAL(done(QString)), this, SLOT(writexmlfinishedOut(QString)));

    threadWritexml->moveToThread(&xmlThread);
    xmlThread.start();

}

void MainClient::setupToolbar()
{
    toolbar = addToolBar("Main toolbar");
    toolbar->layout()->setSpacing(10);

    // Add actions as required
    //https://gist.github.com/peteristhegreat/c0ca6e1a57e5d4b9cd0bb1d7b3be1d6a
    const QIcon backupIcon = QIcon::fromTheme("preferences-system", QIcon(":/images/backup.png"));
    backupAct = new QAction(backupIcon, tr("&Backup"), this);
    backupAct->setStatusTip(tr("Backup."));
    connect(backupAct, &QAction::triggered, this, &MainClient::backupMethod);
    toolbar->addAction(backupAct);

    //const QIcon restoreIcon = QIcon::fromTheme("preferences-system", QIcon(":/images/restore.png"));
    const QIcon restoreIcon = QIcon(":/images/restore.png");
    restoreAct = new QAction(restoreIcon, tr("&Restore"), this);
    restoreAct->setStatusTip(tr("Restore."));
    connect(restoreAct, &QAction::triggered, this, &MainClient::restoreMethod);
    toolbar->addAction(restoreAct);

    mnuBackup->addAction(backupAct);
    mnuBackup->addAction(restoreAct);

    const QIcon xmlIcon = QIcon(":/images/xml.png");
    xmlAct = new QAction(xmlIcon, tr("&Xml"), this);
    xmlAct->setStatusTip(tr("Xml."));
    connect(xmlAct, &QAction::triggered, this, &MainClient::xmlMethod);
    toolbar->addAction(xmlAct);
    mnuPost->addAction(xmlAct);

}
void MainClient::setupContainerWidget()
{
    // Tab 1 - Containers
       QGroupBox *boxGroup(new QGroupBox("Box"));
       QGridLayout *boxlayout(new QGridLayout);
       boxGroup->setLayout(boxlayout);
       QLabel *labelBBreadth(new QLabel("Breadth"));
       boxlayout->addWidget(labelBBreadth, 0, 0);
       boxlayout->addWidget(box_breadth, 0, 1);
       QLabel *labelBLength(new QLabel("Length"));
       boxlayout->addWidget(labelBLength, 1, 0);
       boxlayout->addWidget(box_length, 1, 1);
       QLabel *labelBHeight(new QLabel("Height"));
       boxlayout->addWidget(labelBHeight, 2, 0);
       boxlayout->addWidget(box_height, 2, 1);
       QLabel *labelBWeight(new QLabel("Weight"));
       boxlayout->addWidget(labelBWeight, 3, 0);
       boxlayout->addWidget(box_weight, 3, 1);
       boxlayout->addWidget(buttonAddBox, 4, 0, 1, 2);
       buttonAddBox->setObjectName("BoxButton");

       QGroupBox *cylinderGroup(new QGroupBox("Cylinder"));
       QGridLayout *cylinderlayout(new QGridLayout);
       cylinderGroup->setLayout(cylinderlayout);
       QLabel *labelCDiameter(new QLabel("Diameter"));
       cylinderlayout->addWidget(labelCDiameter, 0, 0);
       cylinderlayout->addWidget(cylinder_diameter, 0, 1);
       QLabel *labelCHeight(new QLabel("Height"));
       cylinderlayout->addWidget(labelCHeight, 1, 0);
       cylinderlayout->addWidget(cylinder_height, 1, 1);
       QLabel *labelCWeight(new QLabel("Weight"));
       cylinderlayout->addWidget(labelCWeight, 2, 0);
       cylinderlayout->addWidget(cylinder_weight, 2, 1);
       QLabel *labelBlank1(new QLabel);
       cylinderlayout->addWidget(labelBlank1, 3, 0);
       cylinderlayout->addWidget(buttonAddCylinder, 4, 0, 1, 2);
       buttonAddCylinder->setObjectName("CylinderButton");

       QWidget *bottomWidget(new QWidget);
       QGridLayout *bottomLayout(new QGridLayout);
       bottomWidget->setLayout(bottomLayout);
       QLabel *labelListOf(new QLabel("List of unallocated containers"));
       bottomLayout->addWidget(labelListOf, 0, 0);
       QLabel *labelClickOn(new QLabel("Click on item in list, choose a pallet number, "
                                       "and Move the container to that pallet"));
       labelClickOn->setWordWrap(true);
       //bottomLayout->addWidget(displayUnallocated, 1, 0, 5, 1);
       bottomLayout->addWidget(listView, 1, 0, 5, 1);
       bottomLayout->addWidget(labelClickOn, 1, 1);
       bottomLayout->addWidget(palletNumber, 2, 1);
       palletNumber->setMinimum(1);
       bottomLayout->addWidget(buttonMoveToPallet, 3, 1);
       QLabel *labelBlank2(new QLabel);
       cylinderlayout->addWidget(labelBlank2, 4, 1);
       bottomLayout->addWidget(buttonBackupRestore, 5, 1);

       QWidget *containerWidget(new QWidget);
       QGridLayout *tabLayoutContainer(new QGridLayout);
       tabLayoutContainer->addWidget(boxGroup, 0, 0);
       tabLayoutContainer->addWidget(cylinderGroup, 0, 1);
       tabLayoutContainer->addWidget(bottomWidget, 1, 0, 1, 2);
       containerWidget->setLayout(tabLayoutContainer);

       // Tab 2 - Post XML
       QWidget *postWidget(new QWidget);
       QVBoxLayout *postLayout(new QVBoxLayout);
       postWidget->setLayout(postLayout);
       postLayout->addWidget(buttonPostXML);
       postLayout->addWidget(displayPalletXML);

       tabWidget->addTab(containerWidget, tr("Containers"));
       tabWidget->addTab(postWidget, tr("Post XML"));

       setCentralWidget(tabWidget);
}
void MainClient::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    // Confirm that user wants to close the application
    //(void)event;//Q_UNUSED(event)
//    if (QMessageBox::Yes == QMessageBox::question(this,
//                            tr(""),
//                            tr("Close application?"),QMessageBox::Yes|QMessageBox::No))


//    {
//        event->accept();
//    } else {
//        event->ignore();
//    }
}
