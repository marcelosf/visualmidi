package proj.musicxml.note;

import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Duration
{
  
  private int value;
  
  
  public Duration(Element e)
  {
    value = Parser.parseInt(XMLReader.textTrim(e));
  }
  
  
  public Duration(int value)
  {
    this.value = value;
  }

  public int getValue()
  {
    return value;
  }
 
}
