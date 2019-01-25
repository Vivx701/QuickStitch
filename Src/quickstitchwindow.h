#ifndef QUICKSTITCHWINDOW_H
#define QUICKSTITCHWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>
#include "imagestitcher.h"

namespace Ui {
class QuickStitchWindow;
}

class QuickStitchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuickStitchWindow(QWidget *parent = 0);
    ImageList getImageList();
    ~QuickStitchWindow();

private:
    Ui::QuickStitchWindow *ui;
    ImageStitcher *stitcher;
    QColor bgColor;

private slots:

    void onAddImageButtonClicked();
    void onRemoveImageButtonClicked();
    void onMoveUpButtonClicked();
    void onMoveDownButtonClicked();

    void onHStitchButtonClicked();
    void onVStitchButtonClicked();
    void onChooseColor();
    void startStich(ImageList imgList, StitchType type);
    void showErrorMessage(QString heading, QString message);

signals:
    void showError(QString heading, QString message);
};

#endif // QUICKSTITCHWINDOW_H
