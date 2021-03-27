package proj.musicxml.note;

import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Pitch
  implements NotePitchType
{
  
  private char step;
  private Float alter;
  private int octave;
  
  
  public Pitch(Element e)
  {
    step = XMLReader.elementText(e, "step").charAt(0);
    Element eAlter = XMLReader.element(e, "alter");
    if (eAlter != null)
      alter = Parser.parseFloatNull(XMLReader.text(eAlter));
    octave = Parser.parseInt(XMLReader.elementText(e, "octave"));
  }
  
  
  public char getStep()
  {
    return step;
  }

  
  public Float getAlter()
  {
    return alter;
  }

  
  public int getOctave()
  {
    return octave;
  }

}
