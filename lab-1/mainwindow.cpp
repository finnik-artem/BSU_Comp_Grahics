#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    onRgbChanged(); // Инициализация цвета по умолчанию
}

void MainWindow::setupUi() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Цветовые модели: RGB - CMYK - HLS");

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // --- RGB Group ---
    QGroupBox* rgbGroup = new QGroupBox("RGB Model", this);
    QGridLayout* rgbLayout = new QGridLayout(rgbGroup);

    spinR = new QSpinBox(); spinR->setRange(0, 255);
    spinG = new QSpinBox(); spinG->setRange(0, 255);
    spinB = new QSpinBox(); spinB->setRange(0, 255);

    sliderR = new QSlider(Qt::Horizontal); sliderR->setRange(0, 255);
    sliderG = new QSlider(Qt::Horizontal); sliderG->setRange(0, 255);
    sliderB = new QSlider(Qt::Horizontal); sliderB->setRange(0, 255);

    rgbLayout->addWidget(new QLabel("R:"), 0, 0); rgbLayout->addWidget(spinR, 0, 1); rgbLayout->addWidget(sliderR, 0, 2);
    rgbLayout->addWidget(new QLabel("G:"), 1, 0); rgbLayout->addWidget(spinG, 1, 1); rgbLayout->addWidget(sliderG, 1, 2);
    rgbLayout->addWidget(new QLabel("B:"), 2, 0); rgbLayout->addWidget(spinB, 2, 1); rgbLayout->addWidget(sliderB, 2, 2);

    // --- CMYK Group ---
    QGroupBox* cmykGroup = new QGroupBox("CMYK Model (%)", this);
    QGridLayout* cmykLayout = new QGridLayout(cmykGroup);

    spinC = new QSpinBox(); spinC->setRange(0, 100);
    spinM = new QSpinBox(); spinM->setRange(0, 100);
    spinY = new QSpinBox(); spinY->setRange(0, 100);
    spinK = new QSpinBox(); spinK->setRange(0, 100);

    sliderC = new QSlider(Qt::Horizontal); sliderC->setRange(0, 100);
    sliderM = new QSlider(Qt::Horizontal); sliderM->setRange(0, 100);
    sliderY = new QSlider(Qt::Horizontal); sliderY->setRange(0, 100);
    sliderK = new QSlider(Qt::Horizontal); sliderK->setRange(0, 100);

    cmykLayout->addWidget(new QLabel("C:"), 0, 0); cmykLayout->addWidget(spinC, 0, 1); cmykLayout->addWidget(sliderC, 0, 2);
    cmykLayout->addWidget(new QLabel("M:"), 1, 0); cmykLayout->addWidget(spinM, 1, 1); cmykLayout->addWidget(sliderM, 1, 2);
    cmykLayout->addWidget(new QLabel("Y:"), 2, 0); cmykLayout->addWidget(spinY, 2, 1); cmykLayout->addWidget(sliderY, 2, 2);
    cmykLayout->addWidget(new QLabel("K:"), 3, 0); cmykLayout->addWidget(spinK, 3, 1); cmykLayout->addWidget(sliderK, 3, 2);

    // --- HLS Group ---
    QGroupBox* hlsGroup = new QGroupBox("HLS Model", this);
    QGridLayout* hlsLayout = new QGridLayout(hlsGroup);

    spinH = new QSpinBox(); spinH->setRange(0, 360);
    spinL = new QSpinBox(); spinL->setRange(0, 100);
    spinS = new QSpinBox(); spinS->setRange(0, 100);

    sliderH = new QSlider(Qt::Horizontal); sliderH->setRange(0, 360);
    sliderL = new QSlider(Qt::Horizontal); sliderL->setRange(0, 100);
    sliderS = new QSlider(Qt::Horizontal); sliderS->setRange(0, 100);

    hlsLayout->addWidget(new QLabel("H (°):"), 0, 0); hlsLayout->addWidget(spinH, 0, 1); hlsLayout->addWidget(sliderH, 0, 2);
    hlsLayout->addWidget(new QLabel("L (%):"), 1, 0); hlsLayout->addWidget(spinL, 1, 1); hlsLayout->addWidget(sliderL, 1, 2);
    hlsLayout->addWidget(new QLabel("S (%):"), 2, 0); hlsLayout->addWidget(spinS, 2, 1); hlsLayout->addWidget(sliderS, 2, 2);

    // --- Control & Preview Panel ---
    QVBoxLayout* rightLayout = new QVBoxLayout();
    btnPalette = new QPushButton("Выбрать из палитры...", this);
    colorPreview = new QLabel(this);
    colorPreview->setMinimumSize(120, 120);
    colorPreview->setFrameShape(QFrame::Box);

    rightLayout->addWidget(btnPalette);
    rightLayout->addWidget(colorPreview);
    rightLayout->addStretch();

    // Adding controls to left container
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(rgbGroup);
    leftLayout->addWidget(cmykGroup);
    leftLayout->addWidget(hlsGroup);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    // --- Signal Connections ---

    // Лямбда-функция для двусторонней синхронизации слайдера и спинбокса
    auto bindSliderAndSpin = [this](QSlider* slider, QSpinBox* spin) {
        connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
        connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
    };

    bindSliderAndSpin(sliderR, spinR);
    bindSliderAndSpin(sliderG, spinG);
    bindSliderAndSpin(sliderB, spinB);

    bindSliderAndSpin(sliderC, spinC);
    bindSliderAndSpin(sliderM, spinM);
    bindSliderAndSpin(sliderY, spinY);
    bindSliderAndSpin(sliderK, spinK);

    bindSliderAndSpin(sliderH, spinH);
    bindSliderAndSpin(sliderL, spinL);
    bindSliderAndSpin(sliderS, spinS);

    // Рекурсивные пересчеты моделей при изменении значений через SpinBox
    connect(spinR, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onRgbChanged);
    connect(spinG, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onRgbChanged);
    connect(spinB, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onRgbChanged);

    connect(spinC, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onCmykChanged);
    connect(spinM, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onCmykChanged);
    connect(spinY, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onCmykChanged);
    connect(spinK, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onCmykChanged);

    connect(spinH, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onHlsChanged);
    connect(spinL, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onHlsChanged);
    connect(spinS, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onHlsChanged);

    connect(btnPalette, &QPushButton::clicked, this, &MainWindow::openColorDialog);
}

void MainWindow::onRgbChanged() {
    if (m_updatingUi) return;

    RGBColor rgb{ static_cast<double>(spinR->value()),
                   static_cast<double>(spinG->value()),
                   static_cast<double>(spinB->value()) };

    CMYKColor cmyk = ColorConverter::rgbToCmyk(rgb);
    HLSColor hls = ColorConverter::rgbToHls(rgb);

    m_updatingUi = true;
    spinC->setValue(std::round(cmyk.c * 100));
    spinM->setValue(std::round(cmyk.m * 100));
    spinY->setValue(std::round(cmyk.y * 100));
    spinK->setValue(std::round(cmyk.k * 100));

    spinH->setValue(std::round(hls.h));
    spinL->setValue(std::round(hls.l * 100));
    spinS->setValue(std::round(hls.s * 100));
    m_updatingUi = false;

    updatePreview(rgb);
}

void MainWindow::onCmykChanged() {
    if (m_updatingUi) return;

    CMYKColor cmyk{ spinC->value() / 100.0,
                     spinM->value() / 100.0,
                     spinY->value() / 100.0,
                     spinK->value() / 100.0 };

    RGBColor rgb = ColorConverter::cmykToRgb(cmyk);
    HLSColor hls = ColorConverter::rgbToHls(rgb);

    m_updatingUi = true;
    spinR->setValue(std::round(rgb.r));
    spinG->setValue(std::round(rgb.g));
    spinB->setValue(std::round(rgb.b));

    spinH->setValue(std::round(hls.h));
    spinL->setValue(std::round(hls.l * 100));
    spinS->setValue(std::round(hls.s * 100));
    m_updatingUi = false;

    updatePreview(rgb);
}

void MainWindow::onHlsChanged() {
    if (m_updatingUi) return;

    HLSColor hls{ static_cast<double>(spinH->value()),
                   spinL->value() / 100.0,
                   spinS->value() / 100.0 };

    RGBColor rgb = ColorConverter::hlsToRgb(hls);
    CMYKColor cmyk = ColorConverter::rgbToCmyk(rgb);

    m_updatingUi = true;
    spinR->setValue(std::round(rgb.r));
    spinG->setValue(std::round(rgb.g));
    spinB->setValue(std::round(rgb.b));

    spinC->setValue(std::round(cmyk.c * 100));
    spinM->setValue(std::round(cmyk.m * 100));
    spinY->setValue(std::round(cmyk.y * 100));
    spinK->setValue(std::round(cmyk.k * 100));
    m_updatingUi = false;

    updatePreview(rgb);
}

void MainWindow::openColorDialog() {
    QColor color = QColorDialog::getColor(
        QColor(spinR->value(), spinG->value(), spinB->value()),
        this,
        "Выберите цвет"
    );

    if (color.isValid()) {
        spinR->setValue(color.red());
        spinG->setValue(color.green());
        spinB->setValue(color.blue());
    }
}

void MainWindow::updatePreview(const RGBColor& rgb) {
    int r = std::clamp(static_cast<int>(std::round(rgb.r)), 0, 255);
    int g = std::clamp(static_cast<int>(std::round(rgb.g)), 0, 255);
    int b = std::clamp(static_cast<int>(std::round(rgb.b)), 0, 255);

    QString style = QString("background-color: rgb(%1, %2, %3); border: 1px solid black;").arg(r).arg(g).arg(b);
    colorPreview->setStyleSheet(style);
}