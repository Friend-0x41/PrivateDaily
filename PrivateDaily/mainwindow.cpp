#include "mainwindow.h"
#include <QAction>
#include "gtexteditor.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QDebug>
#include <QTextCursor>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QStackedWidget>
#include <QDockWidget>
#include <QListWidget>
#include "decode.h"
#include "encryption.h"
#include <QTextCodec>
#include "config.h"
#include <QDate>
#include <QTime>
#include <QDir>
#include <cstring>
#include <QApplication>
#include <verificationwidget.h>
#include <QMessageBox>
#include <QByteArray>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(800,600);
    _stackWidget = new QStackedWidget(this);
    setCentralWidget(_stackWidget);
    QDockWidget* currentFile = new QDockWidget(this);
    QWidget* emptyWidget = new QWidget(this);
    currentFile->setTitleBarWidget(emptyWidget);
    _fileList = new QListWidget(this);
    currentFile->setWidget(_fileList);
    currentFile->setFeatures(QDockWidget::NoDockWidgetFeatures);
    connect(_fileList,&QListWidget::currentRowChanged,this,&MainWindow::on_currentEditor_switch);
    addDockWidget(Qt::LeftDockWidgetArea,currentFile);

    statusBar();

    //Menu
    QMenuBar* menu_bar = menuBar();

    _fileMenu = menu_bar->addMenu("File");

    QAction* newFileAction = new QAction("&New",this);
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip("Create new daily file");
    connect(newFileAction,&QAction::triggered,this,&MainWindow::on_newFileAction_triggered);
    _fileMenu->addAction(newFileAction);

    QAction* openFileAction = new QAction("&Open",this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip("Open an exist daily file");
    connect(openFileAction,&QAction::triggered,this,&MainWindow::on_openFileAction_triggered);
    _fileMenu->addAction(openFileAction);

    QAction* saveAction = new QAction("&Save",this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save dialy file");
    connect(saveAction,&QAction::triggered,this,&MainWindow::on_saveFileAction_triggered);
    _fileMenu->addAction(saveAction);

    _editeMenu = menu_bar->addMenu("Edit");

    QAction* undoAction = new QAction("&Undo",this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip("Undo a operation");
    connect(undoAction,&QAction::triggered,this,&MainWindow::on_undoAction_triggered);
    _editeMenu->addAction(undoAction);

    QAction* redoAction = new QAction("&Redo",this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip("Redo a operation");
    connect(redoAction,&QAction::triggered,this,&MainWindow::on_redoAction_triggered);
    _editeMenu->addAction(redoAction);

    QAction* cutAction = new QAction("&Cut",this);
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction,&QAction::triggered,this,&MainWindow::on_cutAction_triggered);
    _editeMenu->addAction(cutAction);

    QAction* copyAction = new QAction("&Copy",this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction,&QAction::triggered,this,&MainWindow::on_copyAction_triggered);
    _editeMenu->addAction(copyAction);

    QAction* pastAction = new QAction("&Past",this);
    pastAction->setShortcut(QKeySequence::Paste);
    connect(pastAction,&QAction::triggered,this,&MainWindow::on_pasteAction_triggered);
    _editeMenu->addAction(pastAction);

    QAction* deleteAction = new QAction("&Delete",this);
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction,&QAction::triggered,this,&MainWindow::on_deleteAction_triggered);
    _editeMenu->addAction(deleteAction);

    QAction* selectAllAction = new QAction("&Select all",this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(selectAllAction,&QAction::triggered,this,&MainWindow::on_selectAllAction_triggered);
    _editeMenu->addAction(selectAllAction);

    QMenu* helpMenu = new QMenu("Help",this);
    menu_bar->addMenu(helpMenu);
    QAction* whatswrongAction = new QAction("&What's wrong",this);
    connect(whatswrongAction,&QAction::triggered,this,&MainWindow::on_whatswrongActionTriggered);
    helpMenu->addAction(whatswrongAction);

    QAction* aboutQtAction = new QAction("&About Qt",this);
    connect(aboutQtAction,&QAction::triggered,qApp,&QApplication::aboutQt);
    helpMenu->addAction(aboutQtAction);
    //Menu end

    //ToolBar
    _toolBar = addToolBar("Toolbar");
    _toolBar->setMovable(false);
    _toolBar->addAction(undoAction);
    _toolBar->addAction(redoAction);
    _toolBar->addAction(cutAction);
    _toolBar->addAction(copyAction);
    _toolBar->addAction(pastAction);
    _toolBar->addAction(deleteAction);
    _toolBar->addAction(selectAllAction);

    QPushButton* italicBtn = new QPushButton("Italic",this);
    connect(italicBtn,&QPushButton::clicked,this,&MainWindow::on_italicBtn_clicked);
    _toolBar->addWidget(italicBtn);

    QHBoxLayout* fontLayout = new QHBoxLayout(this);
    QLabel* label = new QLabel("Font Size",this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QLineEdit* fontSize = new QLineEdit(this);
    QRegExp re("[1-9][0-9]");
    fontSize->setValidator(new QRegExpValidator(re));

    connect(fontSize,&QLineEdit::textChanged,this,&MainWindow::on_fontSize_changed);
    fontLayout->addWidget(label);
    fontLayout->addWidget(fontSize);
    fontLayout->addStretch(4);
    QWidget* fontWidget = new QWidget(this);
    fontWidget->setLayout(fontLayout);
    _toolBar->addWidget(fontWidget);
    //ToolBar end

    setWindowTitle("Daily");


    if(!LoadConfig())
    {
        OpenedFile openedFile;
        openedFile.editor = new GTextEditor;
        _stackWidget->addWidget(openedFile.editor);
        openedFile.listItem = new QListWidgetItem("new");
        _fileList->insertItem(0,openedFile.listItem);
        _fileList->setCurrentRow(0);
        _currendFileIndex = 0;
        _openedFiles.append(openedFile);
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_newFileAction_triggered()
{
    AddEditor("new","");
}

void MainWindow::on_openFileAction_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,"Open","./","*.e");
    if(path.isEmpty())
    {
        return;
    }
    if(_openedFilePaths.contains(path))
    {
        int i = 0;
        for(i;i < _openedFilePaths.count();++i)
        {
            if(path == _openedFilePaths[i])
            {
                break;
            }
        }
        _fileList->setCurrentRow(i);
        return;
    }
    _openedFilePaths.append(path);
    QFile inputFile(path);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray bytes = inputFile.readAll();
    inputFile.close();
    Decode decode(bytes);
    const char* key = VerificationWidget::getPassword().toStdString().c_str();
    QByteArray& cv = decode.decodeData((unsigned char*)key);
    QStringList l = path.split('/');
    path = l[l.length() - 1];
    AddEditor(path,cv.data());
}

void MainWindow::AddEditor(const QString& fileName,const QString& text)
{
    OpenedFile openedFile;
    openedFile.editor = new GTextEditor(this);
    openedFile.editor->setText(text);
    _stackWidget->addWidget(openedFile.editor);
    openedFile.listItem = new QListWidgetItem(fileName);
    _openedFiles.append(openedFile);
    _fileList->insertItem(_fileList->count(),openedFile.listItem);
    _fileList->setCurrentRow(_fileList->count() - 1);
}

void MainWindow::on_saveFileAction_triggered()
{
    QString data = _openedFiles[_currendFileIndex].editor->toHtml();
    if(data.isEmpty())
    {
        statusBar()->showMessage("No data");
        return;
    }
    QString path = QDir::currentPath() + _defaultUsedPath;
    QDir dir(path);
    if(!dir.exists())
    {
        qDebug() << dir.mkdir(path);
        qDebug() << dir.path();
    }
    QString fileName;
    if(_openedFiles[_currendFileIndex].listItem->text() == "new")
    {
        fileName = QDate::currentDate().toString("yyyy-MM-dd-");
        fileName += QTime::currentTime().toString("hh-mm-ss.e");
        fileName = path + "/" + fileName;

        _openedFilePaths.append(fileName);
    }
    else
    {
        fileName = path + "/" + _openedFiles[_currendFileIndex].listItem->text();
    }
    QFile outputFile(fileName);
    if(!outputFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    QByteArray bytes(data.toStdString().c_str());
    Encryption e(bytes);
    const char* key = VerificationWidget::getPassword().toStdString().c_str();
    QByteArray& vc = e.desData((unsigned char*)key);
    outputFile.write(vc);
    outputFile.close();
    statusBar()->showMessage("Save success");
    QStringList l = fileName.split('/');
    _openedFiles[_currendFileIndex].listItem->setText(l[l.count() - 1]);
}

void MainWindow::on_deleteAction_triggered()
{
    QTextCursor cursor = _openedFiles[_currendFileIndex].editor->textCursor();
    if(cursor.hasSelection())
    {
        cursor.clearSelection();
    }
    else
    {
        cursor.deletePreviousChar();
    }
}

void MainWindow::on_fontSize_changed(const QString &text)
{
    _openedFiles[_currendFileIndex].editor->setFontPointSize(text.toInt());
}

void MainWindow::on_italicBtn_clicked()
{
    static bool isChecked = false;
    if(isChecked)
    {
        _openedFiles[_currendFileIndex].editor->setFontItalic(false);
    }
    else
    {
        _openedFiles[_currendFileIndex].editor->setFontItalic(true);
    }
    isChecked = !isChecked;
}

void MainWindow::on_undoAction_triggered()
{
    _openedFiles[_currendFileIndex].editor->undo();
}

void MainWindow::on_redoAction_triggered()
{
    _openedFiles[_currendFileIndex].editor->redo();
}

void MainWindow::on_cutAction_triggered()
{
    _openedFiles[_currendFileIndex].editor->cut();
}

void MainWindow::on_copyAction_triggered()
{
    _openedFiles[_currendFileIndex].editor->copy();
}

void MainWindow::on_pasteAction_triggered()
{
    _openedFiles[_currendFileIndex].editor->paste();
}

void MainWindow::on_selectAllAction_triggered()
{
    _openedFiles[_currendFileIndex].editor->selectAll();
}

void MainWindow::on_currentEditor_switch(int index)
{
    _stackWidget->setCurrentIndex(index);
    _currendFileIndex = index;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    SaveConfig();
    QApplication::quit();
}


void MainWindow::SaveConfig()
{
    ConfigData data;
    data.currentIndex = _fileList->currentRow();
    data.openedFile = _openedFilePaths;
    Config c;
    c.SaveConfig(data);
}

bool MainWindow::LoadConfig()
{
    bool b;
    Config c;
    ConfigData data = c.loadConfig(b);
    if(!b)
    {
        return false;
    }

    int count = 0;
    for(int i = 0;i < data.openedFile.count();++i)
    {
        QFile inputFile(data.openedFile[i]);
        if(!inputFile.open(QIODevice::ReadOnly))
        {
            continue;
        }
        QByteArray bytes = inputFile.readAll();
        inputFile.close();
        Decode decode(bytes);
        const char* s = VerificationWidget::getPassword().toStdString().c_str();
        QByteArray& cv = decode.decodeData((unsigned char*)s);
        QStringList l = data.openedFile[i].split('/');
        QString path = l[l.length() - 1];
        AddEditor(path,cv.data());
        _openedFilePaths.append(data.openedFile[i]);
        ++count;
    }
    if(!count)
    {
        return false;
    }
    if(data.currentIndex <= count)
    {
        _fileList->setCurrentRow(data.currentIndex);
    }
    return true;
}

void MainWindow::on_whatswrongActionTriggered()
{
    QMessageBox::information(this,"What's wrong?","If you saw error character,please check your password and restart before you laugth at me");
}
