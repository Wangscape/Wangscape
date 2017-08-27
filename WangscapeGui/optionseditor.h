#ifndef OPTIONSEDITOR_H
#define OPTIONSEDITOR_H

#include <memory>

#include <QDockWidget>

#include <Options.h>

namespace Ui {
class OptionsEditor;
}

class OptionsEditor : public QDockWidget
{
    Q_OBJECT

public:
    explicit OptionsEditor(QWidget *parent_ = 0);
    ~OptionsEditor();
    bool useDefaultOuputDir() const;
    void setOptions(std::shared_ptr<Options> options);

private slots:
    void setAlphaCalculatorMode(const QString &mode_name);
    void switchDefaultOutputDirFlag(int newCheckboxState);

private:
    void setAlphaCalculatorModeComboBox();
    Ui::OptionsEditor *mUi;
    std::shared_ptr<Options> mOptions;
    bool mUseDefaultOutputDir;
};

#endif // OPTIONSEDITOR_H
