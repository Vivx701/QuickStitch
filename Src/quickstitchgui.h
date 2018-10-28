#ifndef QUICKSTITCHGUI_H
#define QUICKSTITCHGUI_H

#include <QWidget>

namespace Ui {
class QuickStitchGui;
}

class QuickStitchGui : public QWidget
{
    Q_OBJECT

public:
    explicit QuickStitchGui(QWidget *parent = 0);
    ~QuickStitchGui();
private slots:

    void onAddImageButtonClicked();
    void showError(QString title, QString message);
    void onRemoveImageButtonClicked();
    void onMoveUpButtonClicked();
    void onMoveDownButtonClicked();
    void openStitchDialog();

private:
    Ui::QuickStitchGui *ui;
};

#endif // QUICKSTITCHGUI_H
