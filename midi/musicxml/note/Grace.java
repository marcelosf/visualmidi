package proj.musicxml.note;

import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Grace
{
  
  private Float stealTimePrevious;
  private Float stealTimeFollowing;
  private Float makeTime;
  
  
  public Grace(Element e)
  {
    stealTimePrevious = Parser.parseFloatNull(
      XMLReader.attribute(e, "steal-time-previous"));
    stealTimeFollowing = Parser.parseFloatNull(
      XMLReader.attribute(e, "steal-time-following"));
    makeTime = Parser.parseFloatNull(
      XMLReader.attribute(e, "make-time"));
  }
  
  
  public Float getStealTimePrevious()
  {
    return stealTimePrevious;
  }
  
  
  public Float getStealTimeFollowing()
  {
    return stealTimeFollowing;
  }


  public Float getMakeTime()
  {
    return makeTime;
  }


}
