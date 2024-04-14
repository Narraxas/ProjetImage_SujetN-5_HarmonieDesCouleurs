#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_harmonyComboBox_currentTextChanged(const QString &arg1);

    void on_colorBtn_clicked();

    void on_pushButton_2_clicked();

    void on_isBlurred_stateChanged(int arg1);

    void on_isOpenedClosed_stateChanged(int arg1);

    void updateIntensiteFlou(int value);

    void updateSeuilDistance(int value);


    void on_saveBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
