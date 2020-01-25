#ifndef MODELSCAN_H
#define MODELSCAN_H

#include <QObject>
#include <QAbstractTableModel>
#include "vstbucket.h"
#include "scanresult.h"
class ScanHandler;

class ModelScan : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelScan(const QList<VstBucket> *pVstBuckets, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool mUpdateView;
    const QList<VstBucket> *mVstBuckets;
    QList<ScanResult> mScanResults;
    void triggerScan();
    void emptyModel();

private:
    ScanHandler *scanHandler;

signals:
    void signalTableOperationFinished();

public slots:
    void slotFillModel();
    void slotSelectEntry(QList<int> selectionIndices);
    void slotUnselectEntry(QList<int> selectionIndices);
};

#endif // MODELSCAN_H
