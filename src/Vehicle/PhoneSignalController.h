#pragma once

#include <QAbstractListModel>

struct pDetectionPoint {
    double latitude;
    double longitude;
    float mac_address;
};

class PhoneSignalController : public QAbstractListModel
{
    Q_OBJECT

   public:
    enum Roles {
        LatitudeRole = Qt::UserRole + 1,
        LongitudeRole,
        MacAddressRole
    };

    PhoneSignalController(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addPoint(double lat, double lon, float probability);

   private:
    QList<pDetectionPoint> _points;
};
