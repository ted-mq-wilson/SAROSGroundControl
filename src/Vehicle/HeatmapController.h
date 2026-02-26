#pragma once

#include <QAbstractListModel>

struct DetectionPoint {
    double latitude;
    double longitude;
    float probability;
};

class HeatmapController : public QAbstractListModel
{
    Q_OBJECT

   public:
    enum Roles {
        LatitudeRole = Qt::UserRole + 1,
        LongitudeRole,
        ProbabilityRole
    };

    HeatmapController(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addPoint(double lat, double lon, float probability);

   private:
    QList<DetectionPoint> _points;
};
