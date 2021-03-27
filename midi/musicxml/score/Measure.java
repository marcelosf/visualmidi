package proj.musicxml.score;

import proj.MusicDataElement;
import proj.musicxml.attributes.Attributes;
import proj.musicxml.direction.Direction;
import proj.musicxml.direction.Sound;
import proj.musicxml.note.*;
import proj.util.XMLReader;
import java.util.ArrayList;
import java.util.List;
import org.w3c.dom.Element;

public class Measure
{
  
  private String id;
  private ArrayList<MusicDataElement> musicDataElements;
  
  
  public Measure(Element e)
  {
    id = XMLReader.attribute(e, "id");
    musicDataElements = new ArrayList<MusicDataElement>();
    List<Element> eElements = XMLReader.elements(e);
    for (Element eElement : eElements)
    {
      String name = eElement.getNodeName();
      //note
      if (name.equals("note"))
        musicDataElements.add(new Note(eElement));
      //backup
      else if (name.equals("backup"))
        musicDataElements.add(new Backup(eElement));
      //forward
      else if (name.equals("forward"))
        musicDataElements.add(new Forward(eElement));
      //direction
      else if (name.equals("direction"))
        musicDataElements.add(new Direction(eElement));
      //attributes
      else if (name.equals("attributes"))
        musicDataElements.add(new Attributes(eElement));
      //sound
      else if (name.equals("sound"))
        musicDataElements.add(new Sound(eElement));
    }
  }
  
  public String getId()
  {
    return id;
  }

  
  public List<MusicDataElement> getMusicDataElements()
  {
    return musicDataElements;
  }

}
