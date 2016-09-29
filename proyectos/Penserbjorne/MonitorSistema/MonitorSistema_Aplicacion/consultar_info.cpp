#include <QProcess>

#include "string"
#include "consultar_info.h"
#include "struct_cpuinfo.h"

consultar_info::consultar_info()
{
    propiedades_cpuinfo[0] = "processor";
    propiedades_cpuinfo[1] = "vendor_id";
    propiedades_cpuinfo[2] = "cpu family";
    propiedades_cpuinfo[3] = "model";
    propiedades_cpuinfo[4] = "model name";
    propiedades_cpuinfo[5] = "stepping";
    propiedades_cpuinfo[6] = "cpu MHz";
    propiedades_cpuinfo[7] = "cache size";
    propiedades_cpuinfo[8] = "physical id";
    propiedades_cpuinfo[9] = "siblings";
    propiedades_cpuinfo[10] = "core id";
    propiedades_cpuinfo[11] = "cpu cores";

}

QByteArray consultar_info::ejecutar_comando(string comando){
    QString qcommand = QString::fromStdString(comando);
    QProcess *myProcess = new QProcess();
    QByteArray processOutput;
    myProcess->start(qcommand);
    myProcess->waitForStarted();
    myProcess->waitForBytesWritten();
    myProcess->waitForFinished();
    myProcess->waitForReadyRead();
    processOutput = myProcess->readAll();
    return processOutput;
}

vector<struct_CPUINFO> consultar_info::consultar_cpuinfo(QByteArray info){
    int contador;
    struct_CPUINFO cpuinfo;
    vector<struct_CPUINFO> cores;
    QList<QByteArray> propiedades = info.split('\n');

    contador = 0;
    foreach( const QByteArray &propiedad, propiedades)
    {
        if(propiedad.toStdString().find(propiedades_cpuinfo[contador]) != string::npos){
            QList<QByteArray> valor_propiedad = propiedad.split(':');
            cpuinfo.asignarValor(contador,valor_propiedad[1].toStdString());
            contador++;
            if(contador >= num_props_cpuinfo){
                cores.push_back(cpuinfo);
                contador = 0;
            }
        }
    }
    return cores;
}
