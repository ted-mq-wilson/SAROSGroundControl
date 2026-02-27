#include "HeatmapController.h"

HeatmapController::HeatmapController(QObject* parent)
    : QAbstractListModel(parent)
{
}

int HeatmapController::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _points.count();
}

QVariant HeatmapController::data(const QModelIndex &index, int role) const {
    // qDebug() << "DATA REQUESTED: " << role;

    if (!index.isValid() || index.row() >= _points.count())
        return QVariant();

    const DetectionPoint& point = _points.at(index.row());

    switch (role) {
        case LatitudeRole: return point.latitude;
        case LongitudeRole: return point.longitude;
        case ProbabilityRole: return point.probability;
        default: return QVariant();
    }
}

QHash<int, QByteArray> HeatmapController::roleNames() const {
    return {
        { LatitudeRole, "latitude" },
        { LongitudeRole, "longitude" },
        { ProbabilityRole, "probability" }
    };
}

void HeatmapController::addPoint(double lat, double lon, float probability) {
    // qDebug() << "ADDING POINT: " << lat << lon << probability;

    beginInsertRows(QModelIndex(), _points.count(), _points.count());
    _points.append({lat, lon, probability});
    endInsertRows();
}
