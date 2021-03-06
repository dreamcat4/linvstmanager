// This file is part of LinVstManager.

#ifndef SCANHANDLER_H
#define SCANHANDLER_H

#include <QObject>
#include "enums.h"
#include <QMap>
#include <QVector>
#include "scanresult.h"
#include "vstbucket.h"

class ScanHandler : public QObject
{
    Q_OBJECT
public:
    explicit ScanHandler(const QVector<VstBucket> &pVstBuckets,
                         QString pScanFolder,
                         QString pPathCheckTool64,
                         bool pUseCheckTool64,
                         QString pPathCheckTool32,
                         bool pUseCheckTool32,
                         bool pUseCheckBasic,
                         QObject *parent = nullptr);

private:
    QVector<VstBucket> mVstBuckets;
    QString mScanFolder;
    QString mPathCheckTool64;
    QString mPathCheckTool32;
    bool mUseCheckTool64;
    bool mUseCheckTool32;
    bool mUseCheckBasic;
    QMap<VstType, QString> mapVstExtension;
    void verifyDll(bool &verified, VstType &vstType, BitType &bitType, const QString &finding);
    bool checkDll(QString &pathCheckTool, const QString &findingAbsPath);
    bool checkDllBasic(const QString &findingAbsPath);

signals:
    void signalScanFinished(bool wasCanceled, QVector<ScanResult> scanResults);
    void signalFoundVst3();
    void signalFoundVst2();
    void signalFoundDll();

public slots:
    void slotPerformScan();

};

#endif // SCANHANDLER_H
