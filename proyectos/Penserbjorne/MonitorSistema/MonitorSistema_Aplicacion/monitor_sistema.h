#ifndef MONITOR_SISTEMA_H
#define MONITOR_SISTEMA_H

#include <QObject>
#include <QDebug>
#include <QThread>

class monitor_sistema : public QObject
{
    Q_OBJECT
public:
    explicit monitor_sistema(QObject *parent = 0);

signals:
    void solicito_informacion_del_sistema();    // Señal para solicitar informacion del sistema
    void solicito_informacion_de_memoria();    // Señal para solicitar informacion de la memoria

public slots:
    // "Request" que emite la señal para solicitar informacion al sistema
    void quiero_informacion_del_sistema(){ emit solicito_informacion_del_sistema(); }
    void quiero_informacion_de_memoria(){ emit solicito_informacion_de_memoria(); }

private:
};

#endif // MONITOR_SISTEMA_H
