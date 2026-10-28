#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include "colorconverter.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onRgbChanged();
    void onCmykChanged();
    void onHlsChanged();
    void openColorDialog();

private:
    void setupUi();
    void updateUiFromRgb(const RGBColor& rgb);
    void updatePreview(const RGBColor& rgb);

    // Флаг блокировки сигналов для предотвращения зацикливания обратных вызовов
    bool m_updatingUi = false;

    // RGB Controls
    QSpinBox* spinR;
    QSpinBox* spinG;
    QSpinBox* spinB;
    QSlider* sliderR;
    QSlider* sliderG;
    QSlider* sliderB;

    // CMYK Controls (в процентах 0..100)
    QSpinBox* spinC;
    QSpinBox* spinM;
    QSpinBox* spinY;
    QSpinBox* spinK;
    QSlider* sliderC;
    QSlider* sliderM;
    QSlider* sliderY;
    QSlider* sliderK;

    // HLS Controls (H: 0..360, L/S: 0..100%)
    QSpinBox* spinH;
    QSpinBox* spinL;
    QSpinBox* spinS;
    QSlider* sliderH;
    QSlider* sliderL;
    QSlider* sliderS;

    // Palette & Preview
    QPushButton* btnPalette;
    QLabel* colorPreview;
};

#endif // MAINWINDOW_H