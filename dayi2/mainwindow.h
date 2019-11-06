
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./audioctl/audiorecorder.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QDialog>
#include <QVariantMap>

#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWebEngineView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int SetWebTitle(const QByteArray &message);
    int recvWindowInfo(const QByteArray &message);
    ~MainWindow();
   int SetWebWiew(int mode,int wide,int high);
   void slot_KeyLocation();
 // void resizeEvent(QResizeEvent *event);
public slots:
   void adjustLocation();


//protected:
 //  QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);


private slots:
    void onBackBtnClicked();

private:
 //   QWebEngineView *view;
    Ui::MainWindow *ui;
    QWidget *m_start_Screen;
    QAction *m_escAct;
    QPushButton* m_backBtn;
   // AudioRecorder *recorder;
};

#endif // MAINWINDOW_H
