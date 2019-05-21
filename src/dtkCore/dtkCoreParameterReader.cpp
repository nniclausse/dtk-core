// Version: $Id:
//
//

// Code:

#include "dtkCoreParameterReader.h"

#include "dtkCoreParameter.h"
#include "dtkCoreParameterPath.h"

class dtkCoreParameterReaderPrivate
{
public:
    QHash<QString, dtkCoreParameter *> parameters;
    QString param_file;
};

dtkCoreParameterReader::dtkCoreParameterReader(const QString &json_file_path): d(new dtkCoreParameterReaderPrivate)
{
    d->param_file = json_file_path;

    if (json_file_path.isEmpty())
        return;

    if (!this->read()) {
        qWarning() << Q_FUNC_INFO << "The file" << d->param_file << "could not be read.";
    }
}

void dtkCoreParameterReader::setJsonFile(const QString &json_file_path)
{
    d->param_file = json_file_path;
}

bool dtkCoreParameterReader::read(void)
{
    QFile definition_file(d->param_file);

    if(!definition_file.open(QFile::ReadOnly)) {
        return false;
    }

    d->parameters.clear();

    QJsonParseError definition_error;
    QJsonDocument definition_document = QJsonDocument::fromJson(definition_file.readAll(), &definition_error);

    if(definition_error.error != QJsonParseError::NoError) {
        qWarning() << Q_FUNC_INFO << "Error :" << definition_error.errorString() << "parsing" << d->param_file << "offset :" << definition_error.offset << ".";
        return false;
    }

    QJsonObject definition_object = definition_document.object();
    if(!definition_object.contains("contents")) {
        qWarning() << Q_FUNC_INFO << "The nature parameters file should contain a first json object with key 'contents'. The file cannot be processed any further.";
        return false;
    }

    QJsonValue definition_contents = definition_object["contents"];
    QJsonObject definitions;
    if (definition_contents.isObject()) {
        definitions = definition_contents.toObject();
    } else {
        qWarning() << Q_FUNC_INFO << "The first object with key 'contents' must be an object.";
    }

    QStringList keys = definitions.keys();
    for (auto it = definitions.begin(); it != definitions.end(); ++it) {
        QString name = keys.takeFirst();
        if (it->isObject()) {
            QJsonObject content_object = it->toObject();

            QString type = content_object["type"].toString();

            QVariantHash map = content_object.toVariantHash();
            //map.insert("type", type);

            dtkCoreParameter *parameter = dtkCoreParameter::create(map);
            if (!parameter) {
                qWarnings() << "fail to create parameter" << type << map;
                d->parameters.clear();
                return false;
            }

            //parameter->setValue(this->definition[parameter_uid].toObject().toVariantHash());
            d->parameters.insert(name, parameter);


        } else {
            qWarning() << Q_FUNC_INFO << "'contents' sections are expected to contain objects only. Non object entry is ignored.";
        }
    }
    return true;
}

dtkCoreParameterReader::~dtkCoreParameterReader(void)
{
    delete d;
}


QHash<QString, dtkCoreParameter *> dtkCoreParameterReader::parameters(void) const
{
    return d->parameters;
}
