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
#include <QApplication>
#include <QMainWindow>

#include "box.h"
#include "cylinder.h"
#include "containerfactory.h"

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
      tabWidget(new QTabWidget())

{
    // Setup actions
    setupActions();

    // Setup menu
    setupMenus();

    // Setup tool bar
    setupToolbar();

    connect(actAbout, &QAction::triggered, this, &MainClient::showAbout);
    connect(actHelp, &QAction::triggered, this, &MainClient::showHelp);
    connect(actExit, &QAction::triggered, this, &QWidget::close);

    connect(buttonAddBox, SIGNAL(clicked()), this, SLOT(addBoxMethod()));
    connect(buttonAddCylinder, SIGNAL(clicked()), this, SLOT(addCylinder()));

    connect(buttonMoveToPallet, SIGNAL(clicked()), this, SLOT(moveToPallet()));


    // Initialize window
    setupContainerWidget();
    setWindowTitle("Main window");

    statusBar()->showMessage("Ready");

    containerList = ContainerList::getInstance();
    container = 0;
}

MainClient::~MainClient()
{
    // Tidy up pointers, if required
    //container->deleteLater();
    //delete container;
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
    const int pos = displayUnallocated->currentRow();

    if(pos == -1)
        return;
}
void MainClient::addContainer()
{

    QString typ;
    QString obj = QObject::sender()->objectName();

    if (obj == "BoxButton") typ = "box";
    if (obj == "CylinderButton") typ = "cylinder";

    code cde(cList);

    QString cd = QString("2022/01/C2");//containerCode()
    cd = cde.getCode();
    cList.append(cd);//keep track

    int count = containerList->size();
    int lenght = 0;
    int breath = 0;
    int height = 0;
    int diameter = 0;

    containerFactory *cf = new containerFactory();
    container = cf->createContainer(typ,cd,lenght,breath,height,diameter);
    if (container!= 0)
    {
        containerList->addContainer(container);
        displayUnallocated->addItem(container->toString());
    }

    delete cf;

    (void)count;

}
void MainClient::showAbout()
{
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


    mnuPost = menuBar()->addMenu("Post XML");

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


}
void MainClient::xmlMethod()
{

}

void MainClient::setupToolbar()
{
    toolbar = addToolBar("Main toolbar");
    toolbar->layout()->setSpacing(10);

    // Add actions as required
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
       bottomLayout->addWidget(displayUnallocated, 1, 0, 5, 1);
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
