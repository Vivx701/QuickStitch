#ifndef QUICKSTITCHWINDOW_H
#define QUICKSTITCHWINDOW_H

#include <QMainWindow>

namespace Ui {
class QuickStitchWindow;
}

class QuickStitchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuickStitchWindow(QWidget *parent = 0);
    ~QuickStitchWindow();

private:
    Ui::QuickStitchWindow *ui;

private slots:

    void onAddImageButtonClicked();
    void showError(QString title, QString message);
    void onRemoveImageButtonClicked();
    void onMoveUpButtonClicked();
    void onMoveDownButtonClicked();
    void openStitchDialog();
};

#endif // QUICKSTITCHWINDOW_H
