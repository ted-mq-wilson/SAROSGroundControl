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
    if (!index.isValid())
        return QVariant();

    const DetectionPoint& point = _points[index.row()];

    switch (role) {
        case LatitudeRole: return point.latitude;
        case LongitudeRole: return point.longitude;
        case ProbabilityRole: return point.probability;
    }

    return QVariant();
}

QHash<int, QByteArray> HeatmapController::roleNames() const {
    return {
        { LatitudeRole, "latitude" },
        { LongitudeRole, "longitude" },
        { ProbabilityRole, "probability" }
    };
}

void HeatmapController::addPoint(double lat, double lon, float probability) {
    beginInsertRows(QModelIndex(), _points.count(), _points.count());
    _points.append({lat, lon, probability});
    endInsertRows();
}
