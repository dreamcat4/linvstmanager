// This file is part of LinVstManager.

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>
#include "enums.h"


class Preferences
{
public:
    Preferences();

    bool updatePreferences(bool pEnabledLinVst,
                           bool pEnabledLinVstX,
                           bool pEnabledLinVst3,
                           bool pEnabledLinVst3X,
                           bool pBridgeDefaultVst2IsX,
                           bool pBridgeDefaultVst3IsX,
                           bool pHideBlacklisted,
                           const QString &pPathSoLinVst,
                           const QString &pPathSoLinVstX,
                           const QString &pPathSoLinVst3,
                           const QString &pPathSoLinVst3X,
                           const QString &pPathLinkFolder,
                           const QString &pPathCheckTool64,
                           const QString &pPathCheckTool32,
                           QVector<VstBridge> &pChangedBridges);

    QString getPathLinkFolder() const;
    QString getPathCheckTool64() const;
    QString getPathCheckTool32() const;
    bool checkTool64Enabled() const;
    bool checkTool32Enabled() const;
    bool getBridgeDefaultVst2IsX() const;
    bool getBridgeDefaultVst3IsX() const;
    bool getHideBlacklisted() const;
    bool setHideBlacklisted(bool value);
    bool bridgeEnabled(VstBridge bridgeType) const;
    QString getPathSoTmplBridge(VstBridge bridgeType) const;

private:
    bool enabledLinVst;
    bool enabledLinVstX;
    bool enabledLinVst3;
    bool enabledLinVst3X;
    bool bridgeDefaultVst2IsX;
    bool bridgeDefaultVst3IsX;
    bool hideBlacklisted;
    QString pathSoLinVst;
    QString pathSoLinVstX;
    QString pathSoLinVst3;
    QString pathSoLinVst3X;
    QString pathLinkFolder;
    QString pathCheckTool64;
    QString pathCheckTool32;
};

#endif // PREFERENCES_H
