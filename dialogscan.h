#ifndef DIALOGSCAN_H
#define DIALOGSCAN_H

#include <QObject>
#include <QDialog>
#include <enums.h>
#include <QModelIndexList>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QSpacerItem;
class QDialogButtonBox;
class QTableView;
class QComboBox;
class QSortFilterProxyModel;
class ModelScan;
class VstBucket;
class QMenu;
class QShortcut;

class DialogScan : public QDialog
{
    Q_OBJECT
public:
    DialogScan(const QList<VstBucket> *pVstBuckets);

private:
    const QList<VstBucket> *mVstBuckets;
    QVBoxLayout *mLayoutVMain;
    QHBoxLayout *mLayoutHScanFolder;
    QHBoxLayout *mLayoutHListView;
    QVBoxLayout *mLayoutVListViewLeft;
    QVBoxLayout *mLayoutVListViewRight;
    QHBoxLayout *mLayoutHBottom;
    QLabel *mLabelScanFolder;
    QLineEdit *mLineEditScanFolder;
    QPushButton *mPushButtonSelectFolder;
    QPushButton *mPushButtonScan;
    QPushButton *mPushButtonFilter;
    QPushButton *mPushButtonCancel;
    QPushButton *mPushButtonAdd;
    QTableView *mTableview;
    QWidget *mFilterBar;
    QHBoxLayout *mFilterBarLayout;
    QLabel *mFilterBarLabel;
    QLineEdit *mFilterBarLineEdit;
    QPushButton *mFilterBarCloseButton;
    ModelScan *mModelScan;
    void setupUI();
    QStringList scanFindings;
    QSortFilterProxyModel *mSortFilter;
    QMenu *mouseMenu;
    QAction *actionSelect;
    QAction *actionUnselect;
    QAction *actionFilter;
    QAction *actionResize;
    QShortcut *shortcutSelect;
    QShortcut *shortcutUnselect;
    QShortcut *shortcutFilter;
    void setupMouseMenu();
    void enableViewUpdate(bool enable);
    void repaintTableview();
    QList<int> getSelectionOrigIdx(QModelIndexList indexList);
private slots:
    void slotSelectScanFolder();
    void slotScan();
    void slotScanDone();
    void slotCancel();
    void slotAdd();

    void slotMouseRightClickOnEntry(QPoint point);
    void slotFilterBarClose();
    void slotFilterBar();
    void slotSelectEntry();
    void slotUnselectEntry();
    void slotFilterBarOpen();
    void slotResizeTableToContent();
signals:
    void signalScanSelection(QStringList scanSelection);
};

#endif // DIALOGSCAN_H
