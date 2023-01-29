#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontComboBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->mdiArea2->acceptDrops();
    mdiArea = ui->mdiArea2;

    QVBoxLayout *layout = ui->verticalLayout;
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(ui->actionUlozit, &QAction::triggered, this, &MainWindow::on_actionUlozit_triggered);
    connect(ui->actionUlozit_jako, &QAction::triggered, this, &MainWindow::on_actionUlozit_jako_triggered);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QTextEdit* getActiveTextEdit(QMdiArea* mdi)
{
    QMdiSubWindow *activeSubWindow = mdi->activeSubWindow();
    QWidget *widget = activeSubWindow->widget();
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(widget);
    return textEdit;
}

void MainWindow::on_actionNov_triggered()
{
        QTextEdit *textEdit = new QTextEdit();
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(textEdit);
        subWindow->setWindowTitle("Nové okno");

        subWindow->show();
}


void MainWindow::on_actionOtev_t_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Otevřít soubor");
       QFile file(fileName);
       if (!file.open(QIODevice::ReadOnly))
           return;

       QTextEdit *textEdit = new QTextEdit();
       QTextStream in(&file);
       textEdit->setHtml(in.readAll());
       file.close();
       QMdiSubWindow *subWindow = mdiArea->addSubWindow(textEdit);
       subWindow->setWindowTitle(fileName);
       subWindow->show();
}




void MainWindow::on_actionTisk_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);

    QPrinter printer;
    printer.setPrinterName("printer name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec()== QDialog::Rejected){
        QMessageBox::warning(this,"Varování", "Nelze najít tiskárnu");
        return;
    }
    textEdit->print(&printer);

}


void MainWindow::on_actionUlozit_jako_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    QString text = textEdit->toHtml();
    QString filename = QFileDialog::getSaveFileName(this, "Uložit jako");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
        {
        QMessageBox::warning(this,"Upozornění","Nelze uložit soubor:" + file.errorString());
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);

    out <<text;
    file.close();
}


void MainWindow::on_actionUlozit_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    QString text = textEdit->toHtml();
    QFile f = currentFile;
    QString filename(f.fileName());
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
        {
        QMessageBox::warning(this,"Upozornění","Nelze uložit soubor:" + file.errorString());
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);

    out <<text;
    file.close();
}





void MainWindow::on_action_align_levo_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_action_align_pravo_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->setAlignment(Qt::AlignRight);

}


void MainWindow::on_actionalign_center_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_actionalign_justify_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->setAlignment(Qt::AlignJustify);
}





void MainWindow::on_actionTu_n_p_smo_toggled(bool arg1)
{
    QTextCharFormat format;
    format.setFontWeight(arg1 ? QFont::Bold : QFont::Normal);

    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->mergeCurrentCharFormat(format);
}


void MainWindow::on_actionKurz_va_toggled(bool arg1)
{
    QTextCharFormat format;
    format.setFontItalic(arg1 ? true : false);

    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->mergeCurrentCharFormat(format);
}


void MainWindow::on_actionPodtr_en_toggled(bool arg1)
{
    QTextCharFormat format;
    format.setFontUnderline(arg1 ? true : false);

    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->mergeCurrentCharFormat(format);
}








void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QTextCharFormat format;
    format.setFont(f);
    format.setFontPointSize(ui->SizeComboBox->currentText().toInt());

    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->mergeCurrentCharFormat(format);
}







void MainWindow::on_SizeComboBox_currentTextChanged(const QString &arg1)
{
    QTextCharFormat format;
    format.setFontPointSize(arg1.toInt());

    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->mergeCurrentCharFormat(format);
}


void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok) {
        QTextCharFormat format;
        format.setFont(font);

        QTextEdit* textEdit = getActiveTextEdit(mdiArea);
        textEdit->mergeCurrentCharFormat(format);
    }else return;

}


void MainWindow::on_actionBarva_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this, "Vyberte barvu:");
    if(color.isValid()){
        QTextEdit* textEdit = getActiveTextEdit(mdiArea);
        textEdit->setTextColor(color);
    }
}




void MainWindow::on_pushButton_next_clicked()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->find(ui->lineEdit_word->text());
    textEdit->textCursor();
}




void MainWindow::on_pushButton_zpet_clicked()
{
   QTextEdit* textEdit = getActiveTextEdit(mdiArea);
   textEdit->find(ui->lineEdit_word->text(),QTextDocument::FindBackward);
   textEdit->textCursor();
}


void MainWindow::on_pushButton_replace_clicked()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->moveCursor(QTextCursor::Start);
    while(textEdit->find(ui->lineEdit_word->text()))
        {
        textEdit->textCursor().insertText(ui->lineedit_nahradit->text());
        }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }



void MainWindow::dropEvent(QDropEvent *event)
{
  const QMimeData *mimeData = event->mimeData();
  if (mimeData->hasUrls())
  {
    for (const QUrl &url : mimeData->urls())
    {
      QString fileName = url.toLocalFile();
      QFile file(fileName);
      if (file.open(QIODevice::ReadOnly))
      {
        QTextEdit *textEdit = new QTextEdit();
        QTextStream in(&file);
        textEdit->setText(in.readAll());

        QMdiSubWindow *subWindow = mdiArea->addSubWindow(textEdit);
        subWindow->setWindowTitle(fileName);
        subWindow->show();
      }
    }
  }
}

void MainWindow::on_actionRedo_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->undo();
}


void MainWindow::on_actionKop_rovat_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->copy();
}


void MainWindow::on_actionVlo_it_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->paste();
}


void MainWindow::on_actionVybrat_v_e_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->selectAll();
}


void MainWindow::on_actionVyst_ihnout_triggered()
{
    QTextEdit* textEdit = getActiveTextEdit(mdiArea);
    textEdit->cut();
}

