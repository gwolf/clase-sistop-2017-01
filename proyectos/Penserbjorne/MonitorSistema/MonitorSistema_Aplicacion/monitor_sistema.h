#ifndef MONITOR_SISTEMA_H
#define MONITOR_SISTEMA_H

#include <QObject>

class monitor_sistema : public QObject
{
    Q_OBJECT
public:
    explicit monitor_sistema(QObject *parent = 0);

signals:
    void solicito_informacion_del_sistema();

public slots:
    void quiero_informacion_del_sistema(){ emit solicito_informacion_del_sistema(); }

private:
};

#endif // MONITOR_SISTEMA_H
