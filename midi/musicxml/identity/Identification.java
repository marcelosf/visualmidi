package proj.musicxml.identity;

import proj.util.XMLReader;
import java.util.*;
import org.w3c.dom.Element;

public class Identification
{
  
  private ArrayList<Creator> creators;
  private ArrayList<Rights> rights;
  private Encoding encoding;
  
  
  public Identification(Element e)
  {
    //creators
    creators = new ArrayList<Creator>();
    List<Element> eCreators = XMLReader.elements(e, "creator");
    for (Element eCreator : eCreators)
    {
      creators.add(new Creator(eCreator));
    }
    //rights
    rights = new ArrayList<Rights>();
    List<Element> eRights = XMLReader.elements(e, "rights");
    for (Element eRight : eRights)
    {
      rights.add(new Rights(eRight));
    }
    //software
    Element eEncoding = XMLReader.element(e, "encoding");
    if (eEncoding != null)
    {
      encoding = new Encoding(eEncoding);
    }
  }


  public List<Creator> getCreators()
  {
    return creators;
  }

  public Encoding getEncoding()
  {
    return encoding;
  }

  public List<Rights> getRights()
  {
    return rights;
  }


  
}
