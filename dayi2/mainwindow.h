#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./audioctl/audiorecorder.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QDialog>
#include <QVariantMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   int SetWebWiew(int mode,int wide,int high);
   void resizeEvent(QResizeEvent *event);
public slots:
   void adjustLocation();
private:
    QWebEngineView *view;
   // Ui::MainWindow *ui;
    QWidget *m_start_Screen;
   // AudioRecorder *recorder;
};

#endif // MAINWINDOW_H
