package proj.musicxml.identity;

import proj.util.XMLReader;
import org.w3c.dom.Element;


public class Encoder
{
  
  private String value;
  private String type;
  
  
  public Encoder(Element e)
  {
    value = XMLReader.textTrim(e);
    type = XMLReader.attribute(e, "type");
  }


  public String getValue()
  {
    return value;
  }

  public String getType()
  {
    return type;
  }
  

}
