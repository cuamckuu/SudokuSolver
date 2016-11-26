#include "sudokusolver.h"
#include "ui_sudokusolver.h"

SudokuSolver::SudokuSolver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SudokuSolver)
{
    ui->setupUi(this);
}

SudokuSolver::~SudokuSolver()
{
    delete ui;
}

const int EMPTY = 0;
QVector<QVector<int>> sudoku(9,QVector<int>(9,EMPTY));

bool CheckRow(int rowT, int columnT, int num){
    for(int column = 0; column < 9; column++){
        if(column != columnT && sudoku[rowT][column] == num){
            return 0;
        }
    }
    return 1;
}

bool CheckColumn(int rowT, int columnT, int num){
    for(int row = 0; row < 9; row++){
        if(row != rowT && sudoku[row][columnT] == num){
            return false;
        }
    }
    return true;
}

bool CheckBlock(int rowT, int columnT, int num){
    int row = (rowT/3)*3;
    int column = (columnT/3)*3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if((row+i != rowT || column+j != columnT) && sudoku[row+i][column+j] == num){
                return false;
            }
        }
    }
    return true;
}

//Checks block, row and column
bool IsLegal(int row, int column, int num){
    return (CheckRow(row,column, num) && CheckColumn(row,column, num) && CheckBlock(row,column, num));
}

bool SolveSudoku(int row, int column){
    //Finding next row and column
    int next_row = (column == 8) ? row+1:row;
    int next_column = (column+1) % 9;

    //It means that all(9) rows was solved
    if(row == 9)
        return true;

    //Going to next row and column
    if(sudoku[row][column] != EMPTY)
        return SolveSudoku(next_row, next_column);

    //Trying numbers from 1 to 9
    for(int num = 1; num <= 9; num++){
        sudoku[row][column] = num;

        if(IsLegal(row,column,num) && SolveSudoku(next_row,next_column))
                return true;

        //If it's not ok erase it and try again
        sudoku[row][column] = EMPTY;
    }
    return 0;
}


void SudokuSolver::on_sovleButton_clicked()
{
    QVector<QVector<bool>> visited(9, QVector<bool>(9,false));

    //Read
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            QTableWidgetItem *cell = ui->field->item(i,j);
            if(cell){
                sudoku[i][j] = cell->text().toInt();
                if(sudoku[i][j] != 0){
                    visited[i][j] = true;
                }
            }
        }
    }

    //Stard solving from row 0, column 0
    SolveSudoku(0,0);

    //Print
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(!visited[i][j]){
                ui->field->setItem(i,j, new QTableWidgetItem);
                ui->field->item(i,j)->setBackgroundColor(QColor::fromRgb(139, 0, 255));
                ui->field->item(i,j)->setText(QString::number(sudoku[i][j]));
            }
        }
    }
}

void SudokuSolver::on_restartButton_clicked()
{
    //ClearField
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            ui->field->setItem(i,j, new QTableWidgetItem);
            sudoku[i][j] = EMPTY;
        }
    }
}
