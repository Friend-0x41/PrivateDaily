#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QStringList>
#include "openedfile.h"

class GTextEditor;
class QMenu;
class QToolBar;
class QStackedWidget;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_newFileAction_triggered();
    void on_openFileAction_triggered();
    void on_saveFileAction_triggered();

    void on_undoAction_triggered();
    void on_redoAction_triggered();
    void on_cutAction_triggered();
    void on_copyAction_triggered();
    void on_pasteAction_triggered();
    void on_selectAllAction_triggered();
    void on_deleteAction_triggered();

    void on_currentEditor_switch(int index);

    void on_fontSize_changed(const QString& text);
    void on_italicBtn_clicked();

    void on_whatswrongActionTriggered();

protected:

    virtual void closeEvent(QCloseEvent* e);

private:

    void AddEditor(const QString& fileName,const QString& text);

    void SaveConfig();

    bool LoadConfig();
private:
    QMenu* _fileMenu = nullptr;
    QMenu* _editeMenu = nullptr;
    QToolBar* _toolBar = nullptr;
    QStackedWidget* _stackWidget = nullptr;
    QListWidget* _fileList = nullptr;
    QStringList _openedFilePaths;
    const QString _defaultUsedPath = "/Dailys";

    QList<OpenedFile> _openedFiles;
    int _currendFileIndex = 0;
};

#endif // MAINWINDOW_H
