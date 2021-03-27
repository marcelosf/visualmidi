package proj.util;

import java.io.*;
import java.util.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.*;

public class XMLReader
{
  public static Document LerArquivo(String uri)    throws ParserConfigurationException, SAXException, IOException
  {
    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
    DocumentBuilder builder = factory.newDocumentBuilder();
    builder.setEntityResolver(new NoResolver());
    return builder.parse(uri);
  }
 
  public static Element root(Document doc)
  {
    return doc.getDocumentElement();
  }
 
  public static String text(Element element)
  {
    if (element == null)
      return "";
    else
      return element.getTextContent();
  }
 
  public static String textTrim(Element element)
  {
    if (element == null)
      return "";
    else
      return element.getTextContent().trim();
  }

  public static String attribute(Element element, String name)
  {
    if (element == null) return null;
    NamedNodeMap attributes = element.getAttributes();
    if (attributes == null) return null;
    Node value = attributes.getNamedItem(name);
    if (value == null) return null;
    return value.getTextContent();
  }
 
  public static String attributeNotNull(Element element, String name)
  {
    String ret = attribute(element, name);
    if (ret == null)
      ret = "";
    return ret;
  }
  
  public static Element element(Node parent, String name)
  {
    NodeList children = parent.getChildNodes();
    for (int i = 0; i < children.getLength(); i++)
    {
      if (children.item(i).getNodeName().equals(name))
        return (Element) children.item(i);
    }
    return null;
  }
 
  public static List<Element> elements(Node parent, String name)
  {
    ArrayList<Element> ret = new ArrayList<Element>();
    NodeList children = parent.getChildNodes();
    for (int i = 0; i < children.getLength(); i++)
    {
      if (children.item(i).getNodeName().equals(name))
        ret.add((Element) children.item(i));
    }
    return ret;
  }
 
  public static List<Element> elements(Node parent)
  {
    ArrayList<Element> ret = new ArrayList<Element>();
    NodeList children = parent.getChildNodes();
    for (int i = 0; i < children.getLength(); i++)
    {
      if (children.item(i) instanceof Element)
        ret.add((Element) children.item(i));
    }
    return ret;
  }
 
  public static String elementText(Element parentElement, String elementName)
  {
    return text(element(parentElement, elementName));
  }

}