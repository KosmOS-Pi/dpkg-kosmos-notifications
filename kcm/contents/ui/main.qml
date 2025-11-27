import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.20 as Kirigami

Kirigami.ScrollablePage {
    title: "News from KosmOS"

    Kirigami.FormLayout {
        Kirigami.Heading {
            text: "KosmOS Notifications"
            level: 2
        }

        Kirigami.Separator {
            Layout.fillWidth: true
        }

        Label {
            text: "Control whether you receive notifications from the KosmOS team. If turned on, you'll get alerts about major events when you log in."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
            Layout.preferredWidth: parent.width
        }

        CheckBox {
            id: cb
            checked: kcm.enabled
            text: "Enable"

            onCheckedChanged: {
                kcm.enabled = checked
            }


        }
    }
}
