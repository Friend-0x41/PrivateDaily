#ifndef OPENEDFILE_H
#define OPENEDFILE_H

class GTextEditor;
class QListWidgetItem;

struct OpenedFile
{
    int index;
    GTextEditor* editor;
    QListWidgetItem* listItem;
};

#endif // OPENEDFILE_H
