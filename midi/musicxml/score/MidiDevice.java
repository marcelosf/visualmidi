package proj.musicxml.score;

import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class MidiDevice
{
  
  private String value;
  private Integer port;
  
  public MidiDevice(Element e)
  {
    value = XMLReader.textTrim(e);
    String attr = XMLReader.attribute(e, "port");
    if (attr != null)
      port = Parser.parseInt(attr);
  }


  public String getValue()
  {
    return value;
  }

  public Integer getPort()
  {
    return port;
  }
  

}
