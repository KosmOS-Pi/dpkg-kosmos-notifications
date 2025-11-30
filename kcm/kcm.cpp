#include "kcm.h"
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>

K_PLUGIN_FACTORY_WITH_JSON(KosmosKCMFactory, "kcm.json", registerPlugin<KosmosKCM>();)

KosmosKCM::KosmosKCM(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
{
    auto *layout = new QVBoxLayout(this);
    setLayout(layout);

    auto *quickWidget = new QQuickWidget(this);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    quickWidget->engine()->rootContext()->setContextProperty("kcm", this);

    quickWidget->engine()->addImportPath("qrc:/");
    quickWidget->setSource(QUrl("qrc:/contents/ui/main.qml"));

    layout->addWidget(quickWidget);
}

/* ----------- CHECK AUTOSTART OVERRIDE ----------- */

static QString overridePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
           + "/autostart/kosmos-notifications.desktop";
}

/* ----------- LOAD: READ CURRENT STATE ----------- */

void KosmosKCM::load()
{
    QFile autostartFile(overridePath());

    m_enabled = !autostartFile.exists();   // override = disabled
    Q_EMIT enabledChanged();

    changed(false);
}

/* ----------- SAVE: APPLY CHANGES ----------- */

void KosmosKCM::save()
{
    QFile f(overridePath());

    if (m_enabled) {
        // Remove override → ENABLE autostart
        if (f.exists())
            f.remove();
    } else {
        // Create override → DISABLE autostart
        QDir().mkpath(QFileInfo(f).path());
        f.open(QFile::WriteOnly);
        f.write("[Desktop Entry]\nHidden=true\n");
        f.close();
    }

    changed(false);
}

/* ----------- DEFAULTS ----------- */

void KosmosKCM::defaults()
{
    m_enabled = true; // default: autostart enabled
    Q_EMIT enabledChanged();
    changed(true);
}

/* ----------- PROPERTY SETTER ----------- */

void KosmosKCM::setEnabled(bool value)
{
    if (m_enabled == value)
        return;

    m_enabled = value;
    Q_EMIT enabledChanged();
    changed(true);
}

#include "kcm.moc"
