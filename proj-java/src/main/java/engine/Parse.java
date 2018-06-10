package src.main.java.engine;
import javax.xml.namespace.QName;
import javax.xml.stream.*;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.time.LocalDate;

public class Parse {
    private Post post;
    private Users users;
    private Tag tag;

    public void parseTags(String fileName, Struct estrutura) {
        XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
        try {
            XMLEventReader xmlEventReader = xmlInputFactory.createXMLEventReader(new FileInputStream(fileName));
            while (xmlEventReader.hasNext()) {
                this.tag = new Tag();
                XMLEvent xmlEvent = xmlEventReader.nextEvent();
                if (xmlEvent.isStartElement()) {
                    StartElement startElement = xmlEvent.asStartElement();
                    if (startElement.getName().getLocalPart().equals("row")) {
                        Attribute idAttr = startElement.getAttributeByName(new QName("Id"));
                        if (idAttr != null) {
                            this.tag.setId(Integer.parseInt(idAttr.getValue()));
                        }
                        Attribute nameAttr = startElement.getAttributeByName(new QName("TagName"));
                        if (nameAttr != null) {
                            this.tag.setTagName(nameAttr.getValue());
                        }
                    }
                }
                estrutura.addTags(this.tag);
            }
        } catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }
    }
}






























