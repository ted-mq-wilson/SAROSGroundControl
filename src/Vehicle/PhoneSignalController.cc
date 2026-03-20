#include "PhoneSignalController.h"

PhoneSignalController::PhoneSignalController(QObject* parent)
    : QAbstractListModel(parent)
{
}

int PhoneSignalController::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _points.count();
}

QVariant PhoneSignalController::data(const QModelIndex &index, int role) const {
    // qDebug() << "DATA REQUESTED: " << role;

    if (!index.isValid() || index.row() >= _points.count())
        return QVariant();

    const pDetectionPoint& point = _points.at(index.row());

    switch (role) {
        case LatitudeRole: return point.latitude;
        case LongitudeRole: return point.longitude;
        case MacAddressRole: return point.mac_address;
        default: return QVariant();
    }
}

QHash<int, QByteArray> PhoneSignalController::roleNames() const {
    return {
        { LatitudeRole, "latitude" },
        { LongitudeRole, "longitude" },
        { MacAddressRole, "mac_address" }
    };
}

void PhoneSignalController::addPoint(double lat, double lon, float mac_address) {
    // qDebug() << "ADDING POINT: " << lat << lon << probability;

    beginInsertRows(QModelIndex(), _points.count(), _points.count());
    _points.append({lat, lon, mac_address});
    endInsertRows();
}
