#include "optionseditor.h"
#include "ui_optionseditor.h"

#include <tilegen/alpha/CalculatorMode.h>

OptionsEditor::OptionsEditor(QWidget *parent_) :
    QDockWidget(parent_),
    mUi(new Ui::OptionsEditor)
{
    mUi->setupUi(this);
    mUi->alphaCalculatorModeComboBox->addItems([this]()
    {
        QStringList list;
        for (const auto calculatorMode : tilegen::alpha::calculatorModeByName)
        {
            list << QString(calculatorMode.first.c_str());
        }
        return list;
    }());
    mUi->defaultOuputDirCheckBox->setCheckState(Qt::Checked);
    mUi->tabWidget->setCurrentIndex(0);

    connect(mUi->alphaCalculatorModeComboBox, SIGNAL(activated(const QString&)), this, SLOT(setAlphaCalculatorMode(const QString&)));
    connect(mUi->restoreOptionsButton, SIGNAL(pressed()), this->parent(), SLOT(resetOptions()));
    connect(mUi->defaultOuputDirCheckBox, SIGNAL(stateChanged(int)), this, SLOT(switchDefaultOutputDirFlag(int)));
}

OptionsEditor::~OptionsEditor()
{
    delete mUi;
}

bool OptionsEditor::useDefaultOuputDir() const
{
    return mUseDefaultOutputDir;
}

void OptionsEditor::setOptions(Options *options)
{
    mOptions = options;
    setAlphaCalculatorModeComboBox();
}

void OptionsEditor::setAlphaCalculatorMode(const QString& mode_name)
{
    mOptions->calculatorMode = tilegen::alpha::calculatorModeByName.at(mode_name.toLocal8Bit().constData());
}

void OptionsEditor::switchDefaultOutputDirFlag(int newCheckboxState)
{
    mUseDefaultOutputDir = (newCheckboxState == Qt::Checked);
}

void OptionsEditor::setAlphaCalculatorModeComboBox()
{
    for (const auto& mode : tilegen::alpha::calculatorModeByName)
    {
        if (mode.second == mOptions->calculatorMode)
        {
            mUi->alphaCalculatorModeComboBox->setCurrentText(QString(mode.first.c_str()));
            return;
        }
    }
}
