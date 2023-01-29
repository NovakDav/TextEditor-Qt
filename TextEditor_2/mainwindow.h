#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QMdiArea>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNov_triggered();

    void on_actionOtev_t_triggered();

    void on_actionTisk_triggered();

    void on_actionUlozit_jako_triggered();

    void on_actionUlozit_triggered();

    void on_action_align_levo_triggered();

    void on_action_align_pravo_triggered();

    void on_actionalign_center_triggered();

    void on_actionalign_justify_triggered();


    void on_actionTu_n_p_smo_toggled(bool arg1);

    void on_actionKurz_va_toggled(bool arg1);

    void on_actionPodtr_en_toggled(bool arg1);


    void on_fontComboBox_currentFontChanged(const QFont &f);


    void on_SizeComboBox_currentTextChanged(const QString &arg1);

    void on_actionFont_triggered();

    void on_actionBarva_triggered();


    void on_pushButton_next_clicked();



    void on_pushButton_zpet_clicked();

    void on_pushButton_replace_clicked();
    void dropEvent(QDropEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionKop_rovat_triggered();

    void on_actionVlo_it_triggered();

    void on_actionVybrat_v_e_triggered();

    void on_actionVyst_ihnout_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile ="";
    QMdiArea* mdiArea;
};
#endif // MAINWINDOW_H
