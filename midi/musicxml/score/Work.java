package proj.musicxml.score;

import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Work
{
  
  private String workNumber;
  private String workTitle;
  
  
  public Work(Element e)
  {
    workNumber = XMLReader.elementText(e, "work-number");
    workTitle = XMLReader.elementText(e, "work-title");
  }
 
  public String getWorkNumber()
  {
    return workNumber;
  }
 
  public String getWorkTitle()
  {
    return workTitle;
  }
  
}
