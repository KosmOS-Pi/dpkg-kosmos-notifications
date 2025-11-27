#pragma once

#include <KCModule>
#include <KPluginFactory>

#include <QVBoxLayout>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>

class KosmosKCM : public KCModule
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit KosmosKCM(QWidget *parent = nullptr, const QVariantList &args = QVariantList());

    bool enabled() const { return m_enabled; }
    void setEnabled(bool value);

    void load() override;
    void save() override;
    void defaults() override;

signals:
    void enabledChanged();

private:
    bool m_enabled = false;
};
