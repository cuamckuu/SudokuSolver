#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QWidget>
#include <QObject>
#include <QMessageBox>

namespace Ui {
    class SudokuSolver;
}

class SudokuSolver : public QWidget {
    Q_OBJECT

public:
    explicit SudokuSolver(QWidget *parent = 0);
    ~SudokuSolver();

private slots:
    void on_sovleButton_clicked();
    void on_restartButton_clicked();

private:
    Ui::SudokuSolver *ui;
};

bool SolveSudoku(int,int);

#endif // SUDOKUSOLVER_H
