#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T12:20:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuSolver
TEMPLATE = app


SOURCES += main.cpp\
        sudokusolver.cpp

HEADERS  += sudokusolver.h

FORMS    += sudokusolver.ui

QMAKE_CXXFLAGS += -std=c++11

RC_FILE = sudokusolver.rc
