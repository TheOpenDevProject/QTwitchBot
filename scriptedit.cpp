#include "scriptedit.h"
#include "ui_scriptedit.h"
#include <QMessageBox>
#include <QString>
scriptEdit::scriptEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scriptEdit)
{
    ui->setupUi(this);

}

void scriptEdit::loadFromFile(QString path_toFile)
{
    if(!path_toFile.isEmpty()){
        scriptFile.setFileName(path_toFile);
    scriptFile.open(QFile::ReadWrite);
    if(scriptFile.isOpen() && scriptFile.isReadable() && scriptFile.isWritable()){
    ui->scriptView->setPlainText(scriptFile.readAll());
    }else{
        QMessageBox error;
        error.setText("There was an error when trying to load your script file (FileIO Error)");
        error.exec();
        delete ui;
    }

    }else{
            QMessageBox error;
            error.setText("There was an error when trying to load your script file (PathLoad)");
            error.exec();
            delete ui;
        }

}

scriptEdit::~scriptEdit()
{
    delete ui;
}

void scriptEdit::on_pushButton_clicked()
{
        //Save and flush buffer
    QByteArray dtr = ui->scriptView->toPlainText().toStdString().c_str();
    scriptFile.write(dtr,dtr.size());
    scriptFile.flush();

}

