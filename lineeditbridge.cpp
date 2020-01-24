#include "lineeditbridge.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QGroupBox>
#include <QSizePolicy>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>


LineEditBridge::LineEditBridge(QString t_name, QWidget *parent) : QWidget(parent)
{
    this->name = t_name;

    mCheckBoxBridge = new QCheckBox();

    mLineEditBridge = new QLineEdit();
    mLineEditBridge->setReadOnly(true);
    mLineEditBridge->setEnabled(false);
    mLineEditBridge->setToolTip("Specify the *.so template file for bridge: " + name);

    palette = new QPalette();
    paletteDefault = new QPalette(mLineEditBridge->palette());

    QSizePolicy sp = mLineEditBridge->sizePolicy();
    sp.setHorizontalStretch(1);
    mLineEditBridge->setSizePolicy(sp);

    mPushButtonBridge = new QPushButton("Select");
    mPushButtonBridge->setEnabled(false);

    mLabelBridge = new QLabel(name + ":");
    mLabelBridge->setEnabled(false);
    mLabelBridge->setMinimumWidth(65);

    mLayoutHBridge = new QHBoxLayout();
    mLayoutHBridge->addWidget(mCheckBoxBridge);
    mLayoutHBridge->addWidget(mLabelBridge);
    mLayoutHBridge->addWidget(mLineEditBridge);
    mLayoutHBridge->addWidget(mPushButtonBridge);
    mLayoutHBridge->setSpacing(2);
    mLayoutHBridge->setMargin(0);
    this->adjustSize();

    this->setLayout(mLayoutHBridge);

    connect(mCheckBoxBridge, &QCheckBox::clicked, this, &LineEditBridge::slotCheckBoxBridge);
    connect(mPushButtonBridge, &QPushButton::pressed, this, &LineEditBridge::slotPushButtonSelectBridge);
}

bool LineEditBridge::getBridgeEnabled()
{
    return mCheckBoxBridge->isChecked();
}

bool LineEditBridge::pathIsSet()
{
    if (mLineEditBridge->text() == "") {
        return false;
    } else {
        return true;
    }
}

QString LineEditBridge::getPath()
{
    return mLineEditBridge->text();
}

void LineEditBridge::setBridgeEnabled(bool setEnabled)
{
    if (setEnabled) {
        mCheckBoxBridge->setChecked(true);
        mLabelBridge->setEnabled(true);
        mLineEditBridge->setEnabled(true);
        mPushButtonBridge->setEnabled(true);
    } else {
        mCheckBoxBridge->setChecked(false);
        mLabelBridge->setEnabled(false);
        mLineEditBridge->setEnabled(false);
        mPushButtonBridge->setEnabled(false);
    }
}

void LineEditBridge::setPath(QString path)
{
    mLineEditBridge->setText(path);
}

void LineEditBridge::slotCheckBoxBridge()
{
    if (mCheckBoxBridge->isChecked()) {
        mLineEditBridge->setEnabled(true);
        mPushButtonBridge->setEnabled(true);
        mLabelBridge->setEnabled(true);

        // Check if previously set so-file still exists.
        // If not, color text red.
        if (mLineEditBridge->text() != "") {
            QString filePath = mLineEditBridge->text();
            if (QFileInfo::exists(filePath) && QFileInfo(filePath).isFile()) {
                mLineEditBridge->setPalette(*paletteDefault);
            } else {
                palette->setColor(QPalette::Text,Qt::red);
                mLineEditBridge->setPalette(*palette);
            }
        }
        emit signalCheckBoxBridge(true);
    } else {
        mLineEditBridge->setEnabled(false);
        mPushButtonBridge->setEnabled(false);
        mLabelBridge->setEnabled(false);
        emit signalCheckBoxBridge(false);
    }
}

void LineEditBridge::slotPushButtonSelectBridge()
{
    static QString lastDir = QDir::homePath();
    QString filepath_bridgeSoFile = QFileDialog::getOpenFileName(this,
                                     "Select the *.so template file for bridge: " + name, lastDir,
                                     "(*.so)");
    if (!filepath_bridgeSoFile.isEmpty()) {
        lastDir = QFileInfo(filepath_bridgeSoFile).path();
        mLineEditBridge->setText(filepath_bridgeSoFile);
    }
}
