package proj.musicxml.score;

import proj.util.XMLReader;
import java.util.ArrayList;
import java.util.List;
import org.w3c.dom.Element;

public class Part
{
  
  private String id;
  private ArrayList<Measure> measures;
  
  
  public Part(Element e)
  {
    id = XMLReader.attribute(e, "id");
    measures = new ArrayList<Measure>();
    List<Element> eMeasures = XMLReader.elements(e, "measure");
    for (Element eMeasure : eMeasures)
    {
      measures.add(new Measure(eMeasure));
    }
  }
  
  
  public String getID()
  {
    return id;
  }
  
  public List<Measure> getMeasures()
  {
    return measures;
  }
  

}
