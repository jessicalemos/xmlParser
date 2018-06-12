package engine;
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

    /**
     * Contrutor vazio do Parse
     */    
    public Parse() {
        this.post = new Post();
        this.users = new Users();
        this.tag = new Tag();
    }

    /**
     * Função responsável por fazer o parse dos Posts
     * @param fileName    Caminho para o ficheiro
     * @param estrutura   Estrutura a carregar
     */
    public void parsePosts(String fileName, struct estrutura) {
        XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
        try {
            XMLEventReader xmlEventReader = xmlInputFactory.createXMLEventReader(new FileInputStream(fileName));
            while (xmlEventReader.hasNext()) {
                XMLEvent xmlEvent = xmlEventReader.nextEvent();
                if (xmlEvent.isStartElement()) {
                    StartElement startElement = xmlEvent.asStartElement();
                    if (startElement.getName().getLocalPart().equals("row")) {
                        this.post = new Post();
                        Attribute pIdAttr = startElement.getAttributeByName(new QName("PostTypeId"));
                        if (pIdAttr != null) {
                            this.post.setPostTypeId(Integer.parseInt(pIdAttr.getValue()));
                        }
                        Attribute parentIdAttr = startElement.getAttributeByName(new QName("ParentId"));
                        if (parentIdAttr != null) {
                            this.post.setParentID(Integer.parseInt(parentIdAttr.getValue()));
                        }
                        Attribute ownIdAttr = startElement.getAttributeByName(new QName("OwnerUserId"));
                        if (ownIdAttr != null) {
                            this.post.setOwnerUserID(Integer.parseInt(ownIdAttr.getValue()));
                        }
                        Attribute ACountAttr = startElement.getAttributeByName(new QName("AnswerCount"));
                        if (ACountAttr != null) {
                            this.post.setAnswerCount(Integer.parseInt(ACountAttr.getValue()));
                        }
                        Attribute CCountAttr = startElement.getAttributeByName(new QName("CommentCount"));
                        if (CCountAttr != null) {
                            this.post.setCommentCount(Integer.parseInt(CCountAttr.getValue()));
                        }
                        Attribute scoreAttr = startElement.getAttributeByName(new QName("Score"));
                        if (scoreAttr != null) {
                            this.post.setScore(Integer.parseInt(scoreAttr.getValue()));
                        }
                        Attribute idAttr = startElement.getAttributeByName(new QName("Id"));
                        if (idAttr != null) {
                            this.post.setId(Integer.parseInt(idAttr.getValue()));
                        }
                        Attribute dateAttr = startElement.getAttributeByName(new QName("CreationDate"));
                        String d = dateAttr.getValue();
                        StringBuilder sb = new StringBuilder();
                        for(int i=0; d.charAt(i)!='T' && d!=null; i++) {
                            sb.append(d.charAt(i));
                        }
                        LocalDate date = LocalDate.now();
                        if (sb.toString() != null) {
                            date = LocalDate.parse(sb.toString());
                        }
                        Attribute tittleAttr = startElement.getAttributeByName(new QName("Title"));
                        if (tittleAttr != null) {
                            this.post.setTitle(tittleAttr.getValue());
                        }

                        Attribute tagAttr = startElement.getAttributeByName(new QName("Tags"));
                        if (tagAttr != null) {
                            this.post.setTag(tagAttr.getValue());
                        }
                        estrutura.addPosts(this.post, date);
                    }
                }
            }
        } catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }
    }

    /**
     * Função responsável por fazer o parse dos Users
     * @param fileName   Caminho para o ficheiro
     * @param estrutura  Estrutura a carregar
     */
    public void parseUsers(String fileName, struct estrutura) {
        XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
        try {
            XMLEventReader xmlEventReader = xmlInputFactory.createXMLEventReader(new FileInputStream(fileName));
            while (xmlEventReader.hasNext()) {
                this.users = new Users();
                XMLEvent xmlEvent = xmlEventReader.nextEvent();
                if (xmlEvent.isStartElement()) {
                    StartElement startElement = xmlEvent.asStartElement();
                    if (startElement.getName().getLocalPart().equals("row")) {
                        Attribute idAttr = startElement.getAttributeByName(new QName("Reputation"));
                        if (idAttr != null) {
                            this.users.setReputation(Integer.parseInt(idAttr.getValue()));
                        }
                        Attribute ownerIdAttr = startElement.getAttributeByName(new QName("Id"));
                        if (ownerIdAttr != null) {
                            this.users.setOwnerUserId(Integer.parseInt(ownerIdAttr.getValue()));
                        }
                        Attribute nameAttr = startElement.getAttributeByName(new QName("DisplayName"));
                        if (nameAttr != null) {
                            this.users.setDisplayName(nameAttr.getValue());
                        }
                        Attribute aboutAttr = startElement.getAttributeByName(new QName("AboutMe"));
                        if (aboutAttr != null) {
                            this.users.setAboutMe(aboutAttr.getValue());
                        }
                    }
                }
                estrutura.addUsers(this.users);
            }
        } catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }
    }

    /**
     * Função responsáve por fazer o parse dos Users
     * @param fileName    Caminho para o ficheiro
     * @param estrutura   Estrutura a carregar
     */
    public void parseTags(String fileName, struct estrutura) {
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


