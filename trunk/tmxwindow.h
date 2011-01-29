#ifndef TMXWINDOW_H
#define TMXWINDOW_H

#include <QMainWindow>
#include "files/tmxfile.h"
#include "records/tmxrecord.h"

namespace Ui {
    class TMXWindow;
}

class TMXWindow : public QMainWindow {
    Q_OBJECT
public:
    TMXWindow(QWidget *parent = 0);
    ~TMXWindow();

public slots:

    bool saveFiles(QString base);
    Error addFile(QString filename);

protected:
    void changeEvent(QEvent *e);

    QList<TMXFile* > _files;

private:
    Ui::TMXWindow *ui;

private slots:
    void on__save_clicked();
    void on__chooseDir_clicked();
};

#endif // TMXWINDOW_H
