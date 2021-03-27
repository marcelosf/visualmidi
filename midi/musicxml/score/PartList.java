package proj.musicxml.score;

import proj.util.XMLReader;
import java.util.*;
import org.w3c.dom.Element;

public class PartList
{
  private ArrayList<ScorePart> scoreParts;
  
  
  public PartList(Element e)
  {
    scoreParts = new ArrayList<ScorePart>();
    List<Element> eScoreParts = XMLReader.elements(e, "score-part");
    for (Element eScorePart : eScoreParts)
    {
      scoreParts.add(new ScorePart(eScorePart));
    }
  }
  
  public List<ScorePart> getScoreParts()
  {
    return scoreParts;
  }

}
