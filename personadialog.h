#ifndef PERSONADIALOG_H
#define PERSONADIALOG_H

#include <QDialog>

namespace Ui {
class PersonaDialog;
}

class PersonaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonaDialog(QWidget *parent = nullptr);
    ~PersonaDialog();

    QString nombre() const;
    QString fecha() const;
    QString prioridad() const;
    QString tipo() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    //void on_color_clicked();

private:
    Ui::PersonaDialog *ui;
};

#endif // PERSONADIALOG_H
