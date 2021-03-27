package proj.musicxml.note;

import proj.MusicDataElement;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Forward
  implements MusicDataElement
{
  
  private Duration duration;
  
  
  public Forward(Element e)
  {
    duration = new Duration(XMLReader.element(e, "duration"));
  }


  public Duration getDuration()
  {
    return duration;
  }
  
  public void setDuration(Duration duration)
  {
    this.duration = duration;
  }

}
