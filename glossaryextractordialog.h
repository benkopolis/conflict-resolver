#ifndef GLOSSARYEXTRACTORDIALOG_H
#define GLOSSARYEXTRACTORDIALOG_H

#include <QDialog>
#include <QHash>
#include <QList>
#include "fuzzystrings.h"
#include "records/contentrecord.h"

namespace Ui {
    class GlossaryExtractorDialog;
}

class GlossaryExtractorDialog : public QDialog {
    Q_OBJECT
public:
    GlossaryExtractorDialog(QWidget *parent = 0);
    ~GlossaryExtractorDialog();

    inline unsigned minOccurence() const { return _minOccurence; }
    inline unsigned maxOccurence() const { return _maxOccurence; }
    inline unsigned minWordCount() const { return _minWordCount; }
    inline unsigned maxWordCount() const { return _maxWordCount; }
    inline bool ok() const { return _ok; }
    inline void setContent(QMultiHash<FuzzyStrings, ContentRecord* > cont) { _content = cont; }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::GlossaryExtractorDialog *ui;

    bool _ok;
    unsigned _minWordCount;
    unsigned _maxWordCount;
    unsigned _minOccurence;
    unsigned _maxOccurence;
    QMultiHash<FuzzyStrings, ContentRecord* > _content;
    QMultiHash<FuzzyStrings, ContentRecord* > _found;

private slots:
    void on__close_clicked();
    void on__find_clicked();
    void on__save_clicked();
};

#endif // GLOSSARYEXTRACTORDIALOG_H
