package proj.musicxml.identity;

import proj.util.Parser;
import proj.util.XMLReader;
import java.util.*;
import org.w3c.dom.Element;

public class Encoding
{
  
  private Date encodingDate;
  private ArrayList<Encoder> encoders;
  private String software;
  private ArrayList<String> encodingDescriptions;
  
  
  public Encoding(Element e)
  {
    //encoding-date
    Element eEncodingDate = XMLReader.element(e, "encoding-date");
    String sEncodingDate = XMLReader.textTrim(eEncodingDate);
    encodingDate = Parser.parseDate(sEncodingDate, "yyyy-MM-dd");
    //encoders
    encoders = new ArrayList<Encoder>();
    List<Element> eEncoders = XMLReader.elements(e, "encoder");
    for (Element eEncoder : eEncoders)
    {
      encoders.add(new Encoder(eEncoder));
    }
    //software
    Element eSoftware = XMLReader.element(e, "software");
    software = XMLReader.textTrim(eSoftware);
    //encoding-description
    encodingDescriptions = new ArrayList<String>();
    List<Element> eEncodingDescs = XMLReader.elements(e, "encoding-description");
    for (Element eEncodingDesc : eEncodingDescs)
    {
      encodingDescriptions.add(XMLReader.textTrim(eEncodingDesc));
    }
  }


  public List<Encoder> getEncoders()
  {
    return encoders;
  }


  
  public Date getEncodingDate()
  {
    return encodingDate;
  }


  public List<String> getEncodingDescriptions()
  {
    return encodingDescriptions;
  }

  public String getSoftware()
  {
    return software;
  }

  
}
