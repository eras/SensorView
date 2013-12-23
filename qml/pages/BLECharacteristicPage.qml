import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: characteristicPage

    property string name

    SilicaFlickable {
        anchors.fill: parent
        /* contentWidth: column.width */
	/* contentHeight: column.height */

	Column {
	    id: column
	    anchors.fill: parent
            PageHeader {
		title: "Characteristic"
            }

            Label {
		id: text
		text: name
		font.pixelSize: 30
            }
	    
            Label {
		id: text2
		text: "diudau"
            }
	}
    }
}


