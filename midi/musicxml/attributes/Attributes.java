package proj.musicxml.attributes;

import proj.MusicDataElement;
import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Attributes  implements MusicDataElement
{
  private Integer divisions;
  private Transpose transpose;
  
  public Attributes(Element e)
  {
    divisions = Parser.parseIntegerNull(XMLReader.elementText(e, "divisions"));
    Element eTranspose = XMLReader.element(e, "transpose");
    if (eTranspose != null)
      transpose = new Transpose(eTranspose);
  }
  
  public Integer getDivisions()
  {
    return divisions;
  }

  public void setDivisions(Integer divisions)
  {
    this.divisions = divisions;
  }
  
  public Transpose getTranspose()
  {
    return transpose;
  }
  
}
