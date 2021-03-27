package proj.musicxml.direction;

import proj.MusicDataElement;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Direction
  implements MusicDataElement
{
  
  private Sound sound;
  
  
  public Direction(Element e)
  {
    Element eSound = XMLReader.element(e, "sound");
    if (eSound != null)
      sound = new Sound(eSound);
  }


  public Sound getSound()
  {
    return sound;
  }
}
