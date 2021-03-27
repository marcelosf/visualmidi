package proj.musicxml.score;

import proj.musicxml.identity.Identification;
import proj.util.XMLReader;
import java.util.ArrayList;
import java.util.List;
import org.w3c.dom.Element;

public class ScorePartwise
{
  
  private Work work;
  private String movementNumber;
  private String movementTitle;
  private Identification identification;
  private PartList partList;
  private ArrayList<Part> parts;
  
  
  public ScorePartwise(Element e)
  {
    Element eWork = XMLReader.element(e, "work");
    if (eWork != null)
      work = new Work(eWork);
    movementNumber = XMLReader.elementText(e, "movement-number");
    movementTitle = XMLReader.elementText(e, "movement-title");
    Element eIdentification = XMLReader.element(e, "identification");
    if (eIdentification != null)
      identification = new Identification(eIdentification);
    partList = new PartList(XMLReader.element(e, "part-list"));
    List<Element> eParts = XMLReader.elements(e, "part");
    parts = new ArrayList<Part>();
    for (Element ePart : eParts)
    {
      parts.add(new Part(ePart));
    }
  }

  public String getMovementNumber()
  {
    return movementNumber;
  }

  public String getMovementTitle()
  {
    return movementTitle;
  }

  
  public Identification getIdentification()
  {
    return identification;
  }

  
  public PartList getPartList()
  {
    return partList;
  }

  
  public List<Part> getParts()
  {
    return parts;
  }

  
  public Work getWork()
  {
    return work;
  }
}
