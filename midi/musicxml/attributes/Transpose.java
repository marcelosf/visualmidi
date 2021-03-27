package proj.musicxml.attributes;

import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Transpose
{
  private int chromatic;
  private Integer octaveChange;
  
  public Transpose(Element e)
  {
    chromatic = Parser.parseInt(XMLReader.elementText(e, "chromatic"));
    octaveChange = Parser.parseIntegerNull(XMLReader.elementText(e, "octave-change"));
  }

  
  public int getChromatic()
  {
    return chromatic;
  }
  
  public Integer getOctaveChange()
  {
    return octaveChange;
  }

}