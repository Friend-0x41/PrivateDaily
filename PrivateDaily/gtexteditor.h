#ifndef GTEXTEDITOR_H
#define GTEXTEDITOR_H

#include <QTextEdit>

class GTextEditor : public QTextEdit
{
    Q_OBJECT
public:
    GTextEditor(QWidget* parent = nullptr);
    ~GTextEditor();
};

#endif // GTEXTEDITOR_H
